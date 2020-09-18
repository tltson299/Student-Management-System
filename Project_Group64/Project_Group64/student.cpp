#include "student.h"
#include "lecturer.h"

void checkin(User* user) {
	time_t now = time(0);
	tm* lt = localtime(&now);
	int year = lt->tm_year + 1900,
		mon = lt->tm_mon + 1,
		day = lt->tm_mday,
		wday = lt->tm_wday,
		hour = lt->tm_hour,
		min = lt->tm_min;

	string semester, yearStr;
	if (mon >= 1 && mon <= 3) {
		semester = "spring";
		yearStr = to_string(year - 1) + "-" + to_string(year);
	}
	else if (mon >= 4 && mon <= 6) {
		semester = "summer";
		yearStr = to_string(year - 1) + "-" + to_string(year);
	}
	else if (mon >= 7 && mon <= 9) {
		semester = "fall";
		yearStr = to_string(year) + "-" + to_string(year + 1);
	}
	else if (mon >= 10 && mon <= 12) {
		semester = "winter";
		yearStr = to_string(year) + "-" + to_string(year + 1);
	}

	string path = "../database/acaye/" + yearStr + "/" + semester + "/student_course.txt";
	ifstream fin(path);
	if (!fin.is_open()) {
		cout << "CHECK-IN FAILED" << endl;
		return;
	}

	int counter, choice = -1;
	string temp;
	string* CourseCheckin = nullptr;

	fin >> counter;
	fin.ignore(1234, '\n');
	while (fin.good()) {
		getline(fin, temp);
		if (strcmp(user->username, temp.c_str()) == 0) {
			getline(fin, temp);
			fin >> counter;
			fin.ignore(1233, '\n');
			CourseCheckin = new string[counter];
			cout << "Courses List for Current Semester: " << endl;
			for (int j = 0; j < counter; ++j) {
				getline(fin, CourseCheckin[j]);
				cout << j + 1 << ". " << CourseCheckin[j] << "\n";
				CourseCheckin = CourseCheckin;
			}
			cout << "Please choose a Course: \n";
			cin >> choice;
			cin.ignore(123, '\n');
			break;
		}
	}
	fin.close();


	string className, courseName;
	if (choice >= 1 && choice <= counter && CourseCheckin != nullptr) {
		string delimiter = "_";
		courseName = CourseCheckin[choice - 1].substr(0, CourseCheckin[choice - 1].find(delimiter));
		className = CourseCheckin[choice - 1].substr(CourseCheckin[choice - 1].find(delimiter) + 1, CourseCheckin[choice - 1].length());
	}
	path = "../database/acaye/" + yearStr + "/" + semester + "/course.txt";
	//path = "../database/acaye/2017-2018/fall/course.txt";

	fin.open(path);
	if (!fin.is_open())
	{
		delete[] CourseCheckin;
		cout << "CHECK-IN FAILED" << endl;
		return;
	}
	date start{ 0, 0, 0 };
	date end{ 0, 0, 0 };
	int sH = -1, eH = -1, sM = -1, eM = -1;
	string weekday;

	while (fin.good()) {
		getline(fin, temp);

		if (courseName.compare(temp) == 0) {
			fin.ignore(1234, '\n');
			fin.ignore(1234, '\n');
			fin.ignore(1234, '\n');
			fin >> start.yyyy >> start.mm >> start.dd;
			fin >> end.yyyy >> end.mm >> end.dd;
			fin.ignore(1234, '\n');
			getline(fin, weekday, '\n');
			fin >> sH >> sM >> eH >> eM;
			break;
		}
	}
	fin.close();

	if (weekday.compare("Mon") == 0) weekday = "1";
	else if (weekday.compare("Tue") == 0) weekday = "2";
	else if (weekday.compare("Wed") == 0) weekday = "3";
	else if (weekday.compare("Thu") == 0) weekday = "4";
	else if (weekday.compare("Fri") == 0) weekday = "5";
	else if (weekday.compare("Sat") == 0) weekday = "6";
	else if (weekday.compare("Sun") == 0) weekday = "0";

	if (start.yyyy == 0 || sH == -1) {
		delete[] CourseCheckin;
		return;
	}

	int toDay = year * 365 + mon * 30 + day;
	int startDay = start.yyyy * 365 + start.mm * 30 + start.dd;
	int endDay = end.yyyy * 365 + end.mm * 30 + end.dd;
	if (wday != stoi(weekday) || toDay < startDay || toDay > endDay || hour < sH  || hour > eH || (hour == sH && min < sM) || (hour == eH && min > eH)) {
		delete[] CourseCheckin;
		cout << "CHECK-IN FAILED..." << endl;
		return;
	}
	if (CourseCheckin != nullptr)
		path = "../database/acaye/" + yearStr + "/" + semester + "/" + CourseCheckin[choice - 1] + "/checkin.txt";
	delete[] CourseCheckin;
	//path = "../database/acaye/2017-2018/fall/CM101_19APCS1/checkin.txt";
	fin.open(path);
	if (!fin.is_open()) {
		cout << "CHECKIN FAILED" << endl;
		return;
	}
	fin >> counter;
	fin.ignore(1234, '\n');
	fin.ignore(1234, '\n');
	Checkin* checkin = new Checkin[counter];
	for (int i = 0; i < counter; ++i) {
		getline(fin, checkin[i].id, ';');
		getline(fin, checkin[i].name, ';');
		for(int j = 0; j < 11; ++j) {
			if (j != 10) getline(fin, checkin[i].day[j], ';');
			else getline(fin, checkin[i].day[j], '\n');
		}
		if (strcmp(checkin[i].id.c_str(), user->username) == 0) {
			for (int j = 0; j < 11; ++j) {
				if (checkin[i].day[j].compare(to_string(year) + " " + to_string(mon) + " " + to_string(day)) == 0)
					break;
				if (checkin[i].day[j].compare("0") == 0) {
					checkin[i].day[j] = to_string(year) + " " + to_string(mon) + " " + to_string(day);
					break;
				}
			}
		}
	}
	fin.close();
	ofstream fout(path);
	if (!fout.is_open()) {
		cout << "CHECKIN FAILED" << endl;
		return;
	}
	fout << counter << "\n";
	fout << "id;name;day 1;day 2;day 3;day 4;day 5;day 6;day 7;day 8;day 9;day 10;day 11\n";

	for (int i = 0; i < counter; ++i) {
		fout << checkin[i].id << ";"<< checkin[i].name << ";";
		for (int j = 0; j < 11; ++j) {
			if (j != 10) fout << checkin[i].day[j] << ";";
			else fout << checkin[i].day[j] << "\n";
		}
	}

	fout.close();
	delete[] checkin;
	cout << "CHECK-IN SUCCESSFULLY \n";
}

