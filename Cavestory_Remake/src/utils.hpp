//
//  utils.hpp
//  Cavestory_Remake
//
//  Created by Yevgeniy Tolstikov on 27/11/2016.
//  Copyright © 2016 HandMade. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <string>
#include <vector>

class Utils
{
public:
    
    // return size of a result vector
    static unsigned int split(const std::string &text, std::vector<std::string> &strs, char ch)
    {
        int pos = (int)text.find(ch);
        int initialPos = 0;
        
        strs.clear();
        
        while (pos != std::string::npos)
        {
            strs.push_back(text.substr(initialPos, pos - initialPos + 1));
            initialPos = pos + 1;
            pos = (int)text.find(ch, initialPos);
        }
        
        // add last one
        int lastPiece = (int)text.size() - (initialPos + 1);
        strs.push_back(text.substr(initialPos, std::min<int>(pos, lastPiece)));
        
        return (int)strs.size();
    }
};

#endif /* utils_hpp */
