#include "MatchingStream.hpp"

#include "Proto.hpp"

namespace  mindspy
{

MatchingStream::MatchingStream(CodedStream* s) : stream(s)
{
}

MatchingStream::~MatchingStream()
{
}

bool MatchingStream::get(protobufs::Response& message, const uint32_t reqid)
{
    bool result = false;

    // TODO
    // * check key-value structure and return result if present
    // * .,...
    // message.CopyFrom(storedMessage);

    while (true)
    {
        result = stream->get(message);
        if (message.reqid() == reqid)
        {
            break;
        }
        else
        {
            // TODO
            // * store in key-value structure
            // * prune old records based on timestamp
            // * involve object pool to control creation of the objects
        }
    }

    return result;
}

bool MatchingStream::get(protobufs::Response& message, const protobufs::Request& req)
{
    return get(message, req.reqid());
}

bool MatchingStream::put(const protobufs::Request& message)
{
    return stream->put(message);
}

} // namespace
