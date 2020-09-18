#include"staffscore.h"

void searchScoreBoard()
{
	ifstream acaye, semester, Course, fscoreboard;
	int count_acaye, count_semester, count_Course, count_student;

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

			char link_Course[101] = "../database/acaye/";
			strcat_s(link_Course, y[Cacaye - 1].yearID);
			strcat_s(link_Course, "/");
			strcat_s(link_Course, s[Csemester - 1].semID);
			strcat_s(link_Course, "/course.txt");

			Course.open(link_Course);
			if (!Course.is_open())
				cout << endl << "Cannot load Courses" << endl;
			else
			{
				Course >> count_Course;
				Course.ignore();
				title* t = new title[count_Course];
				for (int i = 0; i < count_Course; ++i)
				{
					Course.getline(t[i].id, 51, '\n');
					Course.getline(t[i].name, 101, '\n');
					Course.getline(t[i].classID, 51, '\n');
					for (int j = 1; j <= 8; ++j)
						Course.ignore(51, '\n');
				}

				cout << endl << "----- Courses -----" << endl;
				for (int i = 0; i < count_Course; ++i)
				{
					t[i].index = i + 1;
					cout << t[i].index << ". " << t[i].id << " - " << t[i].name << " - " << t[i].classID << endl;
				}
				cout << "Please choose a Course: ";
				int CCourse;
				cin >> CCourse;
				while (CCourse < 1 || CCourse > count_Course)
				{
					cout << endl << "Please choose again: ";
					cin >> CCourse;
				}
				cin.ignore();
				cout << endl;

				char link_scoreboard[101] = "../database/acaye/";
				strcat_s(link_scoreboard, y[Cacaye - 1].yearID);
				strcat_s(link_scoreboard, "/");
				strcat_s(link_scoreboard, s[Csemester - 1].semID);
				strcat_s(link_scoreboard, "/");
				strcat_s(link_scoreboard, t[CCourse - 1].id);
				strcat_s(link_scoreboard, "_");
				strcat_s(link_scoreboard, t[CCourse - 1].classID);
				strcat_s(link_scoreboard, "/scoreboard.txt");

				fscoreboard.open(link_scoreboard);
				if (!fscoreboard.is_open())
					cout << " Cannot load Scoreboard." << endl;
				else
				{
					fscoreboard >> count_student;
					fscoreboard.ignore();
					scoreboard* a = new scoreboard[count_student];
					for (int i = 0; i < count_student; ++i)
					{
						fscoreboard.getline(a[i].id, 51, '\n');
						fscoreboard.getline(a[i].name, 51, '\n');
						fscoreboard.getline(a[i].mid, 51, '\n');
						fscoreboard.getline(a[i].finalexam, 51, '\n');
						fscoreboard.getline(a[i].bonus, 51, '\n');
						fscoreboard.getline(a[i].total, 51, '\n');
						fscoreboard.ignore();
					}

					char id[51];
					cout << "Please enter ID of the student: ";
					cin >> id;

					bool check = false;
					for (int i = 0; i < count_student; ++i)
					{
						if (strcmp(a[i].id, id) == 0)
						{
							cout << endl << "Name: " << a[i].name
								<< endl << "1. Midterm Exam: " << a[i].mid
								<< endl << "2. Final Exam: " << a[i].finalexam
								<< endl << "3. Bonus: " << a[i].bonus
								<< endl << "4. Total: " << a[i].total << endl << endl;
							check = true;
							break;
						}
					}
					if (check == false)
						cout << endl << " Cannot find this ID. Please try again!" << endl << endl;
					delete[]a;
				}
				fscoreboard.close();
				delete[]t;
			}
			Course.close();
			delete[]s;
		}
		semester.close();
		delete[]y;
	}
	acaye.close();
}

