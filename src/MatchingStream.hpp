#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include <inttypes.h>
#include "CodedStream.hpp"
#include "Proto.hpp"

#include <google/protobuf/message.h>

namespace mindspy
{

class MatchingStream
{
public:

    MatchingStream(CodedStream*);

    virtual ~MatchingStream();

    // Put to output queue
    bool get(protobufs::Response&, const uint32_t);

    // Put to output queue
    bool get(protobufs::Response&, const protobufs::Request&);

    // Get from input queue
    bool put(const protobufs::Request&);

private:

    CodedStream* stream;
};

} // namespace

#endif // MATCHINGSTREAM_HPP
