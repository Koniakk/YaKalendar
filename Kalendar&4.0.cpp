#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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
		: id(id), name(other.name), breed(other.breed), weight(other.weight) {}

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
			cout << "Not Found!" << endl;
		}
	}

	void remove(int id) {
		int index = FindById(id);
		if (index != -1) {
			data.erase(data.begin() + index);
			writeFile(data);
		}
		else {
			cout << "Not Found!" << endl;
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
	void update(const Animal& animal) {
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

TaskService service;
std::vector<Task> tasks;
char taskTitle[64] = "";
char taskDescription[256] = "";
int scrollIndex = 0;
int activeTask = -1;

void AddTask() {
	if (strlen(taskTitle) > 0) {
		service.create(Task(0, taskTitle, taskDescription));
		tasks = service.read();
		strcpy(taskTitle, "");
	}
}
void UpdateTask() {
	if (activeTask >= 0 && activeTask < tasks.size())
	{
		tasks[activeTask].title = taskTitle;
		tasks[activeTask].description = taskDescription;
		service.update(tasks[activeTask]);
		tasks = service.read();
	}
}
void DeleteTask() {
	if (activeTask >= 0 && activeTask < tasks.size())
	{
		service.remove(tasks[activeTask].id);
		tasks = service.read();
		activeTask = -1;
	}
}

int main()
{
	tasks = service.read();

	InitWindow(800, 600, "raygui - controls test suite");
	SetTargetFPS(60);

	bool showMessageBox = false;

	while (!WindowShouldClose())
	{
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

		GuiLabel({ 20,20,100,30 }, "note:");
		GuiTextBox({ 120,20,200,30 }, taskTitle, 64, true);
		//GuiTextBox({ 330,20,200,30 }, taskDescription, 256, true);

		if (GuiButton({ 530,20,80,30 }, "Add")) AddTask();
		if (GuiButton({ 630,20,80,30 }, "Update")) UpdateTask();
		if (GuiButton({ 730,20,80,30 }, "Delete")) DeleteTask();

		std::string taskList;
		for (auto& task : tasks) {
			taskList += task.ToString() + "\n";
		}
		if (!taskList.empty()) {
			taskList.pop_back();
		}

		GuiListView(
			{ 20,70,760,500 },
			taskList.c_str(),
			&scrollIndex,
			&activeTask);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}