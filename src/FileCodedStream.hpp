#ifndef FILECODEDSTREAM_HPP
#define FILECODEDSTREAM_HPP

#include <istream>
#include <iostream>
#include <inttypes.h>

#include "CodedStream.hpp"

#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/message.h>

namespace mindspy
{

using namespace google::protobuf;
using namespace google::protobuf::io;


/*!
 * The class for nonblocking read and write.
 */
class FileCodedStream : public CodedStream
{
public:
    /*!
     * \brief Constructor. Parameters set value descriptor.
     * \param ifd - input file destcriptor.
     * \param ofd - outpus file destriptor.
     */
    FileCodedStream(int ifd, int ofd);

    bool get(Message&);
    bool put(const Message&);

private:
    int ifd;
    int ofd;
};

} // namespace

#endif // FILECODEDSTREAM_HPP
