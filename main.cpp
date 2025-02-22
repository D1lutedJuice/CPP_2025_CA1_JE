#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
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


int main() {

    const string filename = "C:/Users/Jeili/CLionProjects/CPP_2025_CA1_JE/honkai_data.csv";
    vector<Honkai> honkaiData;

    //calling load function
    load(filename, honkaiData);
    //a header for the data made the width the same as the data
    cout << left << setw(5) << "ID" << setw(35) << "Name" << setw(13) << "Type"
    << setw(15) << "Path" << setw(7) << "Rarity" << setw(8) << "Drop Rate" << endl;

    //loop through each character and lightcone and print it
    for (const Honkai &honkai : honkaiData) {
        display(honkai);
    }
    
    return 0;
}



