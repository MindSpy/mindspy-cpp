#include "Subprocess.hpp"

#include <cstdlib>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

namespace mindspy {
namespace util {

Subprocess::Subprocess(const char* fn, char*const* args) {
    _pid = pcreate(fn, args);
    setStreams();
}

Subprocess::Subprocess(const char* fn) {
    _pid = pcreate(fn, new char*[1]{NULL});
    setStreams();
}

void Subprocess::setStreams() {
    //fcntl(fds[0], F_SETFL, fcntl(fds[0], F_GETFL) | O_NONBLOCK);
}

Subprocess::~Subprocess() {
    close(fds[0]);
    close(fds[1]);
    kill(_pid, SIGKILL);
}

int Subprocess::ifd() {
    return fds[0];
}

int Subprocess::ofd() {
    return fds[1];
}

void Subprocess::sync() {
    fsync(fds[0]);
    fsync(fds[1]);
}

pid_t Subprocess::pid() {
    return _pid;
}

pid_t Subprocess::pcreate(const char* fn, char*const* args) {
    /* Spawn a process from pfunc, returning it's pid. The fds array passed will
     * be filled with two descriptors: fds[0] will read from the child process,
     * and fds[1] will write to it.
     * Similarly, the child process will receive a reading/writing fd set (in
     * that same order) as arguments.
     */

    pid_t pid;
    int pipes[2][2];

    /* Warning: I'm not handling possible errors in pipe/fork */

    if (pipe(pipes[PARENT_READ_PIPE]) < 0) /* Parent read/child write pipe */
        exit(1); // ERROR

    if (pipe(pipes[PARENT_WRITE_PIPE]) < 0) /* Child read/parent write pipe */
        exit(1); // ERROR

    if ((pid = fork()) > 0) {
        /* Parent process */
        fds[0] = PARENT_READ_FD;
        fds[1] = PARENT_WRITE_FD;

        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);

        return pid;

    } else {
        if (dup2(CHILD_READ_FD, STDIN_FILENO) < 0)
            exit(1); // ERROR

        if ( dup2(CHILD_WRITE_FD, STDOUT_FILENO) < 0)
            exit(1); // ERROR

        close(CHILD_READ_FD);
        close(CHILD_WRITE_FD);
        close(PARENT_READ_FD);
        close(PARENT_WRITE_FD);

        // spawn process
        if (execv( fn, args ) < 0)
            exit(1); // ERROR

        exit(0);
    }

    return -1; /* ? */
}

}
} // namespace