void viewCheckin(User* user) {
	string path = "../database/acaye/acaye.txt";
	ifstream fin(path);
	if (!fin.is_open()) return;

	int counter, choice;

	fin >> counter;
	fin.ignore(1234, '\n');
	string* arr = new string[counter];
	string acaye;

	cout << "List of Academic Year(s): \n";
	for (int i = 0; i < counter; ++i) {
		getline(fin, arr[i]);
		cout << i + 1 << ". " << arr[i] << "\n";
	}
	fin.close();
	cout << "Please type in your choice to view check-in result: ";
	cin >> choice;
	cout << endl;

	if (choice >= 1 && choice <= counter) {
		path = "../database/acaye/" + arr[choice - 1] + "/semester.txt";
		acaye = arr[choice - 1];
		delete[] arr;
	}
	else {
		delete[] arr;
		return;
	}

	fin.open(path);
	if (!fin.is_open()) {
		return;
	}
	fin >> counter;
	fin.ignore(1234, '\n');
	arr = new string[counter];
	string semester;

	cout << "List of Semester(s): \n";
	for (int i = 0; i < counter; ++i) {
		getline(fin, arr[i]);
		cout << i + 1 << ". " << arr[i] << "\n";
	}
	fin.close();
	cout << "Please type in your choice to view check-in result: ";
	cin >> choice;
	cout << endl;

	if (choice >= 1 && choice <= counter) {
		path = "../database/acaye/" + acaye + "/" + arr[choice - 1] + "/student_course.txt";
		semester = arr[choice - 1];
		delete[] arr;
	}
	else {
		delete[] arr;
		return;
	}

	fin.open(path);
	if (!fin.is_open()) {
		return;
	}
	string temp;
	while (fin.good()) {
		getline(fin, temp);
		if (strcmp(temp.c_str(), user->username) == 0) {
			fin.ignore(1234, '\n');
			fin >> counter;
			fin.ignore(1234, '\n');
			arr = new string[counter];

			cout << "List of Course(s): \n";
			for (int i = 0; i < counter; ++i) {
				getline(fin, arr[i]);
				cout << i + 1 << ". " << arr[i] << "\n";
			}
			break;
		}
	}
	fin.close();
	cout << "Please type in your choice to view check-in result: ";
	cin >> choice;
	if (choice >= 1 && choice <= counter) {
		path = "../database/acaye/" + acaye + "/" + semester + "/" + arr[choice - 1] + "/checkin.txt";
		delete[] arr;
	}
	else {
		delete[] arr;
		return;
	}
	fin.open(path);
	fin >> counter;
	fin.ignore(123, '\n');

	Checkin checkin;
	int daycount = 0;
	for (int i = 0; i < counter; ++i)
	{
		getline(fin, temp, ';');
		if (strcmp(temp.c_str(), user->username) == 0) {
			checkin.id = temp;
			getline(fin, checkin.name, ';');
			for (int j = 0; j < 11; ++j) {
				if (j == 10) getline(fin, checkin.day[j]);
				else getline(fin, checkin.day[j], ';');
				if (checkin.day[j].compare("0") != 0) {
					++daycount;
				}
			}
			break;
		}
		fin.ignore(1234565, '\n');
	}
	cout << "Student: " << checkin.name << "\n";
	cout << "ID: " << checkin.id << "\n";
	cout << "Total check-in day(s): " << daycount << "\n";
	for (int i = 0; i < daycount; ++i) {
		cout << checkin.day[i] << ",";
	}
	cout << "\n";

	delete[] checkin.day;
	fin.close();
}

