#ifndef CODEDSTREAM_HPP
#define CODEDSTREAM_HPP

#include <istream>

#include "Stream.hpp"

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/message.h>
#include "Queue.hpp"

namespace mindspy
{

using namespace util;

/*
 * Class for nonblocking read and write.
 */
class CodedStream : public Stream
{
public:

    // Stream
    CodedStream(std::istream *in, std::ostream *out);

    // FD's
    CodedStream(int ifd, int ofd);

    ~CodedStream();

    bool get(google::protobuf::MessageLite&);
    bool put(const google::protobuf::MessageLite&);

private:

    google::protobuf::io::ZeroCopyInputStream* rawInput;
    google::protobuf::io::ZeroCopyOutputStream* rawOutput;

    bool readDelimitedFrom(google::protobuf::MessageLite&);
    bool writeDelimitedTo(const google::protobuf::MessageLite&);

    // TODO threads
    void startThreads();

    Queue<google::protobuf::MessageLite>* iqueue;
    Queue<google::protobuf::MessageLite>* oqueue;
};

} // namespace

#endif // CODEDSTREAM_HPP
