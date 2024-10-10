#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


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