//Shadman Thakur
#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <vector>
#include <deque>
using namespace std;


class City
{
    public:
        City(string s);
        vector <City*> getLeadsTo() const;//getter for leadsTo
        void setLeadsTo(City* a_city); //setter for leadsTo
        string getName() const;


    private:
        vector<City*>leadsTo_;// stores all  cities
        string name_; // name of the current city
};

#endif // CITY_H
