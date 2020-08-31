#pragma once

#include <vector>

#include <string>

#include <map>

#include <iostream>



struct Wines {



    std::string country, region, province, winery, variety, price, points, name, description;

};



class Node {





public:



    std::string data; //the string the node will hold



    std::vector<Node*> children; //the children of that node its a vector bc its unknown how many children it will have



    Node(std::string d) { //contructor

        data = d;

    }



};







class Tree {



private:



    Node* root = nullptr; //PV to hold root node

    Node* location = nullptr; //PV to hold location of where you are looking at



    //PVs to hold infromation about the wine(s) you are searching for

    std::string country;

    std::string region;

    std::string province;

    std::string winery;

    std::string variety;

    std::string price;

    std::string points;



public:



    Node* makeChildOf(Node* parent, std::string data); //make a node coming from another node

    Node* addNode(Node* parent, std::string data); //adding a node to the tree

    void createTree(Wines wine); //creating the tree

    void checkForChildMatches(std::string data, std::string topic); //check to see if any of the children of a node match hte string youre looking for



    std::vector<Wines> returnWineNames(); //get a vector of the Wine structs with the inputted constraints

    std::vector<Wines> getName(std::string name);



    //seting the private variable to the inputted string

    void setCountry(std::string c);

    void setRegion(std::string r);

    void setProvience(std::string p);

    void setWinery(std::string w);

    void setVariety(std::string v);

    void setPrice(std::string p);

    void setPoints(std::string p);



    //retreiving the private variable

    std::string getCountry();

    std::string getRegion();

    std::string getProvience();

    std::string getWinery();

    std::string getVariety();

    std::string getPrice();

    std::string getPoints();

};