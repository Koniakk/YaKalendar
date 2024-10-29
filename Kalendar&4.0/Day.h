#ifndef DATASOURSE_H
#define DATASOURSE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Task.h"

using json = nlohmann::json;
using namespace std;



class Day {
public:
	int id;
	int momentDate; //chislo
	string mark; //zametki

	Day(int id, int momentDate, const string& mark)
	: id(id), momentDate(momentDate), mark(mark) {}

	// Конструктор копирования
	Day(int id, const Day& other)
		: id(id), momentDate(momentDate), mark(other.mark) {}

	json toJson();

	static Day fromJson(const json& j);

	string ToString();

};
