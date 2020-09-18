#include"staff.h"

bool PathExist(const char* path) {
	struct stat path_stat;
	return stat(path, &path_stat) == 0;
}
bool checkEmptyTxt(ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}
bool transferTxt(fstream& A, fstream& B, char pathA[])
{
	A.open(pathA, ios::out);
	B.open("temp.txt", ios::in);
	if (!A.is_open())
		return false;
	else
	{
		char line[100];
		while (B.peek() != EOF)
		{
			B.getline(line, 100);
			A << line << endl;
		}
	}
	A.close();
	B.close();
	remove("temp.txt");
	return true;
}
bool searchLecturer(char LecAcc[], lecturer& a)
{
	char path[100] = "../database/lecturer/lecturer.txt";
	int counter = 0;
	fstream lec;
	lec.open(path, ios::in);
	if (lec.is_open())
	{
		lec >> counter;
		lec.ignore(1);
		for (int i = 0; i < counter; i++)
		{
			lec.getline(a.lecturerID, 51);
			lec.getline(a.lecturerPass, 51);
			lec.getline(a.lecturerName, 51);
			lec.getline(a.degree, 51);
			lec.getline(a.gender, 51);
			lec.ignore(1);
			if (strcmp(a.lecturerID, LecAcc) == 0)
			{
				return true;
			}
		}
	}
	return false;
}
bool searchStudent(char path[] /*../database/acaye/2018-2019/fall/CM101_19APCS1*/, char ID[])
{
	fstream stu;
	char line[100];
	stu.open(path, ios::in);
	while (stu.peek() != EOF)
	{
		stu.getline(line, 100);
		if (strcmp(line, ID) == 0)
			return true;
	}
	return false;
}
bool searchStaff(char StaffAcc[], Staff& a)
{
	char path[] = "../database/staff/staff.txt";
	int counter = 0;
	fstream staff;
	staff.open(path, ios::in);
	if (staff.is_open())
	{
		staff >> counter;
		staff.ignore(1);
		for (int i = 0; i < counter; i++)
		{
			staff.getline(a.username, 51);
			staff.getline(a.password, 51);
			staff.getline(a.name, 51);
			staff.getline(a.gender, 51);
			staff.ignore(1);
			if (strcmp(a.username, StaffAcc) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool searchCourseInfo(char tpath[] /*../database/acaye/2018-2019/fall*/, char ID[], char Class[], course& a)
{
	char temppath[100];
	strcpy_s(temppath, 100, tpath);
	strcat_s(temppath, "/course.txt");
	char tempfolder[100];
	strcpy_s(tempfolder, ID);
	strcat_s(tempfolder, "_");
	strcat_s(tempfolder, Class);

	fstream Course;
	Course.open(temppath, ios::in);
	if (!Course.is_open())
		cout << "Cannot open file" << endl;
	else
	{
		int counter;
		Course >> counter;
		Course.ignore(1);
		while (Course.peek() != EOF)
		{
			Course.getline(a.subID, 100);
			Course.getline(a.subName, 100);
			Course.getline(a.subclass, 100);
			Course.getline(a.lecAcc, 100);
			Course.getline(a.startdate, 100);
			Course.getline(a.enddate, 100);
			Course.getline(a.subDay, 100);
			Course.getline(a.starttime, 100);
			Course.getline(a.endtime, 100);
			Course.getline(a.subRoom, 100);
			Course.ignore(1);
			if (strcmp(a.subID, ID) == 0 && strcmp(a.subclass, Class) == 0)
			{
				return true;
			}
		}
	}
	return false;
}