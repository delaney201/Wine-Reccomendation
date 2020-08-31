#pragma once

#include <vector>

#include <string>

#include <map>

#include <iostream>



struct Wine {



    std::string name, province, region, description, country, variety, winery, number;



    double price, points;



    static void printWine(Wine wine);

    bool operator<(const Wine& t) const

    {

        return (this->number < t.number);

    }



};





class AdjacencyList {



private:



    std::map < Wine, std::vector<Wine >> graph;



public:

    void insertEdge(Wine newWine);



    void wineSearch(double price, double points, std::string winery, std::string variety, std::string region, std::string province, std::string country);



    void wineName(std::string name);



};