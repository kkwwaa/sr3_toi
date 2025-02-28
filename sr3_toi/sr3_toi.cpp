#include <iostream>
#include <string>
#include <Windows.h>
#include <set>

using namespace std;

struct Student {
	int id;
	string name;  // ��� � ����� ������
	string submissionDate;
	string reviewDate;
	int gradeReport;
	int gradeDefense;
	string reviewer;
	string seminarist;

	void input() {
		cout << "������� ID ��������: ";
		cin >> id;
		cin.ignore();  // ���������� \n ����� getline
		cout << "������� ���: ";
		getline(cin, name);
		cout << "������� ���� ����� (��.��.����): ";
		cin >> submissionDate;
		cout << "������� ���� �������� (��.��.����): ";
		cin >> reviewDate;
		cout << "������� ������ �� �����: ";
		cin >> gradeReport;
		cout << "������� ������ �� ������: ";
		cin >> gradeDefense;
		cin.ignore();
		cout << "������� ������� ������������: ";
		getline(cin, reviewer);
		cout << "������� ������� �����������: ";
		getline(cin, seminarist);
	}


	void print() {
		cout << "ID: " << id << ", ���: " << name
			<< ", ���� �����: " << submissionDate
			<< ", ���� ��������: " << reviewDate
			<< ", ������ �� �����: " << gradeReport
			<< ", ������ �� ������: " << gradeDefense
			<< ", �����������: " << reviewer
			<< ", ����������: " << seminarist << endl;
	}
};

#pragma region Global
const int MAX_STUDENTS = 100;
int studentsNumber = 10;
Student students[MAX_STUDENTS] = {
	{3, "�������� ��������� ���������", "27.11.2024", "03.12.2024", 6, 9, "���������", "�����"},
	{5, "����� ����� ����������", "01.12.2024", "10.12.2024", 4, 6, "���������", "���������"},
	{9, "��������� ������ ��������", "01.12.2024", "10.12.2024", 6, 8, "�����", "���������"},
	{10, "������� ������ �������", "01.12.2024", "10.12.2024", 0, 0, "���������", "�����"},
	{1, "������ ������� ����������", "25.11.2024", "30.11.2024", 7, 9, "���������", "���������"},
	{8, "�������� ������� ����������", "25.11.2024", "05.12.2024", 8, 8, "�����", "���������"},
	{2, "������� ������� �������������", "25.11.2024", "30.11.2024", 5, 8, "���������", "�����"},
	{6, "������� ����� ������������", "25.11.2024", "01.12.2024", 8, 8, "�����", "���������"},
	{4, "������ ����� �������", "28.11.2024", "03.12.2024", 2, 9, "���������", "���������"},
	{7, "����� ���� ������������", "25.11.2024", "01.12.2024", 7, 7, "�����", "���������"}
};

