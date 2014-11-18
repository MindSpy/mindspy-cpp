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
    virtual bool get(Message& message) = 0;

    /*!
     * Get message from stream.
     */
    virtual bool put(const Message& message) = 0;

};

} // namespace

#endif // STREAM_HPP
