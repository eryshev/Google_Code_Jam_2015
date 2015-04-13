#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cstring>
#include <utility>

using namespace std;

struct Quaternion {
public:
    char c;
    //true = +, false -
    bool sign;

    Quaternion(char c,bool sign = true)
        : c(c), sign(sign)
    {}

    Quaternion() {}

    Quaternion operator*(const Quaternion& q) const {
        char c_res;
        bool sign_res(true);
        Quaternion q_res;
        switch (c) {
        case '1':
            switch (q.c) {
            case '1':
                c_res = '1';
                break;
            case 'i':
                c_res = 'i';
                break;
            case 'j':
                c_res = 'j';
                break;
            case 'k':
                c_res = 'k';
                break;
            }
            break;

        case 'i':
            switch (q.c) {
            case '1':
                c_res = 'i';
                break;
            case 'i':
                c_res = '1';
                sign_res = false;
                break;
            case 'j':
                c_res = 'k';
                break;
            case 'k':
                c_res = 'j';
                sign_res = false;
                break;
            }
            break;

        case 'j':
            switch (q.c) {
            case '1':
                c_res = 'j';
                break;
            case 'i':
                c_res = 'k';
                sign_res = false;
                break;
            case 'j':
                c_res = '1';
                sign_res = false;
                break;
            case 'k':
                c_res = 'i';
                break;
            }
            break;

        case 'k':
            switch (q.c) {
            case '1':
                c_res = 'k';
                break;
            case 'i':
                c_res = 'j';
                break;
            case 'j':
                c_res = 'i';
                sign_res = false;
                break;
            case 'k':
                c_res = '1';
                sign_res = false;
                break;
            }
            break;
        }
        q_res.c = c_res;
        q_res.sign = (sign == q.sign) == sign_res;
        return q_res;
    }

    friend ostream& operator<< (ostream& out,const Quaternion& q) {
        return out << (q.sign ? "" : "-" )<< q.c << endl;
    }

    bool operator== (const Quaternion& that) const {
        return c == that.c && sign == that.sign;
    }

    bool operator!= (const Quaternion& that) const {
        return !(*this == that);
    }
};

vector<Quaternion> mk_quaternions(string s) {
    vector<Quaternion> quaternions;
    for (auto c: s) quaternions.push_back(Quaternion(c));
    return quaternions;
}

Quaternion multiply(const vector<Quaternion>& v, long long begin, long long end, long long L) {
    Quaternion res('1');
    if(end - begin <= L) for(auto i = begin; i <= end; ++i) res = res * v[i % L];
    else {
        Quaternion l('1');
        Quaternion m('1');
        Quaternion r('1');
        long chunks = (begin - end) / L;
        for(auto i = begin; i < L; ++i) l = l * v[i % L];
        if (chunks > 1) {
            if ((chunks - 1) % 2 == 1) {
                for(auto i = 0; i < L; ++i) m = m * v[i % L];
                if ((chunks - 1) / 2 % 2 == 1) m = Quaternion('1', false) * m;
            } else {
                if ((chunks - 1) / 2 % 2 == 1) m = Quaternion('1', false);
                else m = Quaternion('1');
            }
        }
        for(auto i = 0; i < end % L; ++i) r = r * v[i % L];
    }
    return res;
}

string get_solution(pair<pair<long long, long long>, string> data) {
    vector<Quaternion> quaternions;
    long long L, X, begin, end;
    Quaternion l('1'), r('1');
    Quaternion i('i'), j('j'), k('k');
    L = data.first.first;
    X = data.first.second;

    begin = 0;
    end = L * X - 1;

    if (L * X < 3) return "NO";

    quaternions = mk_quaternions(data.second);
    l = l * quaternions[begin % L];
    r = quaternions[end % L] * r;

    while (begin < end) {
        if ( l != i && r != k) {
            begin++;
            end--;
            l = l * quaternions[begin % L];
            r = quaternions[end % L] * r;
        }
        else if ( l == i && r != k) {
            end--;
            r = quaternions[end % L] * r;
        }
        else if ( l != i && r == k) {
            begin++;
            l = l * quaternions[begin % L];
        }
        else {
            begin++;
            end--;
            l = l * quaternions[begin % L];
            r = quaternions[end % L] * r;

            if (multiply(quaternions, begin, end, L) == j) return "YES";
        }
    }

    return "NO";
}

int main()
{
    //INPUT
    typedef string data_type;
    string file_name("../data/Input");
    ifstream input_file(file_name);

    long long i(0);
    long long T;
    input_file >> T;

    istream_iterator<data_type> start(input_file), end;
    vector<data_type> data(start, end);
    long long data_size(0);

    data_size = data.size();
    if (data_size == 0) {
        cerr << "Data from file <" << file_name.c_str() << "> isn't loaded : " << strerror(errno) << endl;
        return 1;
    }
    cout << "T=" << T << endl;
    cout << "File is open" << endl;
    cout << "Read " << data_size << " elements" << std::endl;
    cout << "Data read in:\n";

    //////////////////////////DO YOUR CODE HERE//////////////////////////
    vector<pair<pair<long long, long long>, string>> format_data;
    pair<pair<long long, long long>, string> one_case;
    for (i = 0; i < data_size; i += 3) {
        one_case = pair<pair<long long, long long>, string>(pair<long long, long long>(stoll(data[i]), stoll(data[i+1])), data[i+2]);
        format_data.push_back(one_case);
    }

    i = 0;
    for(auto fd : format_data) {
        //cout << "Case #" << i << ": " << << endl;
        cout << "Case #" << i << ": " << endl;
        cout << "size = " << fd.second.size() << endl;
        i++;
    }

    /////////////////////////////////////////////////////////////////////

    //OUTPUT
    cout << "Start to write " << T << " elements" << std::endl;
    ofstream outfile("../data/Output");
    i = 0;
        for(auto fd : format_data) {
            outfile << "Case #" << i+1 << ": " << get_solution(fd) << endl;
            i++;
        }
    cout << "Finish to write " << T << " elements" << std::endl;
    outfile.close();

    return 0;
}
