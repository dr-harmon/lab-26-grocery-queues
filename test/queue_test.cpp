#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include "queue.h"

using namespace std;

TEST_CASE("Queue elements can be enqueued and dequeued")
{
    Queue<int> q(10);
    REQUIRE(q.getSize() == 0);
    REQUIRE(q.isEmpty());
    q.enqueue(1);
    REQUIRE(q.getFront() == 1);
    REQUIRE(q.getSize() == 1);
    REQUIRE_FALSE(q.isEmpty());
    q.enqueue(2);
    REQUIRE(q.getFront() == 1);
    REQUIRE(q.getSize() == 2);
    REQUIRE_FALSE(q.isEmpty());
    q.enqueue(3);
    REQUIRE(q.getFront() == 1);
    REQUIRE(q.getSize() == 3);
    REQUIRE_FALSE(q.isEmpty());
    REQUIRE(q.dequeue() == 1);
    REQUIRE(q.getFront() == 2);
    REQUIRE(q.getSize() == 2);
    REQUIRE_FALSE(q.isEmpty());
    REQUIRE(q.dequeue() == 2);
    REQUIRE(q.getFront() == 3);
    REQUIRE(q.getSize() == 1);
    REQUIRE_FALSE(q.isEmpty());
    REQUIRE(q.dequeue() == 3);
    REQUIRE(q.getSize() == 0);
    REQUIRE(q.isEmpty());
}

TEST_CASE("Accessing the front of an empty queue throws an exception")
{
    Queue<int> q(10);
    REQUIRE_THROWS(q.getFront());
    q.enqueue(1);
    REQUIRE(q.getFront() == 1);
    q.dequeue();
    REQUIRE_THROWS(q.getFront());
}

TEST_CASE("Enqueuing into a full queue throws an exception")
{
    Queue<int> q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    REQUIRE_THROWS(q.enqueue(4));
    REQUIRE(q.getSize() == 3);
}

TEST_CASE("Dequeuing from an empty queue throws an exception")
{
    Queue<int> q(3);
    REQUIRE_THROWS(q.dequeue());
    REQUIRE(q.getSize() == 0);
}

TEST_CASE("Circular queue test")
{
    Queue<int> q(3);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    REQUIRE(q.dequeue() == 1);
    REQUIRE(q.dequeue() == 2);
    q.enqueue(4);
    q.enqueue(5);
    REQUIRE(q.dequeue() == 3);
    q.enqueue(6);
    REQUIRE(q.getSize() == 3);
    REQUIRE(q.dequeue() == 4);
    q.enqueue(7);
    REQUIRE(q.dequeue() == 5);
    REQUIRE(q.dequeue() == 6);
    REQUIRE(q.dequeue() == 7);
    REQUIRE(q.getSize() == 0);
}
