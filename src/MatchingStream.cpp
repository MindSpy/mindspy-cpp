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

    do
    {
        result = stream->get(message);
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
