#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

struct Student {
	int id;
	string name;  // ФИО в одной строке
	string submissionDate;
	string reviewDate;
	int gradeReport;
	int gradeDefense;
	string reviewer;
	string seminarist;

	void input() {
		cout << "Введите ID студента: ";
		cin >> id;
		cin.ignore();  // Игнорируем \n перед getline
		cout << "Введите ФИО: ";
		getline(cin, name);
		cout << "Введите дату сдачи (ДД.ММ.ГГГГ): ";
		cin >> submissionDate;
		cout << "Введите дату проверки (ДД.ММ.ГГГГ): ";
		cin >> reviewDate;
		cout << "Введите оценку за отчет: ";
		cin >> gradeReport;
		cout << "Введите оценку за защиту: ";
		cin >> gradeDefense;
		cin.ignore();
		cout << "Введите фамилию проверяющего: ";
		getline(cin, reviewer);
		cout << "Введите фамилию семинариста: ";
		getline(cin, seminarist);
	}


	void print() {
		cout << "ID: " << id << ", ФИО: " << name
			<< ", Дата сдачи: " << submissionDate
			<< ", Дата проверки: " << reviewDate
			<< ", Оценка за отчет: " << gradeReport
			<< ", Оценка за защиту: " << gradeDefense
			<< ", Проверяющий: " << reviewer
			<< ", Семинарист: " << seminarist << endl;
	}
};

struct Cell {
	int RecNumID;//индексы в массиве эл-а, к-ый должен
	int RecNumName;//находится на этом месте при той или иной сортировке
	int RecNum;

	Cell* next = nullptr;
};

#pragma region Global
const int MAX_STUDENTS = 100;
int studentsNumber = 10;
Student students[MAX_STUDENTS] = {
	{3, "Борисова Екатерина Андреевна", "27.11.2024", "03.12.2024", 6, 9, "Долныкова", "Будин"},
	{5, "Дуров Павел Валерьевич", "01.12.2024", "10.12.2024", 4, 6, "Долныкова", "Цидвинцев"},
	{9, "Косвинцев Богдан Павлович", "01.12.2024", "10.12.2024", 6, 8, "Осока", "Цидвинцев"},
	{10, "Никитин Никита Никитич", "01.12.2024", "10.12.2024", 0, 0, "Долныкова", "Будин"},
	{1, "Петров Арсений Николаевич", "25.11.2024", "30.11.2024", 7, 9, "Долныкова", "Цидвинцев"},
	{8, "Понькина Татьяна Евгеньевна", "25.11.2024", "05.12.2024", 8, 8, "Осока", "Цидвинцев"},
	{2, "Семенов Евгений Александрович", "25.11.2024", "30.11.2024", 5, 8, "Долныкова", "Будин"},
	{6, "Симонов Антон Владимирович", "25.11.2024", "01.12.2024", 8, 8, "Осока", "Цидвинцев"},
	{4, "Юрьева София Юрьевна", "28.11.2024", "03.12.2024", 2, 9, "Долныкова", "Цидвинцев"},
	{7, "Янина Анна Владимировна", "25.11.2024", "01.12.2024", 7, 7, "Осока", "Цидвинцев"}
};

string normalize(const string& str) {
	string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		char ch = str[i];

		// Приводим к нижнему регистру вручную
		if (ch >= 'А' && ch <= 'Я') {
			ch = ch + ('a' - 'A');
		}

		// Пропускаем пробелы
		if (ch != ' ') {
			result += ch;
		}
	}
	return result;
}
#pragma endregion

#pragma region ID
void sortByID(Cell* cell) {
	if (cell == nullptr) return;

	bool swapped;
	do {
		swapped = false;
		Cell* current = cell;
		while (current->next) {
			if (students[current->RecNumID].id > 
				students[current->next->RecNumID].id) {
				int recnum = current->RecNumID;
				current->RecNumID = current->next->RecNumID;
				current->next->RecNumID = recnum;
				swapped = true;
			}
			current = current->next;
		}
	} while (swapped);
}

void printByID(Cell* cell) {
	Cell* current = cell;
	while (current) {
		if (current->RecNumID != -1)students[current->RecNumID].print();
		current = current->next;
	}
}

int searchByID(int id, Cell* cell) {
	if (students[cell->RecNum].id == id) return cell->RecNum;
	else if (cell->next == nullptr) return -1;
	else searchByID(id, cell->next);
}

void AddID(Cell* mainCell) {
	int id = students[studentsNumber].id;

	Cell* current = mainCell;
	while (current != nullptr && students[current->RecNumID].id < id) {
		if (current->next == nullptr) {
			Cell* newCell = new Cell;
			newCell->RecNumID = studentsNumber;
			newCell->RecNumName = studentsNumber;
			newCell->RecNum = studentsNumber;
			current->next = newCell;
			return;
		}
		current = current->next;
	}
	int rec1;
	int rec = current->RecNumID;
	current->RecNumID = studentsNumber;
	current = current->next;
	while (current != nullptr) {
		rec1 = current->RecNumID;
		current->RecNumID = rec;
		rec = rec1;
		if (current->next == nullptr) {
			Cell* newCell = new Cell;
			newCell->RecNum = studentsNumber;
			newCell->RecNumName = studentsNumber;
			newCell->RecNumID = rec;
			current->next = newCell;
			break;
		}
		current = current->next;
	}
}
#pragma endregion

