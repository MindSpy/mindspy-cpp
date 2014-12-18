#include "FileCodedStream.hpp"

namespace mindspy
{

FileCodedStream::~FileCodedStream()
{

}

FileCodedStream::FileCodedStream(int ifd, int ofd) :
    ifd(ifd), ofd(ofd)
{
}

bool FileCodedStream::get(Message& message)
{
    FileInputStream inputStream(ifd);
    return readDelimitedFrom(message, inputStream);
}

bool FileCodedStream::put(const Message& message)
{
    FileOutputStream outputStream(ofd);
    return writeDelimitedTo(message, outputStream);
}

}
