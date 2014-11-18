#ifndef CODEDSTREAM_HPP
#define CODEDSTREAM_HPP

#include <istream>
#include <memory>

#include "Stream.hpp"
#include "Queue.hpp"

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/message.h>

namespace mindspy
{

using namespace mindspy::util;
using namespace google::protobuf;
using namespace google::protobuf::io;


/*
 * Class for nonblocking read and write.
 */
class CodedStream : public Stream
{
public:

    // Stream
    CodedStream(std::istream *in, std::ostream *out);
    CodedStream(int ifd, int ofd);

    virtual ~CodedStream();

    bool get(Message &);
    bool put(const Message &);

private:

    ZeroCopyInputStream *rawStreamInput;
    ZeroCopyOutputStream *rawStreamOutput;

    Queue<Message*> *inputQueue;
    Queue<Message*> *outputQueue;

    bool readDelimitedFrom(Message &);
    bool writeDelimitedTo(const Message &);

    // TODO threads
    void startThreads();
};

} // namespace

#endif // CODEDSTREAM_HPP
