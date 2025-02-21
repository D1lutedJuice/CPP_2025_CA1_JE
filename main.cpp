#include <iostream>
#include <fstream> // used for access to the file input and output classes


using namespace std;

// function prototype
void read_line_by_line(ifstream &);

int main() {

    ifstream ifs("C:/Users/Jeili/CLionProjects/CPP_2025_CA1_JE/honkai_data.csv");

    if (ifs) { //if file opened
        cout << "\nHonkai Star rail Data:" << endl;
        read_line_by_line(ifs);// pass the ifs into a function that will read its content line-by-line
    } else {
        cout << "Unable to open file" << endl;
    }
    ifs.close();    // close the file

    return 0;
}

void read_line_by_line(ifstream& ifs) {
    string line;
    while (getline(ifs, line)) // while not at end of file, read a full line of text
    {
        cout << line << "\n";   // print the line to the screen followed by a space
    }
}

