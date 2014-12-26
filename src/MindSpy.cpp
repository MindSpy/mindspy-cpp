#include "MindSpy.hpp"

namespace mindspy
{

MindSpy::MindSpy() : stream(nullptr)
{

}

MindSpy::MindSpy(MatchingStream& s) : stream(s)
{

}

MindSpy::~MindSpy()
{

}

bool MindSpy::getSamples(uint32_t module, protobufs::Sample *)
{

}

bool MindSpy::getState(uint32_t *, uint32_t, protobufs::State *)
{

}

bool MindSpy::getState(uint32_t *, uint32_t, protobufs::State *, void*)
{

}

bool MindSpy::getModelName(char *)
{

}

} // namespace
