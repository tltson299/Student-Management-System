#ifndef _ALLROLES_H_
#define _ALLROLES_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;

struct User {
	char username[50], password[50], extraInfo[50];
	int type;
};
struct Student {
	char className[50], id[50], name[50], gender[50], dob[50], password[50];
};
struct Lecturer {
	char username[50], password[50], name[50], degree[50], gender[50];
};
struct Staff {
	char username[50], password[50], name[50], gender[50];
};
User* login();
User* loginTextfile(char iUsername[], char iPassword[]);
void viewProfile();
void viewProfileStudent();
void viewProfileLecturer();
void viewProfileStaff();
bool confirmPass(char password[]);
void changePassword(User* user);


#endif