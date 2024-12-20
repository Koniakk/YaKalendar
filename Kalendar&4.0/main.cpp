
int main()
{
    setlocale(0, "ru");
    DataSource<Day> dataSource;
    //Animal animal1(1, "Bobik", "Dog", 10);
    Day kalendarny_day(1, 29, "smth idk");
    dataSource.create(day1);
    dataSource.create(day2);
    dataSourse.read();
    dataSourse.remove(1);
    dataSourse.remove(2);
    dataSourse.read();
	tasks = service.read();

	InitWindow(800, 600, "raygui - controls test suite");
	SetTargetFPS(60);

	bool showMessageBox = false;

	while (!WindowShouldClose())
	{
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)))

		GuiLabel({ 20,20,100,30 }, "Task title:");
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
			{20,70,760,500}, 
			taskList.c_str(), 
			&scrollIndex,
			&activeTask);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
