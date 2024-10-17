#include "Day.h"

Day::Day(int id, int momentDate, const string& mark)
	: id(id), momentDate(momentDate), mark(mark) {}

	// Конструктор копирования
Day::Day(int id, const Day& other)
	: id(id), momentDate(momentDate), mark(other.mark) {}

json Task:: toJson() const {
	return json{
		{"id",id},
		{"momentDate", momentDate},
		{"", mark}
	};
}

Day Day:: fromJson(const json& j) {
	return Day(j["id"], j["momentDate"], j["mark"]);
}

Day::string ToString() {
	return to_string(id)
		+ " " + to_string(momentDate)         
		+ " " + mark;
}
