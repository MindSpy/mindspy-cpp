#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include "Stream.hpp"
#include "CodedStream.hpp"

#include <google/protobuf/message.h>

namespace mindspy
{

class MatchingStream : public Stream
{
public:

    MatchingStream(Stream* stream);

    virtual ~MatchingStream();

    // Put to output queue
    bool get(Message&);

    // Put to output queue
    bool get(Message&, ::google::protobuf::uint32);

    // Get from input queue
    bool put(const Message& message);

private:

    Stream* stream;
};

} // namespace

#endif // MATCHINGSTREAM_HPP
