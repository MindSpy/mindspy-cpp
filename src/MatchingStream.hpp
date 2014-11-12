#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include <iostream>
#include <istream>
#include <ostream>

#include "Stream.hpp"
#include "CodedStream.hpp"

#include <google/protobuf/message.h>

namespace mindspy
{

using namespace google::protobuf;

class MatchingStream : public Stream
{
public:

    MatchingStream(CodedStream&);
    ~MatchingStream();

    // put to output queue
    bool get(MessageLite&);

    // get from input queue
    bool put(const MessageLite&);

private:
    CodedStream* stream;
};

} // namespace

#endif // MATCHINGSTREAM_HPP