string normalize(const string& str) {
	string result = "";
	for (size_t i = 0; i < str.length(); i++) {
		char ch = str[i];

		// �������� � ������� �������� �������
		if (ch >= '�' && ch <= '�') {
			ch = ch + ('a' - 'A');
		}

		// ���������� �������
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
	if (prevv == nullptr) {//���� ������ ������
		head = cur; //��������� ������� ������� ������� ��������� ������
	}
	else {
		prevv->next = cur;//���� �� ������, �� ����������� ��������� ��������� �������

	}
	prevv = cur;
}

void insertID(Cell* cur) {
	if (headID == nullptr) {//���� ������ �� �� ���������
		headID = cur; //���������
	}
	else if (cur->ID < headID->ID) {//���� ������ ���� � ���� ������, ������ 
		cur->nextID = headID;//��, �������������� ������
		headID = cur;
	}
	else {
		Cell* temp = headID;//���� �� ������, �� ���� ����� �������
		while (temp->nextID != nullptr && temp->nextID->ID < cur->ID) {//���� ���� �� ������ �� ����� ��� �� ������ �����
			temp = temp->nextID;//������ ���� �� �������
		}//temp ������� ����� ������ �������
		cur->nextID = temp->nextID;//������������� ������
		temp->nextID = cur;
	}
}

void insertName(Cell* cur) {
	if (headName == nullptr) {//���� ������ ��� �� ���������
		headName = cur; //���������
	}
	else if (normalize(cur->Name) > normalize(headName->Name)) {//���� ������ ���� � ���� ������, ������ 
		cur->nextName = headName;//��, �������������� ������
		headName = cur;
	}
	else {
		Cell* temp = headName;//���� �� ������, �� ���� ����� �������
		while (temp->nextName != nullptr && normalize(temp->nextName->Name) > normalize(cur->Name)) {//���� ���� �� ������ �� ����� ��� �� ������ �����
			temp = temp->nextName;//������ ���� �� �������
		}//temp ������� ����� ������ �������
		cur->nextName = temp->nextName;//������������� ������
		temp->nextName = cur;
	}
}
#pragma endregion

#pragma region Delete
void deleteID(int key) {
	Cell* temp = headID;
	while (temp->nextID != nullptr && temp->nextID->recNum != key) {//���� ���� �� ������ �� ����� ��� �� ������ ��-�
		temp = temp->nextID;//������ ���� �� �������
	}//temp ������� ����� ��������� ��-��
	temp->nextID = temp->nextID->nextID;
}

void deleteName(int key) {
	Cell* temp = headName;
	while (temp->nextName != nullptr && temp->nextName->recNum != key) {//���� ���� �� ������ �� ����� ��� �� ������ ��-�
		temp = temp->nextName;//������ ���� �� �������
	}//temp ������� ����� ��������� ��-��
	temp->nextName = temp->nextName->nextName;
}

void deleteCell(int key) {
	if (key == 0) {
		head = head->next;
	}
	else {
		Cell* temp = head;//���� ���� �������
		while (temp->next != nullptr && temp->next->recNum != key) {//���� ���� �� ������ �� ����� ��� �� ������ ��-�
			temp = temp->next;//������ ���� �� �������
		}//temp ������� ����� ��������� ��-��
		temp->next = temp->next->next;//������������� ������
	}
	deleteID(key);
	deleteName(key);
}
#pragma endregion

#pragma region Search
int searchID(int id, Cell* cell) {
	if (cell->ID == id) {
		cout << "������� ������: ";
		students[cell->recNum].print();
		return cell->recNum;
	}
	else if (cell->next) searchID(id, cell->next);
	else {
		cout << "������� �� �����(\n";
		return -1;
	}
}

int searchName(string name) {
	Cell* cell = head;
	while (cell) {
		name = normalize(name);
		if (normalize(cell->Name) == name) {
			cout << "������� ������: ";
			students[cell->recNum].print();
			return cell->recNum;
		}
		cell = cell->next;
	}
	cout << "������� �� �����(\n";
	return -1;
}
#pragma endregion

void add() {
	students[studentsNumber].input();
	Cell* cur = new Cell;//������� ����� ������ ��������� ��
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

	//������������� ������ �� ����� ������
	for (int i = 0; i < studentsNumber; i++) {
		Cell* cur = new Cell;//������� ����� ������ ��������� ��
		cur->ID = students[i].id;
		cur->Name = students[i].name;
		cur->recNum = i;
		insertMain(cur);
		insertID(cur);
		insertName(cur);
		prevv = cur;//������ ���������� ������ - ��� ������ ��� ���������
	}

	bool exit = false;
	int choice = 0, subchoice;
	int id, key;
	string Name;

	while (!exit) {
		cout << "������� ����:\n";
		cout << "1. �������� ��������\n";
		cout << "2. ������� ������ ���������\n";
		cout << "3. ������������� ������ ���������\n";
		cout << "4. ����� �������� �� ID\n5. ����� �������� �� ���\n6. �����\n������� �������: ";
		cin >> choice;

		switch (choice) {
		case 1:
			add();
			break;
		case 2:
			print(head);
			break;
		case 3:
			cout << "���������� �� ����������� ID\n";
			printSortID(headID);
			cout << "\n���������� �� �������� ���\n";
			printSortName(headName);
			break;
		case 4:
			cout << "������� ID ��������: ";
			cin >> id;
			key = searchID(id, head);
			if (key == -1) break;
			cout << "1. ������� ������\n2. �����\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 2) break;
			deleteCell(key);
			break;
		case 5:
			cout << "������� ��� ��������: ";
			cin.ignore();
			getline(cin, Name);
			key = searchName(Name);
			if (key == -1) break;
			cout << "1. ������� ������\n2. �����\n������� �������: ";
			cin >> subchoice;
			if (subchoice == 2) break;
			deleteCell(key);
			break;
		case 6:
			exit = true;
			break;
		default:
			cout << "������������ ����. ���������� ���)\n";
			break;
		}
	}
}