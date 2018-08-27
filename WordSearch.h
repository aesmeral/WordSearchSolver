//
//  WordSearch.h
//  Word Search Solver
//
//  Created by Anthony Esmeralda on 8/19/18.
//  Copyright © 2018 Anthony Esmeralda. All rights reserved.
//

#ifndef WordSearch_h
#define WordSearch_h

#include "Grid.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>

class WordSearch {
private:
    Grid Word_Search_Table;
    std::vector<location> Word_List;
protected:
    std::vector<int> compute_fail_function(const std::string &pattern);
    int KMP_match(const std::string &text, const std::string &pattern);
    void find_in_row();
    void find_in_column();
    void find_in_diagonals();
public:
    WordSearch();
    void print_Table();
    void print_Diagonals();
    void print_Rows();
    void print_Columns();
    void print_List();
    void find_words();
    void print_Words_Found();
};

#endif /* WordSearch_h */
