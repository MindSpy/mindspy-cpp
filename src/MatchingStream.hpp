#ifndef MATCHINGSTREAM_HPP
#define MATCHINGSTREAM_HPP

#include <iostream>
#include "Proto.hpp"

using namespace google::protobuf::io;

namespace MindSpy
{

class MatchingStream
{
public:

    MatchingStream(std::istream &in, std::ostream &out);

};

} // namespace

#endif // MATCHINGSTREAM_HPP
