
bool isPalindrome (const string & s) {
  return (s == s.reverse());
}

string isPalindromizable(const string & s) {
  string ret_s = s;
  if (s.length == 1) {
    return s.first + s.first;
  }
  if (s.length == 2) {
    if (s.first != s.last) {
      return "N/A";
    }
  }
  if (s.first != s.last) {
    string tmp = s + s.first;
    if (isPalindrome(tmp)) {
      return tmp;
    }
    tmp = s.last + s;
    if (isPalindrome(tmp)) {
      return tmp;
    }
    return "N/A";
  }
  // First and last are the same
  first = s.first;
  string tmp = s - s.first;
  tmp = tmp - tmp.last;
  if (isPalindromizable(tmp) == "N/A") {
    return "N/A";
  }
  else {
    return first + s + first;
  }
}
