#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <set>
#include <sstream>
#include <stdexcept>
#include <cctype>
using namespace std;
class Validation{
    public:
    virtual bool Valid(string name)
    {
        for (char c : name)
        {
            if (!isalpha(c) && !isspace(c))
            {
                return false;
            }
        }
        return true;
    }

    virtual bool validPrice(float price)
    {
        return (price >= 0);
    }
    virtual bool validateIngredients(string ingredientName)
    {
        ifstream inFile("inventory.txt");
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string name;
            getline(ss, name, ',');
            if (name == ingredientName)
            {
                inFile.close();
                return true;
            }
        }

        inFile.close();
        return false;
     }
    bool validateMenu(string ordername){ifstream inFile("menu.csv");
        string line;
        while(getline(inFile,line)){
            stringstream ss(line);
            string name,price,category;
            getline(ss,name,',');
            getline(ss,price,',');
            getline(ss,category,',');
            if (ordername == name){
                return true;
            }

        }return false;}
    bool validQuantity(int  quantity){
    
    if(quantity<=0  || quantity > 10){
        return false;
    }
    return true;
}
    bool validPhoneNumber(const string& phoneNumber) {
        // 12 characters dekhne kyi liye
        if (phoneNumber.length() != 12) {
            return false;
        }

        //all characters in the phone number are digits
        for (char c : phoneNumber) {
            if (!isdigit(c)) {
                return false;
            }
        }
    }


bool ValidYear(int year) {
        return (year >= 1900 && year <= 2100); // Assuming reasonable year range
    }   
};
