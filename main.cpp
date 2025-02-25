#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>
#include <bits/ranges_algo.h>


using namespace std;

//struct to hold data for each honkai character and light cone(weapon)
struct Honkai {
    int id;
    string name;
    string type;
    string path;
    int rarity;
    double dropRate;
};


//function to read the text and split it
void parseLine(string line, Honkai &honkai) {
    string temp;
    stringstream ss(line);

    //split the lines by commas
    //reads the id and then converts it into an int
    getline(ss, temp, ',');
    honkai.id = stoi(temp);

    getline(ss, honkai.name, ',');
    getline(ss, honkai.type , ',');
    getline(ss, honkai.path, ',');

    //reads rarity converts to int
    getline(ss, temp, ',');
    honkai.rarity = stoi(temp);

    //reads drop rate and converts to double
    getline(ss, temp, ',');
    honkai.dropRate = stod(temp);

}
//loads the data from the file into the vector of structs
void load(const string &file, vector<Honkai> &honkaiData) {
    ifstream ifs(file);

    //if the file opens
    if (ifs) {
        string line;
        //reads lines untill the end
        while (getline(ifs, line)) {
            //creates a new  struct for each line, fills it then adds it to the vector
            Honkai honkai;
            parseLine(line, honkai);
            honkaiData.push_back(honkai);
        }
        ifs.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

//printing in a table format
void display(const Honkai &honkai) {
    cout << left
        << setw(5) << honkai.id
        << setw(35) << honkai.name
        << setw(13) << honkai.type
        << setw(15) << honkai.path
        << setw(7) << honkai.rarity
        << setw(5) << honkai.dropRate
        << endl;
}

int findByName(vector<Honkai> &honkaiData, string nameIn) {
    //loop through the data
    for (int i = 0; i < honkaiData.size(); ++i) {
        //if the name at index i is equal to the given name
        if (honkaiData[i].name == nameIn) {
            //returns the index where name is
            return i;
        }
    }
        return -1;//otherwise returns -1
}

map<string, int> CountByPath(vector<Honkai> &honkaiData) {

    map<string, int> m;
    //goes through all data
    for (int i = 0; i < honkaiData.size(); ++i) {
        //add count of each type
        m[honkaiData[i].path]++;
    }
    return m;
}

void displayByType(vector<Honkai> &honkaiData, string typeIn) {

    bool exists= false;
    cout << "All data for " << typeIn << endl;
    //loops through the data
    for (int i = 0; i < honkaiData.size(); ++i) {
        //if there is a data with that type then call display function
        if (honkaiData[i].type == typeIn) {
            exists = true;
            display(honkaiData[i]);
        }
    }
    if (!exists) {
        cout << "Not found" << endl;
    }
}

//add the & to highest and lowest so it will change the values in function
int findRarityinfo(vector<Honkai> &honkaiData, Honkai &highest, Honkai &lowest) {
    //highest and lowest to the first item in the vector
    highest= honkaiData[0];
    lowest = honkaiData[0];
    int total = 0;

    //go through the data
    for (Honkai &honkai : honkaiData) {
        //add the total of rarities
        total += honkai.rarity;
        //find the lowest one and add it to the vector
        if (honkai.rarity < lowest.rarity) {
            lowest = honkai;
        }
        //find the highest one and add to vector
        if (honkai.rarity > highest.rarity) {
            highest = honkai;
        }
    }
    //get avrage
    int average= total / honkaiData.size();
    return average;

}


vector<Honkai> partialName(vector<Honkai> &honkaiData, string partialName) {
    vector<Honkai> matchingName;
    //iterator goes through the data untill it reaches the end
    for (auto it = honkaiData.begin(); it != honkaiData.end(); it++) {
        //dereference the iterator,it gets the name of the current one that its pointing at
        //and checks if it matches, as long as it does it will add it to vector
       if ((*it).name.find(partialName) != string::npos) {
           //add it to vector
           matchingName.push_back(*it);
       }
    }
    return matchingName;

}

void sortByDropRate(vector<Honkai> &honkaiData) {
    //sorting data in decsending order, based on dRop rate using lambda function
    auto func = [](Honkai s1, Honkai s2) {return s1.dropRate > s2.dropRate; };
    sort(honkaiData.begin(), honkaiData.end(), func);

    //print out header
    cout << left << setw(5) << "ID" << setw(35) << "Name" << setw(13) << "Type"
    << setw(15) << "Path" << setw(7) << "Rarity" << setw(8) << "Drop Rate" << endl;

    for (Honkai &honkai : honkaiData) {
        display(honkai);
    }
}

int main() {
    //stage 2
    const string filename = "honkai_data.csv";
    vector<Honkai> honkaiData;

    //calling load function
    load(filename, honkaiData);

    //stage 3 part 1
    //a header for the data made the width the same as the data
    cout << left << setw(5) << "ID" << setw(35) << "Name" << setw(13) << "Type"
    << setw(15) << "Path" << setw(7) << "Rarity" << setw(8) << "Drop Rate" << endl;

    //loop through each character and lightcone and print it
    for (const Honkai &honkai : honkaiData) {
        display(honkai);
    }

    //stage 3 part 2
    string nameIn;
    cout << "\nEnter name to search for: ";
    //ignores the newline character
    cin.ignore();
    getline(cin , nameIn) ;
    //call method to get index
    int index = findByName(honkaiData, nameIn);
    if (index == -1) {
        cout << "Name not found" << endl;
    }
    else {
        cout << "Found at index: "<< index << endl;
        display(honkaiData[index]);
    }

    //stage 3 part 3
    map<string, int> counts = CountByPath(honkaiData);
    cout << "\nPath Counts:" << endl;

    //got help off w3schools https://www.w3schools.com/cpp/trycpp.asp?filename=demo_maps_loop
    //loops through the map
    for (auto& count : counts) {
        //gets key and value and displays it
        cout << count.first << ": " << count.second << endl;
    }

    //Stage 3 part 4
    string typeIn;
    cout << "Enter what Type to search by (Character or Light Cone)" << endl;
    //ignores the newline character (got this from https://www.geeksforgeeks.org/cin-ignore-function-in-cpp/)
    cin.ignore();
    getline(cin , typeIn) ;
    displayByType(honkaiData, typeIn);

    //stage 3 part 5
    Honkai highest;
    Honkai lowest;
    int average= findRarityinfo(honkaiData, highest, lowest);
    cout << "\nRarity Info:" << endl;
    cout << "Average Rarity: " << average << endl;
    cout << "Lowest Rarity: " << endl;
    display(lowest);
    cout << "Highest Rarity: " << endl;
    display(highest);

    //stage 3 part 6
    string partialNameIn;
    cout << "\nEnter Partial name to search for (The): ";
    cin >> partialNameIn;
   vector <Honkai> r= partialName(honkaiData, partialNameIn);
    if (r.empty()) {
        cout << "No data found" << endl;
    }
    else {
        for (const Honkai &honkai : r) {
            display(honkai);
        }
    }

    //stage 3 part 7
    cout <<"\nSorted By Drop Rate:"<< endl;
    sortByDropRate(honkaiData);

    return 0;
}



