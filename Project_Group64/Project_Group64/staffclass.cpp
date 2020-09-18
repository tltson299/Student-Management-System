#include "staffclass.h"

string inputClassName(char action[]) {
	char className[51] = "";
	cout << "Please type in Class name to " << action << ": ";
	cin.getline(className, 51);

	return className;
}

void importClassCsv() {
	string path;
	cout << "Please type in the csv file you want to import: ";
	getline(cin, path);

	path = "../database/importCSV/" + path + ".csv";

	string className;
	cout << "Please type in the class name you want to import to: ";
	getline(cin, className);

	if (className.length() == 0)
	{
		return;
	}

	ifstream fin(path);
	if (!fin.is_open()) {
		cout << "Cannot open file" << endl;
		return;
	}

	filesystem::create_directories("../database/class/" + className);
	if (!PathExist("../database/class/class.txt")) {
		ofstream fout("../database/class/class.txt");
		fout << 1 << "\n";
		fout << className;
		fout.close();
	}
	else {
		bool update = true;
		ifstream fin("../database/class/class.txt");
		if (!fin.is_open()) {
			cout << "Error manipulating file\n";
			return;
		}
		int counter, count;
		fin >> counter;
		count = counter;
		fin.ignore(123, '\n');
		string* classList = new string[counter];

		bool* skip = new bool[counter];
		for (int i = 0; i < counter; ++i) {
			skip[i] = false;
			getline(fin, classList[i], '\n');
			string each = "../database/class/" + classList[i];
			if (!PathExist(each.c_str())) {
				skip[i] = true;
				--count;
			}
			if (className.compare(classList[i]) == 0) {
				update = false;
			}
		}
		fin.close();

		ofstream fout("../database/class/class.txt");
		fout << count << "\n";
		for (int i = 0; i < counter; ++i) {
			if (skip[i]) continue;
			fout << classList[i] << "\n";
		}
		fout.close();

		delete[] skip;
		if (update) {
			fout.open("../database/class/class.txt");
			fout << counter + 1 << "\n";
			for (int i = 0; i < counter; ++i) {
				fout << classList[i] << "\n";
			}
			fout << className;
			fout.close();
		}
		delete[] classList;
	}

	ofstream fout("../database/class/" + className + "/student.txt");

	int counter = 0;
	counter = count(istreambuf_iterator<char>(fin),
		istreambuf_iterator<char>(), '\n');
	fout << counter << "\n";
	fin.close();

	fin.open(path);
	fin.ignore(1234, '\n');
	student student;
	while (fin.good()) {
		fin.getline(student.studentID, 51, ',');
		fin.getline(student.studentName, 51, ',');
		fin.getline(student.gender, 51, ',');
		fin >> student.birthday.yyyy >> student.birthday.mm >> student.birthday.dd;
		fin.ignore(123, '\n');

		// gia su cac file csv dung 100% format va khong ai trung id
		fout << student.studentID << "\n" << student.studentName << "\n" << student.gender << "\n" << student.birthday.yyyy << " " << student.birthday.mm << " " << student.birthday.dd;
		if (counter != 1) fout << "\n\n";
		--counter;
	}

	fout.close();
	fin.close();

	if (!PathExist("../database/account/student.txt"))initClassAccount(className);
	else createClassAccount(className);

	if (!PathExist("../database/studentlist.txt")) initStudentList(className);
	else createStudentList(className);

	cout << endl << "IMPORT STUDENTS SUCCESSFULLY" << endl << endl;
}

void initClassAccount(string className) {
	int counter, count;
	ifstream fin("../database/class/" + className + "/student.txt");
	if (!fin.is_open()) {
		cout << "Error reading student list of a class \n";
		return;
	}
	fin >> counter;
	count = counter;
	fin.ignore(123, '\n');

	ofstream fout("../database/account/student.txt");
	fout << counter << "\n";
	student student;
	for (int i = 0; i < counter; ++i) {
		fin.getline(student.studentID, 51, '\n');
		fin.getline(student.studentName, 51, '\n');
		fin.getline(student.gender, 51, '\n');
		fin >> student.birthday.yyyy >> student.birthday.mm >> student.birthday.dd;
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fout << className << "\n" << student.studentID << "\n" << student.birthday.yyyy << student.birthday.mm << student.birthday.dd;
		if (count != 1) fout << "\n\n";
		--count;
	}
	fin.close();
	fout.close();
}

