#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Queue {

	vector<T> buffer;
	int head = 0; //то откуда попаем
	int tail = 0; //то куда пушим
	size_t currentSize = 0;
	int capacity = 1;

public:

	Queue(int size = 1) : buffer(size), head(0), tail(0), capacity(size) {
		if (size < 0) {
			throw "size cant be negative";
		}
	}

	void push(const T& val) {
		if (full()) {
			repacking();
		}

		buffer[tail] = val;
		tail = (tail + 1) % capacity;
		/*if (head == tail) {
			tail = (tail + 1) % capacity;
		}*/
		currentSize++;
	}

	void repacking() {
		vector<T> tmp(capacity * 2);
		int j = 0;
		for (int i = tail, j = 0; j < currentSize; i = (i + 1) % capacity, j++) {
			tmp[j] = buffer[i];
		}
		buffer = tmp;
		head = 0;
		tail = currentSize;
		capacity *= 2;
	}

	void pop() {

		if (empty()) {
			throw "nothing to pop";
		}
		head = (head + 1) % capacity;
		currentSize -= 1;
	}

	T& top() {
		if (empty()) {
			throw "Empty queue, no top element";
		}
		return buffer[head];
	}

	T& bottom() { //felt cute might delete later
		if (empty()) {
			throw "Empty queue, no bottom element";
		}
		return buffer[(tail - 1 + capacity) % capacity];
	}

	bool empty() {
		return (currentSize == 0);
	}

	bool full() {
		return (currentSize == capacity);
	}

	size_t size() {
		return currentSize;
	}

	void print_as_is() {
		for (int i = 0; i < buffer.size(); i++) {
			cout << buffer[i] << " ";
		}
	}

	void print() {
		for (int i = head, j = 0; j < currentSize; i = (i + 1) % capacity, j++) {
			cout << buffer[i] << " ";
		}
	}

};

#endif
