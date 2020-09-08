//Shadman Thakur
#ifndef ROUTEMAP_H
#define ROUTEMAP_H
#include "City.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>

class RouteMap
{
    public:
        RouteMap();
        /**
        @param input_file_name of a csv file representing a route map where the first
         line is a comma-separated list of city names, and the remainder is a
         comma-separated list of city-pairs of the form A-B, indicating that B
         is adjacent to A (i.e. there is an arrow in the map going from A to B)
        @post this depends on your design, the input data representing the map must
         have been stored. Cities must be stored in the same order in which
         they are read from the input file
        **/
        bool readMap(std::string input_file_name);
        /**
        @return a pointer to the city found at position, where
         0 <= position <= n-1, and n is the number of cities,
         and cities are stored in the same order in which they appear
         in the input file
        **/
        City* getCity(size_t position);
        /**
        @return true if there is a route from origin to destination, false otherwise
        @post if a route is found from origin to destination, it will print it to
        standard output in the form ORIGIN -> ... -> DESTINATION
        **/
        bool isRoute(City* origin, City* destination);

    private:
        vector<City> CityList;
        City* getCity_by_name(string name);

};

#endif // ROUTEMAP_H
