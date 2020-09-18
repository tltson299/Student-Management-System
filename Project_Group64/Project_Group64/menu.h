#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <cstring>
#include "allroles.h"
using namespace std;

void mainmenu();
void printmainmenu();

void sidemenustudent(User* user);
void sidemenustaff(User* user);
void sidemenulecturer(User* user);

void printsidemenustudent();
void printsidemenustaff();
void printsidemenulecturer();

void stafftaskmenu();
void studenttaskmenu(User* user);
void lecturertaskmenu();

void printstafftaskmenu();
void printlecturertaskmenu();
void printstudenttaskmenu();

void classmenu();
void coursemenu();
void scoreboard();
void attendlist();

void printclassmenu();
void printcoursemenu();

void logout(User* user);

#endif
