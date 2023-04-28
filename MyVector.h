#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

template <typename T> class MyVector {
private:
	T* a;
	int capacity, n;
public:
	MyVector();
	~MyVector();
	MyVector(int newSize);
	MyVector(int newSize, T value);
	int size();
	void resize(int newSize);
	void push_back(T value);
	void pop_back();
	void clear();
	void insert(int pos, T value);
	void erase(int pos);
	bool empty();
	T& operator[](int index) const;
	T& back();
};

template <typename T>
MyVector<T>::MyVector() {
	capacity = 1;
	n = 0;
	a = new T[1];
}

template <typename T>
MyVector<T>::~MyVector() {
	std::cout << "destructing myvector n = " << n << " capacity = " << capacity << "\n";
	delete[] a;
}

template <typename T>
MyVector<T>::MyVector(int newSize) {
	capacity = n = newSize;
	a = new T[n];
}

template <typename T>
MyVector<T>::MyVector(int newSize, T value) {
	capacity = n = newSize;
	a = new T[n];
	for (int i = 0; i < n; i++) {
		a[i] = value;
	}
}

template <typename T>
void MyVector<T>::resize(int newSize) {
	if (n >= newSize) {
		n = newSize;
		return;
	}
	T* newA = new T[newSize];
	for (int i = 0; i < n; i++) {
		newA[i] = a[i];
	}
	delete[] a;
	a = newA;
	n = newSize;
	capacity = newSize;
}

template <typename T>
int MyVector<T>::size() {
	return n;
}

template <typename T>
void MyVector<T>::push_back(T value) {
	std::cout << "start pushing n = " << n << " capacity = " << capacity << "\n";
	if (n == capacity) {
		capacity *= 2;
		T* newA = new T[capacity];
		for (int i = 0; i < n; i++) {
			newA[i] = a[i];
		}
		delete[] a;
		a = newA;
	}
	a[n] = value;
	n++;
	std::cout << "stop pushing n = " << n << " capacity = " << capacity << "\n";
}

template <typename T>
void MyVector<T>::pop_back() {
	assert(n > 0);
	n--;
}

template <typename T>
void MyVector<T>::clear() {
	if (n == 0) {
		return;
	}
	capacity = 1;
	n = 0;
	delete[] a;
	a = new T[1];
}

template <typename T>
void MyVector <T>::insert(int pos, T value) {
	assert(pos >= 0 && pos <= n);
	if (pos == n) {
		push_back(value);
		return;
	}
	T temp = back();
	for (int i = n - 1; i > pos; i--) {
		a[i] = a[i - 1];
	}
	a[pos] = value;
	push_back(temp);
}

template <typename T>
void MyVector <T>::erase(int pos) {
	assert(pos >= 0 && pos < n);
	for (int i = pos; i < n - 1; i++) {
		a[i] = a[i + 1];
	}
	pop_back();
}

template <typename T>
bool MyVector <T>::empty(){
	return n == 0;
}

template <typename T>
T& MyVector <T>::operator[](int index) const {
	assert(index >= 0 && index < n);
	return a[index];
}

template <typename T>
T& MyVector <T>::back() {
	assert(n > 0);
	return a[n - 1];
}

#endif 