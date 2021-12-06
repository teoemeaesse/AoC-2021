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

    long long int timer[9];
    for(int i = 0; i < 9; i++)
        timer[i] = 0;
    
    for(int i : init)
        timer[i]++;

    for(int i = 0; i < 256; i++) {
        long long int spawners = timer[0];
        for(size_t j = 0; j < 8; j++)
            timer[j] = timer[j + 1];
        timer[6] += spawners;
        timer[8] = spawners;
        
        cout << "day " << i + 1 << ": " << spawners << " births" << endl;
    }

    long long int c = 0;
    for(long long int i : timer)
        c += i;

    cout << "population: " << c << endl;

    return 0;
}