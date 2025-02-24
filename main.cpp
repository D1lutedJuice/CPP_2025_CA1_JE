#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <vector>



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
    cin >> nameIn;
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

    //got this off w3schools https://www.w3schools.com/cpp/trycpp.asp?filename=demo_maps_loop
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


    return 0;
}



