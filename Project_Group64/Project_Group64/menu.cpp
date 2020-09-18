#include "allroles.h"
#include "lecturer.h"
#include "menu.h"
#include "staff.h"
#include "staffattend.h"
#include "staffclass.h"
#include "staffcourse.h"
#include "staffscore.h"
#include "student.h"

//main menu function and print main menu options function
void mainmenu()
{
	int choice = 0;
	do
	{
		printmainmenu();
		cin >> choice;
		cin.ignore(1);
		if (choice == 1)
		{
			User* user = login();

			if (user == nullptr) {
				cout << "\n\n==========================================\n";
				cout << " |\t\tLOGIN FAILED\t\t|\n";
				cout << "==========================================\n";
				cout << "PLEASE TRY AGAIN\n";
				cin.get();
				system("cls");
				continue;
			}
			else {
				// return menu of the Student
				if (user->type == 0)
					sidemenustudent(user);
				if (user->type == 1)
					sidemenulecturer(user);
				if (user->type == 2)
					sidemenustaff(user);
			}
		}
		
		if (choice == 0)
		{
			cout << endl << "PROGRAM HAS ENDED. THANK YOU FOR USING" << endl;
			break;
		}
		else
			cout << "ERROR CHOICE. PLEASE CHOOSE AGAIN" << endl;
	} while (choice != 0);
}
void printmainmenu()
{
	cout << "--- WELCOME TO HCMUS STUDENT MANAGEMENT SYSTEM ---" << endl;
	cout << "                   1. LOGIN                     " << endl;
	cout << "                 0. END PROGRAM                 " << endl;
	cout << "Please enter your choice: ";
}

//side menu after user have logged in (for user to choose to do a task or view profile or change password or log out)
void sidemenustudent(User* user)
{
	int choice = 0;
	do
	{
		printsidemenustudent();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (choice == 1)
		{
			studenttaskmenu(user);
			system("pause");
			system("cls");
		}
		if (choice == 2)
		{
			viewProfile();
			system("pause");
			system("cls");
		}
		if (choice == 3)
		{
			changePassword(user);
			system("pause");
			system("cls");
		}

	} while (choice != 4);
	logout(user);
	cout << "                LOG OUT SUCCESSFULLY             " << endl;
	system("pause");
	system("cls");
}
void sidemenustaff(User* user)
{
	int choice = 0;
	do
	{
		printsidemenustaff();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (choice == 1)
		{
			stafftaskmenu();
			system("pause");
			system("cls");
		}
		if (choice == 2)
		{
			viewProfile();
			system("pause");
			system("cls");
		}
		if (choice == 3)
		{
			changePassword(user);
			system("pause");
			system("cls");
		}
	} while (choice != 4);
	logout(user);
	cout << "                LOG OUT SUCCESSFULLY             " << endl;
	system("pause");
	system("cls");
}
void sidemenulecturer(User* user)
{
	int choice = 0;
	do
	{
		printsidemenulecturer();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (choice == 1)
		{
			lecturertaskmenu();
			system("pause");
			system("cls");
		}
		if (choice == 2)
		{
			viewProfile();
			system("pause");
			system("cls");
		}
		if (choice == 3)
		{
			changePassword(user);
			system("pause");
			system("cls");
		}
	} while (choice != 4);
	logout(user);
	cout << endl << "                LOG OUT SUCCESSFULLY             " << endl;
	system("pause");
	system("cls");
}

//print side menu options function
void printsidemenustudent()
{
	cout << endl;
	cout << "----------------STUDENT MENU-----------------" << endl;
	cout << "             1. SHOW TASKS MENU              " << endl;
	cout << "         2. VIEW PROFILE INFORMATION         " << endl;
	cout << "             3. CHANGE PASSWORD              " << endl;
	cout << "                4. LOG OUT                   " << endl;
	cout << "Please enter your choice: ";
}
void printsidemenustaff()
{
	cout << endl;
	cout << "-------------ACADEMIC STAFF MENU-------------" << endl;
	cout << "             1. SHOW TASKS MENU              " << endl;
	cout << "         2. VIEW PROFILE INFORMATION         " << endl;
	cout << "             3. CHANGE PASSWORD              " << endl;
	cout << "                4. LOG OUT                   " << endl;
	cout << "Please enter your choice: ";
}
void printsidemenulecturer()
{
	cout << endl;
	cout << "----------------LECTURER MENU----------------" << endl;
	cout << "             1. SHOW TASKS MENU              " << endl;
	cout << "         2. VIEW PROFILE INFORMATION         " << endl;
	cout << "             3. CHANGE PASSWORD              " << endl;
	cout << "                4. LOG OUT                   " << endl;
	cout << "Please enter your choice: ";
}

