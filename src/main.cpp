#include <algorithm>
#include <chrono>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <map>

#include "hlawka.hpp"
#include "svp.hpp"

using namespace std;
using namespace NTL;
using namespace svp_algorithm;
namespace fs = std::experimental::filesystem;

enum tokens {
    NUMBER,
    FLOAT,
    SVP_ALGORITHM,
    MODE,
};

enum mode {
    ALL,
    SYMMETRIC,
    SYMMETRIC_DIAG,
    SYMMETRIC_DIAG_STOP
};

map<string, svp_alg> d = {
    {"lll", lll_svp},
    {"bkz", exact_svp}};  // map of svp algorithms

map<string, mode> m = {
    {"all", ALL},
    {"sym", SYMMETRIC},
    {"sym_d", SYMMETRIC_DIAG},
    {"sym_ds", SYMMETRIC_DIAG_STOP}};  // map of modes

tokens get_token(string s) {
    if (all_of(s.begin(), s.end(), ::isdigit)) {
        return NUMBER;
    } else if (all_of(s.begin(), s.end(), [](char c) { return isdigit(c) || c == '.'; })) {
        return FLOAT;
    } else if (d.find(s) != d.end()) {
        return SVP_ALGORITHM;
    } else if (m.find(s) != m.end()) {
        return MODE;
    } else {
        cerr << "Error: invalid argument '" << s << "'" << endl;
        exit(1);
    }
}

using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

int main(int argc, char *argv[]) {
    // // ofstream outfile("time.txt");

    // for (int i = 2; i < 999; i++) {
    //     int p = 600;
    //     Vec<ZZ> a = Hlawka::random_U(i, 400, 550);

    //     auto t1 = high_resolution_clock::now();
    //     double l = exact_svp(p, a, i);
    //     auto t2 = high_resolution_clock::now();
    //     cout << "N = " << i << " " << l / Hlawka::q(p, i) << " " << Hlawka::minkowski(i) << endl;
    //     // auto ms_int = duration_cast<milliseconds>(t2 - t1);
    //     // outfile << i << " " << ms_int.count() << endl;
    // }

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
        case SYMMETRIC_DIAG: {
            double r = 0.3;
            if (idx < argc && get_token(argv[idx]) == FLOAT) {
                r = stod(argv[idx]);
                idx++;
            }
            for (int p = start; p <= stop; p += step) {
                svp_sym_diag(f, p, N, r, file);
            }
            break;
        }
        case SYMMETRIC_DIAG_STOP: {
            double r = 0.3;
            if (idx < argc && get_token(argv[idx]) == FLOAT) {
                r = stod(argv[idx]);
                idx++;
            }
            for (int p = start; p <= stop; p += step) {
                if (svp_sym_diag_stop(f, p, N, r, file) >= 1) break;
            }
            break;
        }
    }

    return 0;
}
