#include"staffcourse.h";

//Create Academic Year
void createAcaye()
{
	char path[100] = "../database/acaye";
	if (PathExist(path)) //There is at least 1 academic year created
	{
		addAcaye(path);
	}
	else //There is no academic year. Thus, we need to initialize everything
	{
		createFirstAcaye(path);
	}
} 
void createFirstAcaye(char path[])
{
	char temppath[100];
	strcpy_s(temppath, 100, path);
	_mkdir(temppath);
	if (PathExist(temppath))
	{
		strcat_s(temppath, 100, "/");
		char acaye[100];
		cout << "Please type in the Academic year you want to create: ";
		cin.getline(acaye, 100);
		createFirstAcayeTxt(acaye, temppath);
		strcat_s(temppath, 100, acaye);
		_mkdir(temppath);
		if (PathExist(temppath))
		{
			cout << endl << "ACADEMIC YEAR " << acaye << " CREATED SUCCESSFULLY" << endl;
			char choice;
			cout << "Do you want to create a Semester for this new academic year (y/n): ";
			cin >> choice;
			cin.ignore(1);
			if (choice == 'y' || choice == 'Y')
			{
				char sem[100];
				cout << "Please type in the Semester you want to create: ";
				cin.getline(sem, 100);
				createSemesterDirectly(temppath, sem);
				cout << "Do you want to import Courses for Semester " << sem << " of Academic year " << acaye << " (y/n): ";
				cin >> choice;
				cin.ignore(1);
				if (choice == 'y')
				{
					importCourseDirectly(acaye, sem);
				}
				else
					return;
			}
			else
				return;
		}
		else
			cout << "System error" << endl;
	}
	else
		cout << "System error" << endl;
}
void createFirstAcayeTxt(char acaye[], char path[])
{
	char temppath[200];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 200, "/acaye.txt");
	fstream aca;
	aca.open(temppath, ios::out);
	if (!aca.is_open())
		cout << "System error";
	else
	{
		aca << 1 << endl;
		aca << acaye;
	}
	aca.close();
}
void addAcaye(char path[])
{
	char temppath[100];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 100, "/");
	char acaye[100];
	cout << "Please type in the Academic year you want to create: ";
	cin.getline(acaye, 100);
	strcat_s(temppath, 100, acaye);
	if (PathExist(temppath))
		cout << "This Academic year is already exist" << endl;
	else
	{
		_mkdir(temppath);
		if (PathExist(temppath))
		{
			cout << endl << "ACADEMIC YEAR " << acaye << " CREATED SUCCESSFULLY" << endl << endl;
			addAcayeTxt(acaye);
			char choice;
			cout << "Do you want to create a Semester for this new academic year (y/n): ";
			cin >> choice;
			cin.ignore(1);
			if (choice == 'y' || choice == 'Y')
			{
				char sem[100];
				cout << "Please type in the semester you want to create: ";
				cin.getline(sem, 100);
				createSemesterDirectly(temppath, sem);
				cout << "Do you want to import Courses for Semester " << sem << " of Academic year " << acaye << " (y/n): ";
				cin >> choice;
				cin.ignore(1);
				if (choice == 'y')
				{
					importCourseDirectly(acaye, sem);
				}
				else
					return;
			}
			else
				return;
		}
		else
			cout << "System error" << endl;
	}
}
void addAcayeTxt(char acaye[]) //used to update the academic year text file after the staff want to create a new one
{
	fstream aca;
	fstream temp;
	char path[100] = "../database/acaye/acaye.txt";

	if (PathExist(path))
	{
		aca.open(path, ios::in);
		temp.open("temp.txt", ios::out);
		if (!aca.is_open())
			cout << "System error";
		else
		{
			char line[100];
			int counter;
			aca >> counter;
			aca.ignore(1);
			temp << counter + 1 << endl;
			for (int i = 0; i < counter; i++)
			{
				aca.getline(line, 100);
				temp << line << endl;
			}
			temp << acaye;
		}
		aca.close();
		temp.close();

		transferTxt(aca, temp, path);
	}
	else
	{
		aca.open(path, ios::out);
		aca << 1 << endl;
		aca << acaye;
		aca.close();
	}
}


//Create Semester for an Academic year
void createSemesterDirectly(char path[], char sem[]) //used to create a semester after creating a academic year
{
	char temppath[100];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 100, "/");
	strcat_s(temppath, 100, sem);

	if (PathExist(temppath))
		cout << "This Semester is already exist" << endl;
	else
	{
		_mkdir(temppath);
		if (PathExist(temppath))
		{
			createFirstSemesterTxt(sem, path);
			cout << endl << "SEMESTER " << sem << " CREATED SUCCESSFULLY" << endl;
			cout << endl;
		}
		else
			cout << "System error" << endl;
	}
}
void createSemester()
{
	char path[100] = "../database/acaye/";
	char path_semester[100];
	char path_semester2[100];
	char acaye[100];

	cout << "Please type in the Academic year you want to create a new Semester in: ";
	cin.getline(acaye, 100);

	strcat_s(path, 100, acaye);
	strcpy_s(path_semester, 100, path);
	strcpy_s(path_semester2, 100, path);

	if (PathExist(path))
	{
		char sem[100];
		cout << "Please type in the name for the new Semester: ";
		cin.getline(sem, 100);

		strcat_s(path, 100, "/");
		strcat_s(path, 100, sem);

		if (PathExist(path))
			cout << "This Semester is already exist" << endl;
		else
		{
			_mkdir(path);
			if (PathExist(path))
			{
				cout << endl << "SEMESTER " << sem << " CREATED SUCCESSFULLY" << endl << endl;
				int count_sem;
				strcat_s(path_semester, 100, "/semester.txt");
				ifstream semester;
				semester.open(path_semester);
				if (checkEmptyTxt(semester))
				{
					semester.close();
					createFirstSemesterTxt(sem, path_semester2);
					char choice;
					cout << "Do you want to import Courses to the new Semester (y/n): ";
					cin >> choice;
					cin.ignore(1);
					if (choice == 'y' || choice == 'Y')
						importCourseDirectly(acaye, sem);

				}
				else
				{
					semester.close();
					addSemesterTxt(sem, path_semester2);
					char choice;
					cout << "Do you want to import Courses to the new Semester (y/n): ";
					cin >> choice;
					cin.ignore(1);
					if (choice == 'y' || choice == 'Y')
						importCourseDirectly(acaye, sem);
				}
			}
			else
				cout << "System error" << endl;
		}
	}
	else
		cout << "Academic year " << acaye << " does not exist" << endl;
}
void createFirstSemesterTxt(char semes[], char path[]) // used to create the text file when staff creates a new semester in an academic year
{
	char temppath[200];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 200, "/semester.txt");
	fstream sem;
	sem.open(temppath, ios::out);
	if (!sem.is_open())
		cout << "System error";
	else
	{
		sem << 1 << endl;
		sem << semes;
	}
	sem.close();
}

//Update Academic year
void updateAcaye()
{
	char path[100] = "../database/acaye/";
	char acaye[100];
	cout << "Please type in the Academic year you want to update: ";
	cin.getline(acaye, 100);
	strcat_s(path, 100, acaye);
	char newacaye[100];
	if (PathExist(path))
	{
		int choice=0;
		do
		{
			cout << "1. Rename Academic year" << endl;
			cout << "2. Rename a Semester in Academic year" << endl;
			cout << "3. Delete Academic year" << endl;
			cout << "4. Detele a Semester from an Academic year" << endl;
			cout << "5. Add a Semester to an Academic year" << endl;
			cout << "6. Import Courses to a semester of an Academic year" << endl;
			cout << "0. Exit" << endl;
			cout << "Please enter your choice: ";
			cin >> choice;
			cin.ignore(1);
			system("cls");
			if (choice == 1)
			{
				
				renameAcaye(path, acaye, newacaye);
				strcpy_s(path, 100, "../database/acaye/");
				strcat_s(path, 100, newacaye);
				system("pause");
				system("cls");
			}
			if (choice == 2)
			{
				renameSem(path);
				system("pause");
				system("cls");
			}
			if (choice == 3)
			{
				deleteAcayeDirectly(acaye);
				break;
			}
			if (choice == 4)
			{
				char sem[100];
				cout << "Please type in the Semester in Academic year " << acaye << " that you want to remove: ";
				cin.getline(sem, 100);
				deleteSemDirectly(acaye, sem);
				system("pause");
				system("cls");

			}
			if (choice == 5)
			{
				addSem(path, acaye);
				system("pause");
				system("cls");
			}
			if (choice == 6)
			{
				char sem[100];
				cout << "Please type in the Semester in Academic year " << acaye << " that you want to import Courses to: ";
				cin.getline(sem, 100);
				importCourseDirectly(acaye, sem);
				system("pause");
				system("cls");
			}
		} while (choice != 0);
	}
	else
		cout << "The Academic year " << acaye << " does not exist in the system" << endl;
}
void renameAcaye(char path[], char oldacaye[], char newacaye[])
{
	char newpath[100] = "../database/acaye/";
	cout << "Please enter the new Academic year name: ";
	cin.getline(newacaye, 100);
	strcat_s(newpath, 100, newacaye);
	if (rename(path, newpath) != 0)
		perror("Error renaming file");
	else
		renameAcayeTxt(oldacaye, newacaye);
	strcpy_s(oldacaye, 100, newacaye);
}
void renameAcayeTxt(char oldacaye[], char newacaye[])
{
	fstream aca;
	fstream temp;
	char path[100] = "../database/acaye/acaye.txt";
	aca.open(path, ios::in);
	temp.open("temp.txt", ios::out);
	if (!aca.is_open())
		cout << "System error";
	else
	{
		char line[100];
		int counter;
		aca >> counter;
		aca.ignore(1);
		temp << counter << endl;
		for (int i = 0; i < counter; i++)
		{
			aca.getline(line, 100);
			if (strcmp(line, oldacaye) == 0)
				temp << newacaye << endl;
			else
				temp << line << endl;
		}
	}
	aca.close();
	temp.close();

	transferTxt(aca, temp, path);

	cout << endl << "RENAME ACADEMIC YEAR SUCCESSFULLY" << endl << endl;
	
}
void deleteAcaye()
{
	char path[100] = "../database/acaye/";
	char acaye[100];
	cout << "Please type in the academic year you want to delete: ";
	cin.getline(acaye, 100);
	strcat_s(path, 100, acaye);
	if (PathExist(path))
	{
		deleteAcayeTxt(acaye);
		filesystem::remove_all(path);
	}
	else
		cout << "Academic year does not exsit" << endl;
}
void deleteAcayeDirectly(char acaye[])
{
	char path[100] = "../database/acaye/";
	strcat_s(path, 100, acaye);
	if (PathExist(path))
	{
		deleteAcayeTxt(acaye);
		filesystem::remove_all(path);
		cout << endl << "DELETE ACADEMIC YEAR SUCCESSFULLY" << endl << endl;
	}
	else
		cout << "Academic year does not exsit" << endl;
}
void deleteAcayeTxt(char acaye[])
{
	fstream aca;
	fstream temp;
	char path_acayetxt[100] = "../database/acaye/acaye.txt";
	aca.open(path_acayetxt, ios::in);
	temp.open("temp.txt", ios::out);
	if (!aca.is_open())
		cout << "System error";
	else
	{
		char line[100];
		int counter;
		aca >> counter;
		aca.ignore(1);
		if (counter - 1 == 0)
		{
			temp << 0 << endl;
		}
		else
		{
			temp << counter - 1 << endl;
			for (int i = 0; i < counter; i++)
			{
				aca.getline(line, 100);
				if (strcmp(line, acaye) == 0)
					continue;
				else
					temp << line << endl;
			}
		}
	}
	aca.close();
	temp.close();

	transferTxt(aca, temp, path_acayetxt);

}

