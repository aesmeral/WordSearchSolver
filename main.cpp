//
//  main.cpp
//  Word Search Solver
//
//  Created by Anthony Esmeralda on 8/18/18.
//  Copyright © 2018 Anthony Esmeralda. All rights reserved.
//

#include <iostream>
#include "Grid.h"
#include "WordSearch.h"
#include <chrono>

using namespace std;

// the following word search can be found @ https://www.brainzilla.com/media/wordsearch/pdfs/elementary-school-hard.pdf
// Word Search's can be found @ https://www.brainzilla.com/word-games/word-search/printable/
// Copy and paste the puzzle onto table.txt and the words to search into wordlist.txt

int main(int argc, const char * argv[]) {
    cout << "Author: Anthony Esmeralda\n";
    cout << "This Program is a word search solver for any nxn size word search puzzle\n\n";
    chrono::time_point<chrono::system_clock> start, end;
    chrono::duration<double> elasped_time;
    WordSearch myWordSearch;
    myWordSearch.print_Table();
    myWordSearch.print_List();
    start = chrono::system_clock::now();
    myWordSearch.find_words();
    end = chrono::system_clock::now();
    myWordSearch.print_Words_Found();
    elasped_time = end - start;
    cout << "time: " << elasped_time.count() << endl << endl;
    return 0;
}
