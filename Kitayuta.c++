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
#include <sstream>
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <vector>


#include "Kitayuta.h"

using namespace std;

// ------------
// collatz_eval
// ------------

bool isPalindrome (const string & s) {
  //string rev(s.rbegin(), s.rend());
  //return (s == rev);

  return std::equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}

string isPalindromizable(const string & s) {
  string ret_s = s;
  size_t length = s.length();

  if (length <= 2) {
      ret_s.push_back(s.front());
      return ret_s;
  }
  // string length > 2
  if (s.front() != s.back()) {
    ret_s.push_back(s.front());
    if (isPalindrome(ret_s)) {
      return ret_s;
    }
    ret_s.pop_back();
    ret_s.insert(ret_s.begin(), s.back());
    if (isPalindrome(ret_s)) {
      return ret_s;
    }
    return "NA"; 
  }
  // First and last are the same, length >= 3
  string tmp_s = isPalindromizable(s.substr(1, length - 2));
  if (tmp_s == "NA") {
    return tmp_s;
  }
  else {
    return ret_s.replace(1, length-2, tmp_s);
  }
}

// -------------
// collatz_solve
// -------------

void kitayuta_solve (istream& r, ostream& w) {
    string input_s;
    
    while (getline(r, input_s)) {
      ostringstream output_s;
      w << input_s << ": ";
      //output_s << input_s << " is";
      w << isPalindromizable(input_s) << endl;
    }
}
