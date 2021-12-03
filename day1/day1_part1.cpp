#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> read_file(string filename) {
    vector<int> parsed;
    fstream file;

    file.open(filename, ios::in);
    if(file.is_open()) {
        string tp;
        while(getline(file, tp)) {
            parsed.push_back(stoi(tp));
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

    vector<int> depths = read_file(filename);

    int previous = -1, count = 0;
    for(int d : depths) {
        if(d > previous && previous != -1)
            count++;
        previous = d;
    }

    cout << "depth increased " << count << " times" << endl;

    return 0;
}