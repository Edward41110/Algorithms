#include <iostream>
#include <ctime>
using namespace std;
#define DEFAULT_GROWTH_BASE 1000000
#define DEFAULT_LOAD_FACTOR 0.75

template <class T>
class Record {
public:
	Record(int k, T& v) : key(k), val(v) { }
	Record() : key(-1) { }
	~Record() { }
	int getKey() { return this->key; }
	T& getVal() { return this->val; }
	T* getPointer() { return &(this->val); }
private:
	int key;
	T val;
};

template <class T>
class Map {
public:
	Map(int gb = DEFAULT_GROWTH_BASE, float lf = DEFAULT_LOAD_FACTOR);
	~Map();
	void put(int key, T& val);
	bool get(int key, T& ret);
	bool modify_val(int key);
	void resize();
private:
	int hash(int key);
	void rehash();
	bool getPointer(int key, T** ret);
	bool getReference(int key, T& ret);
	Record<T>& operator[](int i) { return(this->map)[i]; }
	int size;
	int capacity;
	int GrowthBase;
	float LoadFactor;
	Record<T>* map;
};

template<class T>
Map<T>::Map(int gb, float lf) {
	while (gb <= 0)
		cin >> gb;
	while (lf <= 0 || lf > 1)
		cin >> lf;
	this->size = 0;
	this->capacity = gb;
	this->GrowthBase = gb;
	this->LoadFactor = lf;
	this->map = new Record<T>[gb];
}

template<class T>
Map<T>::~Map() {
	delete[](this->map);
}

template<class T>
void Map<T>::put(int key, T& val) {
	if ((this->size + 1) >= this->capacity * this->LoadFactor)
		this->resize();
	int HashKey = hash(key);
	int index = HashKey % this->capacity;
	int displacement = 0;
	while ((*this)[index].getKey() != -1) {
		displacement = -(displacement + (displacement > 0 ? 0 : -1));
		index = (HashKey + displacement + this->capacity) % this->capacity;
	}
	Record<T> newRecord(key, val);
	(*this)[index] = newRecord;
	(this->size)++;
}

template<class T>
bool Map<T>::get(int key, T& ret) {
	T retVal;
	if (getReference(key, retVal)) {
		ret = retVal;
		return true;
	} else {
		cout << key << "\tnot found." << endl;
		return false;
	}
}

template<class T>
bool Map<T>::modify_val(int key) {
	T* modify = NULL;
	if (getPointer(key, &modify)) {
		cout << *modify << "->";
		cin >> *modify;
		return true;
	} else {
		cout << key << "\tnot found." << endl;
		return false;
	}
}

template<class T>
void Map<T>::resize() {
	this->capacity = this->capacity + this->GrowthBase;
	this->rehash();
}

template<class T>
bool Map<T>::getPointer(int key, T** ret) {
	int HashKey = hash(key);
	int index = HashKey % this->capacity;
	int displacement = 0;
	while ((*this)[index].getKey() != key) {
		if ((*this)[index].getKey() == -1) return false;
		displacement = -(displacement + (displacement > 0 ? 0 : -1));
		index = (HashKey + displacement + this->capacity) % this->capacity;
	}
	*ret = (*this)[index].getPointer();
	return true;
}

template<class T>
bool Map<T>::getReference(int key, T& ret) {
	T* retPointer;
	if (this->getPointer(key, &retPointer)) {
		ret = *retPointer;
		return true;
	} else return false;
}

template<class T>
int Map<T>::hash(int key) {
	int HashKey = key;
	HashKey ^= (HashKey << 10) ^ (HashKey << 7);
	HashKey ^= (HashKey >> 5) ^ (HashKey >> 8);
	return HashKey >> 6;
}

template<class T>
void Map<T>::rehash() {
	Record<T>* oldMap = this->map;
	this->map = new Record<T>[this->capacity];
	int i, cnt;
	for (i = 0, cnt = 0;cnt < this->size;i++) {
		if (oldMap[i].getKey() != -1) {
			put(oldMap[i].getKey(), oldMap[i].getVal());
			this->size--, cnt++;
		}
	}
}

