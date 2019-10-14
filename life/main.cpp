#include <iostream>
#include <fstream>
#include <algorithm>
#include <unistd.h>
#include <string>

using namespace std;

const string alive = "\u2588";
const string dead = "\u00B7";
const string default_fname = "Boards/default.txt";

const string hline = "\u2500";

int main(int argc, char* argv[]){
    string fname;
    int width;
    int height;
    if(argc < 2){
        fname = default_fname;
    }else{
        fname = argv[1];
    }

    ifstream infile(fname, ios::in);
    string line;
    int neighbors;

    int Width;
    int Height;
    infile >> Width;
    infile >> Height;
    getline(infile,line);
    bool board[Width][Height];
    bool newboard[Width][Height];

    cout << "\u250C";
    for(int x = 0; x < Width; x++){
        cout << hline;
    }
    cout << "\u2510\n";
    for(int y = 0; y < Height; y++){
        getline(infile,line);
        cout << "\u2502" << string(Width,' ') << "\u2502\n";
        for(int x = 0; x < Width; x++){
            board[x][y] = (line[x]=='1');
        }
    }
    cout << "\n";

    bool done = false;
    int countdown = -1;
    bool nonealive = false;
    while(!done){
        //display
        //print bottom border (this clears the user input too)
        cout << "\x1b[A\u2514";
        for(int x = 0; x < Width; x++){
            cout << hline;
        }
        cout << "\u2518\n";
        cout << ("\x1b[" + to_string(Height+1) + "A") << "\x1b[C";
        //print board and check for nonealive
        nonealive = false;
        for(int y = 0; y < Height; y++){
            for(int x = 0; x < Width; x++){
                cout << (board[x][y] ? alive : dead);
                if(!board[x][y] && !nonealive){
                    nonealive = true;
                }
            }
            cout << "\x1b[B";
            for(int x = 0; x < Width; x++){
                cout << "\x1b[D";
            }
        }

        //update board
        for(int y = 0; y < Height; y++){
            for(int x = 0; x < Width; x++){
                newboard[x][y] = board[x][y];
                neighbors=0;

                //count neighbors
                for(int y1 = y-1; y1 <= y+1; y1++){
                    for(int x1 = x-1; x1 <= x+1; x1++){
                        if(y1==y && x1 == x){
                            continue;
                        }
                        if(x1 < 0 || x1 >= Width ||
                           y1 < 0 || y1 >= Height){
                            continue;
                        }
                        if(board[x1][y1]){
                            neighbors++;
                        }
                    }
                }

                //apply rules
                if(board[x][y] && (neighbors < 2 || neighbors > 3)){
                    newboard[x][y] = false;
                }else if(!board[x][y] && neighbors == 3){
                    newboard[x][y] = true;
                }
            }
        }
        copy(&newboard[0][0],&newboard[0][0]+(Width*Height),&board[0][0]);

        //handle end of loop
        if(nonealive){ //end if none are left alive
            cout << "done\n";
            done = true;
        }else if(countdown >= 0){ //this allows you to loop automatically
            cout << countdown << "\n";
            countdown--;
            usleep(1000000);
        }else{ //user commands
            line = cin.get();
            if(line.size() == 0){
                continue;
            }
            if(line[0] == 'q'){ //quit
                done = true;
            }else if(line[0] == 'r'){ //repeat n times
                cin >> countdown;
            }
        }
    }

    return 0;
}
