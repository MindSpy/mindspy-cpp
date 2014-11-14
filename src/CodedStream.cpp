#include "CodedStream.hpp"

namespace mindspy
{

CodedStream::CodedStream(std::istream *in, std::ostream *out)
{
    rawInput = new IstreamInputStream(in);
    rawOutput = new OstreamOutputStream(out);
    startThreads();
}

CodedStream::CodedStream(int ifd, int ofd)
{
    rawInput = new FileInputStream(ifd);
    rawOutput = new FileOutputStream(ofd);
    startThreads();
}

CodedStream::~CodedStream() {
    delete rawInput;
    delete rawOutput;
}


void CodedStream::startThreads()
{

}

bool CodedStream::get(MessageLite &)
{
    // TODO put object to output synchronized queue
}

bool CodedStream::put(const MessageLite &)
{
    // TODO get from input synchronized queue
}

// call in input thread
bool CodedStream::readDelimitedFrom(MessageLite& message) {
    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    CodedInputStream input(rawInput);

    // Read the size.
    uint32_t size;
    if (!input.ReadVarint32(&size))
        return false;

    // Tell the stream not to read beyond that size.
    CodedInputStream::Limit limit = input.PushLimit(size);

    // Parse the message.
    if (!message.MergeFromCodedStream(&input))
        return false;
    if (!input.ConsumedEntireMessage())
        return false;

    // Release the limit.
    input.PopLimit(limit);

    return true;
}

// call in output thread
bool CodedStream::writeDelimitedTo(const MessageLite& message) {
    // We create a new coded stream for each message.  Don't worry, this is fast.
    CodedOutputStream output(rawOutput);

    // Write the size.
    const uint32_t size = message.ByteSize();
    output.WriteVarint32(size);
    if (output.HadError())
        return false;

    message.SerializeToCodedStream(&output);
    if (output.HadError())
        return false;

    return true;
}

}
