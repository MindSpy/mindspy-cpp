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

// call in input thread
bool CodedStream::readDelimitedFrom(Message& message) {
    ZeroCopyInputStream* zero;
    if (is != NULL) zero = new IstreamInputStream(is);
    else zero = new FileInputStream(ifd);
    {
        // We create a new coded stream for each message.  Don't worry, this is fast,
        // and it makes sure the 64MB total size limit is imposed per-message rather
        // than on the whole stream.  (See the CodedInputStream interface for more
        // info on this limit.)
        CodedInputStream input(zero);

        // Read the size.
        uint32_t size = 0;
        if (!input.ReadVarint32(&size))
            return false;

        // Tell the stream not to read beyond that size.
        CodedInputStream::Limit limit = input.PushLimit(size);

        // Parse the message.
        if (!message.ParseFromCodedStream(&input))
            return false;
        if (!input.ConsumedEntireMessage())
            return false;

        // Release the limit.
        input.PopLimit(limit);
    }
    delete zero;
    return true;
}

// call in output thread
bool CodedStream::writeDelimitedTo(const Message& message) {
    // We create a new coded stream for each message.  Don't worry, this is fast.
    ZeroCopyOutputStream* zero;
    if (os != NULL) zero = new OstreamOutputStream(os);
    else zero = new FileOutputStream(ofd);
    {
        //OstreamOutputStream zero(os);
        CodedOutputStream output(zero);

        // Write the size.
        const uint32_t size = message.ByteSize();
        output.WriteVarint32(size);
        if (output.HadError())
            return false;

        message.SerializeToCodedStream(&output);
        if (output.HadError())
            return false;
    }
    delete zero;
    return true;

}

}
