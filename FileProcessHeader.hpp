/*
 * FileProcessHeader.hpp :
 * Record Data structure Definition.
 * SymInfo - Structure defined for extracting record data from input file.
 * SymDataProcessor - Class defined for processing data extracted file and
 * 					  save data after processing for writing it back to output file.
 */

#ifndef FILEPROCESSHEADER_HPP_
#define FILEPROCESSHEADER_HPP_

#include <iostream>
#include <map>
#include <string>
#include <fstream>

typedef struct recinfo
{
	std::string	      symb;
	unsigned long int timestamp;
	int               quantity;
	int               price;
}SymInfo;

class SymDataProcessor
{
private:
	long int max_timegap;
	long int total_quantity;
	int      max_trade_price;
	int		 quant_price_val;
public:
	SymDataProcessor();
	void set_max_timegap(long int timegap);
	void set_total_quantity(long int quant);
	void set_max_trade_price(int trade_price);
	void set_quant_price_val(int quant_price);
	long int get_max_timegap();
	long int get_total_quantity();
	int get_max_trade_price();
	int get_quant_price_val();
	~SymDataProcessor(){}

};

typedef  std::map<std::string, SymInfo> InMap;
typedef  std::map<std::string, SymInfo>::iterator InMapIterator;
typedef  std::pair<std::string, SymInfo> InPair;
typedef  std::pair<std::string, SymDataProcessor> OutPair;
typedef  std::map<std::string, SymDataProcessor> OutMap;
typedef  std::map <std::string, SymDataProcessor>::iterator OutMapIterator;


#endif /* FILEPROCESSHEADER_HPP_ */
