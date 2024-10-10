#include "Task.h"



	Task::Task(int id, const string& title, const string& description)
		: id(id), title(title), description(description) {}

	// Конструктор копирования
	Task::Task(int id, const Task& other)
		: id(id), title(other.title), description(other.description) {}

	json Task:: toJson() const {
		return json{
			{"id",id},
			{"title",title},
			{"description", description}
		};
	}

    Task Task:: fromJson(const json& j) {
		return Task(j["id"], j["title"], j["description"]);
	}

	Task::string ToString() {
		return to_string(id)
			+ " " + title
			+ " " + description;
	}

};