#ifndef _STAFF_H_
#define _STAFF_H_

#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
#include <sys/stat.h>
#include <direct.h>
#include <filesystem>
#include "lecturer.h"
#include "allroles.h"
using namespace std;

struct Score 
{
	char id[51], name[51], mid[51], finalexam[51], bonus[51], total[51];
};

struct student
{
	char className[51], studentID[51], studentName[51], gender[51], password[51];
	date birthday;
};

struct course
{
	char subID[101], subName[101], subclass[101], lecAcc[101], subDay[101] , subRoom[101];
	char startdate[101], enddate[101];
	char starttime[101], endtime[101];
};

struct Attend
{
	lecturer lec;
	student stu;
};

struct StudentCourse {
	string id, className, * sub;
	int counter;
};

bool PathExist(const char* path);
bool checkEmptyTxt(ifstream& pFile);
bool transferTxt(fstream& A, fstream& B, char pathA[]);
bool searchLecturer(char LecAcc[], lecturer& a);
bool searchStudent(char path[] /*../database/acaye/2018-2019/fall/CM101_19APCS1*/, char ID[]);
bool searchStaff(char StaffAcc[], Staff& a);
bool searchCourseInfo(char tpath[] /*../database/acaye/2018-2019/fall*/, char ID[], char Class[], course& a);

#endif
