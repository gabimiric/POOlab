#ifndef QUEUE_H

#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
using namespace std;
using namespace nlohmann;

// Abstract Queue class that defines the basic interface for all Queue types
template<typename T>
class Queue {
public:
    virtual ~Queue() {}; // Virtual destructor to ensure proper cleanup of derived class objects

    virtual void enqueue(const T &item) = 0; // Adds an item to the queue

    virtual T dequeue() = 0; // Removes and returns the item at the front of the queue

    virtual T front() const = 0; // Returns the item at the front without removing it

    virtual bool isEmpty() const = 0; // Checks if the queue is empty

    virtual size_t size() const = 0; // Returns the number of items in the queue
};

// Array-based implementation of the Queue interface
template<typename T>
class ArrayQueue : public Queue<T> {
private:
    vector<T> data; // Vector that holds the items in the queue

public:
    // Adds an item to the back of the queue
    void enqueue(const T &item) override
    {
        data.push_back(item); // Adds the item to the end of the vector (queue)
    }

    // Removes and returns the front item from the queue
    T dequeue() override
    {
        if (isEmpty()) throw runtime_error("Queue is empty"); // Throws an error if the queue is empty
        T frontItem = data.front(); // Retrieves the front item
        data.erase(data.begin()); // Removes the front item from the vector
        return frontItem; // Returns the removed front item
    }

    // Returns the front item without removing it from the queue
    T front() const override
    {
        if (isEmpty()) throw runtime_error("Queue is empty"); // Throws an error if the queue is empty
        return data.front(); // Returns the front item without modifying the queue
    }

    // Checks if the queue is empty
    bool isEmpty() const override
    {
        return data.empty(); // Returns true if the queue has no items
    }

    // Returns the current size of the queue
    size_t size() const override
    {
        return data.size(); // Returns the number of items currently in the queue
    }
};

#define QUEUE_H

#endif //QUEUE_H
