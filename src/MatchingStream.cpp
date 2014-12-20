#include "MatchingStream.hpp"

#include "Proto.hpp"

namespace  mindspy
{

using namespace mindspy::protobufs;

MatchingStream::MatchingStream(CodedStream* s) : stream(s)
{
}

MatchingStream::~MatchingStream()
{
}

bool MatchingStream::get(Response& message, const uint32_t reqid)
{
    bool result;

    // TODO
    // * check key-value structure and return result if present
    // * .,...

    while (true)
    {
        result = stream->get(message);
        if (message.reqid() == requid)
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
    while (message.reqid() != reqid);

    return result;
}

bool MatchingStream::get(Response& message, const Request& req)
{
    return get(message, req.reqid());
}

bool MatchingStream::put(const Request& message)
{
    return stream->put(message);
}

} // namespace
