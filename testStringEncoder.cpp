#include "StringEncoder.h"

int main() {
    using namespace NStringEncoder;

    constexpr TConstExprString helloWorld {"Hello World!"};
    static_assert(helloWorld.size() == 12, "");
    static_assert(helloWorld[0] == 'H' && helloWorld[11] == '!', "");

    static_assert(sortedBase64Chars.binarySearch(',') == size_t(-1), "");
    static_assert(sortedBase64Chars.binarySearch('A') == 11, "");
    static_assert(sortedBase64Chars.binarySearch('.') == 0, "");
    static_assert(sortedBase64Chars.binarySearch('z') == 63, "");

    return 0;
}
