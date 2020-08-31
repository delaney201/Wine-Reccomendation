//  Wine Project
//COMMENT NOTE: PV = Private Variable


#include "tree.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

//******************************************TREE STRUCTURE******************************************
                                        //ROOT (DATA="WINE")
                                    //COUNTRY
                                //REGION
                            //PROVIENCE
                        //WINERY
                    //VARIETY
                //PRICE
            //POINTS
        //NAME
    //DESCRIPTION

Node* Tree::makeChildOf(Node* parent, string data) {

    Node* child = new Node(data); //create the child node with new data and connects the pointer to it
    parent->children.push_back(child); //add that child to the parents children
    return child;
}


Node* Tree::addNode(Node* parent, string Data) {

    vector<Node*>::iterator itr;
    for (itr = parent->children.begin(); itr != parent->children.end(); itr++) {  //iterate through parent's children

        if ((*itr)->data == Data) { //if data matches any of the children's data
            return (*itr); //return that Node*
        }
    }

    //if it doesnt
    Node* child; //create a new Node*
    child = makeChildOf(parent, Data); //make it a child of parent with its data
    return child; //return the new node
}


void Tree::createTree(Wines wine) {

    //pointers for the info of a wine
    Node* country;
    Node* region;
    Node* province;
    Node* winery;
    Node* variety;
    Node* price;
    Node* points;
    Node* name;
    Node* description;


    if (root == nullptr) { //if there is nothing in the tree

        root = new Node("wine"); //set the root node to wine
        location = root; //set location* to the root so when going through the tree you start at begining

        //add each level as a child of the other since the tree is empty
        country = makeChildOf(root, wine.country);
        province = makeChildOf(country, wine.province);
        region = makeChildOf(province, wine.region);
        winery = makeChildOf(region, wine.winery);
        variety = makeChildOf(winery, wine.variety);
        price = makeChildOf(variety, wine.price);
        points = makeChildOf(price, wine.points);
        name = makeChildOf(points, wine.name);
        description = makeChildOf(name, wine.description);

    }

    else {

        //check to see if the parent already has the child as a node
            //if it does go on to the grandchild
            //if it does not make add it as a child then go on to the grandchild

        country = addNode(root, wine.country);
        province = addNode(country, wine.province);
        region = addNode(province, wine.region);
        winery = addNode(region, wine.winery);
        variety = addNode(winery, wine.variety);
        price = addNode(variety, wine.price);
        points = addNode(price, wine.points);
        name = addNode(points, wine.name);
        description = addNode(name, wine.description);
    }
}


void Tree::checkForChildMatches(string Data, string topic) {

    bool foundMatch = false; //a check to see if one of the children's data matches the inputted data
    Node* temp = nullptr;

    vector<Node*>::iterator itr;
    for (itr = location->children.begin(); itr != location->children.end(); itr++) {  //iterate through parent's (location's) children
        if ((*itr)->data == Data) { //if data matches any of the children's data
            temp = *itr;
            foundMatch = true; //a match was found
        }
    }

    if (foundMatch == false) { //no match was found

        cout << "There is no matching " << topic << " in the tree.\nPlease input another option" << endl; //error message
        string newData;
        getline(cin, newData); //take in the new string
        checkForChildMatches(newData, topic); //go through the process again with the new string
    }
    else if (foundMatch == true) {
        location = temp;

        //set the constraints infromation into the private variables
        if (topic == "country") {
            setCountry(Data);
        }
        else if (topic == "region") {
            setRegion(Data);
        }
        else if (topic == "province") {
            setProvience(Data);
        }
        else if (topic == "winery") {
            setWinery(Data);
        }
        else if (topic == "variety") {
            setVariety(Data);
        }
        else if (topic == "price") {
            setPrice(Data);
        }
        else if (topic == "points") {
            setPoints(Data);
        }


    }


}

