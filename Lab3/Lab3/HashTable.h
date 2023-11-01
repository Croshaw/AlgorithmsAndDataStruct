#include <iostream>
#include <functional>
#pragma once
template <typename T, typename F>
class HashTable
{
private:
	T* _keys;
	F* _values;
	bool* _isOccupied;
	int _size;
	int _count;
	int a;
	int b;
	int getHashCode(T key) {
		std::hash<T> hasher;
		return std::abs((int)hasher(key));
	}
	int hashFunc(int key) {
		return key % a;
	}
	int quadricHashFunc(int hash, int i) {
		return (hash + b * i + a * i * i) % _size;
	}
	int getId(T key) {
		int hash = hashFunc(getHashCode(key));
		int index = hash;
		int i = 0;
		while (_keys[index] != key && i <= _size) {
			index = quadricHashFunc(hash, i);
			i++;
		}
		if (i == _size)
			index = -1;
		return index;
	}
public:
	HashTable(int size)
	{
		this->_size = size;
		_keys = new T[_size]();
		_values = new F[_size]();
		_isOccupied = new bool[_size]();
		_count = 0;
		a = (_size / 2);
		b = 2;
	}
	~HashTable() {
		delete[] _keys;
		delete[] _values;
		delete[] _isOccupied;
	}
	void add(T key, F value) {
		if (_count == _size)
			throw "HashTable is already full!";
		int hash = hashFunc(getHashCode(key));
		int index = hash;
		int i = 0;
		while (_isOccupied[index]) {
			index = quadricHashFunc(hash, i);
			i++;
		}
		_values[index] = value;
		_keys[index] = key;
		_isOccupied[index] = true;
		_count++;
	}
	void remove(T key) {
		int index = getId(key);
		if (index != -1) {
			_values[index] = F();
			_keys[index] = T();
			_isOccupied[index] = false;
			_count--;
		}
	}
	F get(T key) {
		int index = getId(key);
		if (index != -1) {
			return _values[index];
		}
		throw "Key not found";
	}
	void print() {
		try {
			for (int i = 0; i < _size; i++) {
				std::cout << i << ": ";
				std::cout << "Key: " << _keys[i] << "\tValue: " << _values[i];
				std::cout << std::endl;
			}
		}
		catch (std::string err) {
			std::cout << "Îøèáêà: " << err;
		}
	}
};

