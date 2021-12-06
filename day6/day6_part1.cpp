#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> read_file(string filename)
{
    vector<int> parsed;
    fstream file;

    file.open(filename, ios::in);
    if(file.is_open()) {
        string tp, n;
        getline(file, tp);
        stringstream stream(tp);
        while(getline(stream, n, ','))
            parsed.push_back(stoi(n));
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

    vector<int> init = read_file(filename);

    for(int i = 0; i < 80; i++) {
        int births = 0;
        for(size_t f = 0; f < init.size(); f++) {
            if(init[f]-- == 0) {
                init[f] = 6;
                births++;
            }
        }
        cout << "births: " << births << endl;
        while(births-- > 0)
            init.push_back(8);
    }

    cout << "population: " << init.size() << endl;

    return 0;
}