#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

int get_solution(string audience, int guests = 0) {
    if (audience.empty()) return guests;
    int sum(0);
    int sample(0);
    for(auto c : audience) {
        sample = c - 48;
        sum += sample;
    }
    sum -= audience.back() - 48;
    int back = audience.size() - 1;

    int result = back - sum;
    audience.resize(audience.size() - 1);
    if (result >= 0)
        return get_solution(audience, result > guests ? result : guests);
    else {
        return get_solution(audience, guests);
    }
}

int main()
{
    //INPUT
    typedef string data_type;
    string file_name("../data/Input");
    ifstream input_file(file_name);

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

    //OUTPUT
    cout << "Start to write " << T << " elements" << std::endl;
    ofstream outfile("../data/Output");
    //outfile << endl;
    for(auto i = 0; i < T; ++i) {
        outfile << "Case #" << i+1 << ": " << get_solution(data[2*i + 1]) << endl;
    }
    cout << "Finish to write " << T << " elements" << std::endl;
    outfile.close();

    return 0;
}
