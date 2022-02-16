/*Fawzi ElSharayheh
 Employee hash table
 With Adler-32 hshing function
 and quadratic probing*/

// Include necessary libraries
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <regex>

// Using standard library
using namespace std;

// Including the header file
#include "employee.h"

// Initializing values
 emp_table::emp_table()
 {
	 emp_id = first_name = last_name = phone = salary = job = email = dep_id = "";
 
 };

// The hashing function__Adler-32
 int func(string str, int size)
 {
	 //string str = to_string(key);
	 int c, a = 1, b = 0, m = 65521;
	 for (int i = 0; i < str.length(); i++)
	 {
		 c = str[i];
		 a = (a + c) % m;
		 b = (b + a) % m;
	 }
	 return ((b << 16) | a) % size;
 }

// the INSERT function
bool emp_table::insert(emp_table table[], string emp_id, string first_name,string last_name,string phone, string salary, string job, string email, string dep_id, int size)
{

	int pos = func(emp_id, size);
	int probe = 0;

	while (probe < size)
	{
		// making sure the it is inserting in an empty line
		if (table[pos].empty_start == true || table[pos].empty_delete == true)
		{
			table[pos].emp_id = emp_id;
			table[pos].first_name = first_name;
			table[pos].last_name = last_name;
			table[pos].phone = phone;
			table[pos].salary = salary;
			table[pos].job = job;
			table[pos].email = email;
			table[pos].dep_id = dep_id;

			table[pos].empty_start = false;
			table[pos].empty_delete = false;

			cout << "Inserted (" << emp_id << 
				", " << first_name << 
				", " << last_name << 
				", " << phone << 
				", " << salary << 
				", " << job << 
				", " << email << 
				"," << dep_id << 
				") into Employee\n";
			return true;
		}
			// initial values for the quadratic probing
			int c1 = 1, c2 = 1; 

			// quadratic probing sequence
			pos = (pos + c1 * probe + c2 * probe ^ 2) % size; 
			probe++;
	}
	return false;
}

// the SELECT function
int emp_table::search(emp_table table[], string key, int size)
{
	// Searching through the whole table, 
	// because last_name is being used instead of employee ID
	int pos = 0;
	while (pos < size)
	{
		if (table[pos].emp_id == key) { return pos; }
		else if (table[pos].last_name == key) { return pos; }
		else if (key == "*") { return 0; }
		pos++;
	}
	return -1;
}

// the display function
void emp_table::disp(emp_table table[], int size)
{
	cout << "\n------------------------------------------------ Employee ---------------------------------------------------------------\n";
		cout << "-------------------------------------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < size; i++)
	{
		// Making sure not to display any empty lines
		if(table[i].empty_start == false && table[i].empty_delete == false)
		{

			cout << setw(15) << left << table[i].emp_id;
			cout << setw(15) << left << table[i].first_name;
			cout << setw(15) << left << table[i].last_name;
			cout << setw(15) << left << table[i].phone;
			cout << setw(15) << left << table[i].salary;
			cout << setw(15) << left << table[i].job;
			cout << setw(20) << left << table[i].email;
			cout << setw(20) << left << table[i].dep_id;
			cout << endl;
		}
	}
}

// the Delete function
void emp_table::dlt(emp_table table[], string key, int size)
{
	int pos = func(key, size);
	int probe = 0;

	while (probe <= size)
	{
		if (table[pos].emp_id == key)
		{
			table[pos].emp_id = "";
			table[pos].first_name = "";
			table[pos].last_name = "";
			table[pos].phone = "";
			table[pos].salary = "";
			table[pos].job = "";
			table[pos].email = "";
			table[pos].dep_id = "";

			// setting the bucket as a empty after deletion
			table[pos].empty_delete = true;
		}

		// initial values for the quadratic probing
		int c1 = 1, c2 = 1; 

		// quadratic probing sequence
		pos = (pos + c1 * probe + c2 * probe ^ 2) % size;
		probe++;
	}

}

// the write function
void emp_table::write(emp_table table[], int size)
{
	ofstream file("employee_out.csv");

	// first line (key)
	file << table[0].emp_id << endl;

	// The table scheme
	for (int i = 0; i < (size); i++)
	{
		// making sure not to write any empty files
		if (table[i].empty_start == false && table[i].empty_delete == false)
		{
			file << table[i].emp_id << ","
				<< table[i].first_name << ","
				<< table[i].last_name << ","
				<< table[i].phone << ","
				<< table[i].salary << ","
				<< table[i].job << ","
				<< table[i].email << ","
				<< table[i].dep_id << endl;
		}
	}
	// closing the file
	file.close();
}


