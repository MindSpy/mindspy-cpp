#include "FileCodedStream.hpp"

namespace mindspy
{

FileCodedStream::FileCodedStream(int ifd, int ofd) :
    ifd(ifd), ofd(ofd)
{
}

bool FileCodedStream::get(Message& message) {
    FileInputStream rawStream(ifd);
    return readDelimitedFrom(message, rawStream);
}

bool FileCodedStream::put(const Message& message) {
    FileOutputStream rawStream(ofd);
    return writeDelimitedTo(message, rawStream);
}

}
