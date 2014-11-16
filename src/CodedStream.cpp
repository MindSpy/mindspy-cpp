#include "CodedStream.hpp"

namespace mindspy
{

CodedStream::CodedStream(std::istream *in, std::ostream *out)
{
    rawInput = new google::protobuf::io::IstreamInputStream(in);
    rawOutput = new google::protobuf::io::OstreamOutputStream(out);
    //initialize threads
    iqueue = new Queue<google::protobuf::MessageLite>();
    oqueue = new Queue<google::protobuf::MessageLite>();
    startThreads();
}

CodedStream::CodedStream(int ifd, int ofd)
{
    rawInput = new google::protobuf::io::FileInputStream(ifd);
    rawOutput = new google::protobuf::io::FileOutputStream(ofd);
    //initialize threads
    iqueue = new Queue<google::protobuf::MessageLite>();
    oqueue = new Queue<google::protobuf::MessageLite>();
    startThreads();
}

CodedStream::~CodedStream() {
    delete rawInput;
    delete rawOutput;
    delete iqueue;
    delete oqueue;
}


void CodedStream::startThreads()
{

}

bool CodedStream::get(google::protobuf::MessageLite &)
{
    // TODO put object to output synchronized queue
}

bool CodedStream::put(const google::protobuf::MessageLite &)
{
    // TODO get from input synchronized queue
}

// call in input thread
bool CodedStream::readDelimitedFrom(google::protobuf::MessageLite& message) {
    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    google::protobuf::io::CodedInputStream input(rawInput);

    // Read the size.
    uint32_t size;
    if (!input.ReadVarint32(&size))
        return false;

    // Tell the stream not to read beyond that size.
    google::protobuf::io::CodedInputStream::Limit limit = input.PushLimit(size);

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
bool CodedStream::writeDelimitedTo(const google::protobuf::MessageLite& message) {
    // We create a new coded stream for each message.  Don't worry, this is fast.
    google::protobuf::io::CodedOutputStream output(rawOutput);

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
