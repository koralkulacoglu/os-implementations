#include <cassert>
#include <cstdio>

#include "linked_list.hpp"
#include "linked_list_v2.hpp"

void test_basic() {
    LinkedList<int> ll;
    ll.push(1);
    assert(ll.pop() == 1);

    ll.push(1);
    ll.push(2);
    assert(ll.pop() == 2);
    assert(ll.pop() == 1);
}

void test_v2() {
    LinkedListv2<int> ll;
    ll.push(1);
    assert(ll.pop() == 1);

    ll.push(1);
    ll.push(2);
    assert(ll.pop() == 2);
    assert(ll.pop() == 1);
}

int main() {
    test_basic();
    test_v2();
    std::puts("all tests passed!");
}
