//
//  DataTypes.h
//  Word Search Solver
//
//  Created by Anthony Esmeralda on 8/18/18.
//  Copyright © 2018 Anthony Esmeralda. All rights reserved.
//

#ifndef DataTypes_h
#define DataTypes_h

#include <string>

struct dimensions {
    int m;         // rows
    int n;         // columns
};

struct location{
    dimensions begin, end;
    std::string word;
    std::string type;
    bool found;
};

#endif /* DataTypes_h */
