#ifndef CODEDSTREAM_HPP
#define CODEDSTREAM_HPP

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/message.h>


namespace mindspy
{

using namespace google::protobuf;
using namespace google::protobuf::io;

class CodedStream
{
public:
    // streams
    CodedStream(std::istream &in, std::ostream &out);
    // FD's
    CodedStream(int ifd, int ofd);

    ~CodedStream();

    void get(MessageLite&);
    void put(const MessageLite&);


private:
    ZeroCopyInputStream* rawInput;
    ZeroCopyOutputStream* rawOutput;

    bool readDelimitedFrom(MessageLite&);
    bool writeDelimitedTo(const MessageLite&);

};

}

#endif // CODEDSTREAM_HPP
