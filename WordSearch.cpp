//
//  WordSearch.cpp
//  Word Search Solver
//
//  Created by Anthony Esmeralda on 8/19/18.
//  Copyright © 2018 Anthony Esmeralda. All rights reserved.
//

#include "WordSearch.h"


WordSearch::WordSearch()
{
    std::ifstream inFile;
    std::string words;
    inFile.open("table.txt");
    if (inFile.is_open())
    {
        int m, n;
        inFile >> m;
        inFile >> n;
        Word_Search_Table.generate_Table(m,n);
        int cur_row = 0;
        while (!inFile.eof())
        {
            inFile >> words;
            std::transform(words.begin(),words.end(),words.begin(),::toupper);
            Word_Search_Table.set_Matrix(words,cur_row);
            cur_row++;
        }
    }
    inFile.close();
    inFile.open("wordlist.txt");
    if (inFile.is_open())
    {
        while(!inFile.eof())
        {
            inFile >> words;
            std::transform(words.begin(),words.end(),words.begin(), ::toupper);
            location word_data;
            word_data.word = words;
            word_data.found = false;                        // no words have been found yet.
            Word_List.push_back(word_data);
        }
    }
}

void WordSearch::print_Table()
{
    char **matrix = Word_Search_Table.get_grid();
    dimensions d = Word_Search_Table.get_Dimensions();
    std::cout << d.m << "x" << d.n << " matrix: \n\n";
    for (int i = 0; i < d.n; i++)
    {
        std::cout << std::setw(4) << std::setfill(' ') << std::left;
        if (i == 0)
        {
            std::cout << "" << i << "   ";
        }
        else std::cout << i;
    }
    std::cout << std::endl << std::endl;
    for (int i = 0; i < d.m; i++)
    {
        std::cout << std::setw(4) << std::setfill(' ') << std::left;
        std::cout << i;
        for (int j = 0; j < d.n; j++)
        {
            std::cout << std::setw(4) << std::setfill(' ') << std::left;
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

void WordSearch::print_List()
{
    std::cout << "List of Words: \n\n";
    int n = Word_List.size();
    for (int i = 0; i < n; i++)
    {
        std::cout << std::setw(20) << std::setfill(' ') << std::left;
        if (i % 4 == 0 && i != 0) std::cout << std::endl;
        std::cout << Word_List[i].word;
    }
    std::cout << std::endl << std::endl;
}

void WordSearch::print_Diagonals()
{
    std::cout << "All Diagonals: \n\n";
    std::string x;
    dimensions d = Word_Search_Table.get_Dimensions();   // left to right diagonal
    for (int i = d.m-2; i >= 0; i--)                     // starting at d.m-1 will result in me getting the character in the bottom left corner.
    {
        x = Word_Search_Table.get_lower_left(i, 0);
        std::cout << x << std::endl;
    }
    for (int i = 1; i < d.n-1; i++)
    {
        x = Word_Search_Table.get_upper_right(0, i);    // starting at the value next to the top left corner to the second to last on row 0.
        std::cout << x << std::endl;
    }
    for (int i = 1; i < d.n; i++)
    {
        x = Word_Search_Table.get_right_left(i, 0);     // right to left diagonal
        std::cout << x << std::endl;
    }
    for (int i = 1; i < d.m-1; i++)
    {
        x = Word_Search_Table.get_right_left(d.n-1, i);
        std::cout << x << std::endl;
    }
    std::cout << std::endl;
}

void WordSearch::print_Rows()
{
    std::cout << "All Rows: \n\n";
    std::string x;
    dimensions d = Word_Search_Table.get_Dimensions();
    for (int i = 0; i < d.n; i++)
    {
        x = Word_Search_Table.get_row(i);
        std::cout << x << std::endl;
    }
    std::cout << std::endl;
}

void WordSearch::print_Columns()
{
    std::cout << "All Columns: \n\n";
    std::string x;
    dimensions d = Word_Search_Table.get_Dimensions();
    for (int i = 0; i < d.m; i++)
    {
        x = Word_Search_Table.get_column(i);
        std::cout << x << std::endl;
    }
    std::cout << std::endl;
}

int WordSearch::KMP_match(const std::string &text, const std::string &pattern)
{
    int n = text.size();
    int m = pattern.size();
    std::vector<int> fail = compute_fail_function(pattern);
    int i = 0;
    int j = 0;
    while (i < n)
    {
        if (pattern[j] == text[i])
        {
            if(j == m - 1)
            {
                return i - m + 1;           // return last position it was in.
            }
            i++;
            j++;
        }
        
        else if (j > 0)
        {
            j = fail[j-1];
        }
        else
        {
            i++;
        }
    }
    return -1;              // no match
}


std::vector<int> WordSearch::compute_fail_function(const std::string &pattern)
{
    std::vector<int> fail(pattern.size());
    fail[0] = 0;
    int m = pattern.size();
    int i = 1;
    int j = 0;
    while(i < m)
    {
        if (pattern[j] == pattern[i])
        {
            fail[i] = j + 1;
            i++;
            j++;
        }
        else if (j > 0)
        {
            j = fail[j-1];
        }
        else
        {
            fail[i] = 0;
            i++;
        }
    }
    return fail;
}

void WordSearch::find_in_row()
{
    std::string pattern, text;
    location position;
    dimensions d = Word_Search_Table.get_Dimensions();
    for (int i = 0; i < Word_List.size(); i++)
    {
        if (!Word_List[i].found)                    // if the word hasnt been found yet
        {
            pattern = Word_List[i].word;
            for (int j = 0; j < d.m; j++)
            {
                text = Word_Search_Table.get_row(j);
                if (pattern.size() <= text.size())
                {
                    int k = KMP_match(text, pattern);
                    if(k != -1)
                    {
                        position.begin.m = j;
                        position.begin.n = k;
                        position.end.m = j;
                        position.end.n = k + pattern.size() - 1;
                        position.word = pattern;
                        position.found = true;
                        position.type = "horizontal (left -> right)";
                        Word_List[i] = position;
                        break;
                    }
                    else
                    {
                        text = Word_Search_Table.reverse(text);
                        k = KMP_match(text, pattern);
                        if( k != -1)
                        {
                            position.begin.m = j;
                            position.begin.n = text.length() - 1 - k;
                            position.end.m = j;
                            position.end.n = position.begin.n - pattern.length() + 1;
                            position.word = pattern;
                            position.type = "horizontal (right -> left)";
                            position.found = true;
                            Word_List[i] = position;
                            break;
                        }
                    }
                }
            }
        }
    }
}
void WordSearch::find_in_column()
{
    std::string pattern, text;
    location position;
    dimensions d = Word_Search_Table.get_Dimensions();
    for(int i = 0; i < Word_List.size(); i++)                       // o(n)
    {
        if (!Word_List[i].found)
        {
            pattern = Word_List[i].word;
            for (int j = 0; j < d.n; j++)                           // o(m)
            {
                text = Word_Search_Table.get_column(j);
                if (pattern.size() <= text.size())
                {
                    int k = KMP_match(text, pattern);               // o(k)
                    if (k != -1)
                    {
                        position.begin.n = j;
                        position.begin.m = k;
                        position.end.n = j;
                        position.end.m = k + pattern.size() - 1;
                        position.word = pattern;
                        position.found = true;
                        position.type = "vertical (up -> down)";
                        Word_List[i] = position;
                        break;
                    }
                    else
                    {
                        text = Word_Search_Table.reverse(text);
                        k = KMP_match(text, pattern);
                        if(k != -1)
                        {
                            position.begin.n = j;
                            position.begin.m = text.length() - 1 - k;
                            position.end.n = j;
                            position.end.m = position.begin.m - pattern.length() + 1;
                            position.found = true;
                            position.type = "vertical (down -> up)";
                            position.word = pattern;
                            Word_List[i] = position;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void WordSearch::find_in_diagonals()
{
    std::string pattern, text;
    location position;
    dimensions d = Word_Search_Table.get_Dimensions();
    for (int i = 0; i < Word_List.size(); i++)                           
    {
        if (!Word_List[i].found)
        {
            pattern = Word_List[i].word;
            // upper left to lower right diagonal search
            // lower left + longest diagonal of matrix
            for(int j = d.m - 2; j >= 0; j-- )
            {
                text = Word_Search_Table.get_lower_left(j, 0);
                int diff = j - 0;
                if (pattern.size() <= text.size())
                {
                    int k = KMP_match(text, pattern);
                    if (k != -1)
                    {
                        position.begin.m = k + diff;
                        position.begin.n = k;
                        position.end.m = position.begin.m + pattern.size() - 1;
                        position.end.n = k + pattern.size() - 1;
                        position.found = true;
                        position.word = pattern;
                        position.type = "diagonal (left -> right)";
                        Word_List[i] = position;
                        break;
                    }
                    else
                    {
                        text = Word_Search_Table.reverse(text);
                        int k = KMP_match(text, pattern);
                        if (k != -1)            // still need fixing.
                        {
                            position.begin.n = text.length() - 1 - k;
                            position.begin.m = position.begin.n + diff;
                            position.end.n = position.begin.n - pattern.length() + 1;
                            position.end.m = position.end.n + diff;
                            position.found = true;
                            position.word = pattern;
                            position.type = "diagonal (right -> left)";
                            Word_List[i] = position;
                            break;
                        }
                    }
                }
            }
            // upper left to lower right diagonal search
            // upper right matrix.
            for (int j = 1; j < d.n - 1; j++)
            {
                text = Word_Search_Table.get_upper_right(0, j);
                int diff = j + 0;
                if (pattern.size() <= text.size())
                {
                    int k = KMP_match(text, pattern);
                    if (k != -1)
                    {
                        position.begin.n = k + diff;
                        position.begin.m = k;
                        position.end.n = position.begin.n + pattern.size() - 1;
                        position.end.m = k + pattern.size() - 1;
                        position.found = true;
                        position.word = pattern;
                        position.type = "diagonal (left -> right)";
                        Word_List[i] = position;
                        break;
                    }
                    else
                    {
                        text = Word_Search_Table.reverse(text);
                        int k = KMP_match(text, pattern);
                        if (k != -1)            // still need fixing.
                        {
                            position.begin.m = text.length() - 1 - k;
                            position.begin.n = position.begin.m + diff;
                            position.end.m = position.begin.m - pattern.length() + 1;
                            position.end.n = position.end.n + diff;
                            position.found = true;
                            position.word = pattern;
                            position.type = "diagonal (right -> left)";
                            Word_List[i] = position;
                            break;
                        }
                    }
                }
            }
            // upper right to lower left diagonal search
            // row 0 -> max_row - 1 (includes longest diagonal)
            for (int j = 1; j < d.m; j++)
            {
                text = Word_Search_Table.get_right_left(j, 0);
                if (pattern.size() <= text.size())
                {
                    int k = KMP_match(text, pattern);
                    if (k != -1)
                    {
                        position.begin.m = j - k;
                        position.begin.n = k;
                        position.end.n = k + pattern.length() - 1;
                        position.end.m = position.end.n - j;
                        position.found = true;
                        position.word = pattern;
                        position.type = "diagonal (left -> right)";
                        Word_List[i] = position;
                        break;
                    }
                    else
                    {
                        text = Word_Search_Table.reverse(text);
                        int k = KMP_match(text, pattern);
                        if (k != -1)
                        {
                            position.begin.n = j - k;
                            position.begin.m = k;
                            position.end.m = k + pattern.length() - 1;
                            position.end.n = j - position.end.m;
                            position.found = true;
                            position.word = pattern;
                            position.type = "diagonal (right -> left)";
                            Word_List[i] = position;
                            break;
                        }
                    }
                }
            }
            // upper right to lower left diagonal search
            // all of max_row - 1 diagonals (except longest diagonal)
            for (int j = 1; j < d.n; j++)
            {
                text = Word_Search_Table.get_right_left(d.m - 1, j);
                if (pattern.size() <= text.size())
                {
                    int k = KMP_match(text, pattern);
                    int sum = (d.m - 1) + j;
                    if (k != -1)
                    {
                        position.begin.n = j + k;
                        position.begin.m = sum - position.begin.n;
                        position.end.n = position.begin.n + pattern.size() - 1;
                        position.end.m = sum - position.end.n;
                        position.found = true;
                        position.word = pattern;
                        position.type = "diagonal (left -> right)";
                        Word_List[i] = position;
                        break;
                    }
                    else
                    {
                        text = Word_Search_Table.reverse(text);
                        int k = KMP_match(text, pattern);
                        if (k != -1)
                        {
                            position.begin.m = j + k;
                            position.begin.n = sum - position.begin.m;
                            position.end.m = position.begin.m + pattern.size() - 1;
                            position.end.n = sum - position.end.m;
                            position.found = true;
                            position.word = pattern;
                            position.type = "diagonal (right -> left)";
                            Word_List[i] = position;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void WordSearch::print_Words_Found()
{
    std::cout << "Word Locations: \n\n";
    int n = Word_List.size();
    for (int i = 0; i < n; i++)
    {
        std::cout << std::setw(15) << std::setfill(' ') << std::left;
        if (!Word_List[i].found)
        {
            std::cout << Word_List[i].word << "was not found.\n";
        }
        else
        {
            std::cout << Word_List[i].word << "found at [" << Word_List[i].begin.m << "][" << Word_List[i].begin.n << "] to [" << Word_List[i].end.m << "][" << Word_List[i].end.n << "] " << Word_List[i].type << std::endl;
        }
    }
    std::cout << std::endl;
}

void WordSearch::find_words()
{
    find_in_row();
    find_in_column();
    find_in_diagonals();
}


