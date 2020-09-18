#ifndef _LECTURER_H_
#define _LECTURER_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <ctype.h>
using namespace std;

struct year
{
	int index;
	char yearID[11];
};

struct sem
{
	int index;
	char semID[11];
};

struct title
{
	int index;
	char id[51], name[101], classID[51];
};

struct times
{
	int hh, mm;
};

struct date
{
	int yyyy, mm, dd;
};

struct lecturer
{
	char lecturerID[51];
	char lecturerPass[51];
	char lecturerName[51];
	char degree[51];
	char gender[11];
};

struct studentList
{
	char classID[51], id[51], name[51], gender[11];
	date dob;
};

struct schedule
{
	char subjectID[21];
	char subjectName[51];
	char classID[51];
	char lecturerID[11];
	char lecturerName[51];
	char degree[51];
	int gender;
	date startDate;
	date endDate;
	char studyDay[51];
	times startTime;
	times endTime;
	char place[11];
};

struct scoreboard
{
	char id[51], name[51], mid[51], finalexam[51], bonus[51], total[51];
};

void viewCourses();

void viewStudentsOfACourse();

void viewAttendance();

void editAttendance();

int count_students(ifstream& fin);

void importScoreBoard_database();

void editGrade();

#endif