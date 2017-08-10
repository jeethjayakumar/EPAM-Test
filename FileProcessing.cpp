/*
 * FileProcessing.cpp
 *
 * Main rouintes for File processing.
 * 1. read_and_extract_data()
 * 2. write_processed_data()
 */

#include "Fileproto.hpp"
#include <string>
#include <sstream>
using namespace std;

void verify_rec_data(const SymInfo &inp_dat)
{
	if ((inp_dat.timestamp < 0) ||
		!inp_dat.symb.length() ||
		(inp_dat.price < 0) ||
		(inp_dat.quantity < 0))
		throw -1;
}

/*
 * read_and_extract_data() :-
 * Input Parameters : fin - Input Filestream Object
 *                    retain_olddata - InputMap (string, SymInfo) - contains last processed data based on symb
 *                    SymInfo - OutputMap (string, SymDataProcessor) - for saving processed data based on symb
 * Output Return Type : bool - returns error if it comes across any issues with reading data
 * Description: Reads the input data from input.csv and save it on temporary object inp_dat.
 * 				inp_dat will be passed to process_extracted_data() and processed data will be saved in outfil_rec map.
 * 				Apart from that, save the last input record to retain_olddata map using maintain_last_record()
 */
bool read_and_extract_data(ifstream &fin, InMap &retain_olddata, OutMap &outfil_rec)
{
	string rawdata;
	string inpline;
	SymInfo inp_dat;
	int line_count =0;

	while(!getline(fin,inpline).eof())
	{
		stringstream dataline(inpline);
		getline(dataline, rawdata, ',');
		inp_dat.timestamp = stoll(rawdata);
		getline(dataline, rawdata, ',');
		inp_dat.symb = rawdata;
		getline(dataline, rawdata, ',');
		inp_dat.quantity = stoi(rawdata);
		getline(dataline, rawdata, ',');
		inp_dat.price = stoi(rawdata);

		try
		{
			verify_rec_data(inp_dat);
		}
		catch(int)
		{
			cout<<"Error verifying record "<<line_count<<" in file input.csv"<<endl;
			cout<<"Verify the records in the file... Aborting!!!"<<endl;
			return false;
		}
		line_count++;
		process_extracted_data(inp_dat, retain_olddata, outfil_rec);
		maintain_last_record(inp_dat,retain_olddata);
	}

	return 1;
}

/*
 * write_processed_data() :-
 * Input Parameters : fout - Output Filestream Object
 *                    it1 - OutMapIterator (string, SymDataProcessor) - Referring to beginning of output Map
 *                    it2 - OutMapIterator (string, SymDataProcessor) - Referring to end of output Map
 * Output Return Type : void
 * Description: Loops from it1 to it2 of the output map and writes the contents in iterator container to file.
 */
void write_processed_data(ofstream &fout, OutMapIterator it1, OutMapIterator it2)
{
	OutMapIterator it;

	if (fout.is_open())
	{
		for(it = it1; it != it2; it++)
		{
			fout << it->first <<",";
			fout << it->second.get_max_timegap()<<",";
			fout << it->second.get_total_quantity()<<",";
			fout << (it->second.get_quant_price_val()/it->second.get_total_quantity())<<",";
			fout << it->second.get_max_trade_price()<<endl;
		}
	}
}
