#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> parse_entry(string raw)
{
    vector<string> entry;
    string e;
    
    stringstream stream(raw);
    while(getline(stream, e, ' '))
        if(e != "|")
            entry.push_back(e);

    return entry;
}

vector<string> read_file(string filename)
{
    vector<string> entries;
    fstream file;

    file.open(filename, ios::in);
    if(file.is_open()) {
        string ln;
        while(getline(file, ln))
            entries.push_back(ln);
        file.close();
    }

    return entries;
}

vector<string> last_four(vector<string> full)
{
    vector<string> lf(4);
    int s = full.size();

    for(int i = 4; i > 0; i--)
        lf.push_back(full[s - i]);
    
    return lf;
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

    vector<string> segments = read_file(filename);
    int count = 0;

    for(string s : segments) {
        vector<string> entry = parse_entry(s);
        vector<string> lf = last_four(entry);
        for(string e : lf) {
            int ss = e.size();
            if(ss == 2 || ss == 4 || ss == 3 || ss == 7)
                count++;
        }
    }

    cout << "count: " << count << endl;

    return 0;
}