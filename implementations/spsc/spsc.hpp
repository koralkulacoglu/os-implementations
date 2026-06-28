#pragma once
#include <atomic>
#include <cstddef>

template <typename T, std::size_t N>
class SPSCRingBuffer {
    T buffer[N];
    std::atomic<std::size_t> head{0};
    std::atomic<std::size_t> tail{0};

   public:
    std::size_t size() { return head - tail; }

    bool isFull() { return size() == N; }

    bool isEmpty() { return size() == 0; }

    bool push(T item) {
        if (isFull()) {
            return false;
        }

        buffer[head % N] = item;
        head++;

        return true;
    }

    bool pop(T& out) {
        if (isEmpty()) {
            return false;
        }

        out = buffer[tail % N];
        tail++;

        return true;
    }

    T front() { return buffer[head]; }

    T back() { return buffer[tail]; }
};
