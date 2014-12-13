#ifndef STREAM_HPP
#define STREAM_HPP

#include <google/protobuf/message.h>

namespace mindspy
{

using namespace google::protobuf;

// Abstract class for stream.

class Stream
{
public:

    /*!
     * Put message to the stream.
     */
    virtual bool get(Message& ) = 0;

    /*!
     * Put message to the stream.
     */
    virtual bool get(Message&, ::google::protobuf::uint32) = 0;

    /*!
     * Get message from stream.
     */
    virtual bool put(const Message&) = 0;

};

} // namespace

#endif // STREAM_HPP
