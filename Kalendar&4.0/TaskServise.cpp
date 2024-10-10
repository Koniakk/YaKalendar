#include "TaskServise.h"


	DataSource<Task> dataSource;

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