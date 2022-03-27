#include <string>
#include <iostream>
#include "Direction.hpp"
#include <vector>
#include <unordered_map>
#include <cstdlib>
using ariel::Direction;
using namespace std;

namespace ariel{
   
    class Notebook{
        unordered_map<int,vector<vector<char>>> notebook;
        public:
            Notebook();
            ~Notebook();
            void write(int page,int row,int column, Direction dir,const string &text);
            string read(int page,int row,int column, Direction dir,int length);
            void erase(int page,int row,int column, Direction dir,int length);
            void show(int page);
    };

};