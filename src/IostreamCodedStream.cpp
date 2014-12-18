#include "IostreamCodedStream.hpp"

namespace mindspy
{

IostreamCodedStream::~IostreamCodedStream()
{

}

IostreamCodedStream::IostreamCodedStream(std::istream &in, std::ostream &out) :
    is(&in), os(&out)
{
}

bool IostreamCodedStream::get(Message& message)
{
    IstreamInputStream rawStream(is);
    return readDelimitedFrom(message, rawStream);
}

bool IostreamCodedStream::put(const Message& message)
{
    OstreamOutputStream rawStream(os);
    return writeDelimitedTo(message, rawStream);
}

}
