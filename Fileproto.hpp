/*
 * Fileproto.hpp
 */

#ifndef FILEPROTO_HPP_
#define FILEPROTO_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdbool>
#include "FileProcessHeader.hpp"

void populate_input_data(std::string &symb, SymInfo &inp_obj, InMap &infil_dat);
void process_extracted_data(SymInfo &inp_rec_data, InMap &last_olddata, OutMap &out_rec_data);
bool read_and_extract_data(std::ifstream &fin, InMap &retain_olddata, OutMap &outfil_rec);
void write_processed_data(std::ofstream &fout, OutMapIterator it1, OutMapIterator it2);
void maintain_last_record(SymInfo &inp_rec_data, InMap &last_olddata);



#endif /* FILEPROTO_HPP_ */
