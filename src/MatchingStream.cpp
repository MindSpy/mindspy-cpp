#include "MatchingStream.hpp"

namespace  mindspy
{

MatchingStream::MatchingStream(Stream &s) : stream(s)
{
}

MatchingStream::~MatchingStream()
{
}

bool MatchingStream::get(MessageLite& message)
{

}

bool MatchingStream::put(const MessageLite& message)
{

}

} // namespace
