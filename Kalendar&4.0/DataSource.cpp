#include "DataSource.h"


using json = nlohmann::json;
using namespace std;

template <typename T>
DataSource<T>::DataSource(string filename) {
	this->filename = filename;
	readFile();
}
template <typename T>
DataSource<T>::~DataSource() {
	writeFile(data);
}
template <typename T>
void DataSource<T>::create(const T& item) {
	T next(currentId, item);
	data.push_back(next.toJson());
	currentId++;
	writeFile(data);
}
template <typename T>
vector<T> DataSource<T>::read() {
	vector<T> items;
	for (const auto& j : data) {
		items.push_back(T::fromJson(j));
	}
	return items;
}
template <typename T>
void DataSource<T>::update(const T& item) {
	int index = FindById(item.id);
	if (index != -1)
	{
		data[index] = item.toJson();
		writeFile(data);
	}
	else {
		cout << "Not Found!" << endl;
	}
}
template <typename T>
void DataSource<T>::remove(int id) {
	int index = FindById(id);
	if (index != -1) {
		data.erase(data.begin() + index);
		writeFile(data);
	}
	else {
		cout << "Not Found!" << endl;
	}
}

template class DataSource<Task>;




