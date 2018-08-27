//
//  Grid.cpp
//  Word Search Solver
//
//  Created by Anthony Esmeralda on 8/18/18.
//  Copyright © 2018 Anthony Esmeralda. All rights reserved.
//


#include "Grid.h"
#include <iostream>

Grid::Grid()
{
    matrix = nullptr;
    d.m = 0;
    d.n = 0;
}

char ** Grid::get_grid()
{
    return matrix;
}

void Grid::set_Matrix(std::string word, int row_number)
{
    for (int j = 0; j < d.m; j++)
    {
        matrix[row_number][j] = word[j];
    }
}

void Grid::generate_Table(int m, int n)
{
    d.m = m;
    d.n = n;
    matrix = new char*[m];
    for (int i = 0; i < m; i++)
    {
        matrix[i] = new char[n];
    }
}

dimensions Grid::get_Dimensions()
{
    return d;
}

std::string Grid::get_row(int row_number)
{
    std::string word;
    for (int j = 0; j < d.n; j++)
    {
        word = word + matrix[row_number][j];
    }
    return word;
}

std::string Grid::get_column(int column_number)
{
    std::string word;
    for (int i = 0; i < d.m; i++)
    {
        word = word + matrix[i][column_number];
    }
    return word;
}

std::string Grid::reverse(std::string input)
{
    int n = input.length();
    for (int i = 0; i < n/2; i++)
    {
        std::swap(input[i],input[n-i-1]);
    }
    return input;
}

std::string Grid::get_upper_right(int row_number, int column_number)
{
    std::string word;
    int difference = column_number - row_number;
    int i = row_number;
    int j = i + difference;
    while (j < d.m)
    {
        word = word + matrix[i][j];
        i++;
        j++;
    }
    return word;
}

std::string Grid::get_right_left(int row_number, int column_number)
{
    std::string word;
    int i = row_number;
    int j = column_number;
    while (i >= column_number && j <= row_number)
    {
        word = word + matrix[i][j];
        i--;
        j++;
    }
    return word;
}


std::string Grid::get_lower_left(int row_number, int column_number)
{
    std::string word;
    int difference = row_number - column_number;
    int j = column_number;
    int i = j + difference;
    while (i < d.n)
    {
        word = word + matrix[i][j];
        i++;
        j++;
    }
    return word;
}

std::string Grid::get_right_left()
{
    std::string word;
    int i = d.m - 1 ;
    int j = 0;
    while (j < d.n && i >= 0)
    {
        word = word + matrix[i][j];
        i--;
        j++;
    }
    return word;
}

std::string Grid::get_left_right()
{
    std::string word;
    int i = 0;
    int j = 0;
    while (i < d.m && i < d.n)
    {
        word = word + matrix[i][j];
        i++;
        j++;
    }
    return word;
}