void createClassAccount(string className) {
	ifstream fin("../database/account/student.txt");
	if (!fin.is_open()) {
		cout << "CREATE ACCOUNT FAILED" << endl;
		return;
	}
	int counter, total;
	fin >> counter;
	total = counter;
	fin.ignore(123, '\n');

	User* userlist = new User[counter];
	for (int i = 0; i < counter; ++i) {
		fin.getline(userlist[i].extraInfo, 51, '\n');
		if (strcmp(userlist[i].extraInfo, className.c_str()) == 0) --total;
		fin.getline(userlist[i].username, 51, '\n');
		fin.getline(userlist[i].password, 51, '\n');
		fin.ignore(1234, '\n');
	}
	fin.close();

	fin.open("../database/class/" + className + "/student.txt");
	if (!fin.is_open()) {
		cout << "CREATE ACCOUNT FAILED" << endl;
		return;
	}
	int fcounter;
	fin >> fcounter;
	total += fcounter;
	fin.ignore(123, '\n');
	User* appUserlist = new User[fcounter];
	string dob;
	for (int i = 0; i < fcounter; ++i) {
		fin.getline(appUserlist[i].username, 51, '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		getline(fin, dob);
		fin.ignore(123, '\n');
		dob.erase(remove_if(dob.begin(), dob.end(), isspace), dob.end());
		strcpy_s(appUserlist[i].password, dob.c_str());
	}
	fin.close();

	ofstream fout("../database/account/student.txt");
	fout << total << "\n";
	for (int i = 0; i < counter; ++i) {
		if (strcmp(userlist[i].extraInfo, className.c_str()) == 0) continue;
		fout << userlist[i].extraInfo << "\n";
		fout << userlist[i].username << "\n";
		fout << userlist[i].password << "\n\n";
	}
	for (int i = 0; i < fcounter; ++i) {
		fout << className << "\n";
		fout << appUserlist[i].username << "\n";
		fout << appUserlist[i].password;
		if (i != fcounter - 1) fout << "\n\n";
	}
	fout.close();
	delete[] userlist;
	delete[] appUserlist;
}

void initStudentList(string className) {
	int counter, count;
	ifstream fin("../database/class/" + className + "/student.txt");
	fin >> counter;
	count = counter;
	fin.ignore(123, '\n');

	ofstream fout("../database/studentlist.txt");
	fout << counter << "\n";
	student student;
	for (int i = 0; i < counter; ++i) {
		fin.getline(student.studentID, 51, '\n');
		fin.getline(student.studentName, 51, '\n');
		fin.getline(student.gender, 51, '\n');
		fin >> student.birthday.yyyy >> student.birthday.mm >> student.birthday.dd;
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fout << className << "\n" << student.studentID << "\n" << student.studentName << "\n" << student.gender << "\n" << student.birthday.yyyy << " " << student.birthday.mm << " " << student.birthday.dd;
		if (count != 1) fout << "\n\n";
		--count;
	}
	fin.close();
	fout.close();
}

void createStudentList(string className) {
	ifstream fin("../database/studentlist.txt");
	if (!fin.is_open()) {
		cout << "CREATE STUDENT LIST FAILED" << endl;
		return;
	}
	int counter, total;
	fin >> counter;
	total = counter;
	fin.ignore(123, '\n');

	student* studentlist = new student[counter];

	for (int i = 0; i < counter; ++i) {
		fin.getline(studentlist[i].className, 51, '\n');
		if (strcmp(studentlist[i].className, className.c_str()) == 0) --total;
		fin.getline(studentlist[i].studentID, 51, '\n');
		fin.getline(studentlist[i].studentName, 51, '\n');
		fin.getline(studentlist[i].gender, 51, '\n');
		fin >> studentlist[i].birthday.yyyy >> studentlist[i].birthday.mm >> studentlist[i].birthday.dd;
		fin.ignore(1234, '\n');
		fin.ignore(1234, '\n');
	}
	fin.close();
	fin.open("../database/class/" + className + "/student.txt");
	int fcounter;
	fin >> fcounter;
	total += fcounter;
	fin.ignore(123, '\n');
	student* appStudentlist = new student[fcounter];
	string dob;
	for (int i = 0; i < fcounter; ++i) {
		fin.getline(appStudentlist[i].studentID, 51, '\n');
		fin.getline(appStudentlist[i].studentName, 51, '\n');
		fin.getline(appStudentlist[i].gender, 51, '\n');
		fin >> appStudentlist[i].birthday.yyyy >> appStudentlist[i].birthday.mm >> appStudentlist[i].birthday.dd;
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
	}
	fin.close();

	ofstream fout("../database/studentlist.txt");
	fout << total << "\n";
	for (int i = 0; i < counter; ++i) {
		if (strcmp(studentlist[i].className, className.c_str()) == 0) continue;
		fout << studentlist[i].className << "\n";
		fout << studentlist[i].studentID << "\n";
		fout << studentlist[i].studentName << "\n";
		fout << studentlist[i].gender << "\n";
		fout << studentlist[i].birthday.yyyy << " " << studentlist[i].birthday.mm << " " << studentlist[i].birthday.dd << "\n\n";
	}
	for (int i = 0; i < fcounter; ++i) {
		fout << className << "\n";
		fout << appStudentlist[i].studentID << "\n";
		fout << appStudentlist[i].studentName << "\n";
		fout << appStudentlist[i].gender << "\n";
		fout << appStudentlist[i].birthday.yyyy << " " << appStudentlist[i].birthday.mm << " " << appStudentlist[i].birthday.dd;
		if (i != fcounter - 1) fout << "\n\n";
	}
	fout.close();
	delete[] studentlist;
	delete[] appStudentlist;
}

void addStudentToClass() {
	char action[] = "add Student";
	string className = inputClassName(action);

	string path = "../database/class/" + className + "/student.txt";

	if (!PathExist(path.c_str())) {
		cout << "NO DATA FOUND FOR THIS CLASS" << endl;
		return;
	}

	student newStudent;
	if (!inputStudentInfo(newStudent)) return;
	strcpy_s(newStudent.className, className.c_str());

	if (checkStudentIDExist(string(newStudent.studentID))) {
		cout << "ID IS TAKEN" << endl;
		return;
	}

	addStudentClass(newStudent, path, className);
	cout << endl << "ADD STUDENT SUCCESSFULLY" << endl << endl;
}

bool inputStudentInfo(student& newStudent) {
	cout << "Please type in Student's ID: ";
	cin.getline(newStudent.studentID, 51);
	if (checkStudentIDExist(string(newStudent.studentID))) {
		cout << "ID IS TAKEN" << endl;
		return false;
	}
	cout << "Please type in Student's Name: ";
	cin.getline(newStudent.studentName, 51);
	cout << "Please type in Student's Gender: ";
	cin.getline(newStudent.gender, 51);
	cout << "Please type in Student's DOB: ";
	cin >> newStudent.birthday.yyyy >> newStudent.birthday.mm >> newStudent.birthday.dd;
	cin.ignore(1234, '\n');
	return true;
}

void addStudentClass(student newStudent, string path, string className) {
	ifstream fin(path);
	if (!fin.is_open()) {
		cout << "Cannot open file" << endl;
		return;
	}
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');

	student* studentlist = new student[counter];
	for (int i = 0; i < counter; ++i) {
		fin.getline(studentlist[i].studentID, 51, '\n');
		fin.getline(studentlist[i].studentName, 51, '\n');
		fin.getline(studentlist[i].gender, 51, '\n');
		fin >> studentlist[i].birthday.yyyy >> studentlist[i].birthday.mm >> studentlist[i].birthday.dd;
		fin.ignore(12334, '\n');
		fin.ignore(12334, '\n');
	}
	fin.close();

	for (int i = 0; i < counter; ++i) {
		strcpy_s(studentlist[i].className, className.c_str());
	}

	student* newStudentlist = new student[counter + 1];
	for (int i = 0; i < counter; ++i) {
		newStudentlist[i] = studentlist[i];
	}
	newStudentlist[counter] = newStudent;

	ofstream fout(path);
	fout << counter + 1 << "\n";
	for (int i = 0; i < counter + 1; ++i) {
		fout << newStudentlist[i].studentID << "\n";
		fout << newStudentlist[i].studentName << "\n";
		fout << newStudentlist[i].gender << "\n";
		fout << newStudentlist[i].birthday.yyyy << " " << newStudentlist[i].birthday.mm << " " << newStudentlist[i].birthday.dd;
		if (i != counter) fout << "\n\n";
	}
	fout.close();
	createStudentList(newStudent.className);
	// updateClassAccount
	updateAddStudentAccount(newStudent);

}

void updateAddStudentAccount(student newStudent) {
	ifstream fin("../database/account/student.txt");
	int counter;
	fin >> counter;
	fin.ignore(2134, '\n');

	User* userlist = new User[counter];
	for (int i = 0; i < counter; ++i) {
		fin.getline(userlist[i].extraInfo, 51, '\n');
		fin.getline(userlist[i].username, 51, '\n');
		fin.getline(userlist[i].password, 51, '\n');
		fin.ignore(1234, '\n');
	}
	fin.close();

	ofstream fout("../database/account/student.txt");
	fout << counter + 1 << "\n";
	for (int i = 0; i < counter; ++i) {
		fout << userlist[i].extraInfo << "\n";
		fout << userlist[i].username << "\n";
		fout << userlist[i].password << "\n\n";
	}
	fout << newStudent.className << "\n";
	fout << newStudent.studentID << "\n";
	fout << newStudent.birthday.yyyy << newStudent.birthday.mm << newStudent.birthday.dd;
	fout.close();
	delete[] userlist;
}

bool checkStudentIDExist(string id) {
	ifstream fin("../database/studentlist.txt");
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	student* studentlist = new student[counter];

	for (int i = 0; i < counter; ++i) {
		fin.getline(studentlist[i].className, 51, '\n');
		fin.getline(studentlist[i].studentID, 51, '\n');
		fin.getline(studentlist[i].studentName, 51, '\n');
		fin.getline(studentlist[i].gender, 51, '\n');
		fin >> studentlist[i].birthday.yyyy >> studentlist[i].birthday.mm >> studentlist[i].birthday.dd;
		fin.ignore(12345, '\n');
		fin.ignore(12345, '\n');
	}

	for (int i = 0; i < counter; ++i) {
		if (id.compare(studentlist[i].studentID) == 0) {
			delete[] studentlist;
			fin.close();
			return true;
		}
	}
	delete[] studentlist;
	fin.close();
	return false;
}

void editStudent() {
	char action[] = "edit Student";
	string className = inputClassName(action);
	string path = "../database/class/" + className + "/student.txt";

	char id[51];
	cout << "Please type in the Student's ID to edit: ";
	cin.getline(id, 51);

	int edited = -1;

	ifstream fin(path);
	if (!fin.is_open()) {
		cout << "Cannot open file" << endl;
		return;
	}
	else {
		int counter;
		fin >> counter;
		fin.ignore(1234, '\n');

		string tempID;
		student* studentlist = new student[counter];
		for (int i = 0; i < counter; ++i) {
			fin.getline(studentlist[i].studentID, 51, '\n');
			fin.getline(studentlist[i].studentName, 51, '\n');
			fin.getline(studentlist[i].gender, 51, '\n');
			fin >> studentlist[i].birthday.yyyy >> studentlist[i].birthday.mm >> studentlist[i].birthday.dd;
			fin.ignore(12334, '\n');
			fin.ignore(12334, '\n');
			if (strcmp(studentlist[i].studentID, id) == 0) {
				cout << "You want to edit: \n";
				cout << "Student's id: " << studentlist[i].studentID << "\n";
				cout << "Student's name: " << studentlist[i].studentName << "\n";
				cout << "Student's gender: " << studentlist[i].gender << "\n";
				cout << "Student's DOB: " << studentlist[i].birthday.yyyy << " " << studentlist[i].birthday.mm << " " << studentlist[i].birthday.dd << "\n";
				cout << "-------------------------------------------" << "\n\n";

				cout << "Please type in Student's ID: ";
				getline(cin, tempID);
				if (tempID.compare(studentlist[i].studentID) != 0 && checkStudentIDExist(tempID)) {
					cout << "ID is taken" << endl;
					fin.close();
					delete[] studentlist;
					return;
				}
				else {
					edited = i;
					if (tempID.compare(studentlist[edited].studentID) != 0)
						updateEditStudentAccount(tempID, studentlist[edited].studentID);
				}
				// edit student id in <Course>/student.txt
				cout << "Please type in Student's Name: ";
				cin.getline(studentlist[i].studentName, 51);
				// edit student id in <Course>/student.txt
				cout << "Please type in Student's Gender: ";
				cin.getline(studentlist[i].gender, 51);
				// edit student id in <Course>/student.txt
				cout << "Please type in Student's DOB: ";
				cin >> studentlist[i].birthday.yyyy >> studentlist[i].birthday.mm >> studentlist[i].birthday.dd;
				student newStudent;
				strcpy_s(newStudent.studentID, tempID.c_str());
				strcpy_s(newStudent.studentName, studentlist[i].studentName);
				strcpy_s(newStudent.gender, studentlist[i].gender);
				newStudent.birthday.yyyy = studentlist[i].birthday.yyyy;
				newStudent.birthday.mm = studentlist[i].birthday.mm;
				newStudent.birthday.dd = studentlist[i].birthday.dd;
				editStudentFromCourse(newStudent, studentlist[i].studentID);
				// edit student id in <Course>/student.txt
				cin.ignore(1234, '\n');
				strcpy_s(studentlist[i].studentID, tempID.c_str());
			}
		}
		fin.close();
		if (edited == -1) {
			cout << "Not found! \n";
			delete[] studentlist;
			return;
		}
		ofstream fout(path);
		fout << counter << "\n";
		for (int i = 0; i < counter; ++i) {
			fout << studentlist[i].studentID << '\n';
			fout << studentlist[i].studentName << '\n';
			fout << studentlist[i].gender << '\n';
			fout << studentlist[i].birthday.yyyy << " " << studentlist[i].birthday.mm << " " << studentlist[i].birthday.dd;
			if (i != counter - 1) fout << "\n\n";
		}
		fout.close();
		createStudentList(className);
		delete[] studentlist;
	}
	cout << endl << "EDIT SUCCESSFULLY" << endl << endl;
}

void updateEditStudentAccount(string username, string oldId) {
	ifstream fin("../database/account/student.txt");
	int counter;
	fin >> counter;
	fin.ignore(12345, '\n');

	User* userlist = new User[counter];
	for (int i = 0; i < counter; ++i) {
		fin.getline(userlist[i].extraInfo, 51, '\n');
		fin.getline(userlist[i].username, 51, '\n');
		fin.getline(userlist[i].password, 51, '\n');
		fin.ignore(1234, '\n');
	}

	fin.close();
	ofstream fout("../database/account/student.txt");
	fout << counter << "\n";
	for (int i = 0; i < counter; ++i) {
		if (oldId.compare(userlist[i].username)==0) {
			fout << userlist[i].extraInfo << '\n';
			fout << username << "\n";
			fout << userlist[i].password;
		}
		else {
			fout << userlist[i].extraInfo << '\n';
			fout << userlist[i].username << '\n';
			fout << userlist[i].password;
		}
		if (i != counter - 1) fout << "\n\n";
	}
	fout.close();
	delete[] userlist;
}

void removeStudentFromClass() {
	char action[] = "remove Student";
	string className = inputClassName(action);

	char id[51];
	cout << "Please type in Student's ID to remove: ";
	cin.getline(id, 51);

	string path = "../database/class/" + className + "/student.txt";
	if (!PathExist(path.c_str())) {
		cout << "Path not found! \n";
		return;
	}

	ifstream fin(path);
	if (!fin.is_open()) {
		cout << "Cannot open file \n";
		return;
	}

	removeStudent(id, path, className, removeStudentFromCourse, false);
}

void removeStudentFromCourse(string id, string oldClass) {
	ifstream fin("../database/acaye/acaye.txt");
	if (!fin.is_open()) {
		return;
	}
	int counter;
	fin >> counter;
	fin.ignore(1235, '\n');

	for (int i = 0; i < counter; ++i) {
		string acaye;
		getline(fin, acaye);
		ifstream ffin("../database/acaye/" + acaye + "/semester.txt");
		int fcounter;
		ffin >> fcounter;
		ffin.ignore(1235, '\n');

		for (int j = 0; j < fcounter; ++j) {
			string semester;
			getline(ffin, semester);
			ifstream fffin("../database/acaye/" + acaye + "/" + semester + "/student_Course.txt");

			string tempID;
			int ffcounter;
			string studentCourse;
			while (fffin.good()) {
				getline(fffin, tempID);
				if (id.compare(tempID) == 0) {
					fffin.ignore(1234, '\n');
					fffin >> ffcounter;
					fffin.ignore(1234, '\n');
					for (int k = 0; k < ffcounter; ++k) {
						getline(fffin, studentCourse);
						ifstream ffffin("../database/acaye/" + acaye + "/" + semester + "/" + studentCourse + "/student.txt");
						// "../database/acaye/2018-2019/fall/cm_191919191919"
						cout << id << " removed from " << studentCourse << "\n";
						int fffcounter;
						ffffin >> fffcounter;
						ffffin.ignore(1234, '\n');
						student* studentlist = new student[fffcounter];
						for (int l = 0; l < fffcounter; ++l) {
							ffffin.getline(studentlist[l].studentID, 51, '\n');
							ffffin.getline(studentlist[l].studentName, 51, '\n');
							ffffin.getline(studentlist[l].gender, 51, '\n');
							ffffin >> studentlist[l].birthday.yyyy >> studentlist[l].birthday.mm >> studentlist[l].birthday.dd;
							ffffin.ignore(1235, '\n');
							ffffin.ignore(1235, '\n');
						}
						ffffin.close();

						removeFromCheckin(id, "../database/acaye/" + acaye + "/" + semester + "/" + studentCourse + "/checkin.txt");

						ofstream fout("../database/acaye/" + acaye + "/" + semester + "/" + studentCourse + "/student.txt");
						fout << fffcounter - 1 << "\n";
						for (int l = 0; l < fffcounter; ++l) {
							if (id.compare(studentlist[l].studentID) == 0) continue;
							fout << studentlist[l].studentID << '\n';
							fout << studentlist[l].studentName << '\n';
							fout << studentlist[l].gender << '\n';
							fout << studentlist[l].birthday.yyyy << " " << studentlist[l].birthday.mm << " " << studentlist[l].birthday.dd;
							if (l != fffcounter - 1) fout << "\n\n";
							else fout << "\n";
						}
						fout.close();
						delete[] studentlist;
						string path = "../database/acaye/" + acaye + "/" + semester + "/" + studentCourse;
						updateStudentinAttendance((char*)path.c_str());
					}
				}
			}

			fffin.close();

			//
			string path = "../database/acaye/" + acaye + "/" + semester + "/student_Course.txt";
			removeStudentInStuC(id, path);
		}

		ffin.close();
	}
	fin.close();

}

void removeFromCheckin(string id, string path) {
	ifstream fin(path);
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	fin.ignore(1234, '\n');
	Checkin* studentlist = new Checkin[counter];
	for (int i = 0; i < counter; ++i) {
		getline(fin, studentlist[i].id, ';');
		getline(fin, studentlist[i].name, ';');
		for(int j = 0; j < 10; ++j)
		getline(fin, studentlist[i].day[j], ';');
		getline(fin, studentlist[i].day[10]);
	}
	fin.close();
	ofstream fout(path);
	fout << counter - 1 << "\n";
	fout << "id,name,day 1,day 2,day 3,day 4,day 5,day 6,day 7,day 8,day 9,day 10,day 11\n";
	for (int i = 0; i < counter; ++i) {
		if (id.compare(studentlist[i].id) == 0) continue;
		fout << studentlist[i].id << ';';
		fout << studentlist[i].name << ';';
		for (int j = 0; j < 10; ++j)
			fout << studentlist[i].day[j] << ';';
		fout << studentlist[i].day[10] << "\n";
	}
	fout.close();
}

void editStudentFromCourse(student newStudent, string id) {
	ifstream pAca("../database/acaye/acaye.txt");
	if (!pAca.is_open()) 
	{
		return;
	}
	int counter;
	pAca >> counter;
	pAca.ignore(1235, '\n');

	for (int i = 0; i < counter; ++i) {
		string acaye;
		getline(pAca, acaye);

		ifstream pSem("../database/acaye/" + acaye + "/semester.txt");
		int fcounter;
		pSem >> fcounter;
		pSem.ignore(1235, '\n');

		for (int j = 0; j < fcounter; ++j) {
			string semester;
			getline(pSem, semester);
			ifstream fffin("../database/acaye/" + acaye + "/" + semester + "/student_Course.txt");
			int ffcounter;
			fffin >> ffcounter;
			fffin.ignore(123, '\n');
			StudentCourse* studentcl = new StudentCourse[ffcounter];

			for (int k = 0; k < ffcounter; ++k) {
				getline(fffin, studentcl[k].id);
				getline(fffin, studentcl[k].className);
				fffin >> studentcl[k].counter;
				fffin.ignore(123, '\n');
				studentcl[k].sub = new string[studentcl[k].counter];
				for (int l = 0; l < studentcl[k].counter; ++l) {
					getline(fffin, studentcl[k].sub[l]);
				}
				fffin.ignore(123, '\n');
				if(id.compare(studentcl[k].id) == 0)
				for (int l = 0; l < studentcl[k].counter; ++l) {
					ifstream ffffin("../database/acaye/" + acaye + "/" + semester + "/" + studentcl[k].sub[l] + "/student.txt");
					int anotherCounter;
					ffffin >> anotherCounter;
					ffffin.ignore(1234, '\n');
					student* studentlist = new student[anotherCounter];
					for (int m = 0; m < anotherCounter; ++m) {
						ffffin.getline(studentlist[m].studentID, 51);
						
						ffffin.getline(studentlist[m].studentName, 51);
						ffffin.getline(studentlist[m].gender, 51);
						ffffin >> studentlist[m].birthday.yyyy >> studentlist[m].birthday.mm >> studentlist[m].birthday.dd;
						ffffin.ignore(1234, '\n');
						ffffin.ignore(1234, '\n');
						if (id.compare(studentlist[m].studentID) == 0) {
							studentlist[m] = newStudent;
						}
					}
					ffffin.close();
					ofstream fout("../database/acaye/" + acaye + "/" + semester + "/" + studentcl[k].sub[l] + "/student.txt");
					fout << anotherCounter << "\n";
					for (int m = 0; m < anotherCounter; ++m) {
						fout << studentlist[m].studentID << "\n";
						fout << studentlist[m].studentName << "\n";
						fout << studentlist[m].gender << "\n";
						fout << studentlist[m].birthday.yyyy << " " << studentlist[m].birthday.mm << " " << studentlist[m].birthday.dd << "\n";
						if (m != anotherCounter - 1) fout << "\n";
					}
					delete[] studentlist;
					fout.close();
					string path = "../database/acaye/" + acaye + "/" + semester + "/" + studentcl[k].sub[l];
					updateStudentinAttendance((char*)path.c_str());
				}
				if (studentcl[k].id.compare(id) == 0) {
					studentcl[k].id = newStudent.studentID;
				}
			}

			
			fffin.close();

			ofstream fout("../database/acaye/" + acaye + "/" + semester + "/student_Course.txt");
			fout << ffcounter << "\n";

			for (int k = 0; k < ffcounter; ++k) {
				fout << studentcl[k].id << "\n";
				fout << studentcl[k].className << "\n";
				fout << studentcl[k].counter << "\n";
				for (int l = 0; l < studentcl[k].counter; ++l) {
					fout << studentcl[k].sub[l] << "\n";
				}
				if (k != ffcounter - 1) {
					fout << "\n";
				}
			}
			for (int k = 0; k < ffcounter; ++k) {
				delete[] studentcl[k].sub;
			}
			delete[] studentcl;
			fout.close();
			//
		}
		pSem.close();
	}
	pAca.close();
}

void removeStudentInStuC(string id, string path) {
	ifstream fin(path);
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	StudentCourse *studentlist = new StudentCourse[counter];
	for (int i = 0; i < counter; ++i) {
		getline(fin, studentlist[i].id);
		getline(fin, studentlist[i].className);
		fin >> studentlist[i].counter;
		fin.ignore(1234, '\n');
		studentlist[i].sub = new string[studentlist[i].counter];
		for (int j = 0; j < studentlist[i].counter; ++j) {
			getline(fin, studentlist[i].sub[j]);
		}
		fin.ignore(1234, '\n');
	}
	fin.close();

	ofstream fout(path);
	fout << counter - 1 << "\n";

	for (int i = 0; i < counter; ++i) {
		if (id.compare(studentlist[i].id) == 0) continue;
		fout << studentlist[i].id << "\n";
		fout << studentlist[i].className << "\n";
		fout << studentlist[i].counter << "\n";
		for (int j = 0; j < studentlist[i].counter; ++j) {
			fout << studentlist[i].sub[j] << "\n";
		}
		fout << "\n";
	}

	fout.close();

	for (int i = 0; i < counter; ++i) {
		delete[] studentlist[i].sub;
	}
	delete[] studentlist;
}

void removeStudent(char id[], string path, string className, void (*rsfc)(string, string), bool changeClass) {
	ifstream fin(path);
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	bool removed = false;
	student* studentlist = new student[counter];
	for (int i = 0; i < counter; ++i) {
		fin.getline(studentlist[i].studentID, 51, '\n');
		if (strcmp(id, studentlist[i].studentID) == 0) removed = true;
		fin.getline(studentlist[i].studentName, 51, '\n');
		fin.getline(studentlist[i].gender, 51, '\n');
		fin >> studentlist[i].birthday.yyyy >> studentlist[i].birthday.mm >> studentlist[i].birthday.dd;
		fin.ignore(12334, '\n');
		fin.ignore(12334, '\n');
	}
	fin.close();
	if (!removed)
	{
		cout << "Can't find student\n";
		return;
	}
	ofstream fout(path);
	fout << counter - 1 << "\n";
	for (int i = 0; i < counter; ++i) {
		if (strcmp(id, studentlist[i].studentID) == 0) continue;
		fout << studentlist[i].studentID << '\n';
		fout << studentlist[i].studentName << '\n';
		fout << studentlist[i].gender << '\n';
		fout << studentlist[i].birthday.yyyy << " " << studentlist[i].birthday.mm << " " << studentlist[i].birthday.dd;
		if (i != counter - 1) fout << "\n\n";
	}

	fout.close();
	delete[] studentlist;
	createStudentList(className);
	updateDelStudentAccount(string(id));

	//removestudentfromCourse
	if (rsfc != nullptr) {
		rsfc(id, className);
	}
	if (!changeClass)
		cout << endl << "REMOVE STUDENT SUCCESSFULLY" << endl << endl;
}

void updateDelStudentAccount(string id) {
	ifstream fin("../database/account/student.txt");
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	User* userlist = new User[counter];
	for (int i = 0; i < counter; ++i) {
		fin.getline(userlist[i].extraInfo, 51, '\n');
		fin.getline(userlist[i].username, 51, '\n');
		fin.getline(userlist[i].password, 51, '\n');
		fin.ignore(1234, '\n');
	}
	fin.close();

	ofstream fout("../database/account/student.txt");
	fout << counter - 1 << "\n";

	for (int i = 0; i < counter; ++i) {
		if (id.compare(userlist[i].username) == 0) continue;
		fout << userlist[i].extraInfo << '\n';
		fout << userlist[i].username << '\n';
		fout << userlist[i].password;
		if (i + 1 == counter - 1 && id.compare(userlist[i + 1].username) == 0) break;
		if (i != counter - 1) fout << "\n\n";
	}

	fout.close();
	delete[] userlist;
}

void changeStudentFromAToB() {
	char id[51];
	cout << "Please type in Student's ID: ";
	cin.getline(id, 51);

	string oldClass, newClass;

	cout << "Please type in Student's current Class: ";
	getline(cin, oldClass);
	cout << "Please type in Student's new Class: ";
	getline(cin, newClass);

	if (oldClass.compare(newClass) == 0) {
		cout << "Student is already in class " + oldClass << "\n";
		return;
	}

	string path = "../database/class/" + oldClass + "/student.txt";
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		cout << "Error!\n";
		return;
	}

	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	student newStudent{ "0", "0", "0", 0, 0, 0 };
	strcpy_s(newStudent.className, newClass.c_str());
	bool found = false;
	for (int i = 0; i < counter; ++i) {
		fin.getline(newStudent.studentID, 51, '\n');
		fin.getline(newStudent.studentName, 51, '\n');
		fin.getline(newStudent.gender, 51, '\n');
		fin >> newStudent.birthday.yyyy >> newStudent.birthday.mm >> newStudent.birthday.dd;
		if (strcmp(newStudent.studentID, id) == 0) {
			found = true;
			break;
		}
		fin.ignore(1234, '\n');
		fin.ignore(1234, '\n');
	}

	fin.close();
	if (!found) return;
	removeStudent(id, path, oldClass, nullptr, true);


	path = "../database/class/" + newClass + "/student.txt";
	addStudentClass(newStudent, path, newClass);

	cout<< endl << newStudent.studentName << " CHANGE CLASS SUCCESSFULLY FROM " << oldClass << " TO " << newClass << endl << endl;
}

void viewListOfStudentInClass() {
	char action[] = "view list of students in a class";
	string className = inputClassName(action);

	string path = "../database/class/" + className + "/student.txt";
	ifstream fin(path);
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');

	student student;
	for (int i = 0; i < counter; ++i) {
		fin.getline(student.studentID, 51, '\n');
		fin.getline(student.studentName, 51, '\n');
		fin.getline(student.gender, 51, '\n');
		fin >> student.birthday.yyyy >> student.birthday.mm >> student.birthday.dd;
		fin.ignore(124, '\n');
		fin.ignore(124, '\n');
		cout << student.studentID << "," << student.studentName << "," << student.gender << "," << student.birthday.yyyy << " " << student.birthday.mm << " " << student.birthday.dd << "\n";
	}


	fin.close();
}

void showClassList() {
	ifstream fin("../database/class/class.txt");
	if (!fin.is_open()) {
		return;
	}
	else
	{
		int counter;
		fin >> counter;
		fin.ignore(1234, '\n');
		char className[51];
		cout << "Class list: \n";
		for (int i = 0; i < counter; ++i) {
			fin.getline(className, 51, '\n');
			cout << className << "\n";
		}
	}
}