#pragma region Name
void sortByName(Cell* cell) {
	if (cell == nullptr) return;

	bool swapped;
	do {
		swapped = false;
		Cell* current = cell;
		while (current->next) {
			if (normalize(students[current->RecNumName].name) < 
				normalize(students[current->next->RecNumName].name)) {
				int recnum = current->RecNumName;
				current->RecNumName = current->next->RecNumName;
				current->next->RecNumName = recnum;
				swapped = true;
			}
			current = current->next;
		}
	} while (swapped);

	Cell* current = cell;
	while (current && current->next) {
		current = current->next;
	}
	if (current) current->next = nullptr;
}

void printByName(Cell* cell) {
	Cell* current = cell;
	while (current) {
		if (current->RecNumName != -1) students[current->RecNumName].print();
		current = current->next;
	}
}

int searchByName(string Name, Cell* cell) {
	Cell* current = cell;
	while (current != nullptr) {
		if (normalize(students[current->RecNum].name) == Name) return current->RecNum;
		current = current->next;
	}
	return -1;
}

void AddName(Cell* mainCell) {
	string Name = normalize(students[studentsNumber].name);

	Cell* current = mainCell;
	while (current != nullptr && normalize(students[current->RecNumName].name) > Name) {
		current = current->next;
	}
	int rec1;
	int rec = current->RecNumName;
	current->RecNumName = studentsNumber;
	current = current->next;
	while (current != nullptr) {
		rec1 = current->RecNumName;
		current->RecNumName = rec;
		rec = rec1;
		current = current->next;
	}
}
#pragma endregion

Cell* Cover(int i) {
	if (i < studentsNumber) {
		Cell* cell = new Cell;
		cell->RecNum = i;
		cell->RecNumID = i;
		cell->RecNumName = i;
		cell->next = Cover(i + 1);
		return cell;
	}
	else return nullptr;
}

void Print(Cell* cell) {
	if (cell != nullptr) {
		if (cell->RecNum != -1) students[cell->RecNum].print();
		Print(cell->next);
	}
}

void Delete(int key, Cell* cell) {
	Cell* current = cell;
	while (current) {
		if (current->RecNum == key) current->RecNum = -1;
		if (current->RecNumID == key) current->RecNumID = -1;
		if (current->RecNumName == key) current->RecNumName = -1;
		current = current->next;
	}
}

void Add(Cell* mainCell) {
	students[studentsNumber].input();
	
	AddID(mainCell);
	AddName(mainCell);

	studentsNumber++;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool exit = false;
	int choice = 0, subchoice = 0;
	int id, key;
	string Name;

	//Ввод списка
	cout << "Удалить исходные данные?\n1. Да\n2. Нет\nВведите команду: ";
	cin >> choice;
	if (choice == 1) {
		cout << "Введите количество значений для добавления: ";
		cin >> studentsNumber;
		for (int i = 0; i < studentsNumber; i++) {
			students[i].input();
		}
	}

	Cell* mainCell = Cover(0);
	sortByID(mainCell);
	sortByName(mainCell);

	while (!exit) {
		cout << "Главное меню:\n";
		cout << "1. Добавить студента\n";
		cout << "2. Вывести список студентов\n";
		cout << "3. Отсортировать список студентов\n";
		cout << "4. Поиск студента по ID\n5. Поиск студента по ФИО\n6. Выход\nВведите команду: ";
		cin >> choice;

		switch (choice) {
		case 1:
			Add(mainCell);
			break;
		case 2:
			Print(mainCell);
			break;
		case 3:
			cout << "1. Сортировать по возрастанию ID\n2. Сортировать по убыванию ФИО\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 1) {
				printByID(mainCell);
			}
			else {
				printByName(mainCell);
			}
			break;
		case 4:
			if (studentsNumber == 0) {
				cout << "В списке нет студентов: ";
				break;
			}
			cout << "Введите ID студента: ";
			cin >> id;
			key = searchByID(id, mainCell);
			if (key == -1) break;
			students[key].print();
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2) break;
			Delete(key, mainCell);
			break;
		case 5:
			if (studentsNumber == 0) {
				cout << "В списке нет студентов: ";
				break;
			}
			cout << "Введите ФИО студента: ";
			cin.ignore();
			getline(cin, Name);
			key = searchByName(normalize(Name), mainCell);
			if (key == -1) break;
			students[key].print();
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2) break;
			Delete(key, mainCell);
			break;
		case 6:
			exit = true;
			break;
		default:
			cout << "Неправильный ввод. Попробуйте еще)\n";
			break;
		}
	}
}