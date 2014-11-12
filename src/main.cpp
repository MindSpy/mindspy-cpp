
#include "Subprocess.hpp"

#include "CodedStream.hpp"
#include "Subprocess.hpp"
#include "MatchingStream.hpp"
#include "Proto.hpp"

namespace mindspy {
namespace test {

using namespace google::protobuf;
using namespace protobufs;

int main() {
    Subprocess sub("../firmware/test/server");
    CodedStream cs(sub.ifd(), sub.ofd());
    MatchingStream ms(cs);

    Request req;
    Response resp;

    // TODO set request

    ms.put(req);

    ms.get(resp);

    // TODO ..
}

}
}