//Update Semester
void renameSem(char path[])
{
	char oldsem[100], newsem[100];
	char oldpath[100], newpath[100];
	strcpy_s(oldpath, 100, path);
	strcat_s(oldpath, 100, "/");
	cout << "Please type in the Semester you want to rename: ";
	cin.getline(oldsem, 100);
	strcat_s(oldpath, 100, oldsem);
	if (PathExist(oldpath))
	{
		cout << "Please type in the new name for the chosen Semester: ";
		cin.getline(newsem, 100);
		strcpy_s(newpath, 100, path);
		strcat_s(newpath, 100, "/");
		strcat_s(newpath, 100, newsem);
		if (rename(oldpath, newpath) != 0)
			cout << "System error" << endl;
		else
		{
			renameSemTxt(path, oldsem, newsem);
		}

	}
	else
		cout << "The Semester " << oldsem << " does not exist" << endl;

}
void renameSemTxt(char path[], char oldsem[], char newsem[])
{
	char temppath[100];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 100, "/semester.txt");
	fstream sem;
	fstream temp;
	sem.open(temppath, ios::in);
	temp.open("temp.txt", ios::out);
	if (!sem.is_open())
		cout << "System error";
	else
	{
		char line[100];
		int counter;
		sem >> counter;
		sem.ignore(1);
		temp << counter << endl;
		for (int i = 0; i < counter; i++)
		{
			sem.getline(line, 100);
			if (strcmp(line, oldsem) == 0)
				temp << newsem << endl;
			else
				temp << line << endl;
		}
	}
	sem.close();
	temp.close();

	transferTxt(sem, temp, temppath);

	cout << endl << "RENAME SEMESTER SUCCESSFULLY" << endl << endl;
	
}
void deleteSem()
{
	char path[100] = "../database/acaye/";
	char acaye[100];
	cout << "Please type in the Academic year from which you want to delete a Semester: ";
	cin.getline(acaye, 100);
	strcat_s(path, 100, acaye);
	if (PathExist(path))
	{
		char sem[100];
		strcat_s(path, 100, "/");
		cout << "Please type in the Semester in Academic year " << acaye << " that you want to delete: ";
		cin.getline(sem, 100);
		strcat_s(path, 100, sem);
		if (PathExist(path))
		{
			deleteSemTxt(acaye, sem);
			filesystem::remove_all(path);
			cout << endl << "DELETE SEMESTER SUCCESSFULLY" << endl << endl;
		}
		else
			cout << "Semester does not exist" << endl;
	}
	else
		cout << "The academic year you typed in does not exist" << endl;

}
void deleteSemDirectly(char acaye[], char sem[])
{
	char path[100] = "../database/acaye/";
	strcat_s(path, 100, acaye);
	if (PathExist(path))
	{
		strcat_s(path, 100, "/");
		strcat_s(path, 100, sem);
		if (PathExist(path))
		{
			deleteSemTxt(acaye, sem);
			filesystem::remove_all(path);
			cout << endl << "DELETE SEMESTER SUCCESSFULLY" << endl << endl;
		}
		else
			cout << "Semester does not exist" << endl;
	}
	else
		cout << "The academic year you typed in does not exist" << endl;

}
void deleteSemTxt(char acaye[], char sem[])
{
	char path_semTxt[100] = "../database/acaye/";
	strcat_s(path_semTxt, 100, acaye);
	strcat_s(path_semTxt, 100, "/semester.txt");
	fstream fsem;
	fstream ftemp;
	fsem.open(path_semTxt, ios::in);
	ftemp.open("temp.txt", ios::out);
	if (!fsem.is_open())
		cout << "System error";
	else
	{
		char line[100];
		int counter;
		fsem >> counter;
		fsem.ignore(1);
		ftemp << counter - 1 << endl;
		for (int i = 0; i < counter; i++)
		{
			fsem.getline(line, 100);
			if (strcmp(line, sem) == 0)
				continue;
			else
				ftemp << line << endl;
		}
	}
	fsem.close();
	ftemp.close();

	transferTxt(fsem, ftemp, path_semTxt);
}
void addSem(char path[], char acaye[])
{
	char temppath[100];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 100, "/");
	char newsem[100];
	cout << "Please enter the new Semester you want to add in the chosen Academic year: ";
	cin.getline(newsem, 100);
	strcat_s(temppath, 100, newsem);
	if (PathExist(temppath))
		cout << "The Semester " << newsem << " has already existed in the chosen Academic year";
	else
	{
		_mkdir(temppath);
		if (PathExist(temppath))
		{
			addSemesterTxt(newsem, path);
			cout << endl << "ADD SEMESTER SUCCESSFULLY" << endl << endl;
			char choice;
			cout << "Do you want to import courses to semester " << newsem << " you have just created (y/n): ";
			cin >> choice;
			cin.ignore(1);
			if (choice == 'y')
			{
				importCourseDirectly(acaye, newsem);
			}
		}
		else
			cout << "System error" << endl;
	}
}
void addSemesterTxt(char semes[], char path[]) //used to update the semester text file after the staff update something in the semester 
{
	fstream sem;
	fstream temp;
	char temppath[100];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 100, "/semester.txt");

	sem.open(temppath, ios::in);
	temp.open("temp.txt", ios::out);

	if (!sem.is_open())
		cout << "System error";
	else
	{
		char line[100];
		int counter;
		sem >> counter;
		sem.ignore(1);
		temp << counter + 1 << endl;
		for (int i = 0; i < counter; i++)
		{
			sem.getline(line, 100);
			temp << line << endl;
		}
		temp << semes;
	}

	sem.close();
	temp.close();

	transferTxt(sem, temp, temppath);
	
}

//Import Course
void importCourse()
{
	char path_csv[100] = "../database/importCSV/";
	char csv[100];

	cout << "Please enter the name of CSV file you want to used for importing Courses: ";
	cin.getline(csv, 100);

	strcat_s(path_csv, 100, csv);
	strcat_s(path_csv, 100, ".csv");

	if (!PathExist(path_csv))
		cout << "There is no file name " << csv << " in folder importCSV" << endl;
	else
	{
		char path[100] = "../database/acaye/";
		char acaye[100];

		cout << "Please type in the Academic year that you want to import Courses to: ";
		cin.getline(acaye, 100);

		strcat_s(path, 100, acaye);
		if (PathExist(path))
		{
			char sem[100];

			cout << "Please type in the Semester you want to import Courses to: ";
			cin.getline(sem, 100);

			strcat_s(path, 100, "/");
			strcat_s(path, 100, sem);

			if (PathExist(path))
			{
				char path_StuCour[100];
				char path_coursename[100];

				strcpy_s(path_StuCour, 100, path);

				strcpy_s(path_coursename, 100, path);
				strcat_s(path_coursename, 100, "/coursename.txt");

				fstream coursename;
				coursename.open(path_coursename, ios::out);

				strcat_s(path, 100, "/course.txt");

				fstream coursetxt;
				fstream csvfile;
				fstream temp;

				csvfile.open(path_csv, ios::in);
				coursetxt.open(path, ios::out);

				if (!coursetxt.is_open() || !csvfile.is_open())
					cout << "System error";
				else
				{
					int counter = 0;
					course a;
					while (csvfile.good())
					{
						char foldername[101] = "../database/acaye/";
						strcat_s(foldername, 101, acaye);
						strcat_s(foldername, 101, "/");
						strcat_s(foldername, 101, sem);
						strcat_s(foldername, 101, "/");

						csvfile.getline(a.subID, 101, ';');
						coursetxt << a.subID << endl;

						strcat_s(foldername, 101, a.subID);
						strcat_s(foldername, 101, "_");

						coursename << a.subID;
						coursename << "_";

						csvfile.getline(a.subName, 101, ';');
						coursetxt << a.subName << endl;

						csvfile.getline(a.subclass, 101, ';');
						coursetxt << a.subclass << endl;
						strcat_s(foldername, 101, a.subclass);
						coursename << a.subclass << endl;

						csvfile.getline(a.lecAcc, 101, ';');
						coursetxt << a.lecAcc << endl;

						csvfile.getline(a.startdate, 101, ';');
						coursetxt << a.startdate << endl;

						csvfile.getline(a.enddate, 101, ';');
						coursetxt << a.enddate << endl;

						csvfile.getline(a.subDay, 101, ';');
						coursetxt << a.subDay << endl;

						csvfile.getline(a.starttime, 101, ';');
						coursetxt << a.starttime << endl;

						csvfile.getline(a.endtime, 101, ';');
						coursetxt << a.endtime << endl;

						csvfile.getline(a.subRoom, 101, '\n');
						coursetxt << a.subRoom << endl;
						coursetxt << endl;

						counter += 1;
						_mkdir(foldername);
						importStudenttoCourse(a.subclass, foldername);
						createAttendanceTxt(foldername, a.lecAcc);
						createCheckin(a.subclass, foldername);
						

					}
					coursetxt.close();
					csvfile.close();
					coursename.close();

					createCourseTxtWithCounter(coursetxt, temp, path, counter);
					createCourseNameTxt(coursename, temp, path_coursename, counter);
					createStudentCourseTxt(path_StuCour);

					cout << endl << "COURSES IMPORTED SUCCESSFULLY" << endl << endl;
				}
			}
			else
				cout << "The semester you typed in does not exist" << endl;
		}
		else
			cout << "The academic you typed in does not exist" << endl;
	}
}
void importCourseDirectly(char acaye[], char sem[])
{
	char pathcsv[100] = "../database/importCSV/";
	char csv[100];
	cout << "Please enter the name of CSV file you want to used for importing Courses: ";
	cin.getline(csv, 100);
	strcat_s(pathcsv, 100, csv);
	strcat_s(pathcsv, 100, ".csv");
	if (!PathExist(pathcsv))
		cout << "There is no file name " << csv << " in folder importCSV" << endl;
	else
	{
		char path[100] = "../database/acaye/";
		strcat_s(path, 100, acaye);
		strcat_s(path, 100, "/");
		strcat_s(path, 100, sem);

		char pathStuCour[100];
		strcpy_s(pathStuCour, 100, path);

		char cn[100];
		strcpy_s(cn, 100, path);
		strcat_s(cn, 100, "/coursename.txt");

		strcat_s(path, 100, "/course.txt");


		fstream courname;
		courname.open(cn, ios::out);

		fstream coursetxt;
		fstream csvfile;
		csvfile.open(pathcsv, ios::in);
		coursetxt.open(path, ios::out);
		if (!coursetxt.is_open() || !csvfile.is_open())
			cout << "System error";
		else
		{
			int counter = 0;
			course a;
			while (csvfile.good())
			{
				char foldername[101] = "../database/acaye/";
				strcat_s(foldername, 101, acaye);
				strcat_s(foldername, 101, "/");
				strcat_s(foldername, 101, sem);
				strcat_s(foldername, 101, "/");

				csvfile.getline(a.subID, 101, ';');
				coursetxt << a.subID << endl;

				strcat_s(foldername, 101, a.subID);
				strcat_s(foldername, 101, "_");

				courname << a.subID;
				courname << "_";

				csvfile.getline(a.subName, 101, ';');
				coursetxt << a.subName << endl;

				csvfile.getline(a.subclass, 101, ';');
				coursetxt << a.subclass << endl;
				strcat_s(foldername, 101, a.subclass);
				courname << a.subclass << endl;

				csvfile.getline(a.lecAcc, 101, ';');
				coursetxt << a.lecAcc << endl;

				csvfile.getline(a.startdate, 101, ';');
				coursetxt << a.startdate << endl;

				csvfile.getline(a.enddate, 101, ';');
				coursetxt << a.enddate << endl;

				csvfile.getline(a.subDay, 101, ';');
				coursetxt << a.subDay << endl;

				csvfile.getline(a.starttime, 101, ';');
				coursetxt << a.starttime << endl;

				csvfile.getline(a.endtime, 101, ';');
				coursetxt << a.endtime << endl;
				csvfile.getline(a.subRoom, 101, '\n');
				coursetxt << a.subRoom << endl;
				coursetxt << endl;

				counter += 1;
				_mkdir(foldername);
				importStudenttoCourse(a.subclass, foldername);
				createAttendanceTxt(foldername, a.lecAcc);
				createCheckin(a.subclass, foldername);

			}
			coursetxt.close();
			csvfile.close();
			courname.close();

			fstream temp;
			temp.open("temp.txt", ios::out);
			coursetxt.open(path, ios::in);
			temp << counter << endl;
			char line[101];
			while (coursetxt.peek() != EOF)
			{
				coursetxt.getline(line, 101, '\n');
				temp << line << endl;
			}
			coursetxt.close();
			temp.close();

			transferTxt(coursetxt, temp, path);

			courname.open(cn, ios::in);
			temp.open("temp.txt", ios::out);
			temp << counter << endl;
			while (courname.peek() != EOF)
			{
				courname.getline(line, 101, '\n');
				temp << line << endl;
			}
			courname.close();
			temp.close();

			transferTxt(courname, temp, cn);
			createStudentCourseTxt(pathStuCour);
			cout << endl << "COURSES IMPORTED SUCCESSFULLY" << endl << endl;
		}
	}
}