void viewSchedules(User* user)
{
	ifstream acaye, semester, student_Course, ifschedule;
	int count_acaye, count_semester, count_Course, count_schedule;

	acaye.open("../database/acaye/acaye.txt");
	if (!acaye.is_open())
		cout << endl << "Cannot load Academic Years" << endl;
	else
	{
		acaye >> count_acaye;
		acaye.ignore();
		year* y = new year[count_acaye];
		for (int i = 0; i < count_acaye; ++i)
			acaye.getline(y[i].yearID, 11, '\n');

		cout << endl << "----- ACAMEMIC YEARS -----" << endl;
		for (int i = 0; i < count_acaye; ++i)
		{
			y[i].index = i + 1;
			cout << y[i].index << ". " << y[i].yearID << endl;
		}
		cout << "Please choose an Academic year: ";
		int Cacaye;
		cin >> Cacaye;
		while (Cacaye < 1 || Cacaye > count_acaye)
		{
			cout << endl << "Please choose again: ";
			cin >> Cacaye;
		}
		cin.ignore();
		cout << endl;

		char link_sem[101] = "../database/acaye/";
		strcat_s(link_sem, y[Cacaye - 1].yearID);
		strcat_s(link_sem, "/semester.txt");

		semester.open(link_sem);
		if (!semester.is_open())
			cout << endl << "Cannot load Semesters" << endl;
		else
		{
			semester >> count_semester;
			semester.ignore();
			sem* s = new sem[count_semester];
			for (int i = 0; i < count_semester; ++i)
				semester.getline(s[i].semID, 11, '\n');

			cout << endl << "----- SEMESTERS -----" << endl;
			for (int i = 0; i < count_semester; ++i)
			{
				s[i].index = i + 1;
				char temp_semID[11];
				strcpy_s(temp_semID, 11, s[i].semID);
				_strupr_s(temp_semID);
				cout << s[i].index << ". " << temp_semID << endl;
			}
			cout << "Please choose a Semester: ";
			int Csemester;
			cin >> Csemester;
			while (Csemester < 1 || Csemester > count_semester)
			{
				cout << endl << "Please choose again: ";
				cin >> Csemester;
			}
			cin.ignore();
			cout << endl;

			char link_student_Course[101] = "../database/acaye/";
			strcat_s(link_student_Course, y[Cacaye - 1].yearID);
			strcat_s(link_student_Course, "/");
			strcat_s(link_student_Course, s[Csemester - 1].semID);
			strcat_s(link_student_Course, "/student_course.txt");

			student_Course.open(link_student_Course);
			if (!student_Course.is_open())
			{
				cout << endl << "Cannot load Students' Courses." << endl;
			}
			else
			{
				char ID[51];
				student_Course.ignore(10, '\n');
				student_Course.getline(ID, 51, '\n');
				while (strcmp(user->username, ID) != 0)
					student_Course.getline(ID, 51, '\n');
				if (strcmp(user->username, ID) == 0)
				{
					student_Course.ignore(1000, '\n');
					student_Course >> count_Course;
					student_Course.ignore();
					Course* a1 = new Course[count_Course];
					for (int i = 0; i < count_Course; ++i)
					{
						student_Course.getline(a1[i].name, 51, '\n');
						int index = 0;
						while (a1[i].name[index] != '_')
							++index;

						a1[i].course = new char[index];
						int k = 0;
						for (int j = 0; j < index; ++j)
						{
							a1[i].course[k] = a1[i].name[j];
							++k;
						}
						a1[i].course[index] = '\0';

						a1[i].classID = new char[strlen(a1[i].name) - index - 1];
						k = 0;
						for (int j = index + 1; j < strlen(a1[i].name); ++j)
						{
							a1[i].classID[k] = a1[i].name[j];
							++k;
						}
						a1[i].classID[strlen(a1[i].name) - index - 1] = '\0';
					}

					char link_schedule[101] = "../database/acaye/";
					strcat_s(link_schedule, y[Cacaye - 1].yearID);
					strcat_s(link_schedule, "/");
					strcat_s(link_schedule, s[Csemester - 1].semID);
					strcat_s(link_schedule, "/course.txt");

					ifschedule.open(link_schedule);
					if (!ifschedule.is_open())
						cout << endl << " Cannot load Schedules." << endl;
					else
					{
						ifschedule >> count_schedule;
						ifschedule.ignore();
						schedule* a2 = new schedule[count_schedule];
						for (int i = 0; i < count_schedule; ++i)
						{
							ifschedule.getline(a2[i].subjectID, 21, '\n');
							ifschedule.getline(a2[i].subjectName, 51, '\n');
							ifschedule.getline(a2[i].classID, 51, '\n');
							ifschedule.getline(a2[i].lecturerID, 51, '\n');
							ifschedule >> a2[i].startDate.yyyy >> a2[i].startDate.mm >> a2[i].startDate.dd;
							ifschedule >> a2[i].endDate.yyyy >> a2[i].endDate.mm >> a2[i].endDate.dd;
							ifschedule.ignore();
							ifschedule.getline(a2[i].studyDay, 51, '\n');
							ifschedule >> a2[i].startTime.hh >> a2[i].startTime.mm;
							ifschedule >> a2[i].endTime.hh >> a2[i].endTime.mm;
							ifschedule.ignore();
							ifschedule.getline(a2[i].place, 11, '\n');
							ifschedule.ignore();
						}

						cout << endl << "----- SCHEDULES -----" << endl << endl;
						int m = 1;
						for (int i = 0; i < count_Course; ++i)
						{
							for (int j = 0; j < count_schedule; ++j)
							{
								if (strcmp(a1[i].course, a2[j].subjectID) == 0 && strcmp(a1[i].classID, a2[j].classID) == 0)
								{
									cout << m << ". " << a2[j].subjectID << " - " << a2[j].classID << endl
										<< "Study day: " << a2[j].studyDay << endl
										<< "Start time: " << a2[j].startTime.hh << " " << a2[j].startTime.mm << endl
										<< "End time: " << a2[j].endTime.hh << " " << a2[j].endTime.mm << endl
										<< "Study at room: " << a2[j].place << endl << endl;
									++m;
								}
							}
						}

						delete[]a2;
					}
					ifschedule.close();
					delete[]a1;
				}
				else
					cout << endl << " Cannot find your ID." << endl << endl;
			}
			student_Course.close();
			delete[]s;
		}
		semester.close();
		delete[]y;
	}
	acaye.close();
}

