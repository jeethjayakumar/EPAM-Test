/*
 * ClassInitializer.cpp
 * Class SymDataProcessor member function definition - mainly setter and getter functions
 */
#include <iostream>
#include "FileProcessHeader.hpp"

using namespace std;

SymDataProcessor :: SymDataProcessor()
{
	max_timegap = 0;
	total_quantity = 0;
	max_trade_price = 0;
	quant_price_val = 0;
}

void SymDataProcessor :: set_max_timegap(long int timegap)
{
	max_timegap = timegap;
}

void SymDataProcessor :: set_total_quantity(long int quant)
{
	total_quantity = quant;
}
void SymDataProcessor :: set_max_trade_price(int trade_price)
{
	max_trade_price = trade_price;
}

void SymDataProcessor ::set_quant_price_val(int avg_price)
{
	quant_price_val = avg_price;
}

long int SymDataProcessor :: get_max_timegap()
{
	return max_timegap;
}

long int SymDataProcessor :: get_total_quantity()
{
	return total_quantity;
}

int SymDataProcessor :: get_max_trade_price()
{
	return max_trade_price;
}

int SymDataProcessor :: get_quant_price_val()
{
	return quant_price_val;
}




