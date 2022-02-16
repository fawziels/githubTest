/* Tarun Katta
 * modulo hashing and chaining
 * for Project data
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>
#include <cmath>
#include <iomanip>

using namespace std;

#include "Project.h"

//string dInput, line, word;

Project::Project()
{
	projId = empId = projName = startDate = endDate = empTime = "";
};

/*int initial_value;
int multiplier;
int search_return;
*/
int hashp_function(string key, int hash_table_size)
{
	return key.length() % hash_table_size;
}

bool Project::item_insert(Project hash_table[], string projId, string empId, string projName, string startDate, string endDate, string empTime, int hash_table_size)
{
	int bucket_index = hashp_function(projId, hash_table_size);
	int bucket_probed = 0;

	while (bucket_probed < hash_table_size)
	{
		if (hash_table[bucket_index].empty_since_start)
		{
			hash_table[bucket_index].projId = projId;
			hash_table[bucket_index].empId = empId;
			hash_table[bucket_index].projName = projName;
			hash_table[bucket_index].startDate = startDate;
			hash_table[bucket_index].endDate = endDate;
			hash_table[bucket_index].empTime = empTime;
			hash_table[bucket_index].empty_since_start = false;
			return true;
		}
		bucket_index = (bucket_index + 1) % hash_table_size;
		bucket_probed++;
	}
	return false;
}

int Project::item_search(Project hash_table[], string key, int hash_table_size)
{
	int bucket_index = hashp_function(key, hash_table_size);
	int bucket_probed = 0;

	while (bucket_probed < hash_table_size)
	{
		if (hash_table[bucket_index].projId == key)
			return bucket_index;
		bucket_index = (bucket_index + 1) % hash_table_size;
		bucket_probed++;
	}
	return -1;
}

int Project::item_delete(Project hash_table[], string key, int hash_table_size)
{
	int bucket_index = hashp_function(key, hash_table_size);
	int bucket_probed = 0;

	while (bucket_probed <= hash_table_size)
	{
		if (hash_table[bucket_index].projId == key)
		{
			hash_table[bucket_index].projId = "";
			hash_table[bucket_index].empId = "";
			hash_table[bucket_index].projName = "";
			hash_table[bucket_index].startDate = "";
			hash_table[bucket_index].endDate = "";
			hash_table[bucket_index].empTime = "";
			hash_table[bucket_index].empty_since_start = true;
			return 1;
		}
		bucket_index = (bucket_index + 1) % hash_table_size;
		bucket_probed++;
	}

	return 0;
}

int Project::display(Project hash_table[], int pro_size)
{
	cout << "\n------------------------------------------- Project -------------------------------------------\n-----------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < pro_size; i++)
	{
		if (hash_table[i].projId != "" && hash_table[i].empId != "" && hash_table[i].projName != "" &&
			hash_table[i].startDate != "" && hash_table[i].endDate != "" && hash_table[i].empTime != "")
		{
			cout << setw(15) << left << hash_table[i].projId << "\t";
			cout << setw(15) << left << hash_table[i].empId << "\t";
			cout << setw(15) << left << hash_table[i].projName << "\t";
			cout << setw(15) << left << hash_table[i].startDate << "\t";
			cout << setw(15) << left << hash_table[i].endDate << "\t";
			cout << setw(15) << left << hash_table[i].empTime << "\t";
			cout << endl;
		}
	}

	return 0;
}

void Project::Write(Project hash_table[], int hash_table_size)
{
	ofstream fs;
	fs.open("Project_output.csv");
	if (fs.fail())
	{
		cout << "Unable to open project.csv Error Code: 'Failure'." << endl;
		exit(EXIT_FAILURE);
	}
	fs << "projId" << endl;
	for (int i = 0; i < hash_table_size; i++)
	{
		if (hash_table[i].projId != "" && hash_table[i].empId != "" && hash_table[i].projName != "" &&
			hash_table[i].startDate != "" && hash_table[i].endDate != "" && hash_table[i].empTime != "")
		{
			fs << hash_table[i].projId << ",";
			fs << hash_table[i].empId << ",";
			fs << hash_table[i].projName << ",";
			fs << hash_table[i].startDate << ",";
			fs << hash_table[i].endDate << ",";
			fs << hash_table[i].empTime << endl;
		}

	}
	fs.close();
}