//task menu for a staff or lecturer or student to choose
void stafftaskmenu()
{
	int choice;
	do
	{
		printstafftaskmenu();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (choice == 1)
		{
			classmenu();
			system("pause");
			system("cls");
		}
		if (choice == 2)
		{
			coursemenu();
			system("pause");
			system("cls");
		}
		if (choice == 3)
		{
			scoreboard();
			system("pause");
			system("cls");
		}
		if (choice == 4)
		{
			attendlist();
			system("pause");
			system("cls");
		}
	} while (choice != 0);
}
void lecturertaskmenu()
{
	int choice;
	do
	{
		printlecturertaskmenu();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (1 == choice)
		{
			viewCourses();
			system("pause");
			system("cls");
		}
		else if (2 == choice)
		{
			viewStudentsOfACourse();
			system("pause");
			system("cls");
		}
		else if (3 == choice)
		{
			viewAttendance();
			system("pause");
			system("cls");
		}
		else if (4 == choice)
		{
			editAttendance();
			system("pause");
			system("cls");
		}
		else if (5 == choice)
		{
			importScoreBoard_database();
			system("pause");
			system("cls");
		}
		else if (6 == choice)
		{
			editGrade();
			system("pause");
			system("cls");
		}
		else if (7 == choice)
		{
			viewScoreBoard();
			system("pause");
			system("cls");
		}
	} while (choice != 0);

}
void studenttaskmenu(User* user) //update options
{
	int choice;
	do
	{
		printstudenttaskmenu();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (1 == choice)
		{
			checkin(user);
			system("pause");
			system("cls");
		}
		else if (2 == choice)
		{
			viewCheckin(user);
			system("pause");
			system("cls");
		}
		else if (3 == choice)
		{
			viewSchedules(user);
			system("pause");
			system("cls");
		}
		else if (4 == choice)
		{
			viewScoresOfACourse(user);
			system("pause");
			system("cls");
		}
	} while (choice != 0);
}

//print task menu options function for ...taskmenu functions
void printstafftaskmenu()
{
	cout << endl;
	cout << "-----------ACADEMIC STAFF TASKS MENU---------" << endl;
	cout << "               1. EDIT CLASSES               " << endl;
	cout << "               2. EDIT COURSES               " << endl;
	cout << "             3. EDIT SCOREBOARD              " << endl;
	cout << "           4. EDIT ATTENDANCE LIST           " << endl;
	cout << "                  0. EXIT                    " << endl;
	cout << "Please type in your choice: ";
}
void printlecturertaskmenu()
{
	cout << endl;
	cout << "-------------LECTURER TASKS MENU-------------" << endl;
	cout << "               1. VIEW COURSES               " << endl;
	cout << "     2. VIEW STUDENTS' LIST OF A COURSE      " << endl;
	cout << "      3. VIEW ATTENDANCE LIST OF A COURSE    " << endl;
	cout << "             4. EDIT ATTENDANCE              " << endl;
	cout << "     5. IMPORT SCOREBOARD FROM A CSV FILE    " << endl;
	cout << "                6. EDIT GRADE                " << endl;
	cout << "            7. VIEW A SCOREBOARD             " << endl;
	cout << "                   0. EXIT                   " << endl;
	cout << "Please type in your choice: ";
}
void printstudenttaskmenu()
{
	cout << endl;
	cout << "-------------STUDENT TASKS MENU--------------" << endl;
	cout << "            1. CHECK IN A COURSE             " << endl;
	cout << "          2. VIEW CHECK-IN RESULT            " << endl;
	cout << "             3. VIEW SCHEDULES               " << endl;
	cout << "          4. VIEW COURSE'S SCORES            " << endl;
	cout << "                  0. EXIT                    " << endl;
	cout << "Please type in your choice: ";
}

