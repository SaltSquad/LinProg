#include "SimplxTable.h"
#include <iostream>
#include <string>
using namespace std;
using ::SimplxTable;
int main() {
	const char* tests[3] = { "test1.txt" ,
							 "test2.txt" ,
							 "test3.txt" };
	SimplxTable table;
	for (size_t i = 0; i < 3; i++)
	{
		try {
			table.setupFile(tests[i]);
			cout << simplx_method(table);

			// table.print();
			cout << string(20, '=');
		}
		catch (string s)
		{
			cout << "Error!!!\n"
				 << s << endl;
		}

	}


	return 0;
}
