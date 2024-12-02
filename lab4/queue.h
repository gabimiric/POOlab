#ifndef QUEUE_H

#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;
using namespace nlohmann;

// Abstract Queue class
template<typename T>
class Queue {
public:
    virtual ~Queue() {};

    virtual void enqueue(const T &item) = 0; // Adds an item to the queue

    virtual T dequeue() = 0; // Removes and returns an item from the queue

    virtual T front() const = 0; // Returns the item at the front without removing it

    virtual bool isEmpty() const = 0; // Checks if the queue is empty

    virtual size_t size() const = 0; // Returns the size of the queue
};

// Array-based Queue implementation
template<typename T>
class ArrayQueue : public Queue<T> {
private:
    vector<T> data; // Stores the items in the queue

public:
    void enqueue(const T &item) override
    {
        data.push_back(item); // Adds the item to the end of the queue
    }

    T dequeue() override
    {
        if (isEmpty()) throw runtime_error("Queue is empty"); // Throws error if the queue is empty
        T frontItem = data.front(); // Stores the front item
        data.erase(data.begin()); // Removes the front item
        return frontItem;
    }

    T front() const override
    {
        if (isEmpty()) throw runtime_error("Queue is empty"); // Throws error if the queue is empty
        return data.front(); // Returns the front item without removing it
    }

    bool isEmpty() const override
    {
        return data.empty(); // Returns true if the queue is empty
    }

    size_t size() const override
    {
        return data.size(); // Returns the size of the queue
    }
};
#define QUEUE_H

#endif //QUEUE_H
