#ifndef MINDSPY_H
#define MINDSPY_H

#include "Stream.hpp"

namespace mindspy
{

class MindSpy {
public:
    MindSpy(Stream&);

private:
    Stream* stream;
};

} // namespace

#endif // MINDSPY_H
