
#include "Subprocess.hpp"

#include "CodedStream.hpp"
#include "Subprocess.hpp"
#include "MatchingStream.hpp"
#include "Proto.hpp"
#include "Queue.hpp"

using namespace google::protobuf;
using namespace mindspy::protobufs;
using namespace mindspy::util;
using namespace mindspy;

int main(int argc, char * argv[]) {
    Subprocess sub("../firmware/test/server");
    CodedStream cs(sub.ifd(), sub.ofd());
    MatchingStream ms(cs);

    Request req;
    Response resp;

    // TODO set request

    ms.put(req);

    ms.get(resp);

    mindspy::util::Queue<int> i;
    // TODO ..

    return 0;
}
