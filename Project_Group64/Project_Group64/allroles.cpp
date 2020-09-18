#include "allroles.h"
#include"staff.h"

// user->type
// 0: student
// 1: lecturer
// 2: staff

User* login() {
	// user input username
	char iUsername[50];
	cout << endl << "Please input Username: ";
	cin.getline(iUsername, 50);
	// user input password
	char iPassword[50];
	cout << "Please input Password: ";
	cin.getline(iPassword, 50);
	return loginTextfile(iUsername, iPassword);
}

User* loginTextfile(char iUsername[], char iPassword[]) {
	ifstream fin;
	for (int i = 0; i < 3; ++i) {
		if (i == 0) fin.open("../database/account/student.txt");
		else if (i == 1) fin.open("../database/account/lecturer.txt");
		else if (i == 2) fin.open("../database/account/staff.txt");

		int counter;
		fin >> counter;
		fin.ignore(6464, '\n');

		// username and password from a file
		User* user = new User;
		user->type = i;
		for (int j = 0; j < counter; ++j) {
			fin.getline(user->extraInfo, 50, '\n');
			fin.getline(user->username, 50, '\n');
			fin.getline(user->password, 50, '\n');
			if (strcmp(iUsername, user->username) == 0 && strcmp(iPassword, user->password) == 0) {
				cout << "\n\nLOGIN SUCCESSFULLY! \n";
				cout << "======================================\n";
				system("pause");
				system("cls");
				fin.close();
				return user;
			}
			fin.ignore(6464, '\n');
		}
		delete user;
		fin.close();
	}
	return nullptr;
}

void viewProfile() 
{
	int t;
	cout << "You want to view profile of: \n";
	cout << "1. A student\n";
	cout << "2. A lecturer\n";
	cout << "3. A staff\n";
	cin >> t;
	cin.ignore(6464, '\n');

	if (t == 1) viewProfileStudent();
	if (t == 2) viewProfileLecturer();
	if (t == 3) viewProfileStaff();
}

void viewProfileStudent() {
	ifstream fin;
	fin.open("../database/studentlist.txt");

	int counter;
	fin >> counter;
	fin.ignore(6464, '\n');

	// user input id
	char iId[51];
	cout << "Please enter the Student's ID you want to view profile: ";
	cin.getline(iId, 51, '\n');

	// database information
	Student student;
	for (int i = 0; i < counter; ++i) {
		fin.getline(student.className, 51, '\n');
		fin.getline(student.id, 51, '\n');
		fin.getline(student.name, 51, '\n');
		fin.getline(student.gender, 51, '\n');
		fin.getline(student.dob, 51, '\n');
		fin.ignore(123, '\n');
		if (strcmp(iId, student.id) == 0) {
			cout << "Student's Class: " << student.className << "\n";
			cout << "Student's ID: " << student.id << "\n";
			cout << "Student's Name: " << student.name << "\n";
			cout << "Student's Gender: " << student.gender << "\n";
			cout << "Student's DOB: " << student.dob << "\n";
		}

	}
	fin.close();
}

void viewProfileLecturer() 
{
	char lecID[50], temp[50];
	cout << "Please enter Lecturer's Account you want to view profile: ";
	cin.getline(lecID, 50, '\n');
	lecturer lec;
	if (searchLecturer(lecID, lec))
	{
		cout << "Lecturer's ID: " << lec.lecturerID << endl;
		cout << "Lecturer's Name: "<< lec.lecturerName << endl;
		cout << "Student's Degree: " << lec.degree << endl;
		cout << "Student's Gender: " << lec.gender << endl;
	}
	else
	{
		cout << "Lecturer with Account " << lecID << " does not exist in database" << endl;
	}
	
}

void viewProfileStaff() 
{ 
	char StaffAcc[100];
	cout << "Please enter Academic Staff's Account you want to view profile: ";
	cin.getline(StaffAcc, 50, '\n');
	Staff staff;
	if (searchStaff(StaffAcc, staff))
	{
		cout << "Academic Staff's ID: " << staff.username << endl;
		cout << "Academic Staff's Name: " << staff.name << endl;
		cout << "Academic Staff's Gender: " << staff.gender << endl;
	}
	else
	{
		cout << "Academic Staff with Account " << StaffAcc << " does not exist in database" << endl;
	}
}

bool confirmPass(char password[]) {
	char iPassword[50];
	cin.getline(iPassword, 50);
	if (strcmp(iPassword, password) == 0) return true;
	return false;
}

void changePassword(User* user) 
{
	cout << endl << "Please type in your current password: ";
	if (confirmPass(user->password))
	{
		char newPassword[11];
		cout << "***New password: ";
		cin.getline(newPassword, 11);

		cout << "***Confirm new password: ";
		if (confirmPass(newPassword))
		{
			ifstream fin;
			char path[101];
			switch (user->type) {
			case 0:
				strcpy(path, "../database/account/student.txt");
				break;
			case 1:
				strcpy(path, "../database/account/lecturer.txt");
				break;
			case 2:
				strcpy(path, "../database/account/staff.txt");
				break;
			}
			fin.open(path);
			int counter;
			fin >> counter;
			fin.ignore(6464, '\n');

			User* userList = new User[counter];
			for (int i = 0; i < counter; ++i) {
				fin.getline(userList[i].extraInfo, 50, '\n');
				fin.getline(userList[i].username, 50, '\n');
				fin.getline(userList[i].password, 50, '\n');
				if (strcmp(userList[i].username, user->username) == 0 && strcmp(userList[i].password, user->password) == 0) {
					strcpy(user->password, newPassword);
					strcpy(userList[i].password, newPassword);
				}
				fin.ignore(6464, '\n');
			}
			fin.close();

			ofstream fout;
			fout.open(path);
			fout << counter << "\n";
			for (int i = 0; i < counter; ++i) {
				fout << userList[i].extraInfo << '\n';
				fout << userList[i].username << '\n';
				if (i == counter - 1) fout << userList[i].password ;
				else fout << userList[i].password << "\n\n";
			}
			fout.close();
			cout << endl << "CHANGE PASSWORD SUCCESSFULLY" << endl << endl;
		}
	}
}
