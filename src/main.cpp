
#include "Subprocess.hpp"

#include "CodedStream.hpp"
#include "Subprocess.hpp"
#include "MatchingStream.hpp"
#include "Proto.hpp"
#include "Queue.hpp"
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

using namespace google::protobuf;
using namespace mindspy::protobufs;
using namespace mindspy::util;
using namespace mindspy;


unsigned long micros()
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return tp.tv_sec * 1000000 + tp.tv_usec;
}

uint64_t timestamp()
{
    return micros();
}

uint64_t reqid()
{
    return rand();
}

int main(int argc, char * argv[])
{
    Subprocess sub("../firmware/test/server");

    {
        CodedStream cs(sub.ifd(), sub.ofd());
        MatchingStream ms(&cs);

        Request req;
        Response resp;

        req.Clear();
        req.set_timestamp(timestamp());
        req.set_reqid(reqid());

        std::cout << "Request { " << req.ShortDebugString() << " }"  << std::endl;

        ms.put(req);

        ms.get(resp, req.reqid());

        std::cout << "Response { " << resp.ShortDebugString() << " }" << std::endl;
    }
    return 0;
}
