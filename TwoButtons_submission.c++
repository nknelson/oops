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
#include <vector>


using namespace std;

// -------------
// collatz_solve
// -------------

void two_buttons_solve (istream& r, ostream& w) {
  string s;
  getline(r, s);
  istringstream sin(s);
  int n;
  int m;
  sin >> n >> m;
  // w << "n=" << n << ", m=" << m;

  int ctr = 0;
  if (m < n) {
    ctr = n - m;
  }
  else {
    while (true) {
      if (m == n)
	break;
      else if (m < n) {
	ctr += (n - m);
	break;
      }
      else if ((m & 0x1) == 0) {
	m >>= 1;
	++ctr;
      }
      else {
	m += 1;
	m >>= 1;
	ctr += 2;
      }
    }
  }
  w << ctr;
}

int main () {
    using namespace std;
    two_buttons_solve(cin, cout);
    return 0;
}
