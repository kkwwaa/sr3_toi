#include <iostream>
#include <string>
#include <Windows.h>
#include <set>

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

struct Cell {
	int ID;
	string Name;
	int recNum;

	Cell* next = nullptr;
	Cell* nextID = nullptr;
	Cell* nextName = nullptr;
};
Cell* head = nullptr;
Cell* headID = nullptr;
Cell* headName = nullptr;
Cell* prevv = nullptr;

#pragma region Print
void printSortID(Cell* cell) {
	if (!cell) return;
	students[cell->recNum].print();
	printSortID(cell->nextID);
}

void printSortName(Cell* cell) {
	if (!cell) return;
	students[cell->recNum].print();
	printSortName(cell->nextName);
}

void print(Cell* cell) {
	if (!cell) return;
	students[cell->recNum].print();
	print(cell->next);
}
#pragma endregion

#pragma region Insert
void insertMain(Cell* cur) {
	if (prevv == nullptr) {//если первая ячейка
		head = cur; //назначаем главной головой текущую созданную ячейку
	}
	else {
		prevv->next = cur;//если не первая, то предыдущему назначаем следующим текущий

	}
	prevv = cur;
}

void insertID(Cell* cur) {
	if (headID == nullptr) {//если голова ИД не назначена
		headID = cur; //назначаем
	}
	else if (cur->ID < headID->ID) {//если голова есть и знач меньше, головы 
		cur->nextID = headID;//то, переназначааем голову
		headID = cur;
	}
	else {
		Cell* temp = headID;//если же больше, то ищем место вставки
		while (temp->nextID != nullptr && temp->nextID->ID < cur->ID) {//цикл пока не дойдем до конца или не найдем место
			temp = temp->nextID;//просто идем по ячейкам
		}//temp элемент перед местом вставки
		cur->nextID = temp->nextID;//переназначаем ссылки
		temp->nextID = cur;
	}
}

void insertName(Cell* cur) {
	if (headName == nullptr) {//если голова Фио не назначена
		headName = cur; //назначаем
	}
	else if (normalize(cur->Name) > normalize(headName->Name)) {//если голова есть и знач меньше, головы 
		cur->nextName = headName;//то, переназначааем голову
		headName = cur;
	}
	else {
		Cell* temp = headName;//если же больше, то ищем место вставки
		while (temp->nextName != nullptr && normalize(temp->nextName->Name) > normalize(cur->Name)) {//цикл пока не дойдем до конца или не найдем место
			temp = temp->nextName;//просто идем по ячейкам
		}//temp элемент перед местом вставки
		cur->nextName = temp->nextName;//переназначаем ссылки
		temp->nextName = cur;
	}
}
#pragma endregion

#pragma region Delete
void deleteID(int key) {
	Cell* temp = headID;
	while (temp->nextID != nullptr && temp->nextID->recNum != key) {//цикл пока не дойдем до конца или не найдем эл-т
		temp = temp->nextID;//просто идем по ячейкам
	}//temp элемент перед удаляемым эл-ом
	temp->nextID = temp->nextID->nextID;
}

void deleteName(int key) {
	Cell* temp = headName;
	while (temp->nextName != nullptr && temp->nextName->recNum != key) {//цикл пока не дойдем до конца или не найдем эл-т
		temp = temp->nextName;//просто идем по ячейкам
	}//temp элемент перед удаляемым эл-ом
	temp->nextName = temp->nextName->nextName;
}

void deleteCell(int key) {
	if (key == 0) {
		head = head->next;
	}
	else {
		Cell* temp = head;//ищем удал элемент
		while (temp->next != nullptr && temp->next->recNum != key) {//цикл пока не дойдем до конца или не найдем эл-т
			temp = temp->next;//просто идем по ячейкам
		}//temp элемент перед удаляемым эл-ом
		temp->next = temp->next->next;//переназначаем ссылки
	}
	deleteID(key);
	deleteName(key);
}
#pragma endregion

#pragma region Search
int searchID(int id, Cell* cell) {
	if (cell->ID == id) {
		cout << "Студент найден: ";
		students[cell->recNum].print();
		return cell->recNum;
	}
	else if (cell->next) searchID(id, cell->next);
	else {
		cout << "Студент не наден(\n";
		return -1;
	}
}

int searchName(string name) {
	Cell* cell = head;
	while (cell) {
		name = normalize(name);
		if (normalize(cell->Name) == name) {
			cout << "Студент найден: ";
			students[cell->recNum].print();
			return cell->recNum;
		}
		cell = cell->next;
	}
	cout << "Студент не наден(\n";
	return -1;
}
#pragma endregion

void add() {
	students[studentsNumber].input();
	Cell* cur = new Cell;//создаем новую ячейку заполняем ее
	cur->ID = students[studentsNumber].id;
	cur->Name = students[studentsNumber].name;
	cur->recNum = studentsNumber;
	insertMain(cur);
	insertID(cur);
	insertName(cur);
	studentsNumber++;
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	//инициализация списка по исход данным
	for (int i = 0; i < studentsNumber; i++) {
		Cell* cur = new Cell;//создаем новую ячейку заполняем ее
		cur->ID = students[i].id;
		cur->Name = students[i].name;
		cur->recNum = i;
		insertMain(cur);
		insertID(cur);
		insertName(cur);
		prevv = cur;//теперь предыдущая ячейка - это только что созданная
	}

	bool exit = false;
	int choice = 0, subchoice;
	int id, key;
	string Name;

	while (!exit) {
		cout << "Главное меню:\n";
		cout << "1. Добавить студента\n";
		cout << "2. Вывести список студентов\n";
		cout << "3. Отсортировать список студентов\n";
		cout << "4. Поиск студента по ID\n5. Поиск студента по ФИО\n6. Выход\nВведите команду: ";
		cin >> choice;

		switch (choice) {
		case 1:
			add();
			break;
		case 2:
			print(head);
			break;
		case 3:
			cout << "Сортировка по возрастанию ID\n";
			printSortID(headID);
			cout << "\nСортировка по убыванию ФИО\n";
			printSortName(headName);
			break;
		case 4:
			cout << "Введите ID студента: ";
			cin >> id;
			key = searchID(id, head);
			if (key == -1) break;
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2) break;
			deleteCell(key);
			break;
		case 5:
			cout << "Введите ФИО студента: ";
			cin.ignore();
			getline(cin, Name);
			key = searchName(Name);
			if (key == -1) break;
			cout << "1. Удалить запись\n2. Назад\nВведите команду: ";
			cin >> subchoice;
			if (subchoice == 2) break;
			deleteCell(key);
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