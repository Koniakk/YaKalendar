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



class Task
{
public:
	int id;
	string title;
	string description;

	Task(int id, const string& title, const string& description)
		: id(id), title(title), description(description) {}

	// ����������� �����������
	Task(int id, const Task& other)
		: id(id), title(other.title), description(other.description) {}

	json toJson();

	static Task fromJson(const json& j);

	string ToString();

};

