#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include <iostream>
#include <istream>
#include <ostream>

#include "Proto.hpp"

using namespace google::protobuf;
using namespace google::protobuf::io;

namespace MindSpy
{

class MatchingStream
{
public:

    MatchingStream(std::istream &in, std::ostream &out);
    ~MatchingStream();

    // Read stream
    void MatchingStreamRead(const MessageLite* message, ZeroCopyOutputStream* out);

    // Write stream
    void MatchingStreamWrite(ZeroCopyInputStream* in, MessageLite* message);
};

} // namespace

#endif // MATCHINGSTREAM_HPP
