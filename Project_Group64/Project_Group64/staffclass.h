#ifndef _STAFFCLASS_H
#define _STAFFCLASS_H
#define _CRT_SECURE_NO_WARNINGS

#include "staff.h"
#include "staffCourse.h"
#include "student.h"

using namespace std;
void editStudentFromCourse(student newStudent, string id);
// show a string: "Please input class name to " concate with action
// ex: action = "edit student"
// "Please input class name to edit student"
// return className user input
string inputClassName(char action[]);
// This function import class from a csv file
// First, import from csv to student*
// Second, createStudentAccount()
// Third, export a text file via exportClass()
void importClassCsv();

void initClassAccount(string className);

void createClassAccount(string className);

void initStudentList(string className);

void createStudentList(string className);

void addStudentToClass();

bool inputStudentInfo(student& newStudent);

void addStudentClass(student newStudent, string path, string className);

void updateAddStudentAccount(student newStudent);

bool checkStudentIDExist(string id);

void editStudent();

void removeStudentFromClass();

void removeFromCheckin(string id, string path);

void updateEditStudentAccount(string username, string oldId);

void removeStudent(char id[], string path, string className, void (*rsfc)(string, string), bool changClass);

void removeStudentFromCourse(string id, string oldClass);

void removeStudentInStuC(string id, string path);

void updateDelStudentAccount(string id);

void changeStudentFromAToB();

void viewListOfStudentInClass();

// show all classes, view list of classes
void showClassList();

#endif