#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include <inttypes.h>
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
    bool get(Message&, uint32_t);

    // Get from input queue
    bool put(const Message& message);

private:

    Stream* stream;
};

} // namespace

#endif // MATCHINGSTREAM_HPP
