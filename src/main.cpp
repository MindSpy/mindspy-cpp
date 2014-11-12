
#include "Subprocess.hpp"

#include "CodedStream.hpp"
#include "Subprocess.hpp"
#include "MatchingStream.hpp"

namespace mindspy {
namespace test {

using namespace google::protobuf;


int main() {
    Subprocess sub("../firmware/test/server");
    CodedStream cs(sub.ifd(), sub.ofd());
    MatchingStream ms(cs);
    // TODO ..
}

}
}
