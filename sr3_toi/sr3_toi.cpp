#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

const int MAX_STUDENTS = 100;

bool sortById = true;

struct Student {
	int id;
	string name;

	void input() {
		cout << "������� ID ��������: ";
		cin >> id;

		cout << "������� ���: ";
		cin >> name;
	}

	void print() {
		cout << "ID: " << id
			<< " Name: " << name << endl;
	}

	void edit() {
		string newName;
		int newId;

		cout << "������� ID �������� (��� -1, ����� ��������): ";
		cin >> newId;
		if (newId != -1) {
			id = newId;
		}

		cout << "������� ��� (��� enter, ����� ��������): ";
		cin.ignore();
		getline(cin, newName);
		if (!newName.empty()) {
			name = newName;
		}
	}
};

int studentsNumber = 7;
Student students[MAX_STUDENTS] = {
	{4,"Ave",},
	{2,"Bib",},
	{3,"Cid",},
	{1,"Azi",},
	{7,"Dap"},
	{6,"Zon"},
	{5,"Lal"}
};

struct Cell {
	//int main;
	int RecNumID;
	int RecNumName;
	int RecNum;

	Cell* nextID = nullptr;
	Cell* nextName = nullptr;
	Cell* next = nullptr;
};

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

// ���������� ������ �� ID (����������� ����������)
void sortByID(Cell* cell) {
	if (cell==nullptr) return;

	bool swapped;
	do {
		swapped = false;
		Cell* current = cell;
		while (current->next) {
			if (students[current->RecNumID].id > students[current->next->RecNumID].id) {
				int recnum = current->RecNumID;
				current->RecNumID = current->next->RecNumID;
				current->next->RecNumID = recnum;
				swapped = true;
			}
			current = current->next;
		}
	} while (swapped);

	Cell* current = cell;
	while (current && current->next) {
		current->nextID = current->next;
		current = current->next;
	}
	if (current) current->nextID = nullptr; 
}

void sortByName(Cell* cell) {
	if (cell == nullptr) return;

	bool swapped;
	do {
		swapped = false;
		Cell* current = cell;
		while (current->next) {
			if (students[current->RecNumName].name > students[current->next->RecNumName].name) {
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
		current->nextName = current->next;
		current = current->next;
	}
	if (current) current->nextName = nullptr;
}

// ����� ������ �� nextID
void printByID(Cell* cell) {
	Cell* current = cell;
	while (current) {
		students[current->RecNumID].print();
		current = current->next;
	}
}

void printByName(Cell* cell) {
	Cell* current = cell;
	while (current) {
		students[current->RecNumName].print();
		current = current->nextName;
	}
}

void print(Cell* cell) {
	if (cell != nullptr) {
		students[cell->RecNum].print();
		print(cell->next);
	}
}

int searchByID(int id, Cell* cell) {
	if (students[cell->RecNum].id == id) return cell->RecNum;
	else if (cell->next == nullptr) return -1;
	else searchByID(id, cell->next);
}

int searchByName(string Name, Cell* cell) {
	Cell* current = cell;
	while (current->next != nullptr) {
		if (students[current->RecNum].name == Name) return current->RecNum;
		current = current->next;
	}
	return -1;
}

void Delete(int key, Cell*& cell) {
	//�������� �������, ������ �������������� ������. �������� ������� �������������� ������ ��. ��������� ������������ 0 � ��������.
	if (cell->next != nullptr) {
		if (cell->next->RecNum == key) {
			cell->nextID = cell->next->nextID;
			cell->nextName = cell->next->nextName;
			cell->next = cell->next->next;
		}
		Delete(key, cell->next);
	}
}

void Add() {
	//�������� � ������� ������, ��-� ���������, ���������� ���������� ��� ������ �� ����, ����-�� �� ���-��� � ��� ����� �������,
	students[studentsNumber].input();



	studentsNumber++;

}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	int id, ind;
	string Name;

	Cell* mainCell = Cover(0);
	

	sortByID(mainCell);
	printByID(mainCell);
	cout << endl;
	print(mainCell);

	cout << endl;
	sortByName(mainCell);
	printByName(mainCell);

	int key = searchByID(1, mainCell);
	students[key].print();

	key = searchByName("Bib", mainCell);
	students[key].print();
	cout << endl;
	if (key == 0) mainCell = mainCell->next;
	else Delete(key, mainCell);
	print(mainCell);

	bool exit = false;
	int choice = 0, subchoice = 0;
	int number = 0;

	/*while (!exit) {
		cout << "������� ����:\n";
		cout << "1. �������� ������ ���������\n";
		cout << "2. ������� ������ ���������\n";
		cout << "3. ������������� ������ ���������\n";
		cout << "4. ����� �������� �� ID\n5. ����� �������� �� ���\n������� �������: ";
		cin >> choice;

		switch (choice) {
		case 1:
			break;
		case 2:
			print(mainCell);
			break;
		case 3:
			cout << "1. ����������� �� ����������� ID\n2. ����������� �� �������� ���\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 1) {
				printByID(mainCell);
			}
			else {
				PrintTreeDecrease(RootName);
			}
			rec = MAX_STUDENTS;
			break;
		case 4:
			if (studentsNumber == 0) {
				cout << "� ������ ��� ���������: ";
				break;
			}
			cout << "������� ID ��������: ";
			cin >> id;
			ind = SearchID(RootID, id);
			if (ind == -1) break;
			cout << "2. ������� ������\n3. �����\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 3)break;
			DEL(RootID, id, ind);
			break;
		case 5:
			exit = true;
			break;
		default:
			cout << "������������ ����. ���������� ���)\n";
			break;
		}
	}*/
}