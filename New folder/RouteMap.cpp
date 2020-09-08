//Shadman Thakur
#include "RouteMap.hpp"
#include "City.hpp"
#include <iostream>
#include <vector>
#include<fstream>
#include <deque>
#include <unordered_set>

using namespace std;

void dump(unordered_set<City*> marker, deque<City*> visit_order);

RouteMap::RouteMap()
{
    //ctor
}
bool RouteMap :: readMap(string input_file_name)
{
    ifstream csvFile;  //stream for file extraction
    csvFile.open(input_file_name);//input_file
    if(!csvFile)//file fails to open then:
    {
        cout <<"Fail to open file!"<<endl;
        return false;
    }
    if(csvFile.peek()==EOF){
        if (csvFile.eof()){
            cout<<"Catching"<<endl;
            return false;
        }
    }
    string first_line;
    string city_name;
    getline(csvFile,first_line);// store 1st line of CSV into  string first_line
    stringstream c(first_line);// create a string stream from first_line
    while(c.good()){
        getline(c,city_name,',');//parse the string with ',' delim
        CityList.push_back(City(city_name));//fill up City List with initialized City object
    }

    string next_line;
    string pairs;
    vector<string> origin; //string vector to store name of origin city
    vector<string> destination;//string vector to store name of destination city
    while(!csvFile.eof()){
        getline(csvFile,next_line); // extract 2nd line of the CSV into next_line
        stringstream ss_sec_line(next_line); //create a string stream from next_line

        while(ss_sec_line.good()){
            getline(ss_sec_line,pairs,','); // extract the first pair of city ex P-R
            stringstream ss_pairs(pairs); //convert it to sstream
            string temp;
            getline(ss_pairs,temp,'-');//extract the first city 'P' from the pair into a temp string

            origin.push_back(temp);//fill the origin vector with the first city 'P'
            getline(ss_pairs,temp);//extract the second city from the pair
            destination.push_back(temp);//store it in destination
        }
    }
    for(int i= 0; i<origin.size(); i++){
        /** get the address of city with the name == origin and set the leadsto
        member to point to the address of a city with the name == destination **/
        getCity_by_name(origin[i])->setLeadsTo(getCity_by_name(destination[i]));
    }
    return true;
}

City* RouteMap :: getCity(size_t position)
{
    return &CityList[position];//return mem address to the City at position
}
bool RouteMap :: isRoute(City* origin, City* destination)
{
    if(CityList.size()==0){return false;}
    unordered_set<City*> marker;      // -Container for keeping track of visited cities
    deque<City*> visit_order;        //  -Container for finding the path from origin to destination
    visit_order.push_back(origin);  //   -Place the origin city into the deque
    marker.insert(origin);         //    -Mark origin as visited by placing into set
    while(!visit_order.empty()){  //     -As long the deque is not empty...

        City* current_city = visit_order.back(); // create a City pointer = the top/back of deque
        if(current_city==destination){ // if the current_city(top/back of deque) == the destination break from loop
            break;
        }
        int i;
        for(i = 0; i < current_city->getLeadsTo().size(); i++){ //iterate current_city's child cities(adjacents)
            if (marker.find(current_city->getLeadsTo()[i])==marker.end()){// if a child city is not found in the marker set(not visited)
                marker.insert(current_city->getLeadsTo()[i]);// insert it into marker set
                visit_order.push_back(current_city->getLeadsTo()[i]);//insert the city on to the top of the deck
                break;
            }
        }
        if (i == current_city->getLeadsTo().size()){//after all the child cities were visited
            visit_order.pop_back(); //remove parent city from top of deque
        }
    }
    if (visit_order.empty()){//if the deque is empty it means there is no path from origin to destination thus return false
        return false;
    }
    else{//if deque is not empty
        cout<<visit_order.front()->getName();// print the name of bottom/front first(origin city)
        visit_order.pop_front();// remove the city after printing from deque
        while(!visit_order.empty()){//print rest of city
            cout << " -> " << visit_order.front()->getName();
            visit_order.pop_front();
        }
        cout << endl;
        return true;
    }
}
City* RouteMap :: getCity_by_name(string name) //searches the CityList for a city == string name parameter
{
    for (int i = 0; i<CityList.size(); i++){
        if (CityList[i].getName() == name){
            return &CityList[i];        //returns address of the city object if found
        }
    }
}
