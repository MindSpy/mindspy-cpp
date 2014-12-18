#include "CodedStream.hpp"

namespace mindspy
{

CodedStream::~CodedStream()
{
}

bool CodedStream::get(Message& message, uint32_t reqid)
{
    return get(message);
}

bool CodedStream::readDelimitedFrom(Message& message, ZeroCopyInputStream& rawStream)
{
    // We create a new coded stream for each message.  Don't worry, this is fast,
    // and it makes sure the 64MB total size limit is imposed per-message rather
    // than on the whole stream.  (See the CodedInputStream interface for more
    // info on this limit.)
    CodedInputStream input(&rawStream);

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

bool CodedStream::writeDelimitedTo(const Message& message, ZeroCopyOutputStream& rawStream)
{
    // We create a new coded stream for each message.  Don't worry, this is fast.
    CodedOutputStream output(&rawStream);

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
