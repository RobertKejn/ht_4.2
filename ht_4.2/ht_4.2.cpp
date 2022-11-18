

#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

class Adress {
private:
	std::string city;
	std::string street;
	int building;
	int flat;
public:
	Adress() {
		building = 0;
		flat = 0;
	}

	Adress(std::string city, std::string street, int building, int flat) {
		this->city = city;
		this->street = street;
		this->building = building;
		this->flat = flat;
	}

	std::string get_whole_adress() {
		return city + ", " + street + ", " + std::to_string(building) + ", " + std::to_string(flat);
	}

	bool compare(Adress adress) {
		bool res = true;
		int n = (city.length() > adress.city.length()) ? adress.city.length() : city.length();
		for (int i = 0; i < n; i++) {
			if (city[i] != adress.city[i]) {
				res = city[i] < adress.city[i];
				break;
			}
		}
		return res;
	}
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Adress* adresses = nullptr;
	std::ifstream fin("in.txt");
	std::ofstream fout("out.txt");
	std::string city;
	std::string street;
	int building = 0;
	int flat = 0;

	if (fin.is_open()) {
		int n = 0;
		fin >> n;
		adresses = new Adress[n];
		for (int i = 0; i < n; ++i) {
			fin >> city;
			fin >> street;
			fin >> building;
			fin >> flat;
			adresses[i] = Adress(city, street, building, flat);
		}

		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (adresses[i].compare(adresses[j]) == false) {
					Adress a = adresses[i];
					adresses[i] = adresses[j];
					adresses[j] = a;
				}
			}
		}

		if (fout.is_open()) {
			fout << n << "\n";
			for (int i = 0; i < n; ++i) {
				fout << adresses[i].get_whole_adress() << '\n';
			}
		}
		else {
			std::cout << "Ошибка открытия файла на запись\n";
		}
	}
	else {
		std::cout << "Ошибка открытия файла на чтение\n";
	}
	fin.close();
	fout.close();
	delete[] adresses;

}