//side task menus for staff to choose (edit class, course, scoreboard, attendance list)
void classmenu()
{
	int choice = 0;
	do
	{
		printclassmenu();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		switch (choice) {
		case 0:
			break;
		case 1:
			importClassCsv();
			system("pause");
			system("cls");
			break;
		case 2:
			addStudentToClass();
			system("pause");
			system("cls");
			break;
		case 3:
			editStudent();
			system("pause");
			system("cls");
			break;
		case 4:
			removeStudentFromClass();
			system("pause");
			system("cls");
			break;
		case 5:
			changeStudentFromAToB();
			system("pause");
			system("cls");
			break;
		case 6:
			showClassList();
			system("pause");
			system("cls");
			break;
		case 7:
			viewListOfStudentInClass();
			system("pause");
			system("cls");
			break;
		default:
			cout << "ERROR. PLEASE CHOOSE AGAIN" << endl;
			break;
		}
	} while (choice != 0);
}
void coursemenu()
{
	int choice = 0;
	do
	{
		printcoursemenu();
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (choice == 1)
		{
			createAcaye();
			system("pause");
			system("cls");
		}
		else if (choice == 2)
		{
			createSemester();
			system("pause");
			system("cls");
		}
		else if (choice == 3)
		{
			updateAcaye();
			system("pause");
			system("cls");
		}
		else if (choice == 4)
		{
			importCourse();
			system("pause");
			system("cls");
		}
		else if (choice == 5)
		{
			addCourse();
			system("pause");
			system("cls");
		}
		else if (choice == 6)
		{
			editCourse();
			system("pause");
			system("cls");
		}
		else if (choice == 7)
		{
			deleteCourse();
			system("pause");
			system("cls");
		}
		else if (choice == 8)
		{
			removeStudentfromCourse();
			system("pause");
			system("cls");
		}
		else if (choice == 9)
		{
			addStudenttoCourse();
			system("pause");
			system("cls");
		}
		else if (choice == 10)
		{
			viewCourses();
			system("pause");
			system("cls");
		}
		else if (choice == 11)
		{
			viewStudentsOfACourse();
			system("pause");
			system("cls");
		}
		else if (choice == 12)
		{
			viewAttendance();
			system("pause");
			system("cls");
		}
		else if (choice == 13)
		{
			createLecturer();
			system("pause");
			system("cls");
		}
		else if (choice == 14)
		{
			editLecturer();
			system("pause");
			system("cls");
		}
		else if (choice == 15)
		{
			removeLecturer();
			system("pause");
			system("cls");
		}
		else if (choice == 16)
		{
			viewAllLecturer();
			system("pause");
			system("cls");
		}
		else
		{
			break;
		}
	} while (choice != 0);
}
void scoreboard()
{
	int choice;
	do
	{
		cout << endl;
		cout << "-------ACADEMIC STAFF__SCOREBOARD MENU-------" << endl;
		cout << "        1. SEARCH AND VIEW SCOREBOARD        " << endl;
		cout << "            2. EXPORT A SCOREBOARD           " << endl;
		cout << "                  0. EXIT                    " << endl;
		cout << "Please type in your choice: ";
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (choice == 1)
		{
			searchScoreBoard();
			system("pause");
			system("cls");
		}
		if (choice == 2)
		{
			exportScoreboard();
			system("pause");
			system("cls");
		}
	} while (choice != 0);
}
void attendlist()
{
	int choice;
	do
	{
		cout << endl;
		cout << "-------ACADEMIC STAFF--ATTENDANCE MENU-------" << endl;
		cout << "     1. SEARCH AND VIEW ATTENDANCE LIST      " << endl;
		cout << "        2. EXPORT AN ATTENDANCE LIST         " << endl;
		cout << "                  0. EXIT                    " << endl;
		cout << "Please type in your choice: ";
		cin >> choice;
		cin.ignore(1);
		system("cls");
		if (choice == 1)
		{
			searchviewAttend();
			system("pause");
			system("cls");
		}
		if (choice == 2)
		{
			exportAttendCSV();
			system("pause");
			system("cls");
		}

	} while (choice != 0);
}

//print choices for class and course menu options for staff
void printclassmenu()
{
	cout << endl;
		cout << "---------ACADEMIC STAFF__CLASS MENU----------" << endl;
		cout << " 1. IMPORT STUDENTS OF A CLASS FROM CSV FILE " << endl;
		cout << "    2. ADD A STUDENT TO A CLASS MANUALLY     " << endl;
		cout << "        3. EDIT AN EXISTING STUDENT          " << endl;
		cout << "            4. REMOVE A STUDENT              " << endl;
		cout << "    5. CHANGE STUDENTS TO ANOTHER CLASS      " << endl;
		cout << "           6. VIEW CLASSES' LIST             " << endl;
		cout << "    7. VIEW STUDENTS' LIST OF A CLASS        " << endl;
		cout << "                  0. EXIT                    " << endl;
		cout << "Please type in your choice: ";
}
void printcoursemenu()
{
	cout << endl;
	cout << "---------ACADEMIC STAFF__COURSE MENU---------" << endl;
	cout << "          1. CREATE ACADEMIC YEAR            " << endl;
	cout << "            2. CREATE SEMESTER               " << endl;
	cout << "    3. EDIT ACADEMIC YEAR AND SEMESTER       " << endl;
	cout << "       4. IMPORT COURSES TO A SEMESTER       " << endl;
	cout << "          5. ADD A COURSE MANUALLY           " << endl;
	cout << "         6. EDIT AN EXISTING COURSE          " << endl;
	cout << "             7. REMOVE A COURSE              " << endl;
	cout << "     8. REMOVE A STUDENT FROM A COURSE       " << endl;
	cout << "       9. ADD A STUDENT TO A COURSE          " << endl;
	cout << "      10. VIEW CURRENT COURSES' LIST         " << endl;
	cout << "    11. VIEW STUDENTS' LIST OF A COURSE      " << endl;
	cout << "   12. VIEW ATTENDANCE LIST OF A COURSE      " << endl;
	cout << "           13. CREATE LECTURERS              " << endl;
	cout << "            14. EDIT LECTURERS               " << endl;
	cout << "           15. REMOVE LECTURERS              " << endl;
	cout << "            16. VIEW LECTURERS               " << endl;
	cout << "                  0. EXIT                    " << endl;
	cout << "Please type in your choice: ";
}

void logout(User* user)
{
	delete user;
}
