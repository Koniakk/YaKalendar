#ifandif DATASOURSE_H
#define DATASOURSE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Task.h"

using json = nlohmann::json;
using namespace std;



class Day
{
public:
	int id;
	string title;
	string description;

	Day(int id, const string& title, const string& description)
		: id(id), title(title), description(description) {}

	// Êîíñòðóêòîð êîïèðîâàíèÿ
	Day(int id, const Day& other)
		: id(id), title(other.title), description(other.description) {}

	json toJson();

	static Day fromJson(const json& j);

	string ToString();

};
