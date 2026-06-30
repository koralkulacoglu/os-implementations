#pragma once
#include <mutex>
#include <thread>

template <typename T>
class LinkedListv2 {
    struct Node {
        T val;
        Node* next;
        std::mutex mtx;

        Node(T val, Node* next) : val{val}, next{next} {}
    };

    int size{0};
    Node* head;

   public:
    LinkedListv2() : head{new Node(T{}, nullptr)} {}

    void push(T val) {
        Node* prev = head;
        std::unique_lock<std::mutex> prev_lock(prev->mtx);
        Node* cur = prev->next;

        while (cur != nullptr) {
            std::unique_lock<std::mutex> cur_lock(cur->mtx);
            prev_lock.unlock();
            prev = cur;
            prev_lock = std::move(cur_lock);
            cur = cur->next;
        }

        prev->next = new Node(val, nullptr);
        size++;
    }

    T pop() {
        Node* prev = head;
        std::unique_lock<std::mutex> prev_lock(prev->mtx);
        Node* cur = prev->next;

        if (cur == nullptr) return T{};

        while (cur->next != nullptr) {
            std::unique_lock<std::mutex> cur_lock(cur->mtx);
            prev_lock.unlock();
            prev = cur;
            prev_lock = std::move(cur_lock);
            cur = cur->next;
        }

        T res = cur->val;
        prev->next = nullptr;
        delete cur;
        size--;

        return res;
    }

    ~LinkedListv2() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* prev = cur;
            cur = cur->next;
            delete prev;
        }
    }
};
