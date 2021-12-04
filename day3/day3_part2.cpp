#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
    vector<string> co2 = read_file(filename),
                   oxygen = read_file(filename);

    width = co2[0].size();
    
    for(int bit = 0; bit < width && co2.size() > 1; bit++) {
        int c0 = 0;
        char lc_rev;
        for(string number : co2)
            if(number.at(bit) == '0') c0++;
        lc_rev = c0 <= co2.size() / 2 ? '1' : '0';
        co2.erase(
            remove_if(co2.begin(), co2.end(),
                [&](string number) { return number.at(bit) == lc_rev; }),
            co2.end()
        );
    }

    // copy - pasted from above and tweaked due to laziness
    for(int bit = 0; bit < width && oxygen.size() > 1; bit++) {
        int c1 = 0;
        char mc_rev;
        for(string number : oxygen)
            if(number.at(bit) == '1') c1++;
        mc_rev = c1 >= oxygen.size() / 2 ? '0' : '1';
        oxygen.erase(
            remove_if(oxygen.begin(), oxygen.end(),
                [&](string number) { return number.at(bit) == mc_rev; }),
            oxygen.end()
        );
    }

    int co2_rating = stoi(co2[0], 0, 2),
        oxygen_rating = stoi(oxygen[0], 0, 2);
    cout << "co2 scrubber rating: " << co2_rating << endl
         << "oxygen generator rating: " << oxygen_rating << endl
         << "life support rating: " << co2_rating * oxygen_rating << endl;

    return 0;
}