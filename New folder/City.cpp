//shadman Thakur
#include "City.hpp"
#include <iostream>
#include <vector>
#include <deque>
City::City(string s)
{
    name_=s;
}
vector<City*> City :: getLeadsTo() const
{
    return leadsTo_;
}
void City :: setLeadsTo(City* a_city)
{
    leadsTo_.push_back(a_city);
}
string City :: getName() const
{
    return name_;
}
