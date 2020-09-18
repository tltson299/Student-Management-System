#include "lecturer.h"
#include "staff.h"
#include "staffCourse.h"

void viewCourses()
{
	ifstream acaye, semester, Course;
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

			char link_Course[101] = "../database/acaye/";
			strcat_s(link_Course, y[Cacaye - 1].yearID);
			strcat_s(link_Course, "/");
			strcat_s(link_Course, s[Csemester - 1].semID);
			strcat_s(link_Course, "/course.txt");

			Course.open(link_Course);
			if (!Course.is_open())
			{
				cout << endl << "Cannot load Courses" << endl;
			}
			else
			{
				Course >> count_Course;
				Course.ignore();
				schedule* a = new schedule[count_Course];
				for (int i = 0; i < count_Course; ++i)
				{
					Course.getline(a[i].subjectID, 21, '\n');
					Course.getline(a[i].subjectName, 51, '\n');
					Course.getline(a[i].classID, 51, '\n');
					Course.getline(a[i].lecturerID, 51, '\n');
					Course >> a[i].startDate.yyyy >> a[i].startDate.mm >> a[i].startDate.dd;
					Course >> a[i].endDate.yyyy >> a[i].endDate.mm >> a[i].endDate.dd;
					Course.ignore();
					Course.getline(a[i].studyDay, 51, '\n');
					Course >> a[i].startTime.hh >> a[i].startTime.mm;
					Course >> a[i].endTime.hh >> a[i].endTime.mm;
					Course.ignore();
					Course.getline(a[i].place, 11, '\n');
					Course.ignore();
				}
				cout << endl << "NUMBER OF Course(S): " << count_Course << endl << endl;
				int index = 1;
				for (int i = 0; i < count_Course; ++i)
				{
					cout << index << "." << endl << "Subject ID : " << a[i].subjectID << endl
						<< "Subject Name: " << a[i].subjectName << endl
						<< "Class ID: " << a[i].classID << endl
						<< "Lecturer ID: " << a[i].lecturerID << endl
						<< "Start Course: " << a[i].startDate.yyyy << " " << a[i].startDate.mm << " " << a[i].startDate.dd << endl
						<< "End Course: " << a[i].endDate.yyyy << " " << a[i].endDate.mm << " " << a[i].endDate.dd << endl
						<< "Study Day: " << a[i].studyDay << endl
						<< "Start time: " << a[i].startTime.hh << " " << a[i].startTime.mm << endl
						<< "End time: " << a[i].endTime.hh << " " << a[i].endTime.mm << endl
						<< "Study at room: " << a[i].place << endl << endl;
					++index;
				}
				delete[]a;
			}
			Course.close();
			delete[]s;
		}
		semester.close();
		delete[]y;
	}
	acaye.close();
}

