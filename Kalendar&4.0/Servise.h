#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "DataSource.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

using json = nlohmann::json;
using namespace std;

class Servise
{
	template <typename T>
	void create(DataSource<T>& dataSource, const T& item);
	template <typename T>
	vector<T> read(DataSource<T>& dataSource);

	template <typename T>
	void update(DataSource<T>& dataSource, const T& item);
	template <typename T>
	void remove(DataSource<T>& dataSource, int id);
};

