#include "MatchingStream.hpp"

namespace  mindspy
{

MatchingStream::MatchingStream(Stream* s) : stream(s)
{
}

MatchingStream::~MatchingStream()
{
}

bool MatchingStream::get(Message& message, ::google::protobuf::uint32 reqid)
{
    return stream->get(message);
}

bool MatchingStream::get(Message& message)
{
    throw ;
}

bool MatchingStream::put(const Message& message)
{
    return stream->put(message);
}

} // namespace