void createCourseTxtWithCounter(fstream &course, fstream &temp, char path[], int count_course)
{

	temp.open("temp.txt", ios::out);
	course.open(path, ios::in);

	temp << count_course << endl;
	char line[101];
	while (course.peek() != EOF)
	{
		course.getline(line, 101, '\n');
		temp << line << endl;
	}
	course.close();
	temp.close();

	transferTxt(course, temp, path);
}
void createCourseNameTxt(fstream& coursename, fstream& temp, char path_coursename[], int count_course)
{
	char line[101];

	coursename.open(path_coursename, ios::in);
	temp.open("temp.txt", ios::out);

	temp << count_course << endl;
	while (coursename.peek() != EOF)
	{
		coursename.getline(line, 101, '\n');
		temp << line << endl;
	}
	coursename.close();
	temp.close();

	transferTxt(coursename, temp, path_coursename);
}
void importStudenttoCourse(char Class[], char path[] /* ../database/acaye/2018-2019/fall/CM101_19APCS1*/)
{
	char temppath[100];
	strcpy_s(temppath, 100, path);
	strcat_s(temppath, 100, "/student.txt");

	char tempClass1[100], tempClass2[100];
	strcpy_s(tempClass1, 100, Class);
	strcpy_s(tempClass2, 100, Class);

	for (int i = 0; i < strlen(tempClass1) + 1; i++)
		tempClass1[i] = toupper(tempClass1[i]);
	for (int i = 0; i < strlen(tempClass2) + 1; i++)
		tempClass2[i] = tolower(tempClass2[i]);

	char path1[100] = "../database/class/";
	char path2[100] = "../database/class/";
	strcat_s(path1, 100, tempClass1);
	strcat_s(path2, 100, tempClass2);
	if (PathExist(path1))
	{
		strcat_s(path1, 100, "/student.txt");
		if (PathExist(path1))
		{
			int counter = 0;
			fstream stu;
			fstream stucour;
			char line[100];
			int track = 1;
			stu.open(path1, ios::in);
			stucour.open(temppath, ios::out);

			if (!stu.is_open() && !stucour.is_open())
				cout << "Cannot open file" << endl;
			else
			{
				stu >> counter;
				stu.ignore(1);
				stucour << counter << endl;
				while (stu.peek() != EOF)
				{
					stu.getline(line, 100);
					stucour << line << endl;
				}
			}
			stu.close();
			stucour.close();
		}
	}
	else if (PathExist(path2))
	{
		strcat_s(path2, 100, "/student.txt");
		if (PathExist(path2))
		{

			fstream stu;
			fstream stucour;
			char line[100];
			stu.open(path2, ios::in);
			stucour.open(temppath, ios::out);

			if (!stu.is_open() && !stucour.is_open())
				cout << "Cannot open file" << endl;
			else
			{
				while (stu.peek() != EOF)
				{
					stu.getline(line, 100);
					stucour << line << endl;
				}
			}
			stu.close();
			stucour.close();
		}
	}
}
void createAttendanceTxt(char path[] /*../database/acaye/2018-2019/fall/CM101_19APCS1*/, char LecAcc[])
{
	char apath[100];
	char spath[100];
	lecturer b;

	strcpy_s(apath, 100, path);
	strcat_s(apath, 100, "/attendance.txt");

	strcpy_s(spath, 100, path);
	strcat_s(spath, 100, "/student.txt");

	fstream atte;
	fstream stu;
	atte.open(apath, ios::out);
	stu.open(spath, ios::in);
	if (!atte.is_open() || !stu.is_open())
		cout << "Cannot open file" << endl;
	else
	{
		char line[100];
		atte << "1" << endl;
		if (searchLecturer(LecAcc, b))
		{
			atte << b.lecturerID << endl;
			atte << b.lecturerName << endl;
			atte << b.degree << endl;
			atte << b.gender << endl;
			atte << endl;

			while (stu.peek() != EOF)
			{
				stu.getline(line, 100);
				atte << line << endl;
			}
		}
		atte.close();
		stu.close();
	}
}
void createCheckin(char className[], char path[]) {
	string cloneClassName = "../database/class/" + string(className) + "/student.txt";
	string clonePath = string(path) + "/checkin.txt";
	ifstream fin(cloneClassName);
	int counter;
	fin >> counter;
	fin.ignore(1234, '\n');
	ofstream fout(clonePath);
	fout << counter << "\n";
	fout << "id,name,day 1,day 2,day 3,day 4,day 5,day 6,day 7,day 8,day 9,day 10,day 11\n";

	student student;
	for (int i = 0; i < counter; ++i) {
		fin.getline(student.studentID, 51, '\n');
		fin.getline(student.studentName, 51, '\n');
		fin.getline(student.gender, 51, '\n');
		fin >> student.birthday.yyyy >> student.birthday.mm >> student.birthday.dd;
		fin.ignore(1234, '\n');
		fin.ignore(1234, '\n');
		fout << student.studentID << ";" << student.studentName << ";";
		for (int j = 0; j < 10; ++j) {
			fout << "0;";
		}
		fout << "0\n";
	}

	fout.close();
	fin.close();
}
void createStudentCourseTxt(char path[] /*../database/acaye/2018-2019/fall*/)
{
	char stucourpath[100];
	strcpy_s(stucourpath, 100, path);
	strcat_s(stucourpath, "/student_course.txt");

	char courpath[100];
	strcpy_s(courpath, 100, path);
	strcat_s(courpath, "/coursename.txt");

	fstream stucour;
	fstream stu;
	fstream cour;

	stucour.open(stucourpath, ios::out);
	stu.open("../database/studentlist.txt", ios::in);
	cour.open(courpath, ios::in);

	if (!stucour.is_open() || !stu.is_open() || !cour.is_open())
		cout << "File error" << endl;
	else
	{
		int counter_stu, counter_cour;
		stu >> counter_stu;
		stu.ignore(1);
		stucour << counter_stu << endl;
		cour >> counter_cour;
		cour.ignore(1);
		int i = 0, j = 0;
		student* st = new student[counter_stu];
		course* co = new course[counter_cour];

		while (stu.peek() != EOF)
		{
			if (i < counter_stu)
			{

				stu.getline(st[i].className, 51);
				_strupr_s(st[i].className, 51);
				stu.getline(st[i].studentID, 51);
				stu.getline(st[i].studentName, 51);
				stu.getline(st[i].gender, 51);
				stu >> st[i].birthday.yyyy >> st[i].birthday.mm >> st[i].birthday.dd;
				stu.ignore(1);
				stu.ignore(1);
			}
			i += 1;
		}

		while (j < counter_cour)
		{
				cour.getline(co[j].subID, 101);
				j += 1;

		}

		for (int k = 0; k < counter_stu; k++)
		{
			stucour << st[k].studentID << endl;
			stucour << st[k].className << endl;
			int counter = 0;
			for (int l = 0; l < counter_cour; l++)
			{

				string cmpCL = string(st[k].className);
				string cmpST = string(co[l].subID);
				size_t found = cmpST.find(cmpCL);
				if (found != std::string::npos)
					counter += 1;
			}

			stucour << counter << endl;

			for (int l = 0; l < counter_cour; l++)
			{

				string cmpCL = string(st[k].className);
				string cmpST = string(co[l].subID);
				size_t found = cmpST.find(cmpCL);
				if (found != std::string::npos)
					stucour << co[l].subID << endl;
			}
			stucour << endl;
		}
	}
}

// View AcayeandSem
void viewAcayeandSem()
{
	ifstream facaye, fsemes;
	int count_acaye, count_semes;

	facaye.open("../database/acaye/acaye.txt");
	if (!facaye.is_open())
		cout << "Cannot load Academic Years." << endl;
	else
	{
		facaye >> count_acaye;
		facaye.ignore();
		year* y = new year[count_acaye];
		for (int i = 0; i < count_acaye; ++i)
			facaye.getline(y[i].yearID, 11, '\n');

		cout << "ACAMEMIC YEARS" << endl;
		for (int i = 0; i < count_acaye; ++i)
		{
			y[i].index = i + 1;
			cout << y[i].index << ". " << y[i].yearID << endl;

		}
		cout << "Please choose an Academic yearyou want to view: ";
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

		fsemes.open(link_sem);
		if (!fsemes.is_open())
			cout << endl << "Cannot load Semesters" << endl;
		else
		{
			fsemes >> count_semes;
			fsemes.ignore();
			sem* s = new sem[count_semes];
			for (int i = 0; i < count_semes; ++i)
				fsemes.getline(s[i].semID, 11, '\n');

			cout << "SEMESTER" << endl;
			for (int i = 0; i < count_semes; ++i)
			{
				s[i].index = i + 1;
				char temp_semID[11];
				strcpy_s(temp_semID, 11, s[i].semID);
				_strupr_s(temp_semID);
				cout << s[i].index << ". " << temp_semID << endl;
			}
		}
	}

}

//Add Course
void addCourse()
{
	char path[100] = "../database/acaye/";
	char cournamepath[100];
	char coursetpath[100];
	char stucourpath[100];
	char coursefpath[100];
	char acaye[100];
	cout << "Please type in the Academic year from which you want to add a course: ";
	cin.getline(acaye, 100);
	strcat_s(path, 100, acaye);
	if (PathExist(path))
	{
		strcat_s(path, 100, "/");
		char sem[100];
		cout << "Please type in the Semester in Academic year " << acaye << " from which you want to add a Course: ";
		cin.getline(sem, 100);
		strcat_s(path, 100, sem);
		if (PathExist(path))
		{
			strcpy_s(coursefpath, 100, path);
			strcat_s(coursefpath, 100, "/");
			strcpy_s(coursetpath,100 ,path);
			strcat_s(coursetpath, 100, "/course.txt");
			course a;
			char temp[100];
			cout << "Please enter the course's ID: ";
			cin.getline(a.subID, 101);
			_strupr_s(a.subID);
			strcat_s(coursefpath, 100, a.subID);
			strcat_s(coursefpath, 100, "_");
			cout << "Please enter the course's Class: ";
			cin.getline(a.subclass, 101);
			_strupr_s(a.subclass);
			strcat_s(coursefpath, 100, a.subclass);
			if (PathExist(coursefpath))
				cout << "This course has already existed in semester " << sem << " of academic year " << acaye << endl;
			else
			{
				_mkdir(coursefpath); //temppath ../database/acaye/2018-2019/fall/CM101_19APCS1
				cout << "Please enter the course's Name: ";
				cin.getline(a.subName, 101);
				cout << "Please enter the course's Lecturer Account: ";
				cin.getline(a.lecAcc, 101);
				importStudenttoCourse(a.subclass, coursefpath);
				createAttendanceTxt(coursefpath, a.lecAcc);
				cout << "Please enter the course's Start Date (yyyy mm dd): ";
				cin.getline(a.startdate, 101);
				cout << "Please enter the course's End Date (yyyy mm dd): ";
				cin.getline(a.enddate, 101);
				cout << "Please enter the course's Studying Day: ";
				cin.getline(a.subDay, 101);
				cout << "Please enter the course's Start Time (hh mm): ";
				cin.getline(a.starttime, 101);
				cout << "Please enter the course's End Time (hh mm): ";
				cin.getline(a.endtime, 101);
				cout << "Please enter the course's Classroom: ";
				cin.getline(a.subRoom, 101);
				addCoursetoTxt(a, path);
				addCoursetoCName(path, a);
				addCoursetoStuC(path, a);
				createCheckin(a.subclass, coursefpath);
				cout << endl << "ADD COURSE SUCCESSFULLY" << endl;
			}
		}
		else
			cout << "Semester " << sem << " does not exist in academic year " << acaye << endl;
	}
	else
		cout << "Academic year " << acaye << " does not exist" << endl;

}
void addCoursetoTxt(course &a, char path[] /*../database/acaye/2017-2018/fall*/)
{
	char courtxt[100];
	strcpy_s(courtxt, 100, path);
	strcat_s(courtxt, 100, "/course.txt");
	ifstream course_check;
	fstream coursetxt;
	fstream temp;

	course_check.open(courtxt);
	if (checkEmptyTxt(course_check))
	{
		course_check.close();
		coursetxt.open(courtxt, ios::out);
		if (!coursetxt.is_open())
			cout << "Cannot open file" << endl;
		else
		{
			coursetxt << 1 << endl;
			coursetxt << a.subID << endl;
			coursetxt << a.subName << endl;
			coursetxt << a.subclass << endl;
			coursetxt << a.lecAcc << endl;
			coursetxt << a.startdate << endl;
			coursetxt << a.enddate << endl;
			coursetxt << a.subDay << endl;
			coursetxt << a.starttime << endl;
			coursetxt << a.endtime << endl;
			coursetxt << a.subRoom << endl;
			coursetxt << endl;
			coursetxt.close();
		}

	}
	else
	{
		course_check.close();

		coursetxt.open(courtxt, ios::in);
		temp.open("temp.txt", ios::out);
		if (!coursetxt.is_open())
			cout << "Cannot open file" << endl;
		else
		{
			course cmp;
			int counter = 0;
			char line[100];
			coursetxt >> counter;
			coursetxt.ignore(1);
			counter += 1;
			temp << counter << endl;
			for (int i=0; i<counter-1; i++)
			{
				coursetxt.getline(cmp.subID, 100);
				coursetxt.getline(cmp.subName, 100);
				coursetxt.getline(cmp.subclass, 100);
				coursetxt.getline(cmp.lecAcc, 100);
				coursetxt.getline(cmp.startdate, 100);
				coursetxt.getline(cmp.enddate, 100);
				coursetxt.getline(cmp.subDay, 100);
				coursetxt.getline(cmp.starttime, 100);
				coursetxt.getline(cmp.endtime, 100);
				coursetxt.getline(cmp.subRoom, 100);
				coursetxt.ignore(1);

				temp << cmp.subID << endl;
				temp << cmp.subName << endl;
				temp << cmp.subclass << endl;
				temp << cmp.lecAcc << endl;
				temp << cmp.startdate << endl;
				temp << cmp.enddate << endl;
				temp << cmp.subDay << endl;
				temp << cmp.starttime << endl;
				temp << cmp.endtime << endl;
				temp << cmp.subRoom << endl;
				temp << endl;
			}
			temp << a.subID << endl;
			temp << a.subName << endl;
			temp << a.subclass << endl;
			temp << a.lecAcc << endl;
			temp << a.startdate << endl;
			temp << a.enddate << endl;
			temp << a.subDay << endl;
			temp << a.starttime << endl;
			temp << a.endtime << endl;
			temp << a.subRoom << endl;
			temp << endl;
		}
		coursetxt.close();
		temp.close();

		transferTxt(coursetxt, temp, courtxt);
	}


	
}
void addCoursetoCName( char path[] /*../database/acaye/2017-2019/fall*/, course &a )
{
	int count_coursename;
	char line[100];
	char path_coursename[100];
	strcpy_s(path_coursename, 100, path);
	strcat_s(path_coursename, 100, "/coursename.txt");

	fstream coursename;
	fstream temp;
	ifstream coursename_check;
	coursename_check.open(path_coursename);
	if (checkEmptyTxt(coursename_check))
	{
		coursename_check.close();

		coursename.open(path_coursename, ios::out);
		if (!coursename.is_open())
			cout << "System error" << endl;
		else
		{
			coursename << 1 << endl;
			coursename << a.subID << "_" << a.subclass << endl;
			coursename.close();
		}
	}
	else
	{
		coursename_check.close();

		coursename.open(path_coursename, ios::in);
		temp.open("temp.txt", ios::out);
		if (!coursename.is_open())
			cout << "System error" << endl;
		else
		{
			coursename >> count_coursename;
			coursename.ignore(1);
			count_coursename += 1;
			temp << count_coursename << endl;
			for (int i = 0; i < count_coursename - 1; i++)
			{
				coursename.getline(line, 100);
				temp << line << endl;
			}
			temp << a.subID << "_" << a.subclass << endl;
		}
		coursename.close();
		temp.close();

		transferTxt(coursename, temp, path_coursename);
	}
	
}
void addCoursetoStuC(char path[] /*../database/acaye/2017-2018/fall*/, course &a)
{
	student* st;
	course* tmp;
	char line[100];
	int counter_stu=0, counter_cour=0;
	char stucourpath[100];
	strcpy_s(stucourpath, 100, path);
	strcat_s(stucourpath, "/student_course.txt");

	fstream stucour;
	fstream temp;
	if (PathExist(stucourpath))
	{
		stucour.open(stucourpath, ios::in);
		temp.open("temp.txt", ios::out);
		if (!stucour.is_open())
			cout << "System error" << endl;
		else
		{
			stucour >> counter_stu;
			stucour.ignore();
			temp << counter_stu << endl;
			st = new student[counter_stu];
			int i = 0;
			while (i<counter_stu)
			{
				stucour.getline(st[i].studentID, 51);
				stucour.getline(st[i].className, 51);
				temp << st[i].studentID << endl;
				temp << st[i].className << endl;
				stucour >> counter_cour;
				stucour.ignore(1);
				if (strcmp(st[i].className, a.subclass) == 0)
				{
					if (counter_cour == 0)
					{
						temp << 1 << endl;
						temp << a.subID << "_" << a.subclass << endl;
						temp << endl;
						stucour.ignore(1);
					}
					else
					{
						temp << counter_cour + 1 << endl;
						tmp = new course[counter_cour];
						for (int j = 0; j < counter_cour; j++)
						{
							stucour.getline(tmp[j].subName, 101);
							temp << tmp[j].subName << endl;
						}
						temp << a.subID << "_" << a.subclass << endl;
						temp << endl;
						stucour.ignore(1);
						delete[]tmp;
					}
				}
				else
				{
					temp << counter_cour << endl;
					for (int j = 0; j < counter_cour; j++)
					{
						stucour.getline(line, 100);
						temp << line << endl;
					}
					temp << endl;
					stucour.ignore(1);
				}
				i++;
			}
			stucour.close();
			temp.close();
		}

		transferTxt(stucour, temp, stucourpath);
	}
	else
	{
		createStudentCourseTxt(path);
	}
}

