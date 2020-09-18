#include"staffattend.h";

void searchviewAttend()
{
	ifstream facaye, fsemester, fCourse, fattend;
	int count_acaye, count_semester, count_Course, count_lec, count_student;

	facaye.open("../database/acaye/acaye.txt");
	if (!facaye.is_open())
		cout << endl << "Cannot load Academic Years" << endl;
	else
	{
		facaye >> count_acaye;
		facaye.ignore();
		year* y = new year[count_acaye];
		for (int i = 0; i < count_acaye; ++i)
			facaye.getline(y[i].yearID, 11, '\n');

		cout << "ACAMEMIC YEARS" << endl;
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

		fsemester.open(link_sem);
		if (!fsemester.is_open())
			cout << endl << "Cannot load Semesters" << endl;
		else
		{
			fsemester >> count_semester;
			fsemester.ignore();
			sem* s = new sem[count_semester];
			for (int i = 0; i < count_semester; ++i)
				fsemester.getline(s[i].semID, 11, '\n');

			cout << "SEMESTER" << endl;
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

			fCourse.open(link_Course);
			if (!fCourse.is_open())
				cout << endl << "Cannot load Courses" << endl;
			else
			{
				fCourse >> count_Course;
				fCourse.ignore();
				title* t = new title[count_Course];
				for (int i = 0; i < count_Course; ++i)
				{
					fCourse.getline(t[i].id, 51, '\n');
					fCourse.getline(t[i].name, 101, '\n');
					fCourse.getline(t[i].classID, 51, '\n');
					for (int j = 1; j <= 8; ++j)
						fCourse.ignore(51, '\n');
				}

				cout << "Courses" << endl;
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

				char link_attend[101] = "../database/acaye/";
				strcat_s(link_attend, y[Cacaye - 1].yearID);
				strcat_s(link_attend, "/");
				strcat_s(link_attend, s[Csemester - 1].semID);
				strcat_s(link_attend, "/");
				strcat_s(link_attend, t[CCourse - 1].id);
				strcat_s(link_attend, "_");
				strcat_s(link_attend, t[CCourse - 1].classID);
				strcat_s(link_attend, "/attendance.txt");

				fattend.open(link_attend);
				if (!fattend.is_open())
					cout << " Cannot load Scoreboard." << endl;
				else
				{
					fattend >> count_lec;
					fattend.ignore();
					lecturer* a1 = new lecturer[count_lec];
					for (int i = 0; i < count_lec; ++i)
					{
						fattend.getline(a1[i].lecturerID, 11, '\n');
						fattend.getline(a1[i].lecturerName, 51, '\n');
						fattend.getline(a1[i].degree, 51, '\n');
						fattend.getline(a1[i].gender, 11, '\n');
						fattend.ignore();
					}
					fattend >> count_student;
					fattend.ignore();
					student* a2 = new student[count_student];
					for (int j = 0; j < count_student; ++j)
					{
						fattend.getline(a2[j].studentID, 51, '\n');
						fattend.getline(a2[j].studentName, 51, '\n');
						fattend.getline(a2[j].gender, 51, '\n');
						fattend >> a2[j].birthday.yyyy >> a2[j].birthday.mm >> a2[j].birthday.dd;
						fattend.ignore();
						fattend.ignore();
					}

					cout << "LECTURER LIST: " << count_lec << endl << endl;
					for (int i = 0; i < count_lec; ++i)
					{
						cout << a1[i].lecturerID << endl;
						cout << a1[i].lecturerName << endl;
						cout << a1[i].degree << endl;
						cout << a1[i].gender << endl << endl;
					}
					cout << "STUDENT LIST: " << count_student << endl << endl;
					for (int j = 0; j < count_student; ++j)
					{
						cout << a2[j].studentID << endl;
						cout << a2[j].studentName << endl;
						cout << a2[j].gender << endl;
						cout << a2[j].birthday.yyyy << a2[j].birthday.mm << a2[j].birthday.dd << endl << endl;
					}
					fattend.close();
					delete[]a2;
					delete[]a1;
				}
				fattend.close();
				delete[]t;
			}
			fCourse.close();
			delete[]s;
		}
		fsemester.close();
		delete[]y;
	}
	facaye.close();
}

