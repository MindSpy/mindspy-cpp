#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include <inttypes.h>
#include "CodedStream.hpp"
#include "Proto.hpp"

#include <google/protobuf/message.h>

namespace mindspy
{

using namespace mindspy::protobufs;

class MatchingStream
{
public:

    MatchingStream(CodedStream*);

    virtual ~MatchingStream();

    // Put to output queue
    bool get(Response&, const uint32_t);

    // Put to output queue
    bool get(Response&, const Request&);

    // Get from input queue
    bool put(const Request&);

private:

    CodedStream* stream;
};

} // namespace

#endif // MATCHINGSTREAM_HPP
