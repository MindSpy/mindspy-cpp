#ifndef CODEDSTREAM_HPP
#define CODEDSTREAM_HPP

#include <istream>
#include <memory>
#include <thread>

#include "Stream.hpp"
#include "FifoQueue.hpp"
#include "ObjectPool.hpp"

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/message.h>

namespace mindspy
{

using namespace mindspy::util;
using namespace google::protobuf;
using namespace google::protobuf::io;


/*!
 * The class for nonblocking read and write.
 */
class CodedStream : public Stream
{
public:

    /*!
     * \brief Constructor. Parametres set output and input stream.
     * \param in - input stream.
     * \param out - output stream.
     */
    CodedStream(std::istream &in, std::ostream &out);

    /*!
     * \brief Constructor. Parameters set value descriptor.
     * \param ifd - input file destcriptor.
     * \param ofd - outpus file destriptor.
     */
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
    void inputTask();
    void outputTask();

    bool readDelimitedFrom(Message &);
    bool writeDelimitedTo(const Message &);

    //mindspy::util::ObjectPool<Message*> obj;
};

} // namespace

#endif // CODEDSTREAM_HPP