void viewScoresOfACourse(User* user)
{
	ifstream acaye, semester, student_Course, ifscoreboard;
	int count_acaye, count_semester, count_Course;

	acaye.open("../database/acaye/acaye.txt");
	if (!acaye.is_open())
		cout << endl << "Cannot load Academic Years" << endl;
	else
	{
		acaye >> count_acaye;
		acaye.ignore();
		year* y = new year[count_acaye];
		for (int i = 0; i < count_acaye; ++i)
			acaye.getline(y[i].yearID, 11, '\n');

		cout << endl << "----- ACAMEMIC YEARS -----" << endl;
		for (int i = 0; i < count_acaye; ++i)
		{
			y[i].index = i + 1;
			cout << y[i].index << ". " << y[i].yearID << endl;
		}
		cout << "Please choose an Academic year: ";
		int Cacaye;
		cin >> Cacaye;
		while (Cacaye < 1 || Cacaye > count_acaye)
		{
			cout << endl << "Please choose again: ";
			cin >> Cacaye;
		}
		cin.ignore();
		cout << endl;

		char link_sem[101] = "../database/acaye/";
		strcat_s(link_sem, y[Cacaye - 1].yearID);
		strcat_s(link_sem, "/semester.txt");

		semester.open(link_sem);
		if (!semester.is_open())
			cout << endl << "Cannot load Semesters" << endl;
		else
		{
			semester >> count_semester;
			semester.ignore();
			sem* s = new sem[count_semester];
			for (int i = 0; i < count_semester; ++i)
				semester.getline(s[i].semID, 11, '\n');

			cout << endl << "----- SEMESTERS -----" << endl;
			for (int i = 0; i < count_semester; ++i)
			{
				s[i].index = i + 1;
				char temp_semID[11];
				strcpy_s(temp_semID, 11, s[i].semID);
				_strupr_s(temp_semID);
				cout << s[i].index << ". " << temp_semID << endl;
			}
			cout << "Please choose a Semester: ";
			int Csemester;
			cin >> Csemester;
			while (Csemester < 1 || Csemester > count_semester)
			{
				cout << endl << "Please choose again: ";
				cin >> Csemester;
			}
			cin.ignore();
			cout << endl;

			char link_student_Course[101] = "../database/acaye/";
			strcat_s(link_student_Course, y[Cacaye - 1].yearID);
			strcat_s(link_student_Course, "/");
			strcat_s(link_student_Course, s[Csemester - 1].semID);
			strcat_s(link_student_Course, "/student_course.txt");

			student_Course.open(link_student_Course);
			if (!student_Course.is_open())
			{
				cout << endl << " Cannot load Students' Courses." << endl;
			}
			else
			{
				char ID[51];
				student_Course.ignore(10, '\n');
				student_Course.getline(ID, 51, '\n');
				while (strcmp(user->username, ID) != 0)
					student_Course.getline(ID, 51, '\n');
				if (strcmp(user->username, ID) == 0)
				{
					student_Course.ignore(100, '\n');
					student_Course >> count_Course;
					student_Course.ignore();
					Course* a = new Course[count_Course];
					for (int i = 0; i < count_Course; ++i)
					{
						student_Course.getline(a[i].name, 51, '\n');
						int index = 0;
						while (a[i].name[index] != '_')
							++index;

						a[i].course = new char[index];
						int k = 0;
						for (int j = 0; j < index; ++j)
						{
							a[i].course[k] = a[i].name[j];
							++k;
						}
						a[i].course[index] = '\0';

						a[i].classID = new char[strlen(a[i].name) - index - 1];
						k = 0;
						for (int j = index + 1; j < strlen(a[i].name); ++j)
						{
							a[i].classID[k] = a[i].name[j];
							++k;
						}
						a[i].classID[strlen(a[i].name) - index - 1] = '\0';
					}

					cout << endl << "----- Course -----" << endl;
					for (int i = 0; i < count_Course; ++i)
					{
						a[i].index = i + 1;
						cout << a[i].index << ". " << a[i].course << " - " << a[i].classID << endl;
					}
					cout << "Please choose a Course: ";
					int choice;
					cin >> choice;
					while (choice < 1 || choice > count_Course)
					{
						cout << endl << "Please choose again: ";
						cin >> choice;
					}
					cin.ignore();
					cout << endl;

					char link_scoreboard[101] = "../database/acaye/";
					strcat_s(link_scoreboard, y[Cacaye - 1].yearID);
					strcat_s(link_scoreboard, "/");
					strcat_s(link_scoreboard, s[Csemester - 1].semID);
					strcat_s(link_scoreboard, "/");
					strcat_s(link_scoreboard, a[choice - 1].name);
					strcat_s(link_scoreboard, "/scoreboard.txt");

					ifscoreboard.open(link_scoreboard);
					if (!ifscoreboard.is_open())
						cout << endl << " Cannot load Scoreboard." << endl;
					else
					{
						char studentID[51];
						ifscoreboard.ignore(10, '\n');
						ifscoreboard.getline(studentID, 51, '\n');
						while (strcmp(user->username, studentID) != 0)
							ifscoreboard.getline(studentID, 51, '\n');
						if (strcmp(user->username, studentID) == 0)
						{
							scoreboard s;
							ifscoreboard.ignore(100, '\n');
							ifscoreboard.getline(s.mid, 51, '\n');
							ifscoreboard.getline(s.finalexam, 51, '\n');
							ifscoreboard.getline(s.bonus, 51, '\n');
							ifscoreboard.getline(s.total, 51, '\n');

							cout << endl << "***" << a[choice - 1].course << " - " << a[choice - 1].classID
								<< " - " << "ID: " << studentID << endl
								<< " Midterm Exam: " << s.mid << endl
								<< " Final Exam: " << s.finalexam << endl
								<< " Bonus: " << s.bonus << endl
								<< " Total: " << s.total << endl << endl;
						}
						else
							cout << endl << " Cannot find your ID in the Scoreboard." << endl << endl;
					}
					ifscoreboard.close();
					delete[]a;
				}
				else
					cout << endl << " Cannot find your ID." << endl << endl;
			}
			student_Course.close();
			delete[]s;
		}
		semester.close();
		delete[]y;
	}
	acaye.close();
}