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

    bool get(google::protobuf::MessageLite& message);
    bool put(const google::protobuf::MessageLite& message);

private:

    google::protobuf::io::ZeroCopyInputStream *rawStreamInput;
    google::protobuf::io::ZeroCopyOutputStream *rawStreamOutput;

    util::Queue<google::protobuf::MessageLite*> *inputQueue;
    util::Queue<google::protobuf::MessageLite*> *outputQueue;

    bool readDelimitedFrom(google::protobuf::MessageLite& message);
    bool writeDelimitedTo(const google::protobuf::MessageLite& message);

    // TODO threads
    void startThreads();
};

} // namespace

#endif // CODEDSTREAM_HPP
