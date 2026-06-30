#pragma once
#include <mutex>

template <typename T>
class LinkedList {
    struct Node {
        T val;
        Node* next;
        std::mutex mtx;

        Node(T val, Node* next) : val{val}, next{next} {}
    };

    int size{0};
    Node* head;

   public:
    LinkedList() : head{new Node(T{}, nullptr)} {}

    void push(T val) {
        Node* prev = head;
        Node* cur = head->next;

        prev->mtx.lock();

        while (cur != nullptr) {
            cur->mtx.lock();
            prev->mtx.unlock();
            prev = cur;
            cur = cur->next;
        }

        prev->next = new Node(val, nullptr);
        size++;
        prev->mtx.unlock();
    }

    T pop() {
        Node* prev = head;
        Node* cur = head->next;

        prev->mtx.lock();

        if (cur == nullptr) {
            prev->mtx.unlock();
            return T{};
        }

        while (cur->next != nullptr) {
            cur->mtx.lock();
            prev->mtx.unlock();
            prev = cur;
            cur = cur->next;
        }

        T res = prev->next->val;

        prev->next = nullptr;
        delete cur;
        size--;
        prev->mtx.unlock();

        return res;
    }

    ~LinkedList() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* prev = cur;
            cur = cur->next;
            delete prev;
        }
    }
};
