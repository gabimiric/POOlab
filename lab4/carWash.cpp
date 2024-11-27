#include <bits/stdc++.h>

using namespace std;

template<typename T>
class Queue {
public:
	virtual ~Queue() {};

	virtual void enqueue(const T &item) = 0;

	virtual T dequeue() = 0;

	virtual T front() const = 0;

	virtual bool isEmpty() const = 0;

	virtual size_t size() const = 0;
};

template<typename T>
class ArrayQueue : public Queue<T> {
private:
	vector<T> data;

public:
	void enqueue(const T &item) override
	{
		data.push_back(item);
	}

	T dequeue() override
	{
		if (isEmpty()) throw runtime_error("Queue is empty");
		T frontItem = data.front();
		data.erase(data.begin());
		return frontItem;
	}

	T front() const override
	{
		if (isEmpty()) throw runtime_error("Queue is empty");
		return data.front();
	}

	bool isEmpty() const override
	{
		return data.empty();
	}

	size_t size() const override
	{
		return data.size();
	}
};

template<typename T>
class LinkedListQueue : public Queue<T> {
private:
	struct Node {
		T value;
		Node *next;
		Node(const T &val) : value(val), next(nullptr) {}
	};

	Node *head = nullptr;
	Node *tail = nullptr;
	size_t count = 0;

public:
	~LinkedListQueue()
	{
		while (!isEmpty()) dequeue();
	}

	void enqueue(const T &item) override
	{
		Node *newNode = new Node(item);
		if (tail) tail->next = newNode;
		tail = newNode;
		if (!head) head = newNode;
		++count;
	}

	T dequeue() override
	{
		if (isEmpty()) throw runtime_error("Queue is empty");
		Node *oldHead = head;
		T frontItem = oldHead->value;
		head = head->next;
		if (!head) tail = nullptr;
		delete oldHead;
		--count;
		return frontItem;
	}

	T front() const override
	{
		if (isEmpty()) throw runtime_error("Queue is empty");
		return head->value;
	}

	bool isEmpty() const override
	{
		return count == 0;
	}

	size_t size() const override
	{
		return count;
	}
};

template<typename T>
class CircularQueue : public Queue<T> {
private:
	vector<T> data;
	size_t head = 0, tail = 0, count = 0, capacity;

public:
	explicit CircularQueue(size_t cap) : data(cap), capacity(cap) {}

	void enqueue(const T &item) override
	{
		if (count == capacity) throw runtime_error("Queue is full");
		data[tail] = item;
		tail = (tail + 1) % capacity;
		++count;
	}

	T dequeue() override
	{
		if (isEmpty()) throw runtime_error("Queue is empty");
		T frontItem = data[head];
		head = (head + 1) % capacity;
		--count;
		return frontItem;
	}

	T front() const override
	{
		if (isEmpty()) throw runtime_error("Queue is empty");
		return data[head];
	}

	bool isEmpty() const override
	{
		return count == 0;
	}

	size_t size() const override
	{
		return count;
	}
};

int main()
{
	ArrayQueue<int> intQueue;
	cout << "ArrayQueue Example:\n";
	intQueue.enqueue(10);
	intQueue.enqueue(20);
	intQueue.enqueue(30);
	intQueue.enqueue(40);
	intQueue.enqueue(50);
	intQueue.enqueue(60);

	cout << "Size: " << intQueue.size() << "\n";
	cout << "Front: " << intQueue.front() << "\n";
	cout << "Dequeued: " << intQueue.dequeue() << "\n";
	cout << "Front after dequeue: " << intQueue.front() << "\n";
	cout << "Is Empty: " << intQueue.isEmpty() << "\n";
	cout << "Size: " << intQueue.size() << "\n\n";

	LinkedListQueue<string> stringQueue;
	cout << "LinkedListQueue Example:\n";
	stringQueue.enqueue("Harro");
	stringQueue.enqueue("World");
	stringQueue.enqueue("!!!!!");
	stringQueue.enqueue("It");
	stringQueue.enqueue("Me");
	stringQueue.enqueue("!!!!!");

	cout << "Size: " << stringQueue.size() << "\n";
	cout << "Front: " << stringQueue.front() << "\n";
	cout << "Dequeued: " << stringQueue.dequeue() << "\n";
	cout << "Front after dequeue: " << stringQueue.front() << "\n";
	cout << "Is empty? " << (stringQueue.isEmpty() ? "Yes" : "No") << "\n";
	cout << "Size: " << stringQueue.size() << "\n\n";

	CircularQueue<double> doubleQueue(3);
	cout << "CircularQueue Example:\n";
	doubleQueue.enqueue(1.1);
	doubleQueue.enqueue(2.2);
	doubleQueue.enqueue(3.3);

	cout << "Size: " << doubleQueue.size() << "\n";
	cout << "Front: " << doubleQueue.front() << "\n";
	cout << "Dequeued: " << doubleQueue.dequeue() << "\n";
	cout << "Is Empty? " << (doubleQueue.isEmpty() ? "Yes" : "No") << "\n";
	cout << "Front after enqueue: " << doubleQueue.front() << "\n";
	cout << "Size: " << doubleQueue.size() << "\n";

	return 0;
}


