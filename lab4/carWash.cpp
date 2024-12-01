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

// template<typename T>
// class ArrayQueue : public Queue<T> {
// private:
// 	vector<T> data;
//
// public:
// 	void enqueue(const T &item) override
// 	{
// 		data.push_back(item);
// 	}
//
// 	T dequeue() override
// 	{
// 		if (isEmpty()) throw runtime_error("Queue is empty");
// 		T frontItem = data.front();
// 		data.erase(data.begin());
// 		return frontItem;
// 	}
//
// 	T front() const override
// 	{
// 		if (isEmpty()) throw runtime_error("Queue is empty");
// 		return data.front();
// 	}
//
// 	bool isEmpty() const override
// 	{
// 		return data.empty();
// 	}
//
// 	size_t size() const override
// 	{
// 		return data.size();
// 	}
// };
//
// template<typename T>
// class LinkedListQueue : public Queue<T> {
// private:
// 	struct Node {
// 		T value;
// 		Node *next;
// 		Node(const T &val) : value(val), next(nullptr) {}
// 	};
//
// 	Node *head = nullptr;
// 	Node *tail = nullptr;
// 	size_t count = 0;
//
// public:
// 	~LinkedListQueue()
// 	{
// 		while (!isEmpty()) dequeue();
// 	}
//
// 	void enqueue(const T &item) override
// 	{
// 		Node *newNode = new Node(item);
// 		if (tail) tail->next = newNode;
// 		tail = newNode;
// 		if (!head) head = newNode;
// 		++count;
// 	}
//
// 	T dequeue() override
// 	{
// 		if (isEmpty()) throw runtime_error("Queue is empty");
// 		Node *oldHead = head;
// 		T frontItem = oldHead->value;
// 		head = head->next;
// 		if (!head) tail = nullptr;
// 		delete oldHead;
// 		--count;
// 		return frontItem;
// 	}
//
// 	T front() const override
// 	{
// 		if (isEmpty()) throw runtime_error("Queue is empty");
// 		return head->value;
// 	}
//
// 	bool isEmpty() const override
// 	{
// 		return count == 0;
// 	}
//
// 	size_t size() const override
// 	{
// 		return count;
// 	}
// };
// template<typename T>
// class CircularQueue : public Queue<T> {
// private:
// 	vector<T> data;
// 	size_t head = 0, tail = 0, count = 0, capacity;
//
// public:
// 	explicit CircularQueue(size_t cap) : data(cap), capacity(cap) {}
//
// 	void enqueue(const T &item) override
// 	{
// 		if (count == capacity) throw runtime_error("Queue is full");
// 		data[tail] = item;
// 		tail = (tail + 1) % capacity;
// 		++count;
// 	}
//
// 	T dequeue() override
// 	{
// 		if (isEmpty()) throw runtime_error("Queue is empty");
// 		T frontItem = data[head];
// 		head = (head + 1) % capacity;
// 		--count;
// 		return frontItem;
// 	}
//
// 	T front() const override
// 	{
// 		if (isEmpty()) throw runtime_error("Queue is empty");
// 		return data[head];
// 	}
//
// 	bool isEmpty() const override
// 	{
// 		return count == 0;
// 	}
//
// 	size_t size() const override
// 	{
// 		return count;
// 	}
// };


class Dineable {
protected:
	virtual void serveDinner(string carID) {};

	virtual ~Dineable() {};
};

class Refuelable {
protected:
	virtual void refuel(string carID) {};

	virtual ~Refuelable() {};
};

class PeopleDinner : public Dineable {
private:
	static int servedPeople;

public:
	void serveDinner(string carID) override
	{
		servedPeople++;
		cout << "Serving dinner to people in " << carID << endl;
	}

	int getServedPeople() const { return servedPeople; }
};

int PeopleDinner::servedPeople = 0;

class RobotDinner : public Dineable {
private:
	static int servedRobot;

public:
	void serveDinner(string carID) override
	{
		servedRobot++;
		cout << "Serving dinner to robots in " << carID << endl;
	}

	int getServedRobot() const { return servedRobot; }
};

int RobotDinner::servedRobot = 0;

class ElectricStation : public Refuelable {
private:
	static int fueledElectric;

public:
	void refuel(string carID) override
	{
		fueledElectric++;
		cout << "Recharging battery for " << carID << endl;
	}

	int getFueledElectric() const { return fueledElectric; }
};

int ElectricStation::fueledElectric = 0;

class GasStation : public Refuelable {
private:
	static int fueledGas;

public:
	void refuel(string carID) override
	{
		fueledGas++;
		cout << "Refueling gas for " << carID << endl;
	}

	int getFueledGas() const { return fueledGas; }
};

int GasStation::fueledGas = 0;

int main()
{
	PeopleDinner peopleDinner;
	RobotDinner robotDinner1, robotDinner2;

	ElectricStation electricStation1, electricStation2;
	GasStation gasStation1, gasStation2;

	// Dinner
	peopleDinner.serveDinner("Car1");
	peopleDinner.serveDinner("Car2");
	robotDinner1.serveDinner("Car3");
	robotDinner1.serveDinner("Car5");
	robotDinner2.serveDinner("Car6");
	robotDinner2.serveDinner("Car7");

	// Refuel
	electricStation1.refuel("Car1");
	electricStation2.refuel("Car2");
	electricStation2.refuel("Car3");
	gasStation1.refuel("Car4");
	gasStation2.refuel("Car4");
	gasStation2.refuel("Car6");

	// Show counts
	cout << "\n---Summary---\n";
	cout << "People Served Dinner: " << peopleDinner.getServedPeople() << endl;
	cout << "Robots Served Dinner: " << robotDinner1.getServedRobot() << endl;
	cout << "Electric cars recharged: " << electricStation1.getFueledElectric() << endl;
	cout << "Gas cars refueled: " << gasStation1.getFueledGas() << endl;

	return 0;
}


