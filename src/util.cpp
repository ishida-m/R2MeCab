#include "util.h"

/////////////////////////////////////////////////////////////
vector <string> tmpsplit(string str, string delim)
{
    vector <string> result;
    int cutAt;
    while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
        if(cutAt > 0)
        {
            result.push_back(str.substr(0, cutAt));
        }
        str = str.substr(cutAt + 1);
    }
    if(str.size() > 0)
    {
        result.push_back(str);
    }
    return result;
}
/////////////////////////////////////////////////////////////
