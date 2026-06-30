#include <cassert>
#include <cstdio>

#include "linked_list.hpp"

void test_basic() {
    LinkedList<int> ll;
    ll.push(1);
    assert(ll.pop() == 1);

    ll.push(1);
    ll.push(2);
    assert(ll.pop() == 2);
    assert(ll.pop() == 1);
}

int main() {
    test_basic();
    std::puts("all tests passed!");
}
