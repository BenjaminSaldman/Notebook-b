#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <unordered_map>
#include "Notebook.hpp"
#include "Direction.hpp"
using ariel::Direction;
using namespace std;
const int MAX=100;
const int FIRST=0;
const int STAND=5;
const char ASSIGN='_';
const int MIN=0;
const char DEL='~';
const int Invalid=33;
const int Invalid2=127;
const int divisor=10;
const int INT=2147483647;
bool checkValid(int page, int row, int column,const string &text,int length)
{
    bool ans=true;
    if(page<0 || row<0 || column<0 || text.length()<1 || column>=MAX || length<=MIN){
        ans=false;
    }
    for(unsigned i=0;i<text.length();i++)
    {
        if(text.at(i)<Invalid || text.at(i)>=Invalid2)
        {
            ans=false;
            break;
        }
    }
    return ans;
}
namespace ariel{

    Notebook::Notebook()
    {
        this->notebook[0].assign(MAX,vector<char>(MAX,ASSIGN));
    }
    Notebook::~Notebook()
    {
        
    }
    /**
     * @brief 
     * 
     * @param page 
     * @param row 
     * @param column 
     * @param dir 
     * @param text 
     * writing to the notebook.
     */
    void Notebook::write(int page,int row,int column, Direction dir,const string &text){
        
        if(!checkValid(page,row,column,text,1)) // check the validity of the input.
        {
            throw invalid_argument{"Invalid input"};
        }
        unsigned long k=text.length()-1;
        if(dir==Direction::Horizontal)
        {
            if(k+(unsigned)column>=MAX)
            {
                 throw invalid_argument{"Invalid input"};
            }
        }
        bool ans=false; // check if the page exist in the map, if not we add a new one.
        for(auto const &x:notebook)
        {
            if(x.first==page)
            {
                ans=true;
                break;
            }
        }
        if(!ans)
        {
            notebook[page].assign((unsigned)row+text.length(),vector<char>(MAX,ASSIGN));
        }
        else{
            if((unsigned)row+text.length()>=MAX) // Resizing the notebook, if we above the max rows.
            {
                notebook[page].resize((unsigned)row+text.length());
            }
        }
        /**
         * @brief 
         * checking if we can write in this place.
         */
        for(unsigned i=0;i<text.length();i++)
        {
            if(dir==Direction::Horizontal)
            {
                if(notebook[page][(unsigned)row][(unsigned)column+i]!=ASSIGN)
                {
                    throw invalid_argument{"can't write in this place!"};
                }
            }
            else{
                if(notebook[page][(unsigned)row+i][(unsigned)column]!=ASSIGN)
                {
                    throw invalid_argument{"can't write in this place!"};
                }
            }
        }
        /**
         * @brief 
         * writing in the note book.
         */
        for(unsigned i=0;i<text.length();i++){
            if(dir==Direction::Horizontal)
            {
                notebook[page][(unsigned)row][(unsigned)column+i]=text[i];
            }
            else
            {
                notebook[page][(unsigned)row+i][(unsigned)column]=text[i];
            }
        }

    }
     string Notebook::read(int page,int row,int column, Direction dir,int length){
        if(!checkValid(page,row,column,"abcd",length)) // check the validity of the input.
        {
            throw invalid_argument{"Invalid input"};
        }
        if(dir==Direction::Horizontal)
        {
            if(length+column-1>=MAX)
            {
                 throw invalid_argument{"Invalid input"};
            }
        }
        bool ans=false; // check if the page exist in the map, if not we add a new one.
        for(auto const &x:notebook)
        {
            if(x.first==page)
            {
                ans=true;
                break;
            }
        }
        if(!ans)
        {
            notebook[page].assign((unsigned)row+(unsigned)length,vector<char>(MAX,ASSIGN));
        }
        else{
            if((unsigned)row+(unsigned)length>=MAX) // Resizing the notebook, if we above the max rows.
            {
                notebook[page].resize((unsigned)row+(unsigned)length);
            }
        }
        string total;
        for(unsigned i=0;i<(unsigned)length;i++)
        {
            if(dir==Direction::Horizontal)
            {
                total+=notebook[page][(unsigned)row][(unsigned)column+i];
            }
            else{
                total+=notebook[page][(unsigned)row+i][(unsigned)column];
            }
        }
        return total;
    }
    void Notebook::erase(int page,int row,int column, Direction dir,int length){
        if(!checkValid(page,row,column,"abcd",length)) // check the validity of the input.
        {
            throw invalid_argument{"Invalid input"};
        }
        if(dir==Direction::Horizontal)
        {
            if(length+column-1>=MAX)
            {
                 throw invalid_argument{"Invalid input"};
            }
        }
        bool ans=false; // check if the page exist in the map, if not we add a new one.
        for(auto const &x:notebook)
        {
            if(x.first==page)
            {
                ans=true;
                break;
            }
        }
        if(!ans)
        {
            notebook[page].assign((unsigned)row+(unsigned)length,vector<char>(MAX,ASSIGN));
        }
        else{
            if((unsigned)row+(unsigned)length>=MAX) // Resizing the notebook, if we above the max rows.
            {
                notebook[page].resize((unsigned)row+(unsigned)length);
            }
        }
        for(unsigned i=0;i<(unsigned)length;i++)
        {
            if(dir==Direction::Horizontal)
            {
                notebook[page][(unsigned)row][(unsigned)column+i]=DEL;
            }
            else{
                notebook[page][(unsigned)row+i][(unsigned)column]=DEL;
            }
        }
       
    }
    void Notebook::show(int page){
        if(!checkValid(page,STAND,STAND,"abcd",STAND)) // check the validity of the input.
        {
            throw invalid_argument{"Invalid input"};
        }
        bool ans=false; // check if the page exist in the map, if not we add a new one.
        for(auto const &x:notebook)
        {
            if(x.first==page)
            {
                ans=true;
                break;
            }
        }
        if(!ans)
        {
            notebook[page].assign(MAX,vector<char>(MAX,ASSIGN));
        }
        string printer;
        if(!ans)
        {
            for(unsigned i=0;i<notebook[page].size()/divisor;i++)
            {
                for(unsigned j=0;j<notebook[page].size()/divisor;j++)
                {
                    printer+=to_string(i)+": "+notebook[page][i][j];
                }
                printer+='\n';
            }
            cout<<printer<<endl;
            return;
        }
        unsigned int minRow=notebook[page].size();
        unsigned int maxRow=0;
        for(unsigned i=0;i<notebook[page].size();i++)
            {
                for(unsigned j=0;j<notebook[page][i].size();j++)
                {
                    if(notebook[page][i][j]!=ASSIGN)
                    {
                        if(i<minRow)
                        {
                            minRow=i;
                        }
                        if(i>maxRow)
                        {
                            maxRow=i;
                        }
                    }
                }
            }
        string s;
        for(unsigned i=0;i<=maxRow;i++)
        {
            s+=to_string(i)+": ";
            //cout<<i<<": ";
            for(unsigned j=0;j<MAX;j++)
            {

                cout<<notebook[page][i][j];
            }
            cout<<endl;
        }
        
    }

};