void viewScoreBoard()
{
	ifstream acaye, semester, Course, ifscoreboard;
	int count_acaye, count_semester, count_Course, count_student;

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

			char link_Course[101] = "../database/acaye/";
			strcat_s(link_Course, y[Cacaye - 1].yearID);
			strcat_s(link_Course, "/");
			strcat_s(link_Course, s[Csemester - 1].semID);
			strcat_s(link_Course, "/course.txt");

			Course.open(link_Course);
			if (!Course.is_open())
				cout << endl << "Cannot load Courses" << endl;
			else
			{
				Course >> count_Course;
				Course.ignore();
				title* t = new title[count_Course];
				for (int i = 0; i < count_Course; ++i)
				{
					Course.getline(t[i].id, 51, '\n');
					Course.getline(t[i].name, 101, '\n');
					Course.getline(t[i].classID, 51, '\n');
					for (int j = 1; j <= 8; ++j)
						Course.ignore(51, '\n');
				}

				cout << endl << "----- Courses -----" << endl;
				for (int i = 0; i < count_Course; ++i)
				{
					t[i].index = i + 1;
					cout << t[i].index << ". " << t[i].id << " - " << t[i].name << " - " << t[i].classID << endl;
				}
				cout << "Please choose a Course: ";
				int CCourse;
				cin >> CCourse;
				while (CCourse < 1 || CCourse > count_Course)
				{
					cout << endl << "Please choose again: ";
					cin >> CCourse;
				}
				cin.ignore();
				cout << endl;

				char link_scoreboard[101] = "../database/acaye/";
				strcat_s(link_scoreboard, y[Cacaye - 1].yearID);
				strcat_s(link_scoreboard, "/");
				strcat_s(link_scoreboard, s[Csemester - 1].semID);
				strcat_s(link_scoreboard, "/");
				strcat_s(link_scoreboard, t[CCourse - 1].id);
				strcat_s(link_scoreboard, "_");
				strcat_s(link_scoreboard, t[CCourse - 1].classID);
				strcat_s(link_scoreboard, "/scoreboard.txt");

				ifscoreboard.open(link_scoreboard);
				if (!ifscoreboard.is_open())
					cout << endl << " Cannot load Scoreboard." << endl;
				else
				{
					ifscoreboard >> count_student;
					ifscoreboard.ignore();
					scoreboard* a = new scoreboard[count_student];
					for (int i = 0; i < count_student; ++i)
					{
						ifscoreboard.getline(a[i].id, 51, '\n');
						ifscoreboard.getline(a[i].name, 51, '\n');
						ifscoreboard.getline(a[i].mid, 51, '\n');
						ifscoreboard.getline(a[i].finalexam, 51, '\n');
						ifscoreboard.getline(a[i].bonus, 51, '\n');
						ifscoreboard.getline(a[i].total, 51, '\n');
						ifscoreboard.ignore();

					}
					cout << endl << " NUMBER OF STUDENTS: " << count_student << endl;
					cout << endl << "\tID & NAME\t\tMIDTERM EXAM\t\tFINAL EXAM\t\tBONUS\t\t\tTOTAL" << endl << endl;
					for (int i = 0; i < count_student; ++i)
						cout << a[i].id << endl << i + 1 << ".\t\t"
						<< "\t\t" << a[i].mid << "\t\t\t"
						<< a[i].finalexam << "\t\t\t" << a[i].bonus << "\t\t\t"
						<< a[i].total << endl << a[i].name << endl
						<< "-----------------------------------------------------------"
						<< "-----------------------------------------------------------" << endl;
					cout << endl;
					delete[]a;
				}
				ifscoreboard.close();
				delete[]t;
			}
			Course.close();
			delete[]s;
		}
		semester.close();
		delete[]y;
	}
	acaye.close();
}

void exportScoreboard()
{
	string path = "../database/acaye/acaye.txt";
	ifstream fin(path);
	if (!fin.is_open()) {
		cout << "Error. Can't read file! \n";
		return;
	}
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	string* temp = new string[counter];

	int choice;
	cout << "Please choose an Academic year of the followings: \n";
	for (int i = 0; i < counter; ++i) {
		getline(fin, temp[i], '\n');
		cout << i + 1 << ". " << temp[i] << "\n";
	}
	cin >> choice;
	fin.close();

	string acaye = temp[choice - 1];
	delete[] temp;

	path = "../database/acaye/" + acaye + "/semester.txt";
	fin.open(path);
	fin >> counter;
	fin.ignore(1234, '\n');

	temp = new string[counter];
	cout << "Please choose a semester in " + acaye + " : \n";
	for (int i = 0; i < counter; ++i) {
		getline(fin, temp[i], '\n');
		cout << i + 1 << ". " << temp[i] << "\n";
	}
	cin >> choice;
	string semester = temp[choice - 1];
	fin.close();
	delete[] temp;

	path = "../database/acaye/" + acaye + "/" + semester + "/course.txt";

	fin.open(path);
	fin >> counter;
	fin.ignore(1234, '\n');

	temp = new string[counter];
	string* className = new string[counter];
	cout << "Please choose a Course: \n";
	for (int i = 0; i < counter; ++i) {
		getline(fin, temp[i], '\n');
		fin.ignore(123, '\n');
		getline(fin, className[i], '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		fin.ignore(123, '\n');
		cout << i + 1 << ": " << temp[i] << " - " << className[i] << "\n";
	}
	cin >> choice;
	fin.close();

	path = "../database/acaye/" + acaye + "/" + semester + "/" + temp[choice - 1] + "_" + className[choice - 1] + "/scoreboard.txt";


	fin.open(path);
	filesystem::create_directories("../database/exportCSV");
	ofstream fout("../database/exportCSV/" + temp[choice - 1] + "_" + className[choice - 1] + "_scoreboard.csv");
	fout << "Student id,full name,midterm,final,bonus,total\n";
	delete[] temp;
	delete[] className;

	fin >> counter;
	fin.ignore(1234, '\n');

	Score score;
	for (int i = 0; i < counter; ++i) {
		fin.getline(score.id, 51, '\n');
		fin.getline(score.name, 51, '\n');
		fin.getline(score.mid, 51, '\n');
		fin.getline(score.finalexam, 51, '\n');
		fin.getline(score.bonus, 51, '\n');
		fin.getline(score.total, 51, '\n');
		fin.ignore(1234, '\n');
		fout << score.id << "," << score.name << "," << score.mid << "," << score.finalexam << "," << score.bonus << "," << score.total << "\n";
	}

	fout.close();
	fin.close();
}