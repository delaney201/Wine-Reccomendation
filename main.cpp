#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "graph.h"
#include "tree.h"
#include "time.h"
using namespace std;

bool InputCorrect(string num) {  //changes input string to a double for graph, if invalid input (word) recursively asks for new input
    double PriceDouble = 0.0;
    try {
        PriceDouble = stod(num);
    }
    catch (...) {
        return false;

    }
    return true;
}
string removeSpecial(string s) {   //converts common special characters to ascii values matching the conversion of the compiler
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == -61) {
            s[i] = 65;
        }
        else if (s[i] == -76) {
            s[i] = 39;
        }
        else if (s[i] == -68) {
            s[i] = -84;
        }
        else if (s[i] == -84) {
            s[i] = -86;
        }
        else if (s[i] == -87) {
            s[i] = 99;
        }
        else if (s[i] == -94) {
            s[i] = -101;
        }
    }
    return s;
}

int main() {
    //************LOAD WINES************************************
    Tree t;
    AdjacencyList g;
    int counter = 0;
    ifstream file;
    //file.open("data_shortversion.csv");
    file.open("winemag_data_130k.csv");
    cout << "Welcome to the ~Wine Reccomendation Software~" << endl;
    cout << "loading wines";
    string line;
    string token;
    getline(file, line);  //first line containing categories
    while (getline(file, line)) {
        Wine w;  //graph wine
        Wines ww;  //tree wine
        //shows user wines are loading
        if (counter == 10000 || counter == 30000 || counter == 50000 || counter == 70000 || counter == 90000 || counter == 100000 || counter == 120000) {
            cout << ".";
        }
        stringstream row(line);
        getline(row, token, ','); //num
        w.number = token;
        getline(row, token, ','); //country
        w.country = token;
        ww.country = token;
        getline(row, token, ','); //description
        w.description = token;
        ww.description = token;
        getline(row, token, ','); //designation
        getline(row, token, ','); //points
        ww.points = token;
        if (token != "") {
            w.points = stod(token);
        }
        else {
            w.points = 0.0;
        }
        getline(row, token, ','); //price
        ww.price = token;
        if (token != "") {
            w.price = stod(token);
        }
        else {
            w.price = 0.0;
        }
        getline(row, token, ','); //province
        if (counter == 160) {
            cout << "";
        }
        w.province = token;
        ww.province = token;
        getline(row, token, ','); //reg 1
        token = removeSpecial(token);
        w.region = token;
        ww.region = token;
        getline(row, token, ','); //reg 2
        getline(row, token, ','); //taster
        getline(row, token, ','); //twitter handle
        getline(row, token, ','); //title
        token = removeSpecial(token);
        w.name = token;
        ww.name = token;
        getline(row, token, ','); //variety
        token = removeSpecial(token);
        w.variety = token;
        ww.variety = token;
        getline(row, token, ','); //winery
        token = removeSpecial(token);
        w.winery = token;
        ww.winery = token;
        //add to Tree
        t.createTree(ww);
        //add to Graph
        g.insertEdge(w);
        counter++;
    }

    //************TAKE USER INPUT************************************
    clock_t startG, endG;
    clock_t startT, endT;
    int menuOp;
    string secondOp;
    cout << endl;
    cout << "Enter a menu option:" << endl;
    cout << "1. Search for a wine" << endl;
    cout << "2. Search for types of wines" << endl;
    cin >> menuOp;
    if (menuOp == 1) {
        cout << "Enter a wine name: " << endl;
        cin.ignore();
        getline(cin, secondOp);
        vector<Wines> treeMatches;
        startG = clock();
        g.wineName(secondOp);
        endG = clock();
        cout << "Graph DS: " << double(endG - startG) / double(CLOCKS_PER_SEC) << endl;
        startT = clock();
        treeMatches = t.getName(secondOp);
        endT = clock();
        cout << "Tree DS: " << double(endT - startT) / double(CLOCKS_PER_SEC) << endl;
        /*for (unsigned int i = 0; i < treeMatches.size(); i++) {
            Wines wine = treeMatches[i];
            cout << wine.name << endl;
            cout << "     Province: " << wine.province << endl;
            cout << "     Country: " << wine.country << endl;
            cout << "     Region: " << wine.region << endl;
            cout << "     Winery: " << wine.winery << endl;
            cout << "     Variety: " << wine.variety << endl;
            cout << "     Price: " << wine.price << endl;
            cout << "     Points: " << wine.points << endl;
            cout << "     Description: " << wine.description << endl;
        }*/
    }
    else if (menuOp == 2) {
        string priceEntered;
        string regEntered;
        string provEntered;
        string countryEntered;
        string wineryEntered;
        string varEntered;
        string pointsEntered;
        double newPrice;
        double newPoints;
        cout << "Enter filter options " << endl;

        cout << "Specify Country: ";
        cout << ("ex. Italy") << endl;
        cin.ignore();
        getline(cin, countryEntered);

        cout << "Specify Province: ";
        cout << "(ex. California)" << endl;
        getline(cin, provEntered);


        cout << "Specify Region: ";
        cout << "(ex. Napa Valley)" << endl;
        getline(cin, regEntered);

        cout << "Specify Winery: ";
        cout << "(ex. Louis Lator)" << endl;
        getline(cin, wineryEntered);

        cout << "Specify Variety: ";
        cout << "(ex. Chardonnay)" << endl;
        getline(cin, varEntered);

        cout << "Specify Price in $: ";
        cout << "(ex. 15)" << endl;
        cin >> priceEntered;
        while (!InputCorrect(priceEntered)) {  //runs until user inputs valid price
            cout << "Invalid price! Please enter in the form 12" << endl;
            string num2;
            cin >> num2;
            priceEntered = num2;
        }
        newPrice = stod(priceEntered);

        cout << "Specify Points: ";
        cout << "(ex. 85)" << endl;
        cin >> pointsEntered;
        while (!InputCorrect(pointsEntered)) {  //runs until user inputs valid points
            cout << "Invalid points! Please enter in the form 86" << endl;
            string num;
            cin >> num;
            pointsEntered = num;
        }
        newPoints = stod(pointsEntered);

        startT = clock();  //searches tree
        t.checkForChildMatches(countryEntered, "country");
        t.checkForChildMatches(provEntered, "province");
        t.checkForChildMatches(regEntered, "region");
        t.checkForChildMatches(wineryEntered, "winery");
        t.checkForChildMatches(varEntered, "variety");
        t.checkForChildMatches(priceEntered, "price");
        t.checkForChildMatches(pointsEntered, "points");
        endT = clock();
        /*
         vector<Wines> treeMatches = t.returnWineNames();
         for (unsigned int i = 0; i < treeMatches.size(); i++) {
            Wines wine = treeMatches[i];
            cout << wine.name << endl;
            cout << "     Province: " << wine.province << endl;
            cout << "     Country: " << wine.country << endl;
            cout << "     Region: " << wine.region << endl;
            cout << "     Winery: " << wine.winery << endl;
            cout << "     Variety: " << wine.variety << endl;
            cout << "     Price: " << wine.price << endl;
            cout << "     Points: " << wine.points << endl;
            cout << "     Description: " << wine.description << endl;
        }*/

        startG = clock();  //searches graph
        g.wineSearch(newPrice, newPoints, wineryEntered, varEntered, regEntered, provEntered, countryEntered);
        endG = clock();
        cout << "Graph DS: " << double(endG - startG) / double(CLOCKS_PER_SEC) << " seconds" << endl;
        cout << "Tree DS: " << double(endT - startT) / double(CLOCKS_PER_SEC) << " seconds" << endl;
    }
    else {
        cout << "Invalid Menu Option, goodbye" << endl;
    }
    return 0;
}

