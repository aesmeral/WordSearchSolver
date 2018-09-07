# Word Search Solver
## Why create a program that can solve word search puzzles?
The reason why I created a program that can solve word search puzzles is because I hate solving word search puzzle myself. Just putting the time and effort was a struggle for me but my girlfriend seemed to enjoy it and brought her mini word search puzzle everywhere we go and always wanted me to solve with her. Frankly, I was bad at it and an idea sparked through my mind which was you guessed it "lets build a program that can solve word search puzzles". Well that's where we're at now.

## How it works
The program is written in C++ using xcode and uses the Knuth-Morris-Pratt algorithm. It takes in two txt files, **table.txt and wordlist.txt**, which generates the **matrix grid using pointers and a vector of locations** respectively. Because the matrix grid is using dynamic memory, the program itself can run any nxn word search puzzle. The program is expected to run at worse case **O(n<sup>3</sup>)** due to the fact that it has to scan every row/column/diagonal, each word in the list, and also the KMP algorithm. The program outputs three things: the puzzle, list of words, and the location of where the words are at. The puzzle itself will come with positions in the grid starting from 0 to n - 1 on the first row and each row will have a position on the left to make looking for the words alot easier for the user. The list of words are self explanatory and the location will have 3 parts: **word, beginning and ending location, and the type**.

## How to use it
**Note: If running on VS, include the algorithm library in the WordSearch.h. (xcodes didnt need that library for it to work).**
1. Find a [wordsearch](https://www.brainzilla.com/word-games/word-search/printable)
2. Count the number of columns and rows (most likely they're the same) and input those values **first on the table.txt and follow up with the word search puzzle** (can copy and paste from the pdf) after and make sure that the last row does not have a trailing white space. **Note: With Windows: When copying and paste, it will leave spaces between characters. Please remove the space in order for it to work**
3. Copy and paste the list of words that you need to find in the wordlist.txt

Example:
<p align="center">
<img src="docs/TableExample.png" width="250" height="250"/><img src ="docs/WordListsExample.png" width="250" height="250"/>
</p>

4. Compile and run.

After all that you should have something like 
<p align="center">
  <img src="docs/OutputExample.png" width="600" height="450" />
</p>

and congratulations, you now have yourself a working word search puzzle solver. 

## Author
* **Anthony Esmeralda**
