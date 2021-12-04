#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

    vector<string> commands = read_file(filename);

    int size = commands.size(),
        h_dist = 0, v_dist = 0,
        delta;
    string direction;

    for(int i = 0; i < size; i++) {
        direction = commands[i].substr(0, commands[i].find(" "));
        delta = stoi(commands[i].substr(direction.size() + 1, commands[i].size()));
        
        if(direction == "forward") h_dist += delta;
        else if(direction == "down") v_dist += delta;
        else if(direction == "up") v_dist -= delta;
    }

    cout << "horizontal distance:  " << h_dist << endl
         << "depth: " << v_dist << endl
         << "x: " << h_dist * v_dist << endl;

    return 0;
}