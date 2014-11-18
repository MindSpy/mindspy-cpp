#ifndef CODEDSTREAM_HPP
#define CODEDSTREAM_HPP

#include <istream>
#include <memory>
#include <thread>

#include "Stream.hpp"
#include "FifoQueue.hpp"

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
//template<class InputMessage, class OutputMessage>
class CodedStream : public Stream
{
public:

    // Stream
    CodedStream(std::istream &in, std::ostream &out);
    CodedStream(int ifd, int ofd);

    virtual ~CodedStream();

    bool get(Message &);
    bool put(const Message &);

private:

    ZeroCopyInputStream *rawStreamInput;
    ZeroCopyOutputStream *rawStreamOutput;

    FifoQueue<Message*> inputQueue;
    FifoQueue<Message*> outputQueue;

    std::thread *inputThread;
    std::thread *outputThread;

    // thread tasks
    static void inputTask(CodedStream *);
    static void outputTask(CodedStream *);

    bool readDelimitedFrom(Message &);
    bool writeDelimitedTo(const Message &);

    inline Message *inputMessageAllocator()
    {
        return NULL; // new InputMessage();
    }

    inline Message *outputMessageAllocator()
    {
        return NULL; //new OutputMessage();
    }
};

} // namespace

#endif // CODEDSTREAM_HPP
