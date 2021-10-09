#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "mapLoader.h"

using namespace std;

int main()
{
 

    string t;
    std::regex rx("; map:.");
    std::smatch mr;
    vector<string> array1;
    vector<string> array2;
    vector<string> array3;

    std::ifstream file("europe.map");
    std::getline(file, t);
    

    if (regex_search(t, mr, rx) )
    {
       
        cout << "Map is valid :)\n\n\n";
  
    }
    else
    {
        cout << "Wrong Map Format! Closing Program...";
        
    }

    while (getline(file, t))    //Read file line by line
    {

        if (t == "[continents]")
        {
            while (getline(file, t))
            {
                if (t == "")
                    break;
                array1.push_back(t);

                
            }
            cout << "CONTINENTS\n\n" << endl;
            for (int i = 0; i < array1.size(); i++)
                cout << array1[i] + "\n" << endl;
        }

        if (t == "[countries]")
        {
            while (getline(file, t))
            {
                if (t == "")
                    break;
                array2.push_back(t);
            }
            cout << "COUNTRIES\n\n" << endl;
            for (int i = 0; i < array2.size(); i++)
                cout << array2[i] + "\n" << endl;

           
        }

        if (t == "[borders]")
        {
            while (getline(file, t))
            {
                if (t == "")
                    break;
                array3.push_back(t);
            }
            cout << "BORDERS\n\n" << endl;
            for (int i = 0; i < array3.size(); i++)
                cout << array3[i] + "\n" << endl;
        }



    }
    return (0);
}
