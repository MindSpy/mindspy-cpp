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

    MatchingStream(Stream& stream);

    ~MatchingStream();

    // Put to output queue
    bool get(google::protobuf::MessageLite& message);

    // Get from input queue
    bool put(const google::protobuf::MessageLite& message);

private:

    CodedStream* stream;
};

} // namespace

#endif // MATCHINGSTREAM_HPP
