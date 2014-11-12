#ifndef STREAM_HPP
#define STREAM_HPP

#include <google/protobuf/message.h>

namespace mindspy
{

using namespace google::protobuf;

class Stream
{
public:
    virtual ~Stream()
    {
    }

    // put message to the stream
    virtual bool get(MessageLite&) = 0;

    // get message from stream
    virtual bool put(const MessageLite&) = 0;

};

}

#endif // STREAM_HPP
