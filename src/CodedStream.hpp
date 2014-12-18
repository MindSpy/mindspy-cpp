#ifndef CODEDSTREAM_HPP
#define CODEDSTREAM_HPP

#include <inttypes.h>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/message.h>

namespace mindspy
{

using namespace google::protobuf;
using namespace google::protobuf::io;


/*!
 * The class for conversions between objects and serialized messages
 */
class CodedStream
{
public:

    virtual ~CodedStream();

    virtual bool get(Message&) = 0;
    virtual bool put(const Message&) = 0;

protected:

    bool readDelimitedFrom(Message&, ZeroCopyInputStream&);
    bool writeDelimitedTo(const Message&, ZeroCopyOutputStream&);

};

} // namespace

#endif // CODEDSTREAM_HPP
