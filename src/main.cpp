#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>

#include "svp.hpp"

using namespace std;
using namespace NTL;
using namespace svp_algorithm;
namespace fs = std::filesystem;

enum tokens {
    NUMBER,
    SVP_ALGORITHM,
    MODE,
};

enum mode {
    ALL,
    SYMMETRIC,
};

map<string, svp_alg> d = {
    {"lll", lll_svp},
    {"bkz", exact_svp}};  // map of svp algorithms

map<string, mode> m = {
    {"all", ALL},
    {"sym", SYMMETRIC}};  // map of modes

tokens get_token(string s) {
    if (all_of(s.begin(), s.end(), ::isdigit)) {
        return NUMBER;
    } else if (d.find(s) != d.end()) {
        return SVP_ALGORITHM;
    } else if (m.find(s) != m.end()) {
        return MODE;
    } else {
        cerr << "Error: invalid argument '" << s << "'" << endl;
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " N start [stop] [step] [lll|bkz] [all|sym|center] [args...]" << endl;
        exit(1);
    }
    int N, start, stop, step = 1;
    svp_alg f = exact_svp;
    mode mode = ALL;
    string alg_s = "bkz", mode_s = "all";

    if (get_token(argv[1]) != NUMBER) {
        cerr << "Error: invalid argument '" << argv[1] << "'" << endl;
        exit(1);
    } else {
        N = stoi(argv[1]);
    }

    if (get_token(argv[2]) != NUMBER) {
        cerr << "Error: invalid argument '" << argv[2] << "'" << endl;
        exit(1);
    } else {
        start = stop = stoi(argv[2]);
    }

    int idx = 3;
    if (idx < argc && get_token(argv[idx]) == NUMBER) {
        stop = stoi(argv[idx]);
        idx++;
    }

    if (idx < argc && get_token(argv[idx]) == NUMBER) {
        step = stoi(argv[idx]);
        idx++;
    }

    if (idx < argc && get_token(argv[idx]) == SVP_ALGORITHM) {
        f = d[argv[idx]];
        alg_s = argv[idx];
        idx++;
    }

    if (idx < argc && get_token(argv[idx]) == MODE) {
        mode = m[argv[idx]];
        mode_s = argv[idx];
        idx++;
    }

    // create output directory
    fs::create_directory("out");
    fs::create_directory("out/" + to_string(N));

    ofstream file("out/" + to_string(N) + "/" + to_string(start) + "-" + to_string(stop) + "-" + to_string(step) + "-" + alg_s + "-" + mode_s + ".txt");
    cout << "N = " << N << ", start = " << start << ", stop = " << stop << ", step = " << step << ", algorithm = " << alg_s << ", mode = " << mode_s << endl;
    switch (mode) {
        case ALL: {
            for (int p = start; p <= stop; p += step) {
                svp_all(f, p, N, file);
            }
            break;
        }
        case SYMMETRIC: {
            for (int p = start; p <= stop; p += step) {
                svp_sym(f, p, N, file);
            }
            break;
        }
    }

    return 0;
}
