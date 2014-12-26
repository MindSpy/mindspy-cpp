#ifndef MINDSPY_H
#define MINDSPY_H

#include "MatchingStream.hpp"
#include "Sensor.hpp"

namespace mindspy
{

class MindSpy : public sensor::Sensor
{
public:

    MindSpy();
    MindSpy(MatchingStream& stream);
    virtual ~MindSpy();

    bool getSamples(uint32_t module, protobufs::Sample*);
    bool getState(uint32_t *, uint32_t, protobufs::State*);
    bool setState(uint32_t, protobufs::State *, void *);
    bool getModelName(char*);
    bool operator !();

private:

    MatchingStream* stream = nullptr;
    //std::vector<Sensor*> sensor;
};

} // namespace

#endif // MINDSPY_H