//Edit Course
void editCourse()
{
	char path[100] = "../database/acaye/";
	char tpath[100];
	char acaye[100];
	cout << "Please type in the Academic year from which you want to edit a Course: ";
	cin.getline(acaye, 100);
	strcat_s(path, acaye);
	if (PathExist(path))
	{
		strcat_s(path, "/");
		char sem[100];
		cout << "Please type in the Semester in Academic year " << acaye << " to edit a Course from it: ";
		cin.getline(sem, 100);
		strcat_s(path, sem);
		strcpy_s(tpath, 100, path);
		if (PathExist(path))
		{
			strcat_s(path, "/");
			course a;
			cout << "Please type in the Course's ID you want to edit: ";
			cin.getline(a.subID, 101);
			_strupr_s(a.subID);
			strcat_s(path, a.subID);
			strcat_s(path, "_");
			cout << "Please type in the Course's Class you want to edit: ";
			cin.getline(a.subclass, 101);
			_strupr_s(a.subclass);
			strcat_s(path, a.subclass);
			if (PathExist(path))
			{
				int choice = 0;
				do
				{
					cout << "1. Change Course's Information" << endl;
					cout << "2. Remove Course" << endl;
					cout << "0. Exit" << endl;
					cout << "Please type in your choice: ";
					cin >> choice;
					cin.ignore(1);
					if (choice == 1)
					{
						changeCourseInfo(tpath, path, a.subID, a.subclass, sem, acaye);
					}
					if (choice == 2)
					{
						deleteCourseDirectly(acaye, sem, a.subID, a.subclass);
						break;
					}
				} while (choice != 0);

			}
			else
				cout << "There is no course " << a.subID << "_" << a.subclass << " in semester " << sem << " of academic year " << acaye << endl;

		}
		else
			cout << "Semester " << sem << " does not exist in academic year " << acaye << endl;
	}
	else
		cout << "The academic year" << acaye << " does not exist" << endl;
}
void changeCourseInfo(char tpath[], char fpath[], char ID[], char Class[], char sem[], char acaye[])
{
	int choice = 0;
	course a;
	cout << "Here is the information for Course " << ID << "_" << Class << ": " << endl;
	do
	{
		searchCourseInfo(tpath, ID, Class, a);
		cout << "1. Course's ID: " << a.subID << endl;
		cout << "2. Course's Name: " << a.subName << endl;
		cout << "3. Course's Class: " << a.subclass << endl;
		cout << "4. Course's Lecturer Account: " << a.lecAcc << endl;
		cout << "5. Course's Starting Date: " << a.startdate << endl;
		cout << "6. Course's Ending Date: " << a.enddate << endl;
		cout << "7. Course's Studying Day: " << a.subDay << endl;
		cout << "8. Course's Starting Time: " << a.starttime << endl;
		cout << "9. Course's Ending Time: " << a.endtime << endl;
		cout << "10. Course's Classroom: " << a.subRoom << endl;
		cout << "0. Exit" << endl;
		cout << "Please type in the choice to change Course's Information: ";
		cin >> choice;
		cin.ignore(1);
		if (choice == 1)
		{
			char newID[101];
			cout << "Please type in the new Course's ID: ";
			cin.getline(newID, 101);
			if (searchCourseInfo(tpath, newID, Class, a))
				cout << "Course with ID: " << newID << " has already existed" << endl;
			else
			{
				char newpath[100] = "../database/acaye/";
				strcat_s(newpath, acaye);
				strcat_s(newpath, "/");
				strcat_s(newpath, sem);
				strcat_s(newpath, "/");
				strcat_s(newpath, newID);
				strcat_s(newpath, "_");
				strcat_s(newpath, Class);

				editCourseIDFolder(fpath, tpath, newID, a);
				editCourseTxt(tpath, newID, a, 1, ID, Class);
				editCourseIDCourName(tpath, ID, newID, Class);
				editCourseIDStuCour(tpath, ID, newID, Class);

				strcpy_s(ID, 100, newID);
				strcpy_s(fpath, 100, newpath);
				cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;
			}
		}
		if (choice == 2)
		{
			char newName[101];
			cout << "Please type in the new Course's Name: ";
			cin.getline(newName, 101);
			editCourseTxt(tpath, newName, a, 2, ID, Class);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;
		}
		if (choice == 3)
		{
			cout << "Permission denied" << endl;
			cout << "Changing Class of a Course will cause damage to system" << endl;
			cout << "Consider delete Course and create new one" << endl;
			cout << endl;
		}
		if (choice == 4)
		{
			char newLecAcc[101];
			cout << "Please type in the new Course's Lecturer Account: ";
			cin.getline(newLecAcc, 101);
			editCourseTxt(tpath, newLecAcc, a, 4, ID, Class);
			updateLecinAttendance(fpath, newLecAcc);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;
		}
		if (choice == 5)
		{
			char newstartdate[101];
			cout << "Please type in the new Course's Starting Date: ";
			cin.getline(newstartdate, 101);
			editCourseTxt(tpath, newstartdate, a, 5, ID, Class);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;
		}
		if (choice == 6)
		{
			char newenddate[101];
			cout << "Please type in the new Course's Ending Date: ";
			cin.getline(newenddate, 101);
			editCourseTxt(tpath, newenddate, a, 6, ID, Class);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;

		}
		if (choice == 7)
		{
			char newDay[101];
			cout << "Please type in the new Course's Studying Day: ";
			cin.getline(newDay, 101);
			editCourseTxt(tpath, newDay, a, 7, ID, Class);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;

		}
		if (choice == 8)
		{
			char newstarttime[101];
			cout << "Please type in the new Course's Starting Time: ";
			cin.getline(newstarttime, 101);
			editCourseTxt(tpath, newstarttime, a, 8, ID, Class);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;

		}
		if (choice == 9)
		{
			char newendtime[101];
			cout << "Please type in the new Course's Ending Time: ";
			cin.getline(newendtime, 101);
			editCourseTxt(tpath, newendtime, a, 9, ID, Class);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;

		}
		if (choice == 10)
		{
			char newRoom[101];
			cout << "Please type in the new Course's Classroom: ";
			cin.getline(newRoom, 101);
			editCourseTxt(tpath, newRoom, a, 10, ID, Class);
			cout << endl << "EDIT COURSE SUCCESSFULLY" << endl << endl;

		}
	} while (choice != 0);

}
void editCourseIDFolder(char fpath[] /*../database/acaye/2018-2019/fall/CM101_19APCS1*/, char tpath[] /*../database/acaye/2018-2019/fall*/, char newInf[], course a)
{
	char newpath[100];
	strcpy_s(newpath, 100, tpath);
	strcat_s(newpath, 100, "/");
	strcat_s(newpath, 100, newInf);
	strcat_s(newpath, 100, "_");
	strcat_s(newpath, 100, a.subclass);
	if (PathExist(newpath))
		cout << "This Course has already existed" << endl;
	else
		rename(fpath, newpath);
}
void editCourseIDCourName(char tpath[] /*../database/acaye/2018-2019/fall*/, char oldID[], char newID[], char Class[])
{
	char path_coursename[100];
	strcpy_s(path_coursename, 100, tpath);
	strcat_s(path_coursename, 100, "/coursename.txt");

	char cmpcoursename[100];
	strcpy_s(cmpcoursename, 100, oldID);
	strcat_s(cmpcoursename, 100, "_");
	strcat_s(cmpcoursename, 100, Class);

	fstream fcoursename;
	fstream ftemp;

	fcoursename.open(path_coursename, ios::in);
	ftemp.open("temp.txt", ios::out);

	if (!fcoursename.is_open())
		cout << "System error" << endl;
	else
	{
		char line[100];
		while (fcoursename.peek() != EOF)
		{
			fcoursename.getline(line, 100);
			if (strcmp(line, cmpcoursename) == 0)
				ftemp << newID << "_" << Class << endl;
			else
				ftemp << line << endl;
		}
		fcoursename.close();
		ftemp.close();
	}
	transferTxt(fcoursename, ftemp, path_coursename);
}
void editCourseIDStuCour(char tpath[] /*../database/acaye/2018-2019/fall*/, char oldID[], char newID[], char Class[])
{
	char path_studentcoure[100];
	
	strcpy_s(path_studentcoure, 100, tpath);
	strcat_s(path_studentcoure, 100, "/student_course.txt");

	fstream fstudentcourse;
	fstream ftemp;

	fstudentcourse.open(path_studentcoure, ios::in);
	ftemp.open("temp.txt", ios::out);
	
	if (!fstudentcourse.is_open())
		cout << "System error" << endl;
	else
	{
		char cmpcoursename[100];
		strcpy_s(cmpcoursename, 100, oldID);
		strcat_s(cmpcoursename, 100, "_");
		strcat_s(cmpcoursename, 100, Class);
		char line[100];
		while (fstudentcourse.peek() != EOF)
		{
			fstudentcourse.getline(line, 100);
			if (strcmp(line, cmpcoursename) == 0)
				ftemp << newID << "_" << Class << endl;
			else
				ftemp << line << endl;
		}
		fstudentcourse.close();
		ftemp.close();
	}
	transferTxt(fstudentcourse, ftemp, path_studentcoure);
}
void editCourseTxt(char tpath[] /*../database/acaye/2018-2019/fall*/, char newInf[], course a, int choice, char ID[], char Class[])
{
	course b;
	char temppath[100];
	strcpy_s(temppath, 100, tpath);
	strcat_s(temppath, 100, "/course.txt");
	fstream course;
	fstream temp;
	course.open(temppath, ios::in);
	temp.open("temp.txt", ios::out);
	if (!course.is_open())
		cout << "Cannot open file" << endl;
	else
	{
		int counter;
		course >> counter;
		course.ignore(1);
		temp << counter << endl;
		for (int i=0; i<counter; i++)
		{
			course.getline(b.subID, 100);
			course.getline(b.subName, 100);
			course.getline(b.subclass, 100);
			course.getline(b.lecAcc, 100);
			course.getline(b.startdate, 100);
			course.getline(b.enddate, 100);
			course.getline(b.subDay, 100);
			course.getline(b.starttime, 100);
			course.getline(b.endtime, 100);
			course.getline(b.subRoom, 100);

			course.ignore(1);
			if (strcmp(b.subID, ID) == 0 && strcmp(b.subclass, Class) == 0)
			{
				if (choice == 1)
				{
					temp << newInf << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}

				if (choice == 2)
				{
					temp << b.subID << endl;
					temp << newInf << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 3)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << newInf << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 4)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << newInf << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 5)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << newInf << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 6)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << newInf << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 7)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << newInf << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 8)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << newInf << endl;
					temp << b.endtime << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 9)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << newInf << endl;
					temp << b.subRoom << endl;
					temp << endl;
				}
				if (choice == 10)
				{
					temp << b.subID << endl;
					temp << b.subName << endl;
					temp << b.subclass << endl;
					temp << b.lecAcc << endl;
					temp << b.startdate << endl;
					temp << b.enddate << endl;
					temp << b.subDay << endl;
					temp << b.starttime << endl;
					temp << b.endtime << endl;
					temp << newInf << endl;
					temp << endl;
				}
			}
			else
			{
				temp << b.subID << endl;
				temp << b.subName << endl;
				temp << b.subclass << endl;
				temp << b.lecAcc << endl;
				temp << b.startdate << endl;
				temp << b.enddate << endl;
				temp << b.subDay << endl;
				temp << b.starttime << endl;
				temp << b.endtime << endl;
				temp << b.subRoom << endl;
				temp << endl;
			}
		}
	}
	course.close();
	temp.close();

	transferTxt(course, temp, temppath);
}

