#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <cassert>

template <class T>
class MyVector {
public:
	MyVector();
	MyVector(unsigned int size, const T& inital = T());
	MyVector(std::initializer_list <T> list);
	~MyVector();

	unsigned int capacity() const;
	unsigned int size() const;
	bool empty() const;

	T* begin();
	T* end();

	T& front();
	T& back();

	void push_back(T value);
	void pop_back();
	void resize(unsigned int size);
	void clear();
	void insert(unsigned int pos, T value);
	void erase(unsigned int pos);

	T& operator [] (unsigned int index);
	//MyVector& operator = (const MyVector <T>& other);

private:
	unsigned int currentSize;
	unsigned int currentCapacity;
	T* buffer;
};

template <class T>
MyVector <T>::MyVector() {
	currentCapacity = 0;
	currentSize = 0;
	buffer = nullptr;
}

template <class T>
MyVector <T>::MyVector(unsigned int size, const T& inital) {
	currentCapacity = size;
	currentSize = size;
	buffer = new T[currentCapacity];
	for (unsigned int i = 0; i < size; i++) {
		buffer[i] = inital;
	}
}

template <class T>
MyVector <T>::MyVector(std::initializer_list <T> list) {
	unsigned int size = list.size;
	currentCapacity = size;
	currentSize = size;
	buffer = new T[currentCapacity];
	for (unsigned int i = 0; i < size; i++) {
		buffer[i] = *(list.begin() + i);
	}
}

template <class T>
MyVector <T>::~MyVector() {
	delete[]buffer;
}

template <class T>
unsigned int MyVector <T>::capacity() const {
	return currentCapacity;
}

template <class T>
unsigned int MyVector <T>::size() const {
	return currentSize;
}

template <class T>
bool MyVector <T>::empty() const {
	return currentSize == 0;
}

template <class T>
T* MyVector <T>::begin() {
	return buffer;
}

template <class T>
T* MyVector <T>::end() {
	return buffer + currentSize;
}

template <class T>
T& MyVector <T>::front() {
	return buffer[0];
}

template <class T>
T& MyVector <T>::back() {
	return buffer[currentSize - 1];
}

template <class T>
void MyVector <T>::push_back(T value) {
	if (currentSize == currentCapacity) {
		currentCapacity *= 2;
		if (currentCapacity == 0) {
			currentCapacity = 1;
		}

		T* temp = new T[currentCapacity];
		for (unsigned int i = 0; i < currentSize; i++) {
			temp[i] = buffer[i];
		}

		delete buffer;
		buffer = temp;
	}

	buffer[currentSize] = value;
	currentSize++;
}

template <class T>
void MyVector <T>::pop_back() {
	currentSize--;
}

template <class T>
void MyVector <T>::resize(unsigned int size) {
	if (currentSize > currentCapacity) {
		currentCapacity = size;
		T* temp = new T[currentCapacity];
		for (unsigned int i = 0; i < currentSize; i++) {
			temp[i] = buffer[i];
		}

		delete buffer;
		buffer = temp;
	}

	currentSize = size;
}

template <class T>
void MyVector <T>::clear() {
	currentSize = 0;
}

template <class T>
void MyVector <T>::insert(unsigned int pos, T value) {
	assert(pos >= 0 && pos <= currentSize);
	if (pos == currentSize) {
		push_back(value);
		return;
	}
	T temp = back();
	for (int i = currentSize - 1; i > pos; i--) {
		buffer[i] = buffer[i - 1];
	}
	buffer[pos] = value;
	push_back(temp);
}

template <class T>
void MyVector <T>::erase(unsigned int pos) {
	assert(pos >= 0 && pos < currentSize);
	for (int i = pos; i < currentSize - 1; i++) {
		buffer[i] = buffer[i + 1];
	}
	pop_back();
}

template <class T>
T& MyVector <T>::operator [] (unsigned int index) {
	return buffer[index];
}

//template <class T>
//MyVector <T>& MyVector <T>::operator = (const MyVector <T>& other) {
//	if (other.capacity() > currentCapacity) {
//		delete buffer;
//		currentCapacity = other.capacity();
//		buffer = new T[currentCapacity];
//	}
//
//	currentSize = other.size();
//	for (unsigned int i = 0; i < currentSize; i++) {
//		buffer[i] = other[i];
//	}
//}

#endif