#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>

using namespace std;


int get_solution(const pair<int, vector<int>>& config) {
    vector<int> P = config.second;

    int size = P.size();
    int answer(100);

    for (int i = 1; i < 1000; ++i) {
        int cur = i;
        for (int j = 0; j < size; ++j)
            cur += (P[j] - 1)/i;
        answer = min(cur, answer);
    }

    return answer;
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

    ostream_iterator<data_type> out_stream_iterator(cout, " ");
    copy(data.begin(), data.end(), out_stream_iterator);
    input_file.close();
    cout << endl;

    vector<pair<int, vector<int>>> cases;
    vector<int>::iterator it = data.begin();
    int D;
    vector<int> P;
    while(it < data.end()) {
        D = *it;
        for(auto i=0; i<D; ++i) P.push_back(*(it + i+1));
        cases.push_back(pair<int, vector<int>>(D, P));
        P.clear();
        advance(it, D+1);
    }

    //OUTPUT
    cout << "Start to write " << T << " elements" << std::endl;
    ofstream outfile("../data/Output");
    i = 0;
    for(auto c: cases) {
        outfile << "Case #" << i + 1 << ": " << get_solution(c) << endl;
        i++;
    }
    cout << "Finish to write " << T << " elements" << std::endl;
    outfile.close();

    return 0;
}
