// JSONexample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace std;







class Button
{
private:
public:
	//координаты
	int posX;
	int posY;
protected:
};

class Emotion
{
private:
	int counter_emo; //счет той или иной эмоции
public:
	Button emo; //кнопка той или иной эмоции
protected:
};

class Day
{
private:
	Button Zam_Plus; //кнопка +заметка
public:
	

	int id;
    int chislo;  //дата число
	string zametki;  //заметка
	Emotion emot;   //эмоция
	
	


	Day(int id, int chislo, const string& zametki, Emotion emot)
		: id(id), chilso(chislo), zametki(zametki), emot(emot) {}

	json toJson() const {
		return json{
			{"id",id},
			{"chislo",chislo},
			{"zmetki", zmetki},
			{"emot",emot}
		};
	}

	Day fromJson(const json& j) {
		return (j["id"], j["chislo"], j["zmetki"], j["emot"]);
	}
protected:
};

class Diagrammma
{
private:
	int fin_count_to_update; //не помню чтото важное мб
public:
protected:
};






//class Animal {
//public:
//	int id;
//	string name;
//	string breed;
//	double weight;
//
//	Animal(int id, const string& name, const string& breed, double weight)
//		: id(id), name(name), breed(breed), weight(weight) {}
//
//	json toJson() const {
//		return json{
//			{"id",id},
//			{"name",name},
//			{"breed", breed},
//			{"weight",weight}
//		};
//	}
//
//	Animal fromJson(const json& j) {
//		return Animal(j["id"], j["name"], j["breed"], j["weight"]);
//	}
//
//};

template <typename T>
class DataSource {
private:
	static const string filename;
	json data;
	int currentId;

	 void readFile() {
		json j;
		ifstream inputFile(filename);
		if (inputFile) {
			inputFile >> data;
			currentid = data.empty() ? 1 : data.back()["id"] + 1;

		}
		else {
			currentId = 1;
		}

		return j;
	}

	static void writeFile(const json& data) {
		ofstream outputFile(filename);
		outputFile << data.dump(4);
	}

	/// <summary>
	/// Функция поиска по идентификатору
	/// </summary>
	/// <param name="id">Идентификатор</param>
	/// <returns>Индекс элемента или -1, если элемент не найден</returns>
	int FindById(int id) {
		int index = -1;
		for (int i = 0; i < data.size(); i++) {
			if (data[i]["id"] == id) {
				index = i;
				break;
			}
		}
		return index;
	}

public:

	DataSource() {
		readFile();

	}
	~DataSource() {
		writeFile(data);

	}
	//Создание нового элемента
	void create(const T& item) {
		Animal Next(currentId, item);
		data.push_back(next.toJson());
		currentId++;
		writeFile(data);
	}

	void read() {
		cout << data.dump(4) << endl;
	}

	void update(const T& item) {
		int index = FindById(item.id);
		if (index != -1)
		{
			data[index] = item.toJson();
			writeFile(j);
		}
		else {
			cout << "Элемент с таким идентификатором не найден!" << endl;
		}
	}

	void remove(int id) {
		int index = FindById(id);
		if (index != -1) {
			data.erase(j.begin() + index);
			writeFile(j);
		}
		else {
			cout << "Элемент с таким идентификатором не найден!" << endl;
		}
	}

};

template <typename T>
const string DataSource<T>::filename = "data.json";

int main()
{
	setlocale(0, "ru");
	DataSource<Animal> dataSource;

	Animal animal1(1, "Bobik", "Dog", 10);
	Animal animal2(2, "Murka", "Cat", 5);

	dataSource.create(animal1);
	dataSource.create(animal2);

	cout << "Содержимое файла:" << endl;
	dataSource.read();

	//Animal updatedAnimal(3, "Bobik", "Dog", 20);
	//dataSource.update(updatedAnimal);
	//cout << "Содержимое файла:" << endl;
	//dataSource.read();

	dataSource.remove(1);
	dataSource.remove(2);
	cout << "Содержимое файла:" << endl;
	dataSource.read();

	return 0;
}
