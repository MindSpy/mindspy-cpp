#ifndef STREAM_HPP
#define STREAM_HPP

#include <google/protobuf/message.h>

namespace mindspy
{

class Stream
{
public:

    virtual ~Stream() {}

    /*
     * Put message to the stream.
     */
    virtual bool get(google::protobuf::MessageLite& message) = 0;

    /*
     * Get message from stream.
     */
    virtual bool put(const google::protobuf::MessageLite& message) = 0;

};

} // namespace

#endif // STREAM_HPP
