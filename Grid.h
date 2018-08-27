//
//  Grid.h
//  Word Search Solver
//
//  Created by Anthony Esmeralda on 8/18/18.
//  Copyright © 2018 Anthony Esmeralda. All rights reserved.
//

#include "DataTypes.h"
#include <string>

#ifndef Grid_h
#define Grid_h

class Grid{
private:
    char **matrix;
    dimensions d;
public:
    Grid();
    void generate_Table(int m,int n);
    void set_Matrix(std::string word, int row_number);
    dimensions get_Dimensions();
    char ** get_grid();
    std::string get_row(int row_number);
    std::string get_column(int column_number);
    std::string get_upper_right(int row_number,int column_number);
    std::string get_lower_left(int row_number,int column_number);
    std::string get_right_left(int row_number,int column_number);
    std::string get_left_right();
    std::string get_right_left();
    std::string reverse(std::string);
};

#endif /* Grid_h */
