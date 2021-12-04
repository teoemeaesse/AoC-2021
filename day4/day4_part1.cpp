#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct {
    vector<int> data;
} board;

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

vector<int> parse_moves(vector<string> raw)
{
    vector<int> moves;

    stringstream stream(raw[0]);
    while(stream.good()) {
        string sub;
        getline(stream, sub, ',');
        moves.push_back(stoi(sub));
    }

    raw.erase(raw.begin());

    return moves;
}

vector<board> parse_boards(vector<string> raw)
{
    vector<board> boards;

    for(size_t i = 2; i < raw.size(); i += 6) {
        board b = {vector<int>()};

        for(int y = 0; y < 5; y++) {
            stringstream stream(raw[i + y]);
            for(int x = 0; x < 5; x++) {
                string sub;
                while(sub == "")
                    getline(stream, sub, ' ');
                b.data.push_back(stoi(sub));
            }
        }

        boards.push_back(b);
    }

    return boards;
}

void draw_board(board * b, int move, int * x, int * y)
{
    for(int yi = 0; yi < 5; yi++) {
        for(int xi = 0; xi < 5; xi++) {
            if(b->data[yi * 5 + xi] == move) {
                *x = xi;
                *y = yi;
                b->data[yi * 5 + xi] = -1;
            }
        }
    }
}

int sum_unmarked_cells(board b) {
    int sum = 0;

    for(int y = 0; y < 5; y++)
        for(int x = 0; x < 5; x++)
            sum += b.data[y * 5 + x] == -1 ? 0 : b.data[y * 5 + x];

    return sum;
}

bool winner_board(board b, int x, int y)
{
    int s = 0;
    for(int yi = 0; yi < 5; yi++)
        s += b.data[yi * 5 + x];
    if(s == -5)
        return true;
    
    s = 0;
    for(int xi = 0; xi < 5; xi++)
        s += b.data[y * 5 + xi];
    if(s == -5)
        return true;
    
    return false;
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

    vector<string> data = read_file(filename);

    vector<int> moves = parse_moves(data);
    vector<board> boards = parse_boards(data);

    int *x = (int*) malloc(sizeof(int)), *y = (int*) malloc(sizeof(int));
    for(int move : moves) {
        for(board &b : boards) {
            *x = -1;
            draw_board(&b, move, x, y);
            if(*x != -1 && winner_board(b, *x, *y)) {
                cout << "sum of unmarked numbers: " << sum_unmarked_cells(b) << endl
                     << "move: " << move << endl
                     << "x: " << sum_unmarked_cells(b) * move << endl;
                free(x);
                free(y);
                return 0;
            }
        }
    }

    free(x);
    free(y);
    return 0;
}