#pragma once

#include <memory>

template <typename E>
class Queue {
public:

    class QueueEmpty {};
    class QueueFull {};

    Queue(int cap) {
        capacity = cap;
        size = 0;
        front = 0;
        rear = 0;
        queue = std::make_unique<E[]>(cap);
    }
    int getSize() const {
        return size;
    }
    bool isEmpty() const {
        return size == 0;
    }
    const E& getFront() const {
        if (isEmpty()) {
            throw QueueEmpty();
        }
        return queue[front];
    }
    void enqueue(const E& e) {
        if (size == capacity) {
            throw QueueFull();
        }
        queue[rear] = e;
        rear = (rear + 1) % capacity;
        size++;
    }
    E dequeue() {
        if (isEmpty()) {
            throw QueueEmpty();
        }
        E e = queue[front];
        front = (front + 1) % capacity;
        size--;
        return e;
    }
private:
    int capacity;
    int size;
    int front;
    int rear;
    std::unique_ptr<E[]> queue;
};
