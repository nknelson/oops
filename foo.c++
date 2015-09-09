// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <vector>

using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// collatz_eval
// ------------

int cycle_length (int n) {
  int cyclen = 0;
  while (n >= 1) {
    ++cyclen;
    //std::cout << n;
    if (n == 1) {
      break;
    }
    else {
      if (n % 2) {
	n = (3*n) + 1;
      }
      else {
	n = n >> 1;
      }
      //std::cout << " ";
    }
  }
  //std::cout << "\n";
  return cyclen;
}

// Solution 1, brute-force
// int collatz_eval (int i, int j) {

//   int max_cyc_len = 0;
//   int lb;
//   int ub;
//   if (i > j) {
//     lb = j;
//     ub = i;
//   }
//   else {
//     lb = i;
//     ub = j;
//   }
//   for (int k = lb; k <= ub; ++k) {
//     int cyc_len= cycle_length(k);
//     //std::cout << "k = " << i << ", cyc_len = " << cyc_len << std::endl;
//     max_cyc_len = (max_cyc_len >= cyc_len) ? max_cyc_len : cyc_len;
//   }
//   return max_cyc_len;
// }

// Solution 2
// Inline, optimized odd cases
// int collatz_eval (int i, int j) {

//   int max_cyc_len = 0;
//   int lb;
//   int ub;
//   if (i > j) {
//     lb = j;
//     ub = i;
//   }
//   else {
//     lb = i;
//     ub = j;
//   }

//   for (int k = lb; k <= ub; ++k) {
//     //int cyc_len = cycle_length(k);
//     //std::cout << "k = " << i << ", cyc_len = " << cyc_len << std::endl;
//     //max_cyc_len = (max_cyc_len >= cyc_len) ? max_cyc_len : cyc_len;

//     int cyclen = 0;
//     int n = k;

//     while (n >= 1) {
//       //std::cout << n;
//       ++cyclen;
//       if (n == 1) {
// 	break;
//       }
//       else {
// 	if (n % 2) {
// 	  n = (3*n) + 1;
// 	}
// 	else {
// 	  n = n >> 1;
// 	}
//       }
//       //std::cout << " ";
//     }
//     max_cyc_len = (max_cyc_len >= cyclen) ? max_cyc_len : cyclen;
//   }
//   return max_cyc_len;
// }

// Solution 3
int collatz_eval (int i, int j) {

  int max_cyc_len = 0;
  int lb;
  int ub;
  if (i > j) {
    lb = j;
    ub = i;
  }
  else {
    lb = i;
    ub = j;
  }

  static vector<int> cyclen_cache(1000001, 0);
  
  for (int k = lb; k <= ub; ++k) {
    //int cyc_len = cycle_length(k);
    //std::cout << "k = " << i << ", cyc_len = " << cyc_len << std::endl;
    //max_cyc_len = (max_cyc_len >= cyc_len) ? max_cyc_len : cyc_len;

    int cyclen = 0;
    int n = k;

    while (n >= 1) {
      //std::cout << n;
      if (n < cyclen_cache.size() && cyclen_cache[n] > 0) {
	cyclen += cyclen_cache[n];
	break;
      }
      ++cyclen;

      if (n == 1) {
	break;
      }
      
      if (n > 1) {
	if (n % 2) {
	  n = (3*n) + 1;
	}
	else {
	  n = n >> 1;
	}
      }
      //std::cout << " ";
    }
    cyclen_cache[k] = cyclen;
    max_cyc_len = (max_cyc_len >= cyclen) ? max_cyc_len : cyclen;
  }
  return max_cyc_len;
}


// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    string s;
    while (getline(r, s)) {
        const pair<int, int> p = collatz_read(s);
        const int            i = p.first;
        const int            j = p.second;
        const int            v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// -------------------------------

// ----
// main
// ----

int main () {
    using namespace std;
    collatz_solve(cin, cout);
    return 0;}

/*
% g++ -pedantic -std=c++11 -Wall Collatz.c++ RunCollatz.c++ -o RunCollatz



% cat RunCollatz.in
1 10
100 200
201 210
900 1000



% RunCollatz < RunCollatz.in > RunCollatz.out



% cat RunCollatz.out
1 10 1
100 200 1
201 210 1
900 1000 1



% doxygen -g
// That creates the file Doxyfile.
// Make the following edits to Doxyfile.
// EXTRACT_ALL            = YES
// EXTRACT_PRIVATE        = YES
// EXTRACT_STATIC         = YES



% doxygen Doxyfile
// That creates the directory html/.
*/
