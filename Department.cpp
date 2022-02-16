/* Brianna Seisler
 * Multiplicative string hashing with linear probing
 * for Department data
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

#include "Department.h"

string dInput, line, word;

Department::Department()
{
	departID = name = location = mgrId = admrDepartId = "";
};

int initial_value;
int multiplier;
int search_return;

int hash_function(string key, int hash_table_size)
{
	int pos = initial_value;
	for (int i = 0; i < key.size(); i++)
		pos = (pos * multiplier) + key[i];

	return pos % hash_table_size;
}

bool Department::item_insert(Department hash_table[], string departID, string name, string location, string mgrId, string admrDepartId, int hash_table_size)
{
	int bucket_index = hash_function(departID, hash_table_size);
	int bucket_probed = 0;
	//	cout << bucket_index;

	while (bucket_probed < hash_table_size)
	{
		if (hash_table[bucket_index].empty_since_start)
		{
			hash_table[bucket_index].departID = departID;
			hash_table[bucket_index].name = name;
			hash_table[bucket_index].location = location;
			hash_table[bucket_index].mgrId = mgrId;
			hash_table[bucket_index].admrDepartId = admrDepartId;
			hash_table[bucket_index].empty_since_start = false;

			return true;
		}
		bucket_index = (bucket_index + 1) % hash_table_size;
		bucket_probed++;
	}
	return false;
}

int Department::item_search(Department hash_table[], string key, int hash_table_size)
{
	int bucket_index = hash_function(key, hash_table_size);
	int bucket_probed = 0;

	while (bucket_probed < hash_table_size)
	{


		if (hash_table[bucket_index].location == key)
			return bucket_index;
		if (hash_table[bucket_index].departID == key)
			return bucket_index;
		bucket_index = (bucket_index + 1) % hash_table_size;
		bucket_probed++;
	}
	return -1;
}

int Department::item_delete(Department hash_table[], string key, int hash_table_size)
{
	int bucket_index = hash_function(key, hash_table_size);
	int bucket_probed = 0;

	while (bucket_probed <= hash_table_size)
	{
		//		cout << "hash - "<< hash_table[bucket_index].name << " Key - " << key <<endl;
		if (hash_table[bucket_index].departID == key)
		{
			hash_table[bucket_index].departID = "";
			hash_table[bucket_index].name = "";
			hash_table[bucket_index].location = "";
			hash_table[bucket_index].mgrId = "";
			hash_table[bucket_index].admrDepartId = "";
			hash_table[bucket_index].empty_since_start = true;
			return 1;
		}
		bucket_index = (bucket_index + 1) % hash_table_size;
		bucket_probed++;
	}

	return 0;
}

int Department::display(Department hash_table[], int hash_table_size)
{
	cout << endl;
	cout << "\n---------------------------------------------------- Department -------------------------------------------------\n-----------------------------------------------------------------------------------------------------------------\n";

	for (int i = 0; i < hash_table_size; i++)
	{
		if (hash_table[i].departID != "" && hash_table[i].name != "" && hash_table[i].location != "" &&
			hash_table[i].mgrId != "" && hash_table[i].admrDepartId != "")
		{

			cout << setw(15) << left << hash_table[i].departID;
			cout << setw(15) << left << hash_table[i].name;
			cout << setw(18) << left << hash_table[i].location;
			cout << setw(15) << left << hash_table[i].mgrId;
			cout << setw(15) << left << hash_table[i].admrDepartId;
			cout << endl;
		}

	}
	cout << endl;
	return 0;
}


void Department::write(Department hash_table[], int hash_table_size)
{
	ofstream file("Department_out.csv");

	// first line (key)
	file << "departId" << endl;

	// The table scheme
	for (int i = 0; i < (hash_table_size); i++)
	{
		// making sure not to write any empty files
		if (hash_table[i].departID != "" && hash_table[i].name != "" && hash_table[i].location != "" &&
			hash_table[i].mgrId != "" && hash_table[i].admrDepartId != "")
		{

			file << hash_table[i].departID << ","
				<< hash_table[i].name << ","
				<< hash_table[i].location << ","
				<< hash_table[i].mgrId << ","
				<< hash_table[i].admrDepartId << endl;
		}

	}
	// closing the file
	file.close();
}