//Delete Course
void deleteCourse()
{
	char path[100] = "../database/acaye/";
	char path_course[100];
	char path_coursename[100];
	char path_studentcourse[100];
	char acaye[100];
	cout << "Please type in the Academic year from which you want to remove a Course: ";
	cin.getline(acaye, 100);
	strcat_s(path, 100, acaye);
	if (PathExist(path))
	{
		strcat_s(path, 100, "/");
		char sem[100];
		cout << "Please enter the Semester from which you want to remove a Course: ";
		cin.getline(sem, 100);
		strcat_s(path, 100, sem);
		strcpy_s(path_course, 100, path);
		if (PathExist(path))
		{
			strcat_s(path, 100, "/");
			char ID[100];
			char Class[100];
			char course[100];
			cout << "Please type in the Course's ID you want to remove: ";
			cin.getline(ID, 100);
			strcpy_s(course, 100, ID);
			strcat_s(course, 100, "_");
			cout << "Please type in the Course's Class you want to remove: ";
			cin.getline(Class, 100);
			strcat_s(course, 100, Class);
			strcat_s(path, 100, course);
			if (PathExist(path))
			{
				strcpy_s(path_coursename, 100, path_course);
				strcpy_s(path_studentcourse, 100, path_course);

				strcat_s(path_coursename, 100, "/coursename.txt");
				strcat_s(path_course, 100, "/course.txt");
				strcat_s(path_studentcourse, 100, "/student_course.txt");
				deleteCourseinTxt(path_course, course);
				deleteCourseinCname(path_coursename, course);
				deleteCourseinStuC(path_studentcourse, course, ID, Class);
				filesystem::remove_all(path);
				cout << endl << "REMOVE COURSE SUCCESSFULLY" << endl << endl;
			}
			else
				cout << "Course " << course << " of semester " << sem << " of academic year " << acaye << " does not exist" << endl;
		}
		else
			cout << "Semester " << sem << " of academic year " << acaye << " does not exsit" << endl;
	}
	else
		cout << "Academic year " << acaye << " does not exist" << endl;
}
void deleteCourseDirectly(char acaye[], char sem[], char ID[], char Class[])
{
	char path[100] = "../database/acaye/";
	char path_course[100];
	char path_coursename[100];
	char path_studentcourse[100];

	char course[100];
	strcpy_s(course, 100, ID);
	strcat_s(course, 100, "_");
	strcat_s(course, 100, Class);

	strcat_s(path, 100, acaye);
	strcat_s(path, 100, "/");
	strcat_s(path, 100, sem);
	strcpy_s(path_course, 100, path);
	strcat_s(path, 100, "/");
	strcat_s(path, 100, course);

	strcpy_s(path_coursename, 100, path_course);
	strcpy_s(path_studentcourse, 100, path_course);

	strcat_s(path_coursename, 100, "/coursename.txt");
	strcat_s(path_course, 100, "/course.txt");
	strcat_s(path_studentcourse, 100, "/student_course.txt");

	if (PathExist(path_course))
		deleteCourseinTxt(path_course, course);
	else
		cout << "System error with course.txt" << endl;
	if (PathExist(path_coursename))
		deleteCourseinCname(path_coursename, course);
	else
		cout << "System error with coursename.txt" << endl;
	if (PathExist(path_studentcourse))
		deleteCourseinStuC(path_studentcourse, course, ID, Class);
	else
		cout << "System error with student_course.txt" << endl;
	filesystem::remove_all(path);

	cout << endl << "REMOVE COURSE SUCCESSFULLY" << endl << endl;

}
void deleteCourseinTxt(char path_course[], char cmpcourse[])
{
	fstream fcourse;
	fstream ftemp;
	int counter = 0;
	fcourse.open(path_course, ios::in);
	ftemp.open("temp.txt", ios::out);
	if (!fcourse.is_open())
		cout << "Cannot open file" << endl;
	else
	{
		fcourse >> counter;
		fcourse.ignore(1);
		counter -= 1;
		ftemp << counter << endl;
		course a;
		char templine[101];
		for (int i=0; i<counter+1; i++)
		{
			fcourse.getline(a.subID, 101);
			fcourse.getline(a.subName, 101);
			fcourse.getline(a.subclass, 101);
			fcourse.getline(a.lecAcc, 101);
			fcourse.getline(a.startdate, 101);
			fcourse.getline(a.enddate, 101);
			fcourse.getline(a.subDay, 101);
			fcourse.getline(a.starttime, 101);
			fcourse.getline(a.endtime, 101);
			fcourse.getline(a.subRoom, 101);
			fcourse.ignore(1);
			strcpy_s(templine, a.subID);
			strcat_s(templine, "_");
			strcat_s(templine, a.subclass);

			if (strcmp(templine, cmpcourse))
			{
				ftemp << a.subID << endl;
				ftemp << a.subName << endl;
				ftemp << a.subclass << endl;
				ftemp << a.lecAcc << endl;
				ftemp << a.startdate << endl;
				ftemp << a.enddate << endl;
				ftemp << a.subDay << endl;
				ftemp << a.starttime << endl;
				ftemp << a.endtime << endl;
				ftemp << a.subRoom << endl;
				ftemp << endl;
			}
			else
			{
				continue;
			}
		}
		fcourse.close();
		ftemp.close();

		transferTxt(fcourse, ftemp, path_course);
	}
}
void deleteCourseinCname(char path_coursename[], char course[])
{
	fstream fcoursename;
	fstream ftemp;
	int counter = 0;
	char line[100];
	fcoursename.open(path_coursename, ios::in);
	ftemp.open("temp.txt", ios::out);
	if (fcoursename.is_open())
	{
		fcoursename >> counter;
		fcoursename.ignore(1);
		counter -= 1;
		ftemp << counter << endl;
		while (fcoursename.peek() != EOF)
		{
			fcoursename.getline(line, 100);
			if (strcmp(line, course) == 0)
				continue;
			else
				ftemp << line << endl;
		}
	}
	fcoursename.close();
	ftemp.close();

	transferTxt(fcoursename, ftemp, path_coursename);
}
void deleteCourseinStuC(char path_studentcourse[], char coursecmp[], char ID[], char Class[])
{
	fstream fstudentcourse;
	fstream ftemp;

	int count_course, count_student;
	student *stu;
	course* cour;

	fstudentcourse.open(path_studentcourse, ios::in);
	ftemp.open("temp.txt", ios::out);

	if (!fstudentcourse.is_open())
		cout << "System error" << endl;
	else
	{
		fstudentcourse >> count_student;
		fstudentcourse.ignore(1);
		ftemp << count_student << endl;
		stu = new student[count_student];
		bool flag = false;
		for (int i = 0; i < count_student; i++)
		{
			fstudentcourse.getline(stu[i].studentID, 51);
			fstudentcourse.getline(stu[i].className, 51);
			ftemp << stu[i].studentID << endl;
			ftemp << stu[i].className << endl;
			fstudentcourse >> count_course;
			fstudentcourse.ignore(1);
			if (strcmp(stu[i].className, Class) == 0)
			{
				cour = new course[count_course];
				for (int j = 0; j < count_course; j++)
				{
					fstudentcourse.getline(cour[j].subID, 51);
					if (strcmp(cour[j].subID, coursecmp) == 0)
						flag = true;
				}
				fstudentcourse.ignore(1);
				if (flag == true)
				{
					ftemp << count_course - 1 << endl;
					for (int j = 0; j < count_course; j++)
					{
						if (strcmp(cour[j].subID, coursecmp) == 0)
							continue;
						else
							ftemp << cour[j].subID << endl;
					}
					ftemp << endl;
				}
				else
				{
					ftemp << count_course << endl;
					for (int j = 0; j < count_course; j++)
						ftemp << cour[j].subID << endl;
					ftemp << endl;
				}
				delete[]cour;
			}
			else
			{
				ftemp << count_course << endl;
				cour = new course[count_course];
				for (int j = 0; j < count_course; j++)
				{
					fstudentcourse.getline(cour[j].subID, 51);
					ftemp << cour[j].subID << endl;
				}
				fstudentcourse.ignore(1);
				ftemp << endl;
			}
		}

		fstudentcourse.close();
		ftemp.close();
	}
	transferTxt(fstudentcourse, ftemp, path_studentcourse);
}

