#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <math.h>

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

int fuel_cost(int dist) {
    if(dist == 0)
        return 0;
    return dist + fuel_cost(dist - 1);
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

    vector<int> h_pos = read_file(filename);

    int max = h_pos[0];
    for(int p : h_pos)
        if(p > max)
            max = p;
    
    int m_c, m_p;
    for(int i = 0; i <= max; i++) {
        int c = 0;
        for(int p : h_pos)
            c += fuel_cost(abs(p - i));
        if(i == 0 || c < m_c) {
            m_c = c;
            m_p = i;
        }
    }

    cout << "optimal position: " << m_p << endl <<
            "optimal fuel cost: " << m_c << endl;

    return 0;
}