vector<Wines> Tree::returnWineNames() {

    vector<Wines> wineNames; //create a vector of Wines to return

    Wines w; //create a wine

    //set the wine w information to the infromation that the user inputted

    w.country = getCountry();
    w.region = getRegion();
    w.province = getProvience();
    w.winery = getWinery();
    w.variety = getVariety();
    w.price = getPrice();
    w.points = getPoints();

    vector<Node*>::iterator itr; //iterator needed incase there is more than one wine that has those characteristics

    for (itr = location->children.begin(); itr != location->children.end(); itr++) {  //iterate through parent's (location's) children

        w.name = (*itr)->data; //get the name of the wine in question and set it to w

        if ((*itr)->children.size() > 1) { //if there is more than one wine with the same name and all other factors but two+ different descriptions you need to make two nodes with the different descriptions

            vector<Node*>::iterator itr2;

            for (itr2 = (*itr)->children.begin(); itr2 != (*itr)->children.end(); itr2++) {   //go through children of the name

                w.description = (*itr2)->data;

                wineNames.push_back(w); //push back a wine with all the same informatiion but with the unique description for it

            }

        }

        else { //this is if there is only one description for the name

            w.description = (*itr)->children[0]->data;

            wineNames.push_back(w);

        }

    }

    return wineNames;

}
vector<Wines> Tree::getName(string name) {

    vector<Wines> wines;

    Wines w;

    location = root;

    Node* countryLocation;
    Node* regionLocation;
    Node* proviencelocation;
    Node* wineryLocation;
    Node* varietyLocation;
    Node* priceLocation;
    Node* pointsLocation;

    vector<Node*>::iterator countryitr;

    for (countryitr = location->children.begin(); countryitr != location->children.end(); countryitr++) { //for each country

        setCountry((*countryitr)->data);//set country name
        w.country = getCountry();
        countryLocation = (*countryitr);

        vector<Node*>::iterator provienceitr;
        for (provienceitr = countryLocation->children.begin(); provienceitr != countryLocation->children.end(); provienceitr++) {//for each provience

            setProvience((*provienceitr)->data);//set provience name
            w.province = getProvience();
            proviencelocation = (*provienceitr);

            vector<Node*>::iterator regionitr;
            for (regionitr = proviencelocation->children.begin(); regionitr != proviencelocation->children.end(); regionitr++) { //for each region

                setRegion((*regionitr)->data);//set region name
                w.region = getRegion();
                regionLocation = (*regionitr);


                vector<Node*>::iterator wineryitr;
                for (wineryitr = regionLocation->children.begin(); wineryitr != regionLocation->children.end(); wineryitr++) {//for each winery

                    setWinery((*wineryitr)->data);//set winery name
                    w.winery = getWinery();
                    wineryLocation = (*wineryitr);


                    vector<Node*>::iterator varietyitr;
                    for (varietyitr = wineryLocation->children.begin(); varietyitr != wineryLocation->children.end(); varietyitr++) { //for each variety

                        setVariety((*varietyitr)->data);//set variety name
                        w.variety = getVariety();
                        varietyLocation = (*varietyitr);
                        vector<Node*>::iterator priceitr;

                        for (priceitr = varietyLocation->children.begin(); priceitr != varietyLocation->children.end(); priceitr++) { //for each price

                            setPrice((*priceitr)->data);//set price name
                            w.price = getPrice();
                            priceLocation = (*priceitr);
                            vector<Node*>::iterator pointsitr;

                            for (pointsitr = priceLocation->children.begin(); pointsitr != priceLocation->children.end(); pointsitr++) { //for each points

                                setPoints((*pointsitr)->data);//set points name
                                w.points = getPoints();
                                pointsLocation = (*pointsitr);
                                vector<Node*>::iterator nameitr;

                                for (nameitr = pointsLocation->children.begin(); nameitr != pointsLocation->children.end(); nameitr++) { //for each name

                                    if ((*nameitr)->data == name) { //if the name matches the inputted name

                                        w.name = (*nameitr)->data; //set that name to w

                                        if ((*nameitr)->children.size() > 1) { //if there are 1+ wines with the same name but different descriptions

                                            vector<Node*>::iterator descriptionitr;

                                            for (descriptionitr = (*nameitr)->children.begin(); descriptionitr != (*nameitr)->children.end(); descriptionitr++) {   //go through descriptions

                                                w.description = (*descriptionitr)->data;
                                                wines.push_back(w); //push back w with unique description

                                            }

                                        }

                                        else { //this is if there is only one description for the name

                                            w.description = (*nameitr)->children[0]->data;

                                            wines.push_back(w);

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

    if (wines.size() == 0) {
        cout << "We apologize but there is no wine in our database called " << name << ". Please search again." << endl;
        string newData;
        getline(cin, newData); //take in the new string
        getName(newData);

    }

    return wines;

}





void Tree::setCountry(string c) {
    country = c;
}

void Tree::setRegion(string r) {
    region = r;
}

void Tree::setProvience(string p) {
    province = p;
}

void Tree::setWinery(string w) {
    winery = w;
}

void Tree::setVariety(string v) {
    variety = v;
}

void Tree::setPrice(string p) {
    price = p;
}

void Tree::setPoints(string p) {
    points = p;
}

string Tree::getCountry() {
    return country;
}

string Tree::getRegion() {
    return region;
}

string Tree::getProvience() {
    return province;
}

string Tree::getWinery() {
    return winery;
}

string Tree::getVariety() {
    return variety;
}

string Tree::getPrice() {
    return price;
}

string Tree::getPoints() {
    return points;
}

