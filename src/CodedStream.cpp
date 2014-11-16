#include "CodedStream.hpp"

namespace mindspy
{

CodedStream::CodedStream(std::istream *in, std::ostream *out)
{
    rawStreamInput = new google::protobuf::io::IstreamInputStream(in);
    rawStreamOutput = new google::protobuf::io::OstreamOutputStream(out);

    // Initialize threads

    inputQueue = new util::Queue<google::protobuf::MessageLite*>();
    outputQueue = new util::Queue<google::protobuf::MessageLite*>();

    startThreads();
}

CodedStream::CodedStream(int ifd, int ofd)
{
    rawStreamInput = new google::protobuf::io::FileInputStream(ifd);
    rawStreamOutput = new google::protobuf::io::FileOutputStream(ofd);

    // Initialize threads
    inputQueue = new util::Queue<google::protobuf::MessageLite*>();
    outputQueue = new util::Queue<google::protobuf::MessageLite*>();

    startThreads();
}

CodedStream::~CodedStream() {
    delete rawStreamInput;
    delete rawStreamOutput;
    delete inputQueue;
    delete outputQueue;
}


void CodedStream::startThreads()
{

}

bool CodedStream::get(google::protobuf::MessageLite &message)
{
    // TODO put object to output synchronized queue
}

bool CodedStream::put(const google::protobuf::MessageLite &message)
{
    // TODO get from input synchronized queue
}

// call in input thread
bool CodedStream::readDelimitedFrom(google::protobuf::MessageLite& message) {
    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    google::protobuf::io::CodedInputStream input(rawStreamInput);

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
    google::protobuf::io::CodedOutputStream output(rawStreamOutput);

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
