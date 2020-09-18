#ifndef _STAFFCourse_H
#define _STAFFCourse_H

#include "staff.h"
using namespace std;

//Create Academic Year
void createAcaye();
void createFirstAcaye(char path[]);
void createFirstAcayeTxt(char acaye[], char path[]);
void addAcaye(char path[]);
void addAcayeTxt(char acaye[]);

//Create Semester for an Academic year
void createSemesterDirectly(char path[], char sem[]);
void createSemester();
void createFirstSemesterTxt(char semes[], char path[]);

//Update Academic year
void updateAcaye();
void renameAcaye(char path[], char oldacaye[], char newacaye[]);
void renameAcayeTxt(char oldacaye[], char newacaye[]);
void deleteAcaye();
void deleteAcayeDirectly(char acaye[]);
void deleteAcayeTxt(char acaye[]);

//Update Semester
void renameSem(char path[]);
void renameSemTxt(char path[], char oldsem[], char newsem[]);
void deleteSem();
void deleteSemDirectly(char acaye[], char sem[]);
void deleteSemTxt(char acaye[], char sem[]);
void addSem(char path[], char acaye[]);
void addSemesterTxt(char semes[], char path[]);

//Import Course
void importCourse();
void importCourseDirectly(char acaye[], char sem[]);

void createCourseTxtWithCounter(fstream& Course, fstream& temp, char path[], int count_Course);
void createCourseNameTxt(fstream& Coursename, fstream& temp, char path_Coursename[], int count_Course);
void importStudenttoCourse(char Class[], char path[] /* ../database/acaye/2018-2019/fall/CM101_19APCS1*/);
void createAttendanceTxt(char path[] /*../database/acaye/2018-2019/fall/CM101_19APCS1*/, char LecAcc[]);
void createCheckin(char className[], char path[]);
void createStudentCourseTxt(char path[] /*../database/acaye/2018-2019/fall*/);

// View AcayeandSem
void viewAcayeandSem();

//Add Course
void addCourse();
void addCoursetoTxt(course& a, char path[] /*../database/acaye/2017-2018/fall*/);
void addCoursetoCName(char path[] /*../database/acaye/2017-2019/fall*/, course& a);
void addCoursetoStuC(char path[] /*../database/acaye/2017-2018/fall*/, course& a);

//Edit Course
void editCourse();
void changeCourseInfo(char tpath[], char fpath[], char ID[], char Class[], char sem[], char acaye[]);
void editCourseIDFolder(char fpath[] /*../database/acaye/2018-2019/fall/CM101_19APCS1*/, char tpath[] /*../database/acaye/2018-2019/fall*/, char newInf[], course a);
void editCourseIDCourName(char tpath[] /*../database/acaye/2018-2019/fall*/, char oldID[], char newID[], char Class[]);
void editCourseIDStuCour(char tpath[] /*../database/acaye/2018-2019/fall*/, char oldID[], char newID[], char Class[]);
void editCourseTxt(char tpath[] /*../database/acaye/2018-2019/fall*/, char newInf[], course a, int choice, char ID[], char Class[]);

//Delete Course
void deleteCourse();
void deleteCourseDirectly(char acaye[], char sem[], char ID[], char Class[]);
void deleteCourseinTxt(char path_Course[], char Course[]);
void deleteCourseinCname(char path_Coursename[], char Course[]);
void deleteCourseinStuC(char path_studentCourse[], char Course[], char ID[], char Class[]);

//Remove Student from Course
void removeStudentfromCourse();
void removeStudentfromCourseinTxt(char path[], char stuID[], char ID[], char Class[], char sem[], char acaye[]);
void removeStudentinStuC(char path[] /*../database/acaye/2016-2017/fall*/, char stuID[], char ID[], char Class[]);
void removeStudentinCheckin(char path[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/, char stuID[]);

//Add Student to Course
void addStudenttoCourse();
void addStudenttoCourseinTxt(char path_student[], char ID[], student& a, char Class[], char sem[], char acaye[], bool& check);
void addStudenttoCourseinStuC(char path_studentCourse[], char ID[], char Class[], student& a);
void addStudenttoCheckin(char path_checkin[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/, student stu);
void updateStudentinAttendance(char path[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/);

//Update Lecturer Info for AttendanceTxt for 1 Course
void updateLecinAttendance(char path[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/, char newLecAcc[]);

//Update Lecturer Info for all AttendanceTxt 
void UpdateLecturerinAttendance(lecturer& lec);

//Update Student Info for all AttendanceTxt 
void UpdateStudentInAttendance(student& stu);

//Create Lecturer Info and Account
void createLecturer();
void createFirstLecturerTxt(char path[], lecturer lec);
void addLecturerTxt(char path[], lecturer lec);
void createFirstLecturerAcc(char path[], lecturer lec);
void addLecturerAcc(char path[], lecturer lec);

//Edit Existing Lecturer Info and Account
void editLecturer();
void editLecturerTxt(lecturer& lec, char newInfo[], char choice);
void editLecturerAcc(lecturer& lec, char newInfo[], char choice);

//Remove Existing Lecturer Info and Account
void removeLecturer();
void removeLecturerTxt(char path[], lecturer lec);
void removeLecturerAcc(char path[], lecturer lec);

//ViewLecturer
void viewAllLecturer();

#endif