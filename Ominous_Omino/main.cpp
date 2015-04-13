#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

string get_solution(int X, int R, int C) {
    if (R*C % X != 0) return "RICHARD";
    else {
        if(X == 4) {
            if(R*C == 4 || R*C == 8) return "RICHARD";
        }
        if(X == 3) {
            if(R*C == 3) return "RICHARD";
        }
        return "GABRIEL";
    }
}

int main()
{
    //INPUT
    typedef int data_type;
    string file_name("../data/Input");
    ifstream input_file(file_name);

    int i(0);
    int T;
    input_file >> T;

    istream_iterator<data_type> start(input_file), end;
    vector<data_type> data(start, end);
    int data_size(0);

    data_size = data.size();
    if (data_size == 0) {
        cerr << "Data from file <" << file_name.c_str() << "> isn't loaded : " << strerror(errno) << endl;
        return 1;
    }
    cout << "T=" << T << endl;
    cout << "File is open" << endl;
    cout << "Read " << data_size << " elements" << std::endl;
    cout << "Data read in:\n";

    ostream_iterator<data_type> out_stream_iterator(cout, " ");
    copy(data.begin(), data.end(), out_stream_iterator);
    input_file.close();
    cout << endl;

    //////////////////////////DO YOUR CODE HERE//////////////////////////

    for(auto i = 0; i < data_size; i += 3) {
        cout << "Case #" << i / 3 + 1 << ": " << get_solution(data[i], data[i+1], data[i+2]) << endl;
    }

    /////////////////////////////////////////////////////////////////////

    //OUTPUT
    cout << "Start to write " << T << " elements" << std::endl;
    ofstream outfile("../data/Output");
    for(auto i = 0; i < data_size; i += 3) {
        outfile << "Case #" << i / 3 + 1 << ": " << get_solution(data[i], data[i+1], data[i+2]) << endl;
    }
    cout << "Finish to write " << T << " elements" << std::endl;
    outfile.close();

    return 0;
}
