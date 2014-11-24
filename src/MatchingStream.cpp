#include "MatchingStream.hpp"

namespace  mindspy
{

MatchingStream::MatchingStream(Stream* s) : stream(s)
{
}

MatchingStream::~MatchingStream()
{
}

bool MatchingStream::get(Message& message)
{
    return stream->get(message);
}

bool MatchingStream::put(const Message& message)
{
    return stream->put(message);
}

} // namespace
