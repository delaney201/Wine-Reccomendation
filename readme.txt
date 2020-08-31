# GitTest1

User Overview 

Once the user runs the program it should take about 60 seconds to load the wines from the data set. The zip file will contain the data set in a csv file named  winemag_data_130k.csv which the program uses a file stream to access. The gradual loading of wines will be indicated by ellipses after the word loading. Once the wines are loaded, the menu will print allowing the user to enter option 1 (by entering 1) or option 2 (by entering 2). If option 1 is entered, the user can enter a wine name and the attributes of that wine will be printed if it is found in the graph and tree. An example entry is:Leon Beyer 2012 Gewurztraminer (Alsace). Another example entry is: Acrobat 2013 Pinot Noir (Oregon). If option 2 is selected, the user will be prompted to enter specifications about a wine in the order country, province, region, winery, variety, price, points. An example entry is:Spain/nNorthern Spain/nRibera del Duero/nPradorey/nTempranillo Blend/n28/n87. Another example entry is:Italy/nSouthern Italy/nPuglia/nFeudi di San Marzano/nPrimitivo/n11/n86. Make sure to include spaces in between words for multi word entries but not before or after the entries themselves. If a wine or specifications containing common special characters is entered, the program will convert those special characters to regular ASCII and the wine will be found by the program, but will just print slightly differently than entered. If a wine or specification containing an uncommon special characters is searched for, the program will not find it in the tree or graph even though they do internally contain that entry. The time taken for each data structure to perform the searching task will print last. We created the program with the expectation that the user knows wine and will input exact and specific characteristics and names. We did this so that the user gets exactly what they are looking for, not wines that may be similar. 

graph.cpp Overview 
  
  We implemented an adjacency list graph. Each node in the graph is a wine with its information. Below are the functions in this class and a description of what they do.

  printWine(Wine wine)
    This function is used to print the wine which fits the inputted characteristics

  void insertEdge(Wine newWine);
    This function is how the graph is created. We check to see if the graph is empty or not. If it is empty, we create a node which doesn't point to anything. 
    If it is not empty, we create a new node and point it to the last one in the graph.

  void wineSearch(double price, double points, std::string winery, std::string variety, std::string region, std::string province, std::string country);
     This function takes all of the user's inputted wine characteristics and iterates through the graph to see if any of the wines match those 
     characteristics. When a matching wine is found it is printed. If no matching wine is found an error message will be outputtd instructing the user to change 
     one or more of their values.

  void wineName(string name);
    This function iterates through the entire graph to see if any of the wines have the same name as the inputted name. If they do, that wine is printed. If 
    there is no match, an error message is outputted telling the user to search again.



tree.cpp Overview 

  The tree data structure is created to have each level of the tree hold a different topic of information. The root node just holds the string "wine". From then 
  on we have each descending level holding the information for country, region, province, winery, variety, price, points, name, and description, respectively.
  The tree function holds a private Node pointer variable called location which points to the node on the tree where the user is looking into. It also has
  private variables for each topic to hold the string data the user is looking for. Below are the functions in this class and a description of what they do. 

  Node* makeChildOf(Node* parent, string data);
    This function creates a new child node coming from the imported parent node.

  Node* addNode(Node* parent,string data);
    This function checks to see if the parent node already has a child with the matching data. If it does, it returns that existing node. If it doesn't, 
    it creates a new node by calling makeChildOf(Node* parent, string data).

  void createTree(Wines wine);
    This function creates the tree. If the root equals null, meaning there is nothing in the tree, then it creates the root, sets location equal to the root,
    and calls makeChildOf(Node* parent, string data) for all of that wine's information. If the Roots is not null, then it calls addnode for all of the wines 
    information.

  void checkForChildMatches(string data,string topic);
    This function is used to go through the tree to find the wines. In the order of the tree (country, region, province,...) it checks to see if any of location's 
    children matches the inputted string. If there is a match then location now equals that found node and that data now equals the matching private variable for 
    that topic in the tree class. If it doesn't find a match an error message is outputted saying to input a new value for that topic. 

  vector<Wines> returnWineNames();
     This function returns a vector of the struct, wines, holding all of the wines which match the imported characteristics. It gets, through getter functions, all 
     of the values for the saved private variables and sets them to the approiate topic for the newly created wines. Then, the function iterates through location's
     children (which are the wine names) to get all the names of the wines which fit the characteristics. It then iterates through all the name's children to get all 
     the descriptions for those wines.

  vector<Wines> getName(string name);
    This function returns a vector of wines which match the users inputted name. It goes through each node on each level of the tree until it gets to the name level. 
    There, it checks to see if any of the names match the inputted name. If there is a match it adds that wine to the vector. If there isnt a match it outputs 
    an error message. 
  
  
  
main.cpp Overview 

  bool InputCorrect(string num); 
    This function changes the string input into a double. This is needed since the graph takes in doubles for price and points.

  string removeSpecial(string s);
    This function removes the special characters into matching normal characters.
    
  main
    In the main we load each line of the CSV file and create a wine from it and place the wine into both the tree and the graph. Then we take in the user's input 
    for which option they would like to select; option one to search for a name of the wine and option 2 to find wines with the inputted characteristics. We time
    each data structure to see how long it takes to get the solution. After each data structure completes its task, main will print the times to show how long 
    it took for each of them. There are commented-out sections in order to prevent the solutions getting printed twice. These comments are left in the code to 
    test and see the tree and the graph outputs both. 

