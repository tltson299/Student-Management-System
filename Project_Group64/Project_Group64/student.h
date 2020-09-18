#ifndef _STUDENT_H_
#define _STUDENT_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <ctime>
#include "allroles.h"
using namespace std;

struct Checkin
{
	string id, name, * day = new string[11];
};

struct Course
{
	int index;
	char name[51], * course, * classID;
};

void checkin(User* user);

void viewCheckin(User* user);

void viewSchedules(User* user);

void viewScoresOfACourse(User* user);

#endif