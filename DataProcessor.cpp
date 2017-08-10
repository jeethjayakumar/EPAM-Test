/*
 * DataProcessor.cpp
 * Main Functions Defined:
 * 1. process_extracted_data()
 * 2. maintain_last_record()
 * 3. calculate_max_time_gap()
 * 4. calculate_total_quantity()
 * 5. get_max_trade_price()
 */

#include <iostream>
#include <map>
#include "FileProcessHeader.hpp"

using namespace std;

/*
 * calculate_max_time_gap() :-
 * Input Parameters : inp_rec_data - SymInfo Reference Object - contains input_record_data processed from file
 *                    last_data - SymInfo Reference Object - contains last processed data based on symb
 *                    temp_obj - SymDataProcessor Refernce - contains last output data based on symb
 * Output Return Type : void
 * Description: Calculate the timegap between last saved record of the symb and current extract record of the symb.
 *              If new record, maxtimegap = 0; if calculated time gap is greater than the one already saved in temp_obj
 *              then rewrite the temp_obj data
 */
void calculate_max_time_gap(const SymInfo &inp_rec_data, const SymInfo &last_data, SymDataProcessor &temp_obj)
{
	long int diff = inp_rec_data.timestamp - last_data.timestamp;
	if (last_data.timestamp == 0) temp_obj.set_max_timegap(0);
	if (temp_obj.get_max_timegap() < diff)
		temp_obj.set_max_timegap(diff);

}

/*
 * calculate_total_quantity() :-
 * Input Parameters : inp_rec_data - SymInfo Reference Object - contains input extracted data of a symb
 *                    temp_obj - SymDataProcessor Reference Object - contains last output data based on symb
 *                    SymInfo - OutputMap (string, SymDataProcessor) - for saving processed data based on symb
 * Output Return Type : void
 * Description: Calculates total quantity for a symb and rewrite on temp_obj
 */
void calculate_total_quantity(const SymInfo &inp_rec_data, SymDataProcessor &temp_obj)
{
	int sum = temp_obj.get_total_quantity();
	sum += inp_rec_data.quantity;
	int quant_price = temp_obj.get_quant_price_val();
	quant_price += (inp_rec_data.quantity * inp_rec_data.price);

	temp_obj.set_total_quantity(sum);
	temp_obj.set_quant_price_val(quant_price);
}

/*
 * get_max_trade_price() :-
 * Input Parameters : inp_rec_data - SymInfo Reference Object - contains input extracted data of a symb
 *                    temp_obj - SymDataProcessor Reference Object - contains last output data based on symb
 *                    SymInfo - OutputMap (string, SymDataProcessor) - for saving processed data based on symb
 * Output Return Type : void
 * Description: Verifies if max_price in temp_obj is less than input data.
 * 				If yes, then it rewrites temp_obj
 */
void get_max_trade_price(const SymInfo &inp_rec_data, SymDataProcessor &temp_obj)
{
	if (temp_obj.get_max_trade_price() < inp_rec_data.price)
		temp_obj.set_max_trade_price(inp_rec_data.price);
}

/*
 * process_extracted_data() :-
 * Input Parameters : inp_rec_data - SymInfo Reference Object - contains extracted input data
 *                    last_olddata - InputMap (string, SymInfo) - contain last processed data for all symbs
 *                    out_rec_data - OutputMap (string, SymDataProcessor) - for saving processed data based on symb
 * Output Return Type : void
 * Description: First it verifies if the symb in the input_extracted_data has any previous records.
 *              If not present, then it will reset last_data to 0 else it will save the last processed data for the symb.
 *              This information is used for calculating all the necessary output data for the symb (max_timegap, total_quantity, max_price, avg_price)
 *              and this information will be first saved in temporary output obj.
 *              Then it will check in the output map if there is any record for the processed symb.
 *              If present, it will erase that record first. Then it will proceed to insert the new temp_obj to Outmap
 */
void process_extracted_data(SymInfo &inp_rec_data, InMap &last_olddata, OutMap &out_rec_data)
{
	SymDataProcessor temp_obj;
	SymInfo  last_data;
	OutMapIterator out_it;
	InMapIterator  in_it;

	if (!last_olddata.empty())
	{
		in_it = last_olddata.find(inp_rec_data.symb);
		if (in_it != last_olddata.end())
		{
			last_data = in_it->second;
		}
		else
		{
			last_data.price = 0;
			last_data.quantity = 0;
			last_data.timestamp = 0;
			last_data.symb = "";
		}
	}

	if (out_rec_data.empty())
	{
		temp_obj.set_max_timegap(0);
		temp_obj.set_max_trade_price(inp_rec_data.price);
		temp_obj.set_total_quantity(inp_rec_data.quantity);
		temp_obj.set_quant_price_val(inp_rec_data.quantity * inp_rec_data.price);
	}
	else
	{
		out_it = out_rec_data.find(inp_rec_data.symb);
		if (out_it != out_rec_data.end())
		{
			temp_obj = out_it->second;
			out_rec_data.erase(out_it);
		}
		calculate_max_time_gap(inp_rec_data, last_data, temp_obj); // Pass temp_obj by reference
		get_max_trade_price(inp_rec_data, temp_obj);
		calculate_total_quantity(inp_rec_data, temp_obj);
	}
	out_rec_data.insert(OutPair(inp_rec_data.symb, temp_obj));
}

/*
 * maintain_last_record() :-
 * Input Parameters : inp_rec_data - SymInfo Reference Object - contains current processed input data for a symb
 *                    last_olddata - InputMap (string, SymInfo) - map for last processed data for all symb
 * Output Return Type : void
 * Description: First checks if there is any record for the input symb in the map.
 * 				If present, it will first delete that record and then insert the new ones.
 */
void maintain_last_record(SymInfo &inp_rec_data, InMap &last_olddata)
{
	InMapIterator in_it = last_olddata.find(inp_rec_data.symb);

	if (in_it != last_olddata.end())
	{
		last_olddata.erase(in_it);
	}
	last_olddata.insert(InPair(inp_rec_data.symb, inp_rec_data));
}
