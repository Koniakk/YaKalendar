// JSONexample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;

class Animal {
public:
	int id;
	string name;
	string breed;
	double weight;

	Animal(int id, const string& name, const string& breed, double weight)
		: id(id), name(name), breed(breed), weight(weight) {}

	// Конструктор копирования
	Animal(int id, const Animal& other)
		: id(id),name(other.name), breed(other.breed), weight(other.weight) {}

	json toJson() const {
		return json{
			{"id",id},
			{"name",name},
			{"breed", breed},
			{"weight",weight}
		};
	}

	static Animal fromJson(const json& j) {
		return Animal(j["id"], j["name"], j["breed"], j["weight"]);
	}

	string ToString() {
		return to_string(id) 
			+ " " + name 
			+ " " + breed 
			+ " " + to_string(weight);
	}

};


class Task {
public:
	int id;
	string title;
	string description;

	Task(int id, const string& title, const string& description)
		: id(id), title(title), description(description) {}

	// Конструктор копирования
	Task(int id, const Task& other)
		: id(id), title(other.title), description(other.description) {}

	json toJson() const {
		return json{
			{"id",id},
			{"title",title},
			{"description", description}
		};
	}

	static Task fromJson(const json& j) {
		return Task(j["id"], j["title"], j["description"]);
	}

	string ToString() {
		return to_string(id)
			+ " " + title
			+ " " + description;
	}

};

template <typename T>
class DataSource {
private:
	string filename;
	json data;
	int currentId;

	void readFile() {
		ifstream inputFile(filename);
		if (inputFile) {
			inputFile >> data;
			currentId = data.empty() ? 1 : data.back()["id"] + 1;
		}
		else {
			currentId = 1;
		}
	}

	void writeFile(const json& j) {
		ofstream outputFile(filename);
		outputFile << j.dump(4);
	}

	int FindById(int id) {
		int index = -1;
		for (int i = 0; i < data.size(); i++) {
			if (data[i]["id"] == id) {
				index = i;
				break;
			}
		}
		return index;
	}

public:

	DataSource(string filename) {
		this->filename = filename;
		readFile();
	}

	~DataSource() {
		writeFile(data);
	}

	void create(const T& item) {
		T next(currentId, item);
		data.push_back(next.toJson());
		currentId++;
		writeFile(data);
	}

	vector<T> read() {
		vector<T> items;
		for (const auto& j : data) {
			items.push_back(T::fromJson(j));
		}
		return items;
	}

	void update(const T& item) {
		int index = FindById(item.id);
		if (index != -1)
		{
			data[index] = item.toJson();
			writeFile(data);
		}
		else {
			cout << "������� � ����� ��������������� �� ������!" << endl;
		}
	}

	void remove(int id) {
		int index = FindById(id);
		if (index != -1) {
			data.erase(data.begin() + index);
			writeFile(data);
		}
		else {
			cout << "������� � ����� ��������������� �� ������!" << endl;
		}
	}
};

class Service {
public:
	template <typename T>
	void create(DataSource<T>& dataSource, const T& item) {
		dataSource.create(item);
	}
	template <typename T>
	vector<T> read(DataSource<T>& dataSource) {
		return dataSource.read();
	}
	template <typename T>
	void update(DataSource<T>& dataSource, const T& item) {
		dataSource.update(item);
	}
	template <typename T>
	void remove(DataSource<T>& dataSource, int id) {
		dataSource.remove(id);
	}
};

class AnimalService : public Service {
private:
	DataSource<Animal> dataSource;
public:
	AnimalService() :dataSource("animals.json") {}
	void create(const Animal& animal) {
		Service::create(dataSource, animal);
	}
	vector<Animal> read() {
		return Service::read(dataSource);
	}
	void update(const Animal& animal){
		Service::update(dataSource, animal);
	}
	void remove(int id) {
		Service::remove(dataSource, id);
	}
};

class TaskService : public Service {
private:
	DataSource<Task> dataSource;
public:
	TaskService() :dataSource("tasks.json") {}
	void create(const Task& task) {
		Service::create(dataSource, task);
	}
	vector<Task> read() {
		return Service::read(dataSource);
	}
	void update(const Task& task) {
		Service::update(dataSource, task);
	}
	void remove(int id) {
		Service::remove(dataSource, id);
	}
};

template <typename T>
void PrintList(vector<T> list) {
	for (auto& item : list) {
		cout << item.ToString() << endl;
	}
}

int main()
{
	setlocale(0, "ru");
	cout << "Работа с животными" << endl;
	AnimalService animalService;
	Animal animal1(1, "Bobik", "Dog", 10);
	Animal animal2(2, "Murka", "Cat", 5);

	animalService.create(animal1);
	animalService.create(animal2);

	cout << "Содержимое файла:" << endl;
	PrintList(animalService.read());
	

	animalService.remove(1);

	cout << "Содержимое файла:" << endl;
	PrintList(animalService.read());

	cout << "Работа с задачами" << endl;

	TaskService taskService;

	Task task1(0,"Task1","Description1");
	Task task2(0,"Task2","Description2");

	taskService.create(task1);
	taskService.create(task2);

	cout << "Содержимое файла:" << endl;
	PrintList(taskService.read());

	taskService.remove(1);

	cout << "Содержимое файла:" << endl;
	PrintList(taskService.read());

	return 0;
}
