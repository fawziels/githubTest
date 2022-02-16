#pragma once
#include <string.h>
#include <string>

using namespace std;

#ifndef PROJECT_H_
#define PROJECT_H_

class Project
{
public:
	string projId, empId, projName, startDate, endDate, empTime;
	Project();
	bool empty_since_start = true;

	//void readProFile(string dInput);

	bool item_insert(Project hash_table[], string projId, string empId, string projName, string startDate, string endDate, string empTime, int hash_table_size);

	int item_search(Project hash_table[], string key, int hash_table_size);
	int item_delete(Project hash_table[], string key, int hash_table_size);

	int display(Project hash_table[], int hash_table_size);
	void Write(Project hash_table[], int hash_table_size);
};



#endif /* PROJECT_H_ */
