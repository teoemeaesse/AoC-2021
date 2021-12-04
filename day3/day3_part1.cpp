#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> read_file(string filename)
{
    vector<string> parsed;
    fstream file;

    file.open(filename, ios::in);
    if(file.is_open()) {
        string tp;
        while(getline(file, tp)) {
            parsed.push_back(tp);
        }
        file.close();
    }

    return parsed;
}

int main(int argc, char * argv[])
{
    string filename;

    if(argc == 1) {
        cout << "input file (q to quit): ";
        string reply;
        cin >> reply;

        if(reply == "q")
            return 0;
        
        filename = reply;
    }
    else
        filename = argv[1];

    int width;
    stringstream gamma, epsilon;

    vector<string> diagnostic = read_file(filename);

    width = diagnostic[0].size();
    for(int bit = 0; bit < width; bit++) {
        int c0 = 0, mc;
        for(string number : diagnostic)
            if(number.at(bit) == '0') c0++;
        mc = c0 > diagnostic.size() / 2 ? 0 : 1;
        gamma << mc;
        epsilon << (1 - mc);
    }

    int gamma_rate = stoi(gamma.str(), 0, 2),
        epsilon_rate = stoi(epsilon.str(), 0, 2);

    cout << "gamma rate: " << gamma_rate << endl
         << "epsilon rate: " << epsilon_rate << endl
         << "x: " << gamma_rate * epsilon_rate << endl;

    return 0;
}