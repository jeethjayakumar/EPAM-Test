/*
 * Main.cpp :
 * 1. Reads the file from input.csv.
 * 2. Two maps are maintained in this code:
 * 	  a. last_inprec_per_sym - for saving the last procesed input data based on symbol
 * 	  b. out_rec_data - for saving the output processed data based on symbol
 */
//#include <iostream>
//#include <fstream>
//#include <map>
#include "Fileproto.hpp"

using namespace std;

int main()
{
	ifstream  fin("input.csv", ios::in);
	ofstream  fout("output.csv", ios::out);
	InMap  last_inprec_per_sym;   // JJ: For maintaining last processed record for each sym
	OutMap out_rec_data;          // JJ: For Recording output formatted data
	bool stat;

	// JJ : If not able to open the file, then throw error and end execution.
	if (!fin)
	{
		cout<< "Error opening input file : input.csv "<<endl;
		cout<< "Aborting!!!"<<endl;
	}
	else
	{
		// JJ : For reading the data in input.csv
		stat = read_and_extract_data(fin, last_inprec_per_sym, out_rec_data);
		// JJ : For writing the data from out_rec_data to output.csv
		if ((stat == true) && !out_rec_data.empty())
			write_processed_data(fout, out_rec_data.begin(), out_rec_data.end());
		fin.close();
	}
	fout.close();
	return 0;
}



