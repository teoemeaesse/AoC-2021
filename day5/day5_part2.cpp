#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

typedef struct {
    int x1, x2, 
        y1, y2;
} line;

vector<line> read_file(string filename)
{
    vector<line> parsed;
    fstream file;

    file.open(filename, ios::in);
    if(file.is_open()) {
        string tp;
        while(getline(file, tp)) {
            int x1, x2, y1, y2;
            sscanf(tp.c_str(), "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
            line l = {x1, x2, y1, y2};
            parsed.push_back(l);
        }
        file.close();
    }

    return parsed;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int max(int a, int b)
{
    return a > b ? a : b;
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

    int map[1000][1000] = {0};

    vector<line> lines = read_file(filename);
    
    for(line l : lines) {
        int xd = l.x2 - l.x1 > 0 ? 1 : l.x2 - l.x1 == 0 ? 0 : -1,
            yd = l.y2 - l.y1 > 0 ? 1 : l.y2 - l.y1 == 0 ? 0 : -1,
            d = 0;
        while(abs(d) <= max(abs(l.x2 - l.x1), abs(l.y2 - l.y1))) {
            map[l.x1 + d * xd][l.y1 + d * yd]++;
            d++;
        }
    }

    int count = 0;

    for(int x = 0; x < 1000; x++)
        for(int y = 0; y < 1000; y++)
            if(map[x][y] > 1)
                count++;
    
    cout << "overlaps: " << count << endl;

    return 0;
}