#include <cassert>
#include <cstdio>

#include "spsc.hpp"

void test_basic() {
    SPSCRingBuffer<int, 8> buffer;

    assert(buffer.isEmpty());

    buffer.push(1);
    buffer.push(2);
    buffer.push(3);

    int val;
    buffer.pop(val);
    assert(val == 1);

    buffer.pop(val);
    assert(val == 2);
}

int main() {
    test_basic();
    std::puts("all tests passed!");
}