void exportAttendCSV()
{
	ifstream facaye, fsemester, fCourse, fattend;
	ofstream fattendout;
	int count_acaye, count_semester, count_Course, count_lec, count_student;

	facaye.open("../database/acaye/acaye.txt");
	if (!facaye.is_open())
		cout << endl << "Cannot load Academic Years" << endl;
	else
	{
		facaye >> count_acaye;
		facaye.ignore();
		year* y = new year[count_acaye];
		for (int i = 0; i < count_acaye; ++i)
			facaye.getline(y[i].yearID, 11, '\n');

		cout << "ACAMEMIC YEARS" << endl;
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

		fsemester.open(link_sem);
		if (!fsemester.is_open())
			cout << endl << "Cannot load Semesters" << endl;
		else
		{
			fsemester >> count_semester;
			fsemester.ignore();
			sem* s = new sem[count_semester];
			for (int i = 0; i < count_semester; ++i)
				fsemester.getline(s[i].semID, 11, '\n');

			cout << "SEMESTER" << endl;
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
			fCourse.open(link_Course);

			if (!fCourse.is_open())
				cout << endl << "Cannot load Courses" << endl;
			else
			{
				fCourse >> count_Course;
				fCourse.ignore();
				title* t = new title[count_Course];
				for (int i = 0; i < count_Course; ++i)
				{
					fCourse.getline(t[i].id, 51, '\n');
					fCourse.getline(t[i].name, 101, '\n');
					fCourse.getline(t[i].classID, 51, '\n');
					for (int j = 1; j <= 8; ++j)
						fCourse.ignore(51, '\n');
				}

				cout << "Courses" << endl;
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

				char link_attend[101] = "../database/acaye/";
				strcat_s(link_attend, y[Cacaye - 1].yearID);
				strcat_s(link_attend, "/");
				strcat_s(link_attend, s[Csemester - 1].semID);
				strcat_s(link_attend, "/");
				strcat_s(link_attend, t[CCourse - 1].id);
				strcat_s(link_attend, "_");
				strcat_s(link_attend, t[CCourse - 1].classID);
				strcat_s(link_attend, "/attendance.txt");


				char link_export[100] = "../database/exportCSV/";
				strcat_s(link_export, y[Cacaye - 1].yearID);
				strcat_s(link_export, "_");
				strcat_s(link_export, s[Csemester - 1].semID);
				strcat_s(link_export, "_");
				strcat_s(link_export, t[CCourse - 1].id);
				strcat_s(link_export, "_");
				strcat_s(link_export, t[CCourse - 1].classID);
				strcat_s(link_export, "_attendance.csv");

				fattend.open(link_attend);
				fattendout.open(link_export);
				if (!fattend.is_open() || !fattendout.is_open())
					cout << " Cannot open file" << endl;
				else
				{
					fattend >> count_lec;
					fattend.ignore();
					lecturer* a1 = new lecturer[count_lec];
					for (int i = 0; i < count_lec; ++i)
					{
						fattend.getline(a1[i].lecturerID, 11, '\n');
						fattend.getline(a1[i].lecturerName, 51, '\n');
						fattend.getline(a1[i].degree, 51, '\n');
						fattend.getline(a1[i].gender, 11, '\n');
						fattend.ignore();
						fattendout << a1[i].lecturerID << ";" << a1[i].lecturerName << ";" << a1[i].degree << ";" << a1[i].gender << endl;
					}
					fattend >> count_student;
					fattend.ignore();
					student* a2 = new student[count_student];
					for (int j = 0; j < count_student; ++j)
					{
						fattend.getline(a2[j].studentID, 11, '\n');
						fattend.getline(a2[j].studentName, 51, '\n');
						fattend.getline(a2[j].gender, 11, '\n');
						fattend >> a2[j].birthday.yyyy >> a2[j].birthday.mm >> a2[j].birthday.dd;
						fattend.ignore();
						fattend.ignore();
						fattendout << a2[j].studentID << ";" << a2[j].studentName << ";" << a2[j].gender << ";" << a2[j].birthday.yyyy << a2[j].birthday.mm << a2[j].birthday.dd << endl;
					}

				}
				fattend.close();
				fattendout.close();
				delete[]t;
			}
			fCourse.close();
			delete[]s;
		}
		fsemester.close();
		delete[]y;
	}
	facaye.close();
	cout << "EXPORT SUCCESSFULLY" << endl;
}