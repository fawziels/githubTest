#pragma once

/* Brianna Seisler
 * Multiplicative string hashing with linear probing
 * for Department data
 * Department.h
 */


class Department
{
public:
	Department();
	string departID, name, location, mgrId, admrDepartId;

	bool empty_since_start = true;

	//	void readDepFile(string input);
	int display(Department hash_table[], int hash_table_size);
	bool item_insert(Department hash_table[], string departID, string name, string location, string mgrId, string admrDepartId, int hash_table_size);
	int item_search(Department hash_table[], string key, int hash_table_size);
	int item_delete(Department hash_table[], string key, int hash_table_size);
	void write(Department hash_table[], int hash_table_size);
};
