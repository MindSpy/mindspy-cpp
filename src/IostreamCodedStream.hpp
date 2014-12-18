#ifndef IOSTREAMCODEDSTREAM_HPP
#define IOSTREAMCODEDSTREAM_HPP

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
class IostreamCodedStream : public CodedStream
{
public:

    /*!
     * \brief Constructor. Parametres set output and input stream.
     * \param in - input stream.
     * \param out - output stream.
     */
    IostreamCodedStream(std::istream &, std::ostream &);
    virtual IostreamCodedStream();

    bool get(Message&);
    bool put(const Message&);

private:

    std::istream *is;
    std::ostream *os;
};

} // namespace

#endif // IOSTREAMCODEDSTREAM_HPP
