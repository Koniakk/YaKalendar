int id;
	int momentDate; //chislo
	string mark; //zametki

	Day(int id, int momentDate, const string& mark)
		: id(id), momentDate(momentDate), mark(mark) {}

	// Конструктор копирования
	Day(int id, const Day& other)
		: id(id), momentDate(momentDate), mark(other.mark) {}

	json toJson() const {
		return json{
			{"id",id},
			{"momentDate", momentDate},
			{"", mark}
		};
	}

	static Day fromJson(const json& j) {
		return Day(j["id"], j["momentDate"], j["mark"]);
	}

	string ToString() {
		return to_string(id)
			+ " " + to_string(momentDate)         
			+ " " + mark;
	}
