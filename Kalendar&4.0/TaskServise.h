#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Task.h"
#include "Servise.h"
#include "DataSource.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

class TaskServise
{
private:
	DataSource<Task> dataSource;
public:
	TaskService() :dataSource("tasks.json");

	vector<Task> read();

	void update(const Task& task);
	void remove(int id);

};

