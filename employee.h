#pragma once
#define employee_h

// Header file for employee.cpp

class emp_table
{
public:
	
	emp_table();
	string emp_id, first_name, last_name, phone, salary, job, email, dep_id;
	bool empty_start = true;
	bool empty_delete = true;

	bool insert(emp_table table[], string emp_id, string first_name, string last_name, string phone, string salary, string job, string email, string dep_id, int size);
	void disp(emp_table table[], int size);
	int search(emp_table table[], string key, int size);
	void dlt(emp_table table[], string key, int size);
    void write(emp_table table[], int size);
	void proj(emp_table table[], string line, int size);

}; 