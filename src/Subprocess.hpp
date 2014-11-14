#ifndef SUBPROCESS_HPP
#define SUBPROCESS_HPP

#include <iostream>
#include <cstdio>

#define PARENT_WRITE_PIPE  0
#define PARENT_READ_PIPE   1

#define READ_FD  0
#define WRITE_FD 1

#define PARENT_READ_FD  ( pipes[PARENT_READ_PIPE][READ_FD]   )
#define PARENT_WRITE_FD ( pipes[PARENT_WRITE_PIPE][WRITE_FD] )

#define CHILD_READ_FD   ( pipes[PARENT_WRITE_PIPE][READ_FD]  )
#define CHILD_WRITE_FD  ( pipes[PARENT_READ_PIPE][WRITE_FD]  )

namespace mindspy
{
namespace util
{

class Subprocess
{
public:

    Subprocess(const char* fn, char*const* args);
    Subprocess(const char* fn);

    ~Subprocess();

    int ifd();
    int ofd();
    void sync();
    pid_t pid();

private:

    pid_t pcreate(const char* fn, char*const*);
    void setStreams();

    int fds[2];
    pid_t _pid;

};

}
} // namespace

#endif // SUBPROCESS_HPP
