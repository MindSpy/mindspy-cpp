#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include <iostream>
#include <istream>
#include <ostream>

#include "Proto.hpp"
#include "CodedStream.hpp"

namespace mindspy
{

using namespace google::protobuf;
using namespace google::protobuf::io;

class MatchingStream
{
public:

    MatchingStream(CodedStream&);
    ~MatchingStream();

    // put to output queue
    bool get(const MessageLite&);

    // get from input queue
    bool put(MessageLite&);

private:
    CodedStream* stream;
};

} // namespace

#endif // MATCHINGSTREAM_HPP
