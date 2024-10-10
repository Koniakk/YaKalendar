#ifndef DATASOURCE_H
#define DATASOURCE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
using json = nlohmann::json;
using namespace std;



class DataSource
{
private:
	string filename;
	json data;
	int currentId;

	void readFile();

	void writeFile(const json& j);

	int FindById(int id);

public:

	DataSource(string filename);

	~DataSource();
	template <typename T>
	void create(const T& item);
	template <typename T>
	vector<T> read();
	template <typename T>
	void update(const T& item);
	template <typename T>
	void remove(int id);
};


