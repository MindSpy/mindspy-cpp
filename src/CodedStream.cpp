#include "CodedStream.hpp"

namespace mindspy
{

CodedStream::CodedStream(std::istream &in, std::ostream &out) :
    is(&in), os(&out)
{
}

CodedStream::CodedStream(int ifd, int ofd) :
    ifd(ifd), ofd(ofd)
{
}

CodedStream::~CodedStream()
{
}

bool CodedStream::get(Message& message)
{
    return readDelimitedFrom(message);
}

bool CodedStream::get(Message& message, uint32_t reqid)
{
    return get(message);
}

bool CodedStream::put(const Message& message)
{
    return writeDelimitedTo(message);
}


bool CodedStream::readDelimitedFrom(Message& message) {
    ZeroCopyInputStream* rawStream = nullptr;
    if (is != nullptr)
        rawStream = new IstreamInputStream(is);
    else if (ifd != -1)
        rawStream = new FileInputStream(ifd);
    else
        return false;
    bool result =  readDelimitedFrom(message, rawStream);
    delete rawStream;
    return result;
}

bool CodedStream::readDelimitedFrom(Message& message, ZeroCopyInputStream* rawStream) {
    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    CodedInputStream input(rawStream);

    // Read the size.
    uint32_t size = 0;
    if (!input.ReadVarint32(&size))
    {
        return false;
    }

    // Tell the stream not to read beyond that size.
    CodedInputStream::Limit limit = input.PushLimit(size);

    // Parse the message.
    if (!message.ParseFromCodedStream(&input))
    {
        return false;
    }
    if (!input.ConsumedEntireMessage())
    {
        return false;
    }

    // Release the limit.
    input.PopLimit(limit);

    return true;
}


bool CodedStream::writeDelimitedTo(const Message& message) {
    ZeroCopyOutputStream* rawStream = nullptr;
    if (os != nullptr)
    {
        rawStream = new OstreamOutputStream(os);
    }
    else if (ofd != -1)
    {
        rawStream = new FileOutputStream(ofd);
    }
    else
    {
        return false;
    }
    bool result =  writeDelimitedTo(message, rawStream);
    delete rawStream;
    return result;
}

// call in output thread
bool CodedStream::writeDelimitedTo(const Message& message, ZeroCopyOutputStream* rawStream) {
    // We create a new coded stream for each message.  Don't worry, this is fast.
    //OstreamOutputStream zero(os);
    CodedOutputStream output(rawStream);

    // Write the size.
    const uint32_t size = message.ByteSize();
    output.WriteVarint32(size);

    if (output.HadError())
    {
        return false;
    }

    message.SerializeToCodedStream(&output);
    if (output.HadError())
    {
        return false;
    }

    return true;
}

}
