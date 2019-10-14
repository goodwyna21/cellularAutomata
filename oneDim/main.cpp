#include <iostream>
#include <bitset>
#include <cstdlib>
#include <fstream>

using namespace std;

//constants
const int default_max_gens = 20;
const string default_t0 = "1";
const bool default_state = false;
const char default_active = '*';
const char default_inactive = ' ';

int main(int argc, char* argv[]){
    if(argc == 1){
        cout << "expected parameters:\nautomata rule_number [generations] [initial generation] [output image filename]\n";
        return 0;
    }

    //command line arguments
    const int rule_number = atoi(argv[1]);
    const int max_gens = ((argc > 2)?atoi(argv[2]):default_max_gens);
    const string t0_string = ((argc > 3)?argv[3]:default_t0);
    const bool image_out = (argc > 4);
    const string img_fname = (argc > 4)?argv[4]:"";

    //intialize rules from rule number
    string rule_bin = bitset<8>(rule_number).to_string();
    bool rules[8];
    for(int i = 0; i < 8; ++i){rules[i] = (rule_bin[i]=='1');}

    string above(3,'0'); //used for determining rule

    //initial state
    const int initial_size = t0_string.size();
    bool t0[initial_size];
    for(int i = 0; i < initial_size; ++i){
        t0[i] = (t0_string[i]=='1');
    }

    //initialize rows
    const int row_size = 2*max_gens - 1;
    bool rows[max_gens][row_size];

    //initialize t0 into rows[0]
    const int padding = (row_size-initial_size)/2;
    for(int i = 0; i < padding; ++i){
        rows[0][i] = default_state;
        rows[0][row_size-(i+1)] = default_state;
    }
    for(int i = 0; i < initial_size; ++i){
        rows[0][padding+i] = t0[i];
    }

    //image output setup
    ostream* output;
    char active,inactive;
    ofstream outfile;
    if(image_out){
        outfile.open(img_fname, ios::out);
        output = (&outfile);
        (*output) << "P1\n" << row_size << " " << max_gens << "\n";
        active = '1';
        inactive = '0';
    }else{
        output = (&cout);
        active = default_active;
        inactive = default_inactive;
    }

    //mainloop
    for(int gen = 0; gen < max_gens; ++gen){
        for(int i = 0; i < row_size; ++i){
            //display row
            (*output) << (rows[gen][i] ? active : inactive);

            //build next row
            if(gen < max_gens-1){
                for(int k = -1; k <= 1; ++k){
                    if( i+k < 0 || i+k >= row_size){
                        above[k+1] = (default_state?'1':'0');
                    }else{
                        above[k+1] = (rows[gen][i+k]?'1':'0');
                    }
                }
                rows[gen+1][i] = rules[7 - bitset<8>(above).to_ulong()];
            }

        }
        if(!image_out){
            (*output) << "\n";
        }
    }

    if(image_out){
        outfile.close();
    }

    return 0;
}