void emp_table::proj(emp_table table[], string line, int size)
{
	// regular expression for the bonus section
	regex emp_bonus("\\w*,(empId|(.*)),(firstName|(.*)),(lastName|(.*)),(phone|(.*)),(salary|(.*)),(job|(.*)),(email|(.*)),(departId|(.*))");
	smatch match_b;

	string word;
	string star;

	regex_search(line, match_b, emp_bonus);
	stringstream ss(match_b[0]);

	// grabbing the select function
	getline(ss, word, ')');
		stringstream ps(word);
		// selecting the third entry (lastname) to search for the employee
		getline(ps, star, ',');
		getline(ps, star, ',');
		getline(ps, star, ',');

		if (search(table, star, size) == 0) 
		{
			getline(ss, word, ')');
			getline(ss, word, ',');
			bool emp = false;
			bool first = false;
			bool last = false;
			bool phone = false;
			bool salary = false;
			bool job = false;
			bool email = false;
			bool dep = false;

			// Getting what info needed to be printed 
			while (getline(ss, word, ','))
			{
				if (word == "empId")
					emp = true;
				else if (word == "firstName")
					first = true;
				else if (word == "lastName")
					last = true;
				else if (word == "phone")
					phone = true;
				else if (word == "salary")
					salary = true;
				else if (word == "job")
					job = true;
				else if (word == "email")
					email = true;
				else if (word == "departId")
					dep = true;
			}

			// prints the info of each employee in the hashtable
			for (int i = 0; i < size; i++)
			{
				if (table[i].empty_start == false && table[i].empty_delete == false)
				{
					if (emp)
						cout << setw(15) << left << table[i].emp_id;
					if (first)
						cout << setw(15) << left << table[i].first_name;
					if (last)
						cout << setw(15) << left << table[i].last_name;
					if (phone)
						cout << setw(15) << left << table[i].phone;
					if (salary)
						cout << setw(15) << left << table[i].salary;
					if (job)
						cout << setw(15) << left << table[i].job;
					if (email)
						cout << setw(20) << left << table[i].email;
					if (dep)
						cout << setw(20) << left << table[i].dep_id;

					cout << endl;

				}
			}

		}
		else if (search(table, star, size) != -1)
		{
			int i = search(table, star, size);

			getline(ss, word, ')');
				getline(ss, word, ',');
				bool emp = false;
				bool first = false;
				bool last = false;
				bool phone = false;
				bool salary = false;
				bool job = false;
			bool email = false;
			bool dep = false;


			while (getline(ss, word, ','))
			{
				if (word == "empId")
					emp = true;
				else if (word == "firstName")
					first = true;
				else if (word == "lastName")
					last = true;
				else if (word == "phone")
					phone = true;
				else if (word == "salary")
					salary = true;
				else if (word == "job")
					job = true;
				else if (word == "email")
					email = true;
				else if (word == "departId")
					dep = true;
			}

			if (table[i].empty_start == false && table[i].empty_delete == false)
			{
				// Printing the Scheme
				if (emp)
					cout << setw(15) << left << table[0].emp_id;
				if (first)
					cout << setw(15) << left << table[0].first_name;
				if (last)
					cout << setw(15) << left << table[0].last_name;
				if (phone)
					cout << setw(15) << left << table[0].phone;
				if (salary)
					cout << setw(15) << left << table[0].salary;
				if (job)
					cout << setw(15) << left << table[0].job;
				if (email)
					cout << setw(20) << left << table[0].email;
				if (dep)
					cout << setw(20) << left << table[0].dep_id;

				cout << endl;

				// Printing the specific employee details 
				if (emp)
					cout << setw(15) << left << table[i].emp_id;
				if (first)
					cout << setw(15) << left << table[i].first_name;
				if (last)
					cout << setw(15) << left << table[i].last_name;
				if (phone)
					cout << setw(15) << left << table[i].phone;
				if (salary)
					cout << setw(15) << left << table[i].salary;
				if (job)
					cout << setw(15) << left << table[i].job;
				if (email)
					cout << setw(20) << left << table[i].email;
				if (dep)
					cout << setw(20) << left << table[i].dep_id;

				cout << endl;
			}
		}
		// If the select returns false
		else {
			cout << "No entries match query(*" << word << ") into Employee\n";
		}


}