void viewStudentsOfACourse()
{
	ifstream acaye, semester, Course, ifstudent;
	int count_acaye, count_semester, count_Course, count_student;

	acaye.open("../database/acaye/acaye.txt");
	if (!acaye.is_open())
		cout << endl << "Cannot load Academic Years." << endl;
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

				char link_student[101] = "../database/acaye/";
				strcat_s(link_student, y[Cacaye - 1].yearID);
				strcat_s(link_student, "/");
				strcat_s(link_student, s[Csemester - 1].semID);
				strcat_s(link_student, "/");
				strcat_s(link_student, t[CCourse - 1].id);
				strcat_s(link_student, "_");
				strcat_s(link_student, t[CCourse - 1].classID);
				strcat_s(link_student, "/student.txt");
				
				ifstudent.open(link_student);
				if (!ifstudent.is_open())
					cout << endl << "Cannot load Students" << endl;
				else
				{
					ifstudent >> count_student;
					ifstudent.ignore();
					student* a = new student[count_student];
					for (int i = 0; i < count_student; ++i)
					{
						ifstudent.getline(a[i].studentID, 51, '\n');
						ifstudent.getline(a[i].studentName, 51, '\n');
						ifstudent.getline(a[i].gender, 11, '\n');
						ifstudent >> a[i].birthday.yyyy >> a[i].birthday.mm >> a[i].birthday.dd;
						ifstudent.ignore();
						ifstudent.ignore();
					}
					cout << endl << "NUMBER OF STUDENT(S): " << count_student << endl << endl
						<< "\tID & NAME\t\t\tGENDER\t\t\t\tDATE OF BIRTH" << endl << endl;
					for (int i = 0; i < count_student; ++i)
						cout << a[i].studentID << endl << i + 1 << "."
							<< "\t\t\t\t\t" << a[i].gender << "\t\t\t\t"
							<< a[i].birthday.yyyy << " "
							<< a[i].birthday.mm << " "
							<< a[i].birthday.dd << endl
							<< a[i].studentName << endl
							<< "-----------------------------------------------------------"
							<< "-----------------------------------------------------------" << endl;
					delete[]a;
				}
				ifstudent.close();
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

void viewAttendance()
{
	ifstream acaye, semester, Course, attendance;
	int count_acaye, count_semester, count_Course, count_lecturer, count_student;

	acaye.open("../database/acaye/acaye.txt");
	if (!acaye.is_open())
		cout << endl << "Cannot load Academic Years." << endl;
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
			cout << endl << "Cannot load Semesters." << endl;
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
				cout << endl << "Cannot load Courses." << endl;
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

				cout << endl << "----- Course -----" << endl;
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

				char link_attendance[101] = "../database/acaye/";
				strcat_s(link_attendance, y[Cacaye - 1].yearID);
				strcat_s(link_attendance, "/");
				strcat_s(link_attendance, s[Csemester - 1].semID);
				strcat_s(link_attendance, "/");
				strcat_s(link_attendance, t[CCourse - 1].id);
				strcat_s(link_attendance, "_");
				strcat_s(link_attendance, t[CCourse - 1].classID);
				strcat_s(link_attendance, "/attendance.txt");

				attendance.open(link_attendance);
				if (!attendance.is_open())
					cout << endl << "Cannot load Attendance." << endl;
				else
				{
					attendance >> count_lecturer;
					attendance.ignore();
					lecturer* a1 = new lecturer[count_lecturer];
					for (int i = 0; i < count_lecturer; ++i)
					{
						attendance.getline(a1[i].lecturerID, 51, '\n');
						attendance.getline(a1[i].lecturerName, 51, '\n');
						attendance.getline(a1[i].degree, 51, '\n');
						attendance.getline(a1[i].gender, 11, '\n');
						attendance.ignore();
					}
					attendance >> count_student;
					attendance.ignore();
					student* a2 = new student[count_student];
					for (int j = 0; j < count_student; ++j)
					{
						attendance.getline(a2[j].studentID, 51, '\n');
						attendance.getline(a2[j].studentName, 51, '\n');
						attendance.getline(a2[j].gender, 11, '\n');
						attendance >> a2[j].birthday.yyyy >> a2[j].birthday.mm >> a2[j].birthday.dd;
						attendance.ignore();
						attendance.ignore();
					}

					cout << endl << "NUMBER OF LECTURER(S): " << count_lecturer << endl << endl;
					for (int i = 0; i < count_lecturer; ++i)
					{
						cout << "Lecturer's ID: " << a1[i].lecturerID << endl;
						cout << "Name: " << a1[i].lecturerName << endl;
						cout << "Degree: " << a1[i].degree << endl;
						cout << "Gender: " << a1[i].gender << endl << endl;
					}
					cout << endl << "NUMBER OF STUDENT(S): " << count_student << endl << endl
						<< "\tID & NAME\t\t\tGENDER\t\t\t\tDATE OF BIRTH" << endl << endl;
					for (int i = 0; i < count_student; ++i)
						cout << a2[i].studentID << endl << i + 1 << "."
						<< "\t\t\t\t\t" << a2[i].gender << "\t\t\t\t"
						<< a2[i].birthday.yyyy << " "
						<< a2[i].birthday.mm << " "
						<< a2[i].birthday.dd << endl
						<< a2[i].studentName << endl
						<< "-----------------------------------------------------------"
						<< "-----------------------------------------------------------" << endl;
					attendance.close();
					delete[]a2;
					delete[]a1;
				}
				attendance.close();
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

void editAttendance()
{
	ifstream acaye, semester, Course;
	fstream attendance, lecturer_txt, studentlist_txt, class_stuedent_txt;
	int count_acaye, count_semester, count_Course, count_lecturer, count_student;

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

				char link_attendance[101] = "../database/acaye/";
				strcat_s(link_attendance, y[Cacaye - 1].yearID);
				strcat_s(link_attendance, "/");
				strcat_s(link_attendance, s[Csemester - 1].semID);
				strcat_s(link_attendance, "/");
				strcat_s(link_attendance, t[CCourse - 1].id);
				strcat_s(link_attendance, "_");
				strcat_s(link_attendance, t[CCourse - 1].classID);
				strcat_s(link_attendance, "/attendance.txt");

				attendance.open(link_attendance, ios::in);
				if (!attendance.is_open())
					cout << endl << "Cannot load Attendance" << endl;
				else
				{
					attendance >> count_lecturer;
					attendance.ignore();
					lecturer* a1 = new lecturer[count_lecturer];
					for (int i = 0; i < count_lecturer; ++i)
					{
						attendance.getline(a1[i].lecturerID, 51, '\n');
						attendance.getline(a1[i].lecturerName, 51, '\n');
						attendance.getline(a1[i].degree, 51, '\n');
						attendance.getline(a1[i].gender, 11, '\n');
						attendance.ignore();
					}
					attendance >> count_student;
					attendance.ignore();
					student* a2 = new student[count_student];
					for (int j = 0; j < count_student; ++j)
					{
						attendance.getline(a2[j].studentID, 51, '\n');
						attendance.getline(a2[j].studentName, 51, '\n');
						attendance.getline(a2[j].gender, 11, '\n');
						attendance >> a2[j].birthday.yyyy >> a2[j].birthday.mm >> a2[j].birthday.dd;
						attendance.ignore();
						attendance.ignore();
					}

					int choice;
					cout << "You want to edit:" << endl
						<< "1. LECTURER" << endl
						<< "2. STUDENT" << endl
						<< "Your choice: ";
					cin >> choice;
					while (choice != 1 && choice != 2)
					{
						cout << endl << "Please choose again: ";
						cin >> choice;
					}
					cout << endl;

					char lec[51] = "../database/lecturer/lecturer.txt",
						studentlist[51] = "../database/studentlist.txt",
						class_student[51] = "../database/class/";
					_strlwr_s(t[CCourse - 1].classID);
					strcat_s(class_student, t[CCourse - 1].classID);
					strcat_s(class_student, "/student.txt");

					bool check = false;
					if (1 == choice)          // EDIT LECTURER
					{
						char id[51];
						cout << "Please enter Lecturer's ID: ";
						cin >> id;

						for (int i = 0; i < count_lecturer; ++i)
						{
							if (strcmp(a1[i].lecturerID, id) == 0)
							{
								cout << endl << "ID: " << a1[i].lecturerID
									<< endl << "Name: " << a1[i].lecturerName
									<< endl << "1. Degree: " << a1[i].degree
									<< endl << "2. Gender: " << a1[i].gender << endl << endl;
								int choice;
								cout << "Please choose what you want to edit (1-2): ";
								cin >> choice;
								while (choice < 1 || 2 < choice)
								{
									cout << endl << "Please choose again: ";
									cin >> choice;
								}
								cin.ignore();

								if (1 == choice)
								{
									char newDegree[51];
									cout << endl << "New Degree: ";
									cin.getline(newDegree, 51, '\n');
									strcpy_s(a1[i].degree, newDegree);
								}
								else
								{
									char newGender[11];
									cout << endl << "New Gender: ";
									cin.getline(newGender, 11, '\n');
									strcpy_s(a1[i].gender, newGender);
								}

								lecturer_txt.open(lec, ios::in);
								if (!lecturer_txt.is_open())
									cout << endl << "Cannot load Lecturer." << endl;
								else
								{
									int count_lec;
									lecturer_txt >> count_lec;
									lecturer_txt.ignore();
									lecturer* newLec = new lecturer[count_lec];
									for (int j = 0; j < count_lec; ++j)
									{
										lecturer_txt.getline(newLec[j].lecturerID, 51, '\n');
										lecturer_txt.getline(newLec[j].lecturerPass, 51, '\n');
										lecturer_txt.getline(newLec[j].lecturerName, 51, '\n');
										lecturer_txt.getline(newLec[j].degree, 51, '\n');
										lecturer_txt.getline(newLec[j].gender, 51, '\n');
										lecturer_txt.ignore();
									}
									for (int j = 0; j < count_lec; ++j)
									{
										if (strcmp(id, newLec[j].lecturerID) == 0)
										{
											strcpy_s(newLec[j].degree, a1[i].degree);
											strcpy_s(newLec[j].gender, a1[i].gender);
											break;
										}
									}
									lecturer_txt.close();
									lecturer_txt.open(lec, ios::out);
									lecturer_txt << count_lec << endl;
									for (int j = 0; j < count_lec; ++j)
									{
										lecturer_txt << newLec[j].lecturerID << endl
											<< newLec[j].lecturerPass << endl
											<< newLec[j].lecturerName << endl
											<< newLec[j].degree << endl
											<< newLec[j].gender << endl << endl;
									}
									delete[]newLec;
								}
								lecturer_txt.close();

								UpdateLecturerinAttendance(a1[i]);

								check = true;
								break;
							}
						}
					}
					else if (2 == choice)          // EDIT STUDENT
					{
						char id[51];
						cout << "Please enter ID of student: ";
						cin >> id;

						for (int i = 0; i < count_student; ++i)
						{
							if (strcmp(a2[i].studentID, id) == 0)
							{
								cout << endl << "ID: " << a2[i].studentID
									<< endl << "1. Name: " << a2[i].studentName
									<< endl << "2. Gender: " << a2[i].gender
									<< endl << "3. Birthday: " << a2[i].birthday.yyyy << " "
									<< a2[i].birthday.mm << " " << a2[i].birthday.dd << endl << endl;

								int choice;
								cout << "Please choose what you want to edit (1-3): ";
								cin >> choice;
								while (choice < 1 || 3 < choice)
								{
									cout << endl << "Please choose again: ";
									cin >> choice;
								}
								cin.ignore();

								if (1 == choice)
								{
									char newName[51];
									cout << endl << "New Name: ";
									cin.getline(newName, 51, '\n');
									strcpy_s(a2[i].studentName, newName);
								}
								else if (2 == choice)
								{
									char newGender[11];
									cout << endl << "New Gender: ";
									cin.getline(newGender, 11, '\n');
									strcpy_s(a2[i].gender, newGender);
								}
								else if (3 == choice)
								{
									date newBD;
									cout << endl << " New Birthday (yyyy/mm/dd): ";
									cin >> newBD.yyyy >> newBD.mm >> newBD.dd;
									a2[i].birthday.yyyy = newBD.yyyy;
									a2[i].birthday.mm = newBD.mm;
									a2[i].birthday.dd = newBD.dd;
								}

								studentlist_txt.open(studentlist, ios::in);
								if (!studentlist_txt.is_open())
									cout << endl << "Cannot Load Students List." << endl;
								else
								{
									int count_SL;
									studentlist_txt >> count_SL;
									studentlist_txt.ignore();
									studentList* newSL = new studentList[count_SL];
									for (int j = 0; j < count_SL; ++j)
									{
										studentlist_txt.getline(newSL[j].classID, 51, '\n');
										studentlist_txt.getline(newSL[j].id, 51, '\n');
										studentlist_txt.getline(newSL[j].name, 51, '\n');
										studentlist_txt.getline(newSL[j].gender, 11, '\n');
										studentlist_txt >> newSL[j].dob.yyyy
											>> newSL[j].dob.mm >> newSL[j].dob.dd;
										studentlist_txt.ignore();
										studentlist_txt.ignore();
									}
									for (int j = 0; j < count_SL; ++j)
									{
										if (strcmp(id, newSL[j].id) == 0)
										{
											strcpy_s(newSL[j].name, a2[i].studentName);
											strcpy_s(newSL[j].gender, a2[i].gender);
											newSL[j].dob.yyyy = a2[i].birthday.yyyy;
											newSL[j].dob.mm = a2[i].birthday.mm;
											newSL[j].dob.dd = a2[i].birthday.dd;
											break;
										}
									}
									studentlist_txt.close();
									studentlist_txt.open(studentlist, ios::out);
									studentlist_txt << count_SL << endl;
									for (int j = 0; j < count_SL; ++j)
									{
										studentlist_txt << newSL[j].classID << endl
											<< newSL[j].id << endl
											<< newSL[j].name << endl
											<< newSL[j].gender << endl
											<< newSL[j].dob.yyyy << " "
											<< newSL[j].dob.mm << " "
											<< newSL[j].dob.dd<< endl << endl;
									}
									delete[]newSL;
								}
								studentlist_txt.close();

								class_stuedent_txt.open(class_student, ios::in);
								if (!class_stuedent_txt.is_open())
									cout << endl << "Cannot Load Students List." << endl;
								else
								{
									int count_S;
									class_stuedent_txt >> count_S;
									class_stuedent_txt.ignore();
									student* newS = new student[count_S];
									for (int j = 0; j < count_S; ++j)
									{
										class_stuedent_txt.getline(newS[j].studentID, 51, '\n');
										class_stuedent_txt.getline(newS[j].studentName, 51, '\n');
										class_stuedent_txt.getline(newS[j].gender, 11, '\n');
										class_stuedent_txt >> newS[j].birthday.yyyy >> newS[j].birthday.mm >> newS[j].birthday.dd;
										class_stuedent_txt.ignore();
										class_stuedent_txt.ignore();
									}
									for (int j = 0; j < count_S; ++j)
									{
										if (strcmp(id, newS[j].studentID) == 0)
										{
											strcpy_s(newS[j].studentName, a2[i].studentName);
											strcpy_s(newS[j].gender, a2[i].gender);
											newS[j].birthday.yyyy = a2[i].birthday.yyyy;
											newS[j].birthday.mm = a2[i].birthday.mm;
											newS[j].birthday.dd = a2[i].birthday.dd;
											break;
										}
									}
									class_stuedent_txt.close();
									class_stuedent_txt.open(class_student, ios::out);
									class_stuedent_txt << count_S << endl;
									for (int j = 0; j < count_S; ++j)
									{
										class_stuedent_txt << newS[j].studentID << endl
											<< newS[j].studentName << endl
											<< newS[j].gender << endl
											<< newS[j].birthday.yyyy << " "
											<< newS[j].birthday.mm << " "
											<< newS[j].birthday.dd << endl << endl;
									}
									delete[]newS;
								}
								studentlist_txt.close();

								UpdateStudentInAttendance(a2[i]);

								check = true;
								break;
							}
						}
					}

					attendance.close();
					attendance.open(link_attendance, ios::out);
					if (!attendance.is_open())
						cout << " Cannot save file." << endl << endl;
					else
					{
						attendance << count_lecturer << endl;
						for (int i = 0; i < count_lecturer; ++i)
						{
							attendance << a1[i].lecturerID << endl;
							attendance << a1[i].lecturerName << endl;
							attendance << a1[i].degree << endl;
							attendance << a1[i].gender << endl << endl;
						}
						attendance << count_student << endl;
						for (int j = 0; j < count_student; ++j)
						{
							attendance << a2[j].studentID << endl;
							attendance << a2[j].studentName << endl;
							attendance << a2[j].gender << endl;
							attendance << a2[j].birthday.yyyy << " "
								<< a2[j].birthday.mm << " "
								<< a2[j].birthday.dd << endl << endl;
						}
						if (check == false)
							cout << endl << " Cannot find this ID. Please try again!" << endl << endl;
						else
							cout << endl << " EDIT ATTENDANCE SUCCESSFULLY." << endl << endl;
					}
					attendance.close();
					delete[]a2;
					delete[]a1;
				}
				attendance.close();
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

int count_students(ifstream& fin)
{
	int count = 0;
	char data[101];
	while (fin.good())
	{
		fin.getline(data, 101, '\n');
		++count;
	}
	return count;
}

void importScoreBoard_database()
{
	char input[51];
	cout << endl << "Please enter the name of the CSV file: ";
	cin.getline(input, 51, '\n');

	char from[101] = "../database/importCSV/";
	strcat_s(from, input);
	strcat_s(from, ".csv");

	ifstream check;     // check file name
	check.open(from);
	if (!check.is_open())
	{
		cout << endl << " Cannot find this name." << endl;
		return;
	}
	check.close();

	ifstream acaye, semester, Course;
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

		cout << endl << "******* DESTINATION *******" << endl
			<< "----- ACAMEMIC YEARS -----" << endl;
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

				char to[101] = "../database/acaye/";
				strcat_s(to, y[Cacaye - 1].yearID);
				strcat_s(to, "/");
				strcat_s(to, s[Csemester - 1].semID);
				strcat_s(to, "/");
				strcat_s(to, t[CCourse - 1].id);
				strcat_s(to, "_");
				strcat_s(to, t[CCourse - 1].classID);
				strcat_s(to, "/scoreboard.txt");

				ifstream fin;
				ofstream fout;
				fin.open(from);
				if (!fin.is_open())
					cout << endl << "Cannot load file." << endl;
				else
				{
					fout.open(to);
					if (!fout.is_open())
						cout << endl << "Cannot save file." << endl;
					else
					{
						int count_student = count_students(fin);
						fin.close();
						fin.open(from);
						scoreboard* a = new scoreboard[count_student];
						for (int i = 0; i < count_student; ++i)
						{
							fin.getline(a[i].id, 51, ';');
							fin.getline(a[i].name, 51, ';');
							fin.getline(a[i].mid, 51, ';');
							fin.getline(a[i].finalexam, 51, ';');
							fin.getline(a[i].bonus, 51, ';');
							fin.getline(a[i].total, 51, '\n');
						}

						fout << count_student << endl;
						for (int i = 0; i < count_student; ++i)
						{
							fout << a[i].id << endl
								<< a[i].name << endl
								<< a[i].mid << endl
								<< a[i].finalexam << endl
								<< a[i].bonus << endl
								<< a[i].total << endl << endl;
						}

						cout << " IMPORT SUCCESSFULLY" << endl;
						delete[]a;
					}
					fout.close();
				}
				fin.close();
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

void editGrade()
{
	ifstream acaye, semester, Course;
	fstream fscoreboard;
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

				fscoreboard.open(link_scoreboard, ios::in);
				if (!fscoreboard.is_open())
					cout << endl << " Cannot load Scoreboard." << endl;
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
					cout << endl << "Please enter ID of student: ";
					cin >> id;

					bool check = false;
					for (int i = 0; i < count_student; ++i)
					{
						if (strcmp(a[i].id, id) == 0)
						{
							cout << endl << " Name: " << a[i].name
								<< endl << "1. Midterm Exam: " << a[i].mid
								<< endl << "2. Final Exam: " << a[i].finalexam
								<< endl << "3. Bonus: " << a[i].bonus
								<< endl << "4. Total: " << a[i].total << endl << endl;
							int choice;
							cout << "Please choose the grade you want to edit (1-4): ";
							cin >> choice;
							while (choice < 1 || 4 < choice)
							{
								cout << endl << "Please choose again: ";
								cin >> choice;
							}

							char newgrade[51];
							cout << endl << "New Grade: ";
							cin >> newgrade;

							if (1 == choice)
								strcpy_s(a[i].mid, newgrade);
							else if (2 == choice)
								strcpy_s(a[i].finalexam, newgrade);
							else if (3 == choice)
								strcpy_s(a[i].bonus, newgrade);
							else if (4 == choice)
								strcpy_s(a[i].total, newgrade);

							fscoreboard.close();
							fscoreboard.open(link_scoreboard, ios::out);
							if (!fscoreboard.is_open())
								cout << "Cannot save file." << endl << endl;
							else
							{
								fscoreboard << count_student << endl;
								for (int i = 0; i < count_student; ++i)
								{
									fscoreboard << a[i].id << endl
										<< a[i].name << endl
										<< a[i].mid << endl
										<< a[i].finalexam << endl
										<< a[i].bonus << endl
										<< a[i].total << endl << endl;
								}
								cout << endl << " EDIT GRADE SUCCESSFULLY." << endl;
							}
							check = true;
							break;
						}
					}
					if (check == false)
						cout << endl << "Cannot find this ID. Please try again!" << endl;
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