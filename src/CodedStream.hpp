#ifndef CODEDSTREAM_HPP
#define CODEDSTREAM_HPP

#include <istream>
#include <iostream>
#include <inttypes.h>

#include "Stream.hpp"

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/message.h>

namespace mindspy
{

using namespace google::protobuf;
using namespace google::protobuf::io;


/*!
 * The class for nonblocking read and write.
 */
class CodedStream : public Stream
{
public:
    virtual ~CodedStream();

    bool get(Message&, uint32_t);

    virtual bool get(Message&) = 0;
    virtual bool put(const Message&) = 0;

protected:
    bool readDelimitedFrom(Message&, ZeroCopyInputStream&);
    bool writeDelimitedTo(const Message&, ZeroCopyOutputStream&);

};

} // namespace

#endif // CODEDSTREAM_HPP
