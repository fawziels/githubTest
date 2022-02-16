/*
Fawzi Elsharayheh
Brianna Seisler
Tarun Katta

CSCE 2110.001
Dec-4th-2020
Project 2 Employee information using HASHTABLES*/

// Include necessary libraries
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <sstream>

// Using standard library
using namespace std;

// Including header files
#include "employee.h"
#include "Department.h"
#include "Project.h"


// Making an object to fetch the functionalities accordingly
emp_table empo;
Department depo;
Project proo;


int main() {

	/*--------Making the hashtables------------*/
	const int hash_table_size = 10;
	const int pro_size = 10;
	const int size = 10;
	emp_table emp_table[size];
	Department hash_table[hash_table_size];
	Project pro_table[10];


	// prompting user to input the .txt file
	string input;
	cout << "\nEnter the file name:  ";
	getline(cin, input);
	cout << endl;
	ifstream file;


	// opening the file
	file.open(input);

	// File check
	if (file.fail())
	{
		cout << "Unable to open " << input << ".........EXITING" << endl;
		exit(EXIT_FAILURE);
	}

	// reading lines from .txt
	string line;
	while (getline(file, line))
	{
		stringstream ss(line);
		
		// line number
		int ln = 0; 


		/*---------------------------------------------------------------------*/
		/*------------------------Regular expressions--------------------------*/
		/*---------------------------------------------------------------------*/
		// Using regular expression to assign each .csv file to its hashtable
		regex emp_pat("(.*)[.](csv)[ ](employee)(\r)");
		regex dep_pat("(.*)[.](csv)[ ](department)(\r)");
		regex pro_pat("(.*)[.](csv)[ ](project)(\r)");

		bool match_emp = regex_match(line, emp_pat);
		bool match_dep = regex_match(line, dep_pat);
		bool match_pro = regex_match(line, pro_pat);

		// Displaying the tables
		regex disp_pat("(DISPLAY\\(\\))(\r)");
		bool match_disp = regex_match(line, disp_pat);


		// Using regex to extract the functions
		string strFunc;
		regex str_func("INSERT|UPDATE|SELECT|DELETE|PROJECT");
		smatch match;
		smatch match2;
		smatch match3;
		smatch match_b;


		// employee functions
		regex emp_expr(",employee");
		string detst, st1, st2, st3, st4, st5, st6, st7, st8;
		int sind;
		regex st_detail("(\\w*|\\*),(\\w*|\\*),(\\w*|\\w*-\\w*|\\*),(\\w*|\\*),([a-zA-Z0-9\\.]*|\\*),(\\w*|\\*),([a-zA-Z0-9\\.]*|\\*),([a-zA-Z0-9\\.]*|\\*)");


		// Bonus function
		regex emp_bonus("\\w*,(empId|(.*)),(firstName|(.*)),(lastName|(.*)),(phone|(.*)),(salary|(.*)),(job|(.*)),(email|(.*)),(departId|(.*))");


		// department functions
		string detstr, str1, str2, str3, str4, str5, str6;
		int sindex;
		regex str_expr(",department");
		regex str_detail("\\w*,(\\w*|\\*),(\\w*|\\w*-\\w*|\\*),(\\w*|\\*),(\\w*|\\*)");


		// project functions
		regex pro_expr(",project");
		regex pro_detail("\\(\\([\\w\\,\\*\\/\\.]*");


		// Write function
		regex write_pat("(WRITE)(.*)");
		bool match_write = regex_match(line, write_pat);

		/*---------------------------------------------------------------------*/
		/*---------------allocating data into hashtables-----------------------*/
		/*---------------------------------------------------------------------*/
		// Opening the employee.csv and assigning it to its hashtable 
		if (match_emp)
		{
			// Fetching the .csv file from the input.txt
			string emp_file;
			getline(ss, emp_file, ' ');

			// opening the .csv file
			ifstream emp;
			emp.open(emp_file);

			// Error check
			if (emp.fail())
			{
				cout << "Unable to open " << emp_file << ". Error Code: 'Failure'.\n" << endl;
			}
			else cout << "Opening " << emp_file << endl;


			// Getting data from .csv file
			while (emp.good())
			{
				int j = 0, c = 0, pos = 1;
				emp_table[0].empty_start = false;
				emp_table[0].empty_delete = false;

				bool g = true;
				string iline, word, wordB, fs, line2;

				// diregarding the first line (key) 
				getline(emp, iline);

				// Getting each line in employee.csv 
				while (getline(emp, line2))
				{
					// Seperating the line
					stringstream fs(line2);

					// Making up the scheme for the table from the second line
					if (g)
					{
						while (j < 8)
						{
							getline(fs, word, ',');
							switch (j)
							{
							case(0):
								emp_table[0].emp_id = word;
								break;
							case(1):
								emp_table[0].first_name = word;
								break;
							case(2):
								emp_table[0].last_name = word;
								break;
							case(3):
								emp_table[0].phone = word;
								break;
							case(4):
								emp_table[0].salary = word;
								break;
							case(5):
								emp_table[0].job = word;
								break;
							case(6):
								emp_table[0].email = word;
								break;
							case(7):
								emp_table[0].dep_id = word;
								break;
							}j++;
						}
						g = false;
					}
					else
					{

						// Inserting the data
						int k = 0;
						while (k < 8)
						{
							getline(fs, wordB, ',');

							switch (k)
							{
							case(0):
								empo.emp_id = wordB;
								break;
							case(1):
								empo.first_name = wordB;
								break;
							case(2):
								empo.last_name = wordB;
								break;
							case(3):
								empo.phone = wordB;
								break;
							case(4):
								empo.salary = wordB;
								break;
							case(5):
								empo.job = wordB;
								break;
							case(6):
								empo.email = wordB;
								break;
							case(7):
								empo.dep_id = wordB;
								break;
							}k++;
						}
						empo.insert(emp_table, empo.emp_id, empo.first_name, empo.last_name, empo.phone, empo.salary, empo.job, empo.email, empo.dep_id, size);
					}
				}
			}
			cout << endl;

			//Closes the .csv file
			emp.close();
		}

		// Opening the department.csv and assigning it to its hashtable 
		else if (match_dep) {

			// Fetching the .csv file from the input.txt
			string dep_file, lined, wordd;
			getline(ss, dep_file, ' ');
			// opening the .csv file

			//depo.readDepFile(dep_file);

			int hash_table_size = 10;
			int initial_value;
			int multiplier;
			//int search_return;

			string item_value;
			initial_value = 3;
			multiplier = 5;

			ifstream file;
			file.open(dep_file);
			// Error check
			if (file.fail())
			{
				cout << "Unable to open " << dep_file << ". Error Code: 'Failure'." << endl;
				exit(EXIT_FAILURE);
			}
			cout << "Opening " << dep_file << endl;

			getline(file, lined); // Skip first line

			while (getline(file, lined))
			{
				stringstream s_stream(lined);
				int i = 0;
				while (i <= 4)
				{
					getline(s_stream, wordd, ',');

					switch (i)
					{
					case(0):
						depo.departID = wordd;
						break;
					case(1):
						depo.name = wordd;
						break;
					case(2):
						depo.location = wordd;
						break;
					case(3):
						depo.mgrId = wordd;
						break;
					case(4):
						depo.admrDepartId = wordd;
						break;
					}
					i++;
				}

				depo.item_insert(hash_table, depo.departID, depo.name, depo.location, depo.mgrId, depo.admrDepartId, hash_table_size);
				if (ln > 0) cout << "Inserted (" << depo.departID << ", " << depo.name << ", " << depo.location << ", " << depo.mgrId << ", " << depo.admrDepartId << ") into Department\n";
				ln++;
			}
			//Close the file
			cout << endl;
			file.close();

		}

		// Opening the project.csv and assigning it to its hashtable 
		else if (match_pro) {

			// Fetching the .csv file from the input.txt
			string pro_file, wordp, linep;
			getline(ss, pro_file, ' ');

			// opening the .csv file
			ifstream pro;
			pro.open(pro_file);

			if (pro.fail())
			{
				cout << "Unable to open " << pro_file << ". Error Code: 'Failure'.\n" << endl;
			}

			else cout << "Opening " << pro_file << endl;



			getline(pro, linep); // Skip first line
			bool p = true;
			string projId, empId, projName, startDate, endDate, empTime, word;
			int i = 0;
			while (getline(pro, linep))
			{
				stringstream s_stream(linep);

				if (p)
				{
					while (i <= 5)
					{
						getline(s_stream, wordp, ',');

						switch (i)
						{
						case(0):
							pro_table[0].projId = wordp;
							break;
						case(1):
							pro_table[0].empId = wordp;
							break;
						case(2):
							pro_table[0].projName = wordp;
							break;
						case(3):
							pro_table[0].startDate = wordp;
							break;
						case(4):
							pro_table[0].endDate = wordp;
							break;
						case(5):
							pro_table[0].empTime = wordp;
							break;
						}
						i++;
					}
					p = false;

				}
				else {
					cout << "Inserted (" << linep << ") into project" << endl;

					int i = 0;
					while (i <= 5)
					{
						getline(s_stream, wordp, ',');

						switch (i)
						{
						case(0):
							projId = wordp;
							break;
						case(1):
							empId = wordp;
							break;
						case(2):
							projName = wordp;
							break;
						case(3):
							startDate = wordp;
							break;
						case(4):
							endDate = wordp;
							break;
						case(5):
							empTime = wordp;
							break;
						}
						i++;
					}

					proo.item_insert(pro_table, projId, empId, projName, startDate, endDate, empTime, pro_size);
				}
			}
			cout << endl;
			pro.close();
		}

		// Displaying the tables
		else if (match_disp)
		{
			empo.disp(emp_table, size);
			depo.display(hash_table, hash_table_size);
			proo.display(pro_table, pro_size);
			cout << "\n\n";
		}

		// Wrtie function
		else if (match_write)
		{

			// writing the data into a new .csv file
			empo.write(emp_table, size);
			proo.Write(pro_table, pro_size);
			depo.write(hash_table, hash_table_size);

			cout << "WRITE" << "\n\n";
			cout << "Processing Complete!\n" << endl;

		}

		/*---------------------------------------------------------------------*/
		/*------------------------hashtables functionalities-------------------*/
		/*---------------------------------------------------------------------*/
		// Doing the functionalitioes on employee hash_table
		regex_search(line, match, emp_expr);
		if (match[0] == ",employee")
		{
			// grabbing the function to apply on the table
			regex_search(line, match3, str_func);
			strFunc = match3[0];

			// grabbing the data within the line
			regex_search(line, match2, st_detail);
			stringstream s_stream(match2[0]);
			for (int x = 0; x <= 7; x++)
			{
				getline(s_stream, detst, ',');
				switch (x)
				{
				case 0:
					st1 = detst;
					break;
				case 1:
					st2 = detst;
					break;
				case 2:
					st3 = detst;
					break;
				case 3:
					st4 = detst;
					break;
				case 4:
					st5 = detst;
					break;
				case 5:
					st6 = detst;
					break;
				case 6:
					st7 = detst;
					break;
				case 7:
					st8 = detst;
					break;

				}
			}

			// Implementing insert function into employee hashtable
			if (strFunc == "INSERT")
			{
				empo.insert(emp_table, st1, st2, st3, st4, st5, st6, st7, st8, size);
			}

			// Implementing Select function into employee hashtable
			else if (strFunc == "SELECT")
			{
				sind = empo.search(emp_table, st3, size);

				if (sind != -1) {
					cout << "Found  (" << emp_table[sind].emp_id <<
						", " << emp_table[sind].first_name <<
						", " << st3 <<
						", " << emp_table[sind].phone <<
						", " << emp_table[sind].salary <<
						", " << emp_table[sind].job <<
						", " << emp_table[sind].email <<
						"," << emp_table[sind].dep_id << ") into Employee\n";
				}
				else {
					cout << "No entries match query (" << st1 <<
						", " << st2 << ", " << st3 << ", " << st4 <<
						", " << st5 << ", " << st6 << ", " << st7 <<
						"," << st8 << ") into Employee\n";
				}
			}

			// Implementing update function into employee hashtable
			else if (strFunc == "UPDATE")
			{
				sind = empo.search(emp_table, st1, size);
				if (sind != -1) {
					emp_table[sind].emp_id = st1;
					emp_table[sind].phone = st4;
					emp_table[sind].salary = st5;
					emp_table[sind].job = st6;
					emp_table[sind].email = st7;
					emp_table[sind].dep_id = st8;
					cout << "Updated (" << st1 <<
						", " << st2 <<
						", " << st3 <<
						", " << st4 <<
						", " << st5 <<
						", " << st6 <<
						", " << st7 <<
						"," << st8 << ") into Employee\n";
				}
				else {
					cout << "Failed to Update (" << st1 <<
						", " << st2 << ", " << st3 << ", " << st4 <<
						", " << st5 << ", " << st6 << ", " << st7 <<
						"," << st8 << ") into Employee\n";
				}
			}

			// Implementing the delete function into the employee hashtable
			else if (strFunc == "DELETE")
			{
				// delete data
				if (empo.search(emp_table, st1, size) != -1) {
					empo.dlt(emp_table, st1, size);
					cout << "Deleted (" << st1 <<
						", " << st2 << ", " << st3 << ", " << st4 <<
						", " << st5 << ", " << st6 << ", " << st7 <<
						"," << st8 << ") in Employee" << endl;
				}
				else cout << "Failed to delete(" << st1 <<
					", " << st2 << ", " << st3 << ", " << st4 <<
					", " << st5 << ", " << st6 << ", " << st7 <<
					"," << st8 << ") in Employee" << endl;
			}

			// bonus section
			else if (strFunc == "PROJECT")
			{
				cout << endl;
				empo.proj(emp_table, line, size);

			}
		}


		// Doing the functionalitioes on Department hashtable
		regex_search(line, match, str_expr);
		if (match[0] == ",department")
		{
			regex_search(line, match3, str_func);
			strFunc = match3[0];
			regex_search(line, match2, str_detail);
			stringstream s_stream(match2[0]);

			for (int x = 0; x <= 4; x++)
			{
				getline(s_stream, detstr, ',');
				switch (x)
				{
				case 0:
					str1 = detstr;
					break;
				case 1:
					str2 = detstr;
					break;
				case 2:
					str3 = detstr;
					break;
				case 3:
					str4 = detstr;
					break;
				case 4:
					str5 = detstr;
					break;

				}
			}
			//					cout << strFunc << " - " << str1 << " - " << str2 << " - " << str3 << " - " << str4 << " - " << str5 <<endl;
								// Do more stuff here - call correct function based on strFunc using str1-4
			if (strFunc == "INSERT")
			{
				depo.item_insert(hash_table, str1, str2, str3, str4, str5, hash_table_size);
				cout << "Inserted (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ") in Department\n";

			}
			else if (strFunc == "SELECT")
			{
				sindex = depo.item_search(hash_table, str1, hash_table_size);

				if (sindex != -1 && hash_table[sindex].location == str3) {
					cout << "Found  (" << str1 << ", "
						<< hash_table[sindex].name << ", "
						<< hash_table[sindex].location << ", "
						<< hash_table[sindex].mgrId << ", "
						<< hash_table[sindex].admrDepartId << ") in Department\n";
				}
				else {
					cout << "No entries match query (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ") in Department\n";
				}
			}
			else if (strFunc == "UPDATE")
			{
				// update an exisitng data
				sindex = depo.item_search(hash_table, str1, hash_table_size);
				if (sindex != 0) {
					hash_table[sindex].name = str2;
					hash_table[sindex].location = str3;
					hash_table[sindex].mgrId = str4;
					hash_table[sindex].admrDepartId = str5;
					cout << "Updated (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ") in Department\n";

				}
				else {
					cout << "Failed to Update (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ") in Department\n";
				}
			}
			else if (strFunc == "DELETE")
			{
				// delete something
				if (depo.item_delete(hash_table, str1, hash_table_size))
					cout << str1 << " Deleted " << endl;
				else cout << "Failed to Delete (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << "*" << ") in Department\n";
				//					     cout << "Delete Something" << endl;
			}

		}


		// Doing the functionalitioes on Project hashtable
		regex_search(line, match, pro_expr);
		if (match[0] == ",project")
		{
			regex_search(line, match3, str_func);
			strFunc = match3[0];
			regex_search(line, match2, pro_detail);
			string values = match2[0];
			values = values.substr(2);
			stringstream s_stream(values);
			for (int x = 0; x <= 5; x++)
			{
				getline(s_stream, detstr, ',');
				switch (x)
				{
				case 0:
					str1 = detstr;
					break;
				case 1:
					str2 = detstr;
					break;
				case 2:
					str3 = detstr;
					break;
				case 3:
					str4 = detstr;
					break;
				case 4:
					str5 = detstr;
					break;
				case 5:
					str6 = detstr;
					break;

				}
			}

			// Do more stuff here - call correct function based on strFunc using str1-4
			if (strFunc == "INSERT")
			{
				proo.item_insert(pro_table, str1, str2, str3, str4, str5, str6, pro_size);
				cout << "Inserted (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ", " << str6 << ") into Project\n";


			}
			else if (strFunc == "SELECT")
			{
				sindex = proo.item_search(pro_table, str1, pro_size);

				if (sindex != -1) {
					cout << "Found  (" << pro_table[sindex].projId <<
						", " << pro_table[sindex].empId <<
						", " << st3 <<
						", " << pro_table[sindex].projName <<
						", " << pro_table[sindex].startDate <<
						", " << pro_table[sindex].endDate <<
						", " << pro_table[sindex].empTime << ") in Project\n";
				}
				else {
					cout << "No entries match query (" << st1 <<
						", " << st2 << ", " << st3 << ", " << st4 <<
						", " << st5 << ", " << st6 << ", " << ") in Project\n";
				}

			}
			else if (strFunc == "UPDATE")
			{
				// update an exisitng data
				sindex = proo.item_search(pro_table, str1, pro_size);
				if (sindex != 0) {
					pro_table[sindex].empId = str2;
					pro_table[sindex].projName = str3;
					pro_table[sindex].startDate = str4;
					pro_table[sindex].endDate = str5;
					pro_table[sindex].empTime = str6;
					cout << "Updated (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ", " << str6 << ") in Projet\n";

				}
				else {
					cout << "Failed to Update (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ", " << str6 << ") in Project\n";
				}

			}
			else if (strFunc == "DELETE")
			{
				// delete something from project table
				if (proo.item_delete(pro_table, str1, pro_size))
					cout << "Deleted (" << str1 << ", " << str2 << ", " << str3 << ", " << str4 << ", " << str5 << ", " << str6 << ") in Project\n";
				else cout << str1 << " Not found and Not Deleted " << endl;

			}


		}



		 
	}
}