//Remove Student from Course
void removeStudentfromCourse()
{
	char path[100] = "../database/acaye/";
	char acaye[100];
	char path_coursename[100];
	cout << "Please type in the academic year from which you want to remove a student from a course: ";
	cin.getline(acaye, 100);
	strcat_s(path, 100, acaye); //../database/acaye/2018-2019
	if (PathExist(path))
	{
		strcat_s(path, 100, "/"); //../database/acaye/2018-2019/
		char sem[100];
		cout << "Please type in the semester in academic year " << acaye << " that you want to remove a student from a course: ";
		cin.getline(sem, 100);
		strcat_s(path, 100, sem); //../database/acaye/2018-2019/fall
		strcpy_s(path_coursename, 100, path);
		if (PathExist(path))
		{
			strcat_s(path, 100, "/"); //../database/acaye/2018-2019/fall/
			char ID[100];
			char Class[100];
			cout << "Please type in the Course's ID in semester " << sem << " in academic year " << acaye << " that you want to remove a student from: ";
			cin.getline(ID, 100);
			strcat_s(path, 100, ID); //../database/acaye/2018-2019/fall/CM101
			strcat_s(path, 100, "_"); //../database/acaye/2018-2019/fall/CM101_
			cout << "Please type in the Course's Class for " << ID << " in semester " << sem << " in academic year " << acaye << " that you want to remove a student from: ";
			cin.getline(Class, 100);
			strcat_s(path, 100, Class); //../database/acaye/2018-2019/fall/CM101_19APCS1
			if (PathExist(path))
			{
				char stuID[51];
				cout << "Please type in the Student's ID you want to remove: ";
				cin.getline(stuID, 51);

				if (!searchStudent(path, stuID))
				{
					cout << "Student " << stuID << " has not enrolled in course " << ID << " of class " << Class << " in semester " << sem << " of academic year " << acaye << endl;
				}
				else
				{
					removeStudentfromCourseinTxt(path, stuID, ID, Class, sem, acaye);
					updateStudentinAttendance(path);
					removeStudentinStuC(path_coursename, stuID, ID, Class);
					removeStudentinCheckin(path, stuID);
					cout << endl << "REMOVE STUDENT SUCCESSFULLY" << endl;
				}
				
			}
			else
				cout << "Course " << ID << " for class " << Class << " does not exist in semester " << sem << " of academic year " << acaye << endl;
		}
		else
			cout << "Semester " << sem << " does not exist in academic year " << acaye << endl;
	}
	else
		cout << "Academic year " << acaye << " does not exist" << endl;
}
void removeStudentfromCourseinTxt(char path[], char stuID[] ,char ID[], char Class[], char sem[], char acaye[])
{
	char path_student[100];
	strcpy_s(path_student, 100, path);
	strcat_s(path_student, 100, "/student.txt");
	
	if (searchStudent(path_student, stuID))
	{
		fstream stu;
		fstream temp;
		stu.open(path_student, ios::in);
		temp.open("temp.txt", ios::out);
		if (!stu.is_open())
			cout << "Cannot open file" << endl;
		else
		{
			student a;
			char line[100];
			int counter = 0;
			stu >> counter;
			stu.ignore(1);
			counter -= 1;
			temp << counter << endl;
			for (int i = 0; i < counter + 1; i++)
			{
				stu.getline(a.studentID, 51);
				stu.getline(a.studentName, 51);
				stu.getline(a.gender, 51);
				stu >> a.birthday.yyyy >> a.birthday.mm >> a.birthday.dd;
				stu.ignore(1);
				stu.ignore(1);
				if (strcmp(a.studentID, stuID) == 0)
					continue;
				else
				{
					temp << a.studentID << endl;
					temp << a.studentName << endl;
					temp << a.gender << endl;
					temp << a.birthday.yyyy << " " << a.birthday.mm << " " << a.birthday.dd << endl;
					temp << endl;
				}
			}

		}
		stu.close();
		temp.close();

		transferTxt(stu, temp, path_student);
	}
}
void removeStudentinStuC(char path[] /*../database/acaye/2016-2017/fall*/, char stuID[], char ID[], char Class[])
{
	char path_studentcourse[100];
	strcpy_s(path_studentcourse, 100, path);
	strcat_s(path_studentcourse, "/student_course.txt");
	fstream fstudentcourse;
	fstream temp;
	int count_student, count_course;
	char line[100];
	char removecourse[100];
	strcpy_s(removecourse, 100, ID);
	strcat_s(removecourse, 100, "_");
	strcat_s(removecourse, 100, Class);
	student* stu;
	fstudentcourse.open(path_studentcourse, ios::in);
	temp.open("temp.txt", ios::out);
	if (!fstudentcourse.is_open())
		cout << "Cannot open file" << endl;
	else
	{
		fstudentcourse >> count_student;
		fstudentcourse.ignore(1);
		temp << count_student << endl;
		stu = new student[count_student];
		for (int i = 0; i < count_student; i++)
		{
			fstudentcourse.getline(stu[i].studentID, 51);
			temp << stu[i].studentID << endl;
			fstudentcourse.getline(stu[i].className, 51);
			temp << stu[i].className << endl;
			if (strcmp(stu[i].studentID, stuID) == 0)
			{
				fstudentcourse >> count_course;
				fstudentcourse.ignore(1);
				count_course -= 1;
				temp << count_course << endl;
				for (int j = 0; j < count_course + 1; j++)
				{
					fstudentcourse.getline(line, 100);
					if (strcmp(line, removecourse) == 0)
						continue;
					else
						temp << line << endl;
				}
				fstudentcourse.ignore(1);
				temp << endl;
			}
			else
			{
				fstudentcourse >> count_course;
				fstudentcourse.ignore(1);
				temp << count_course << endl;
				for (int j = 0; j < count_course; j++)
				{
					fstudentcourse.getline(line, 100);
					temp << line << endl;
				}
				fstudentcourse.ignore(1);
				temp << endl;
			}

		}
	}
	fstudentcourse.close();
	temp.close();
	transferTxt(fstudentcourse, temp, path_studentcourse);
}
void removeStudentinCheckin(char path[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/, char stuID[])
{
	char path_checkin[100];
	string cmpID = string(stuID);
	strcpy_s(path_checkin, path);
	strcat_s(path_checkin, 100, "/checkin.txt");

	fstream fcheckin, ftemp;
	fcheckin.open(path_checkin, ios::in);
	ftemp.open("temp.txt", ios::out);
	if (!fcheckin.is_open())
		cout << "System error" << endl;
	else
	{
		int count_student;
		char line[100];
		fcheckin >> count_student;
		ftemp << count_student - 1 << endl;
		fcheckin.ignore(1);
		fcheckin.getline(line, 100);
		ftemp << line << endl;
		for (int i = 0; i < count_student; i++)
		{
			fcheckin.getline(line, 100);
			string cmpLine = string(line);
			size_t found = cmpLine.find(cmpID);
			if (found != std::string::npos)
				continue;
			else
				ftemp << line << endl;
		}
		fcheckin.close();
		ftemp.close();
	}

	transferTxt(fcheckin, ftemp, path_checkin);
}

//Add Student to Course
void addStudenttoCourse()
{
	char path[100] = "../database/acaye/";
	char path_student[100];
	char path_studentcourse[100];
	char path_course[100];
	char path_attend[100];
	char path_checkin[100];
	char acaye[100];
	cout << "Please type in the academic year from which you want to add a student to a course: ";
	cin.getline(acaye, 100);
	strcat_s(path, 100, acaye); //../database/acaye/2018-2019
	if (PathExist(path))
	{
		strcat_s(path, 100, "/"); //../database/acaye/2018-2019/
		char sem[100];
		cout << "Please type in the semester in academic year " << acaye << " that you want to add a student to a course: ";
		cin.getline(sem, 100);
		strcat_s(path, 100, sem); //../database/acaye/2018-2019/fall
		if (PathExist(path))
		{
			strcpy_s(path_student, 100, path);
			strcpy_s(path_studentcourse, 100, path);
			strcat_s(path_student, 100, "/"); //../database/acaye/2018-2019/fall/
			char ID[100];
			char Class[100];
			cout << "Please type in the Course's ID in semester " << sem << " in academic year " << acaye << " that you want to add a student to: ";
			cin.getline(ID, 100);
			strcat_s(path_student, 100, ID); //../database/acaye/2018-2019/fall/CM101
			strcat_s(path_student, 100, "_"); //../database/acaye/2018-2019/fall/CM101_
			cout << "Please type in the Course's Class for " << ID << " in semester " << sem << " in academic year " << acaye << " that you want to add a student to: ";
			cin.getline(Class, 100);
			strcat_s(path_student, 100, Class); //../database/acaye/2018-2019/fall/CM101_19APCS1
			strcpy_s(path_attend, 100, path_student);
			strcpy_s(path_checkin, 100, path_student);
			if (PathExist(path_student))
			{
				student stu;
				bool check;
				addStudenttoCourseinTxt(path_student, ID, stu, Class, sem, acaye, check);
				addStudenttoCourseinStuC(path_studentcourse, ID, Class, stu);
				updateStudentinAttendance(path_attend);
				addStudenttoCheckin(path_checkin, stu);
				cout << endl << "ADD STUDENT SUCCESSFULLY" << endl;

			}
			else
				cout << "Course " << ID << " for class " << Class << " does not exist in semester " << sem << " of academic year " << acaye << endl;
		}
		else
			cout << "Semester " << sem << " does not exist in academic year " << acaye << endl;
	}
	else
		cout << "Academic year " << acaye << " does not exist" << endl;
}
void addStudenttoCourseinTxt(char path_student[], char ID[], student &a ,char Class[], char sem[], char acaye[], bool &check)
{
	strcat_s(path_student, 100, "/student.txt");
	cout << "Please type in the Student's ID: ";
	cin.getline(a.studentID, 51);
	check = searchStudent(path_student, a.studentID);
	if (check)
		cout << "Student with ID " << a.studentID << " has already existed in course " << ID << " of class" << Class << " in semester " << sem << " of academic year " << acaye << endl;
	else
	{
		fstream stu;
		fstream temp;
		stu.open(path_student, ios::in);
		temp.open("temp.txt", ios::out);
		if (!stu.is_open())
			cout << "Cannot open file" << endl;
		else
		{
			cout << "Please type in Student's Name: ";
			cin.getline(a.studentName, 100);
			cout << "Please type in Student's Class: ";
			cin.getline(a.className, 100);
			cout << "Please type in the Student's Gender: ";
			cin.getline(a.gender, 100);
			cout << "Please type in the Student's DOB (yyyy mm dd): ";
			cin >> a.birthday.yyyy >> a.birthday.mm >> a.birthday.dd;
			cin.ignore(1);
			char line[100];
			int counter = 0;
			stu >> counter;
			stu.ignore(1);
			counter += 1;
			temp << counter << endl;
			student cmp;
			for (int i = 0; i < counter-1; i++)
			{
				stu.getline(cmp.studentID, 51);
				stu.getline(cmp.studentName, 51);
				stu.getline(cmp.gender, 51);
				stu >> cmp.birthday.yyyy;
				stu >> cmp.birthday.mm;
				stu>> cmp.birthday.dd;
				stu.ignore(1);
				stu.ignore(1);

				temp << cmp.studentID << endl;
				temp << cmp.studentName << endl;
				temp << cmp.gender << endl;
				temp << cmp.birthday.yyyy << " " << cmp.birthday.mm << " " << cmp.birthday.dd << endl;
				temp << endl;
			}

			temp << a.studentID << endl;
			temp << a.studentName << endl;
			temp << a.gender << endl;
			temp << a.birthday.yyyy << " " << a.birthday.mm << " " << a.birthday.dd << endl;
		}
		stu.close();
		temp.close();

		transferTxt(stu, temp, path_student);
	}
}
void addStudenttoCourseinStuC(char path_studentcourse[], char ID[], char Class[], student &a)
{
	bool check;
	char line[100];
	strcat_s(path_studentcourse, 100, "/student_course.txt");
	check = searchStudent(path_studentcourse, a.studentID);
	if (PathExist(path_studentcourse))
	{
		fstream fstudentcourse;
		fstream ftemp;
		fstudentcourse.open(path_studentcourse, ios::in);
		ftemp.open("temp.txt", ios::out);
		if (!fstudentcourse.is_open())
			cout << "Cannot open file" << endl;
		else
		{
			int i = 0;
			student* stu;
			int count_student = 0, count_cour = 0;
			fstudentcourse >> count_student;
			fstudentcourse.ignore(1);
			if (check == true)
			{
				ftemp << count_student << endl;
				stu = new student[count_student];
				for (int i = 0; i < count_student; i++)
				{
					fstudentcourse.getline(stu[i].studentID, 51);
					fstudentcourse.getline(stu[i].className, 51);
					ftemp << stu[i].studentID << endl;
					ftemp << stu[i].className << endl;
					if (strcmp(stu[i].studentID, a.studentID) == 0)
					{
						fstudentcourse >> count_cour;
						fstudentcourse.ignore(1);
						count_cour += 1;
						ftemp << count_cour << endl;
						for (int j = 0; j < count_cour - 1; j++)
						{
							fstudentcourse.getline(line, 100);
							ftemp << line << endl;
						}
						fstudentcourse.ignore(1);
						ftemp << ID << "_" << Class << endl;
						ftemp << endl;
					}
					else
					{
						fstudentcourse >> count_cour;
						fstudentcourse.ignore(1);
						ftemp << count_cour << endl;
						for (int j = 0; j < count_cour; j++)
						{
							fstudentcourse.getline(line, 100);
							ftemp << line << endl;
						}
						fstudentcourse.ignore(1);
						ftemp << endl;
					}
				}
			}

			else
			{
				stu = new student[count_student];
				ftemp << count_student + 1 << endl;
				for (int i = 0; i < count_student; i++)
				{
					fstudentcourse.getline(stu[i].studentID, 51);
					fstudentcourse.getline(stu[i].className, 51);
					ftemp << stu[i].studentID << endl;
					ftemp << stu[i].className << endl;
					fstudentcourse >> count_cour;
					fstudentcourse.ignore(1);
					ftemp << count_cour << endl;
					for (int j = 0; j < count_cour; j++)
					{
						fstudentcourse.getline(line, 100);
						ftemp << line << endl;
					}
					fstudentcourse.ignore(1);
					ftemp << endl;
				}
				ftemp << a.studentID << endl;
				ftemp << a.className << endl;
				ftemp << 1 << endl;
				ftemp << ID << "_" << Class << endl;
				ftemp << endl;
			}
			fstudentcourse.close();
			ftemp.close();
		}
		transferTxt(fstudentcourse, ftemp, path_studentcourse);
	}
	else
		cout << "System error" << endl;
}
void addStudenttoCheckin(char path_checkin[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/, student stu)
{
	strcat_s(path_checkin, 100, "/checkin.txt");

	fstream fcheckin, ftemp;

	fcheckin.open(path_checkin, ios::in);
	ftemp.open("temp.txt", ios::out);

	if (!fcheckin.is_open())
		cout << "System error" << endl;
	else
	{
		int count_student;
		char line[100];
		fcheckin >> count_student;
		ftemp << count_student + 1 << endl;
		fcheckin.ignore(1);
		fcheckin.getline(line, 100);
		ftemp << line << endl;
		for (int i = 0; i < count_student; i++)
		{
			fcheckin.getline(line, 100);
			ftemp << line << endl;
		}
		ftemp << stu.studentID << ";" << stu.studentName << ";0;0;0;0;0;0;0;0;0;0;0" << endl;
		fcheckin.close();
		ftemp.close();
	}
	transferTxt(fcheckin, ftemp, path_checkin);
}
void updateStudentinAttendance(char path[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/)
{
	char path_attendance[100], path_student[100];

	strcpy_s(path_attendance, 100, path);
	strcat_s(path_attendance, 100, "/attendance.txt");

	strcpy_s(path_student, 100, path);
	strcat_s(path_student, 100, "/student.txt");

	fstream attend, temp, student;
	attend.open(path_attendance, ios::in);
	temp.open("temp.txt", ios::out);
	if (!attend.is_open())
		cout<<"Cannot open old file"<<endl;
	else
	{
		char line[100];
		for (int i = 0; i < 5; i++)
		{
			attend.getline(line, 100);
			temp << line << endl;
		}
		temp << endl;
		attend.close();

		student.open(path_student, ios::in);
		if (!student.is_open())
			cout << "Cannot open student file" << endl;
		else
		{
			while (student.peek() != EOF)
			{
				student.getline(line, 100);
				temp << line << endl;
			}
			student.close();
		}
	}
	temp.close();

	transferTxt(attend, temp, path_attendance);

}

//Update Lecturer Info for AttendanceTxt for 1 course
void updateLecinAttendance(char path[] /*../database/acaye/2016-2017/fall/CM101_19APCS1*/, char newLecAcc[])
{
	char path_attendance[100], path_student[100];
	char path_lecturer[100] = "..database/account/lecturer.txt";

	lecturer a;

	strcpy_s(path_attendance, 100, path);
	strcat_s(path_attendance, 100, "/attendance.txt");


	strcpy_s(path_student, 100, path);
	strcat_s(path_student, 100, "/student.txt");

	fstream attend, temp, student;
	temp.open("temp.txt", ios::out);
	if (searchLecturer(newLecAcc, a))
	{
		temp << 1 << endl;
		temp << a.lecturerID << endl;
		temp << a.lecturerName << endl;
		temp << a.degree << endl;
		temp << a.gender << endl;
		temp << endl;
	}
	else
	{
		cout << "Lecturer account does not exist" << endl;
		return;
	}
	student.open(path_student, ios::in);
	if (!student.is_open())
		cout << "Cannot open student file" << endl;
	else
	{
		char line[100];
		while (student.peek() != EOF)
		{
			student.getline(line, 100);
			temp << line << endl;
		}
		student.close();
	}
	temp.close();

	transferTxt(attend, temp, path_attendance);

}

//Update Lecturer Info for all AttendanceTxt 
void UpdateLecturerinAttendance(lecturer& lec)
{
	char path_acaye[100] = "../database/acaye/";
	char path_semester[100];
	char path_course[100];
	char path_acatetxt[100] = "../database/acaye/acaye.txt";
	char path_semestertxt[100];
	char path_coursenametxt[100];
	char path_attendancetxt[100];
	fstream facaye, fsem, fcourse, fattend, ftemp;
	facaye.open(path_acatetxt, ios::in);
	if (!facaye.is_open())
		cout << "System error" << endl;
	else
	{
		char line_acaye[100];
		int count_acaye;
		facaye >> count_acaye;
		facaye.ignore(1);
		for (int i = 0; i < count_acaye; i++)
		{
			facaye.getline(line_acaye, 100); //2019-2020
			strcat_s(path_acaye, 100, line_acaye); //path_acaye: ..database/acaye/2019-2020
			strcpy_s(path_semester, 100, path_acaye); //path_semester: ..database/acaye/2019-2020
			if (PathExist(path_acaye))
			{
				strcpy_s(path_semestertxt, 100, path_acaye); //path_semestertxt: ..database/acaye/2019-2020
				strcat_s(path_semestertxt, 100, "/semester.txt"); //path_semestertxt: ..database/acaye/2019-2020/semester.txt
				fsem.open(path_semestertxt, ios::in);
				if (!fsem.is_open())
					cout << "System error" << endl;
				else
				{
					char line_semester[100];
					int count_semester;
					fsem >> count_semester;
					fsem.ignore(1);
					for (int j = 0; j < count_semester; j++)
					{
						fsem.getline(line_semester, 100);
						strcat_s(path_semester, 100, "/"); //path_semester: ..database/acaye/2019-2020/
						strcat_s(path_semester, 100, line_semester); //path_semester: ..database/acaye/2019-2020/fall
						if (PathExist(path_semester))
						{
							strcpy_s(path_coursenametxt, 100, path_semester); //path_coursenametxt: ..database/acaye/2019-2020/fall
							strcat_s(path_coursenametxt, 100, "/coursename.txt"); //path_coursenametxt: ..database/acaye/2019-2020/fall/coursename.txt
							strcpy_s(path_course, 100, path_semester); //path_course: ..database/acaye/2019-2020/fall
							strcat_s(path_course, 100, "/"); //path_course: ..database/acaye/2019-2020/fall/
							fcourse.open(path_coursenametxt, ios::in);
							if (!fcourse.is_open())
								cout << "System error" << endl;
							else
							{
								char line_coursename[100];
								int count_coursename;
								fcourse >> count_coursename;
								fcourse.ignore(1);
								for (int k = 0; k < count_coursename; k++)
								{
									fcourse.getline(line_coursename, 100);
									strcat_s(path_course, 100, line_coursename); //path_course: ..database/acaye/2019-2020/fall/CM101_19APCS1
									if (PathExist(path_course))
									{
										strcpy_s(path_attendancetxt, 100, path_course);
										strcat_s(path_attendancetxt, 100, "/attendance.txt");
										fattend.open(path_attendancetxt, ios::in);
										if (!fattend.is_open())
											cout << "System error" << endl;
										else
										{
											int count_lecturer;
											char line_lecturer[100];
											fattend >> count_lecturer;
											fattend.ignore(1);
											fattend.getline(line_lecturer, 100);
											if (strcmp(line_lecturer, lec.lecturerID) == 0)
											{
												fattend.close();
												updateLecinAttendance(path_course, lec.lecturerID);
											}
											else
											{
												fattend.close();
											}

										}
										strcpy_s(path_course, 100, path_semester); //path_course: ..database/acaye/2019-2020/fall
										strcat_s(path_course, 100, "/"); //path_course: ..database/acaye/2019-2020/fall/
									}

								}
								fcourse.close();
							}

						}
						strcpy_s(path_semester, 100, path_acaye);

					}
					fsem.close();
				}
			}
			strcpy_s(path_acaye, 100, "..database/acaye/");
		}
		facaye.close();
	}

}

//Update Student Info for all AttendanceTxt 
void UpdateStudentInAttendance(student& stu)
{
	char path_acaye[100] = "../database/acaye/";
	char path_semester[100];
	char path_course[100];
	char path_acatetxt[100] = "../database/acaye/acaye.txt";
	char path_semestertxt[100];
	char path_coursenametxt[100];
	char path_attendancetxt[100];
	char path_studenttxt[100];
	fstream facaye, fsem, fcourse, fattendance, fstudent, ftemp;
	facaye.open(path_acatetxt, ios::in);
	if (!facaye.is_open())
		cout << endl << "Cannot load Academic Years" << endl;
	else
	{
		char line_acaye[100];
		int count_acaye;
		facaye >> count_acaye;
		facaye.ignore();
		for (int i = 0; i < count_acaye; ++i)
		{
			facaye.getline(line_acaye, 100); //2019-2020
			strcat_s(path_acaye, 100, line_acaye); //path_acaye: ..database/acaye/2019-2020
			strcpy_s(path_semester, 100, path_acaye); //path_semester: ..database/acaye/2019-2020
			if (PathExist(path_acaye))
			{
				strcpy_s(path_semestertxt, 100, path_acaye); //path_semestertxt: ..database/acaye/2019-2020
				strcat_s(path_semestertxt, 100, "/semester.txt"); //path_semestertxt: ..database/acaye/2019-2020/semester.txt
				fsem.open(path_semestertxt, ios::in);
				if (!fsem.is_open())
					cout << endl << "Cannot load Semesters" << endl;
				else
				{
					char line_semester[100];
					int count_semester;
					fsem >> count_semester;
					fsem.ignore();
					for (int j = 0; j < count_semester; ++j)
					{
						fsem.getline(line_semester, 100);
						strcat_s(path_semester, 100, "/"); //path_semester: ..database/acaye/2019-2020/
						strcat_s(path_semester, 100, line_semester); //path_semester: ..database/acaye/2019-2020/fall
						if (PathExist(path_semester))
						{
							strcpy_s(path_coursenametxt, 100, path_semester); //path_coursenametxt: ..database/acaye/2019-2020/fall
							strcat_s(path_coursenametxt, 100, "/coursename.txt"); //path_coursenametxt: ..database/acaye/2019-2020/fall/coursename.txt
							strcpy_s(path_course, 100, path_semester); //path_course: ..database/acaye/2019-2020/fall
							strcat_s(path_course, 100, "/"); //path_course: ..database/acaye/2019-2020/fall/
							fcourse.open(path_coursenametxt, ios::in);
							if (!fcourse.is_open())
								cout << endl << " Cannot load Courses' Name." << endl;
							else
							{
								char line_coursename[100];
								int count_coursename;
								fcourse >> count_coursename;
								fcourse.ignore();
								for (int k = 0; k < count_coursename; ++k)
								{
									fcourse.getline(line_coursename, 100);
									strcat_s(path_course, 100, line_coursename); //path_course: ..database/acaye/2019-2020/fall/CM101_19APCS1
									if (PathExist(path_course))
									{
										strcpy_s(path_attendancetxt, 100, path_course);
										strcat_s(path_attendancetxt, 100, "/attendance.txt");
										fattendance.open(path_attendancetxt, ios::in);
										if (!fattendance.is_open())
											cout << endl << " Cannot load Attendance." << endl;
										else
										{
											int count1, count2;
											fattendance >> count1;
											fattendance.ignore();
											lecturer* newLecturer = new lecturer[count1];
											for (int m = 0; m < count1; ++m)
											{
												fattendance.getline(newLecturer[m].lecturerID, 51, '\n');
												fattendance.getline(newLecturer[m].lecturerName, 51, '\n');
												fattendance.getline(newLecturer[m].degree, 51, '\n');
												fattendance.getline(newLecturer[m].gender, 11, '\n');
												fattendance.ignore();
											}
											fattendance >> count2;
											fattendance.ignore();
											student* newStudent = new student[count2];
											for (int m = 0; m < count2; ++m)
											{
												fattendance.getline(newStudent[m].studentID, 51, '\n');
												fattendance.getline(newStudent[m].studentName, 51, '\n');
												fattendance.getline(newStudent[m].gender, 11, '\n');
												fattendance >> newStudent[m].birthday.yyyy >> newStudent[m].birthday.mm >> newStudent[m].birthday.dd;
												fattendance.ignore();
												fattendance.ignore();
											}
											for (int m = 0; m < count2; ++m)
											{
												if (strcmp(stu.studentID, newStudent[m].studentID) == 0)
												{
													strcpy_s(newStudent[m].studentName, stu.studentName);
													strcpy_s(newStudent[m].gender, stu.gender);
													newStudent[m].birthday.yyyy = stu.birthday.yyyy;
													newStudent[m].birthday.mm = stu.birthday.mm;
													newStudent[m].birthday.dd = stu.birthday.dd;
													break;
												}
											}
											fattendance.close();
											fattendance.open(path_attendancetxt, ios::out);
											if (!fattendance.is_open())
												cout << " Cannot save Attendance." << endl << endl;
											else
											{
												fattendance << count1 << endl;
												for (int m = 0; m < count1; ++m)
												{
													fattendance << newLecturer[m].lecturerID << endl;
													fattendance << newLecturer[m].lecturerName << endl;
													fattendance << newLecturer[m].degree << endl;
													fattendance << newLecturer[m].gender << endl << endl;
												}
												fattendance << count2 << endl;
												for (int m = 0; m < count2; ++m)
												{
													fattendance << newStudent[m].studentID << endl;
													fattendance << newStudent[m].studentName << endl;
													fattendance << newStudent[m].gender << endl;
													fattendance << newStudent[m].birthday.yyyy << " "
														<< newStudent[m].birthday.mm << " "
														<< newStudent[m].birthday.dd << endl << endl;
												}
											}
											delete[]newLecturer;
											delete[]newStudent;
										}
										fattendance.close();

										strcpy_s(path_studenttxt, 100, path_course);
										strcat_s(path_studenttxt, 100, "/student.txt");
										fstudent.open(path_studenttxt, ios::in);
										if (!fstudent.is_open())
											cout << endl << " Cannot load Students." << endl;
										else
										{
											int count_student;
											fstudent >> count_student;
											fstudent.ignore();
											student* newfile = new student[count_student];
											for (int m = 0; m < count_student; ++m)
											{
												fstudent.getline(newfile[m].studentID, 51, '\n');
												fstudent.getline(newfile[m].studentName, 51, '\n');
												fstudent.getline(newfile[m].gender, 11, '\n');
												fstudent >> newfile[m].birthday.yyyy >> newfile[m].birthday.mm >> newfile[m].birthday.dd;
												fstudent.ignore();
												fstudent.ignore();
											}
											for (int m = 0; m < count_student; ++m)
											{
												if (strcmp(stu.studentID, newfile[m].studentID) == 0)
												{
													strcpy_s(newfile[m].studentName, stu.studentName);
													strcpy_s(newfile[m].gender, stu.gender);
													newfile[m].birthday.yyyy = stu.birthday.yyyy;
													newfile[m].birthday.mm = stu.birthday.mm;
													newfile[m].birthday.dd = stu.birthday.dd;
													break;
												}
											}
											fstudent.close();
											fstudent.open(path_studenttxt, ios::out);
											fstudent << count_student << endl;
											for (int m = 0; m < count_student; ++m)
											{
												fstudent << newfile[m].studentID << endl
													<< newfile[m].studentName << endl
													<< newfile[m].gender << endl
													<< newfile[m].birthday.yyyy << " "
													<< newfile[m].birthday.mm << " "
													<< newfile[m].birthday.dd << endl << endl;
											}
											delete[]newfile;
										}
										fstudent.close();

										strcpy_s(path_course, 100, path_semester); //path_course: ..database/acaye/2019-2020/fall
										strcat_s(path_course, 100, "/"); //path_course: ..database/acaye/2019-2020/fall/
									}
								}
								fcourse.close();
							}
						}
						strcpy_s(path_semester, 100, path_acaye);
					}
					fsem.close();
				}
			}
			strcpy_s(path_acaye, 100, "..database/acaye/");
		}
		facaye.close();
	}
}

//Create Lecturer Info and Account
void createLecturer()
{
	char path_lecturertxt[100] = "../database/lecturer/lecturer.txt";
	char path_lectureracc[100] = "../database/account/lecturer.txt";

	lecturer lec;
	cout << "Please type in Lecturer's Name: ";
	cin.getline(lec.lecturerName, 51);
	cout << "Please type in Lecturer's ID: ";
	cin.getline(lec.lecturerID, 51);
	cout << "Please type in Lecturer's Degree: ";
	cin.getline(lec.degree, 51);
	cout << "Please type in Lecturer's Gender: ";
	cin.getline(lec.gender, 51);
	cout << "Please type in Lecturer's Password: ";
	cin.getline(lec.lecturerPass, 51);

	if (PathExist(path_lecturertxt))
	{
		lecturer templec;
		if (!searchLecturer(lec.lecturerID, templec))
		{
			addLecturerTxt(path_lecturertxt, lec);
			addLecturerAcc(path_lectureracc, lec);
			cout << endl << "LECTURER CREATED SUCCESSFULLY" << endl;
		}
		else
			cout << "ID "<<lec.lecturerID<<" is taken or this lecturer has existed in database" << endl;
	}
	else
	{
		createFirstLecturerTxt(path_lecturertxt, lec);
		createFirstLecturerAcc(path_lectureracc, lec);
		cout << endl << "LECTURER CREATED SUCCESSFULLY" << endl;

	}
}
void createFirstLecturerTxt(char path[], lecturer lec)
{
	fstream flecturer;

	flecturer.open(path, ios::out);

	if (!flecturer.is_open())
		cout << "System error" << endl;
	else
	{
		flecturer << 1 << endl;
		flecturer << lec.lecturerID << endl;
		flecturer << lec.lecturerPass << endl;
		flecturer << lec.lecturerName << endl;
		flecturer << lec.degree << endl;
		flecturer << lec.gender << endl;
		flecturer << endl;

		flecturer.close();
	}

}
void addLecturerTxt(char path[], lecturer lec)
{
	fstream flecture;
	fstream temp;

	flecture.open(path, ios::in);
	temp.open("temp.txt", ios::out);

	if (!flecture.is_open())
		cout << "System error" << endl;
	else
	{
		int count_lecturer;
		char line[100];

		flecture >> count_lecturer;
		flecture.ignore(1);

		lecturer* tmp = new lecturer[count_lecturer];

		temp << count_lecturer + 1 << endl;
		for (int i = 0; i < count_lecturer; i++)
		{
			flecture.getline(tmp[i].lecturerID, 51);
			flecture.getline(tmp[i].lecturerPass, 51);
			flecture.getline(tmp[i].lecturerName, 51);
			flecture.getline(tmp[i].degree, 51);
			flecture.getline(tmp[i].gender, 51);
			flecture.ignore(1);
			temp << tmp[i].lecturerID << endl;
			temp << tmp[i].lecturerPass << endl;
			temp << tmp[i].lecturerName << endl;
			temp << tmp[i].degree << endl;
			temp << tmp[i].gender << endl;
			temp << endl;
		}
		temp << lec.lecturerID << endl;
		temp << lec.lecturerPass << endl;
		temp << lec.lecturerName << endl;
		temp << lec.degree << endl;
		temp << lec.gender << endl;

		flecture.close();
		temp.close();
	}

	transferTxt(flecture, temp, path);
}
void createFirstLecturerAcc(char path[], lecturer lec)
{
	ofstream flecacc;
	flecacc.open(path);
	if (!flecacc.is_open())
		cout << "System error" << endl;
	else
	{
		flecacc << 1 << endl;
		flecacc << lec.lecturerName << endl;
		flecacc << lec.lecturerID << endl;
		flecacc << lec.lecturerPass << endl;
		flecacc << endl;
		flecacc.close();
	}
}
void addLecturerAcc(char path[], lecturer lec)
{
	fstream flecacc;
	fstream temp;

	flecacc.open(path, ios::in);
	temp.open("temp.txt", ios::out);

	if (!flecacc.is_open())
		cout << "System error" << endl;
	else
	{
		int count_lecturer;
		char line[100];

		flecacc >> count_lecturer;
		flecacc.ignore(1);

		temp << count_lecturer + 1 << endl;
		lecturer* tmp = new lecturer[count_lecturer];

		for (int i = 0; i < count_lecturer; i++)
		{
			flecacc.getline(tmp[i].lecturerName, 51);
			flecacc.getline(tmp[i].lecturerID, 51);
			flecacc.getline(tmp[i].lecturerPass, 51);
			flecacc.ignore(1);
			temp << tmp[i].lecturerName << endl;
			temp << tmp[i].lecturerID << endl;
			temp << tmp[i].lecturerPass << endl;
			temp << endl;
		}
		temp << lec.lecturerName << endl;
		temp << lec.lecturerID << endl;
		temp << lec.lecturerPass << endl;

		flecacc.close();
		temp.close();
	}

	transferTxt(flecacc, temp, path);
}

//Edit Existing Lecturer Info and Account
void editLecturer()
{
	char lecID[51];
	lecturer lec;
	char path_acaye[100] = "../database/acaye/";
	char path_semester[100], path_course[100], path_lecturertxt[100], path_lectureracc[100];
	cout << "Please type in the Lecturer's ID you want to edit: ";
	cin.getline(lecID, 51);
	if (searchLecturer(lecID, lec))
	{
		int choice = 0;
		do
		{
			cout << "1. Lecturer's ID: " << lec.lecturerID << endl;
			cout << "2. Lecturer's Name: " << lec.lecturerName << endl;
			cout << "3. Lecturer's Degree: " << lec.degree << endl;
			cout << "4. Lecturer's Gender: " << lec.gender << endl;
			cout << "5. Lecturer's Password: " << lec.lecturerPass << endl;
			cout << "0. Exit" << endl;
			cout << "Please type in your choice: ";
			cin >> choice;
			cin.ignore(1);
			if (choice == 1 || choice==2)
			{
				cout << "Permission denied" << endl;
				cout << "Considering removing and creating new lecturer" << endl;
			}
			if (choice == 3)
			{
				char newInfo[100];
				cout << "Please type in Lecturer's New Degree: ";
				cin.getline(newInfo, 100);
				editLecturerTxt(lec, newInfo, choice);
				searchLecturer(lecID, lec);
				UpdateLecturerinAttendance(lec);
				if (searchLecturer(lecID, lec))
					cout << endl << "EDIT SUCCESSFULLY" << endl;
				else
					cout << "System error" << endl;
			}
			if (choice == 4)
			{
				char newInfo[100];
				cout << "Please type in Lecturer's New Gender: ";
				cin.getline(newInfo, 100);
				editLecturerTxt(lec, newInfo, choice);
				searchLecturer(lecID, lec);
				UpdateLecturerinAttendance(lec);
				if (searchLecturer(lecID, lec))
					cout << endl << "EDIT SUCCESSFULLY" << endl << endl;
				else
					cout << "System error" << endl;
			}
			if (choice == 5)
			{
				char newInfo[100];
				cout << "Please type in Lecturer's New Password: ";
				cin.getline(newInfo, 100);
				editLecturerTxt(lec, newInfo, choice);
				editLecturerAcc(lec, newInfo, choice);
				if (searchLecturer(lecID, lec))
					cout << endl << "EDIT SUCCESSFULLY" << endl << endl;
				else
					cout << "System error" << endl;
			}
		} while (choice != 0);
	}
	else
		cout << "Lecturer with ID " << lecID << " does not exist in database" << endl;
}
void editLecturerTxt(lecturer &lec, char newInfo[], char choice)
{
	char path_lecturertxt[100] = "../database/lecturer/lecturer.txt";
	fstream flec, temp;
	flec.open(path_lecturertxt, ios::in);
	temp.open("temp.txt", ios::out);
	if (!flec.is_open())
		cout << "System error" << endl;
	else
	{
		int count_lec;
		lecturer *cmp=new lecturer;
		flec >> count_lec;
		flec.ignore();
		temp << count_lec << endl;
		for (int i = 0; i < count_lec; i++)
		{
			flec.getline(cmp->lecturerID, 51);
			flec.getline(cmp->lecturerPass, 51);
			flec.getline(cmp->lecturerName, 51);
			flec.getline(cmp->degree, 51);
			flec.getline(cmp->gender, 51);
			if (strcmp(cmp->lecturerID, lec.lecturerID) == 0)
			{
				if (choice == 3) //degree
				{
					temp << lec.lecturerID << endl;
					temp << lec.lecturerPass << endl;
					temp << lec.lecturerName << endl;
					temp << newInfo << endl;
					temp << lec.gender << endl;
					temp << endl;
				}
				if (choice == 4) //gender
				{
					temp << lec.lecturerID << endl;
					temp << lec.lecturerPass << endl;
					temp << lec.lecturerName << endl;
					temp << lec.degree << endl;
					temp << newInfo << endl;
					temp << endl;
				}
				if (choice == 5) //password
				{
					temp << lec.lecturerID << endl;
					temp << newInfo << endl;
					temp << lec.lecturerName << endl;
					temp << lec.degree << endl;
					temp << lec.gender << endl;
					temp << endl;
				}
			}
			else
			{
				temp << cmp->lecturerID << endl;
				temp << cmp->lecturerPass << endl;
				temp << cmp->lecturerName << endl;
				temp << cmp->degree << endl;
				temp << cmp->gender << endl;
				temp << endl;
			}
			flec.ignore(1);
		}
		delete cmp;
		flec.close();
		temp.close();
	}

	transferTxt(flec, temp, path_lecturertxt);
}
void editLecturerAcc(lecturer& lec, char newInfo[], char choice)
{
	char path_lectureraccount[100] = "../database/account/lecturer.txt";
	fstream flec, temp;
	flec.open(path_lectureraccount, ios::in);
	temp.open("temp.txt", ios::out);
	if (!flec.is_open())
		cout << "System error" << endl;
	else
	{
		int count_lec;
		lecturer cmp;
		flec >> count_lec;
		flec.ignore();
		temp << count_lec << endl;
		for (int i = 0; i < count_lec; i++)
		{
			flec.getline(cmp.lecturerName, 51);
			flec.getline(cmp.lecturerID, 51);
			flec.getline(cmp.lecturerPass, 51);
			if (strcmp(cmp.lecturerID, lec.lecturerID) == 0)
			{
				if (choice == 5) //password
				{
					temp << lec.lecturerName << endl;
					temp << lec.lecturerID << endl;
					temp << newInfo << endl;
					temp << endl;
				}
			}
			else
			{
				temp << cmp.lecturerName << endl;
				temp << cmp.lecturerID << endl;
				temp << cmp.lecturerPass << endl;
				temp << endl;
			}
			flec.ignore(1);
		}
		flec.close();
		temp.close();
	}

	transferTxt(flec, temp, path_lectureraccount);
}

//Remove Existing Lecturer Info and Account
void removeLecturer()
{
	char path_lecturertxt[100] = "../database/lecturer/lecturer.txt";
	char path_lectureracc[100] = "../database/account/lecturer.txt";

	char lecID[51];
	lecturer lec;
	cout << "Please type in Lecturer's ID you want to remove: ";
	cin.getline(lecID, 51);
	if (searchLecturer(lecID, lec))
	{
		removeLecturerTxt(path_lecturertxt, lec);
		removeLecturerAcc(path_lectureracc, lec);
		if (!searchLecturer(lecID, lec))
			cout << endl << "REMOVE SUCCESSFULLY" << endl;
	}
	else
		cout << "Lecturer with ID " << lecID << " does not exist in database" << endl;

}
void removeLecturerTxt(char path[], lecturer lec)
{
	fstream flecture;
	fstream temp;

	lecturer cmp;

	flecture.open(path, ios::in);
	temp.open("temp.txt", ios::out);

	if (!flecture.is_open())
		cout << "System error" << endl;
	else
	{
		int count_lecturer;
		char line[100];

		flecture >> count_lecturer;
		flecture.ignore(1);
		temp << count_lecturer -1 << endl;
		for (int i = 0; i < count_lecturer; i++)
		{
			flecture.getline(cmp.lecturerID, 51);
			flecture.getline(cmp.lecturerPass, 51);
			flecture.getline(cmp.lecturerName, 51);
			flecture.getline(cmp.degree, 51);
			flecture.getline(cmp.gender, 51);
			flecture.ignore(1);

			if (strcmp(cmp.lecturerID, lec.lecturerID) == 0)
				continue;
			else
			{
				temp << cmp.lecturerID << endl;
				temp << cmp.lecturerPass << endl;
				temp << cmp.lecturerName << endl;
				temp << cmp.degree << endl;
				temp << cmp.gender << endl;
				temp << endl;
			}

		}
		flecture.close();
		temp.close();
	}

	transferTxt(flecture, temp, path);
}
void removeLecturerAcc(char path[], lecturer lec)
{
	fstream flecacc;
	fstream temp;

	lecturer cmp;

	flecacc.open(path, ios::in);
	temp.open("temp.txt", ios::out);

	if (!flecacc.is_open())
		cout << "System error" << endl;
	else
	{
		int count_lecturer;
		char line[100];

		flecacc >> count_lecturer;
		flecacc.ignore(1);

		temp << count_lecturer -1 << endl;

		for (int i = 0; i < count_lecturer; i++)
		{
			flecacc.getline(cmp.lecturerName, 51);
			flecacc.getline(cmp.lecturerID, 51);
			flecacc.getline(cmp.lecturerPass, 51);
			flecacc.ignore(1);

			if (strcmp(cmp.lecturerID, lec.lecturerID) == 0)
				continue;
			else
			{
				temp << cmp.lecturerName << endl;
				temp << cmp.lecturerID << endl;
				temp << cmp.lecturerPass << endl;
				temp << endl;
			}

		}
		flecacc.close();
		temp.close();
	}

	transferTxt(flecacc, temp, path);
}

//ViewLecturer
void viewAllLecturer()
{
	char path[100] = "../database/lecturer/lecturer.txt";

	ifstream flecturer;

	flecturer.open(path);

	if (!flecturer.is_open())
		cout << "System error" << endl;
	else
	{
		int count_lecturer;
		flecturer >> count_lecturer;
		flecturer.ignore(1);

		lecturer* lec = new lecturer[count_lecturer];
		for (int i = 0; i < count_lecturer; i++)
		{
			flecturer.getline(lec[i].lecturerID, 51);
			flecturer.getline(lec[i].lecturerPass, 51);
			flecturer.getline(lec[i].lecturerName, 51);
			flecturer.getline(lec[i].degree, 51);
			flecturer.getline(lec[i].gender, 51);
			flecturer.ignore(1);
		}
		cout << endl << "NUMBER OF LECTURER(S): " << count_lecturer << endl;
		for (int i = 0; i < count_lecturer; i++)
		{
			cout << "Lecturer's ID: " << lec[i].lecturerID << endl;
			cout << "Lecturer's Password: " << lec[i].lecturerPass << endl;
			cout << "Lecturer's Name: " << lec[i].lecturerName << endl;
			cout << "Lecturer's Degree: " << lec[i].degree << endl;
			cout << "Lecturer's Gender: " << lec[i].gender << endl;
			cout << endl;
		}
	}
}