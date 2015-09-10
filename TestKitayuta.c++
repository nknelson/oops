// --------------------------------
// projects/collatz/TestKitayuta.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Kitayuta.h"

using namespace std;

// -----------
// TestKitayuta
// -----------

// ----
// eval
// ----

TEST(KitayutaFixture, eval_1) {
    const std::string s = isPalindromizable("abc");
    ASSERT_STREQ(s.c_str(), "NA");}

// TEST(KitayutaFixture, eval_2) {
//     const int v = collatz_eval(100, 200);
//     ASSERT_STREQ(125, v);}

// TEST(KitayutaFixture, eval_3) {
//     const int v = collatz_eval(201, 210);
//     ASSERT_STREQ(89, v);}

// TEST(KitayutaFixture, eval_4) {
//     const int v = collatz_eval(900, 1000);
//     ASSERT_STREQ(174, v);}

// TEST(KitayutaFixture, eval_5) {
//      const int v = collatz_eval(1, 1);
//      ASSERT_STREQ(1, v);}

// TEST(KitayutaFixture, eval_6) {
//     const int v = collatz_eval(10, 10);
//     ASSERT_STREQ(7, v);}

// TEST(KitayutaFixture, eval_7) {
//     const int v = collatz_eval(22, 22);
//     ASSERT_STREQ(16, v);}

// TEST(KitayutaFixture, eval_8) {
//     const int v = collatz_eval(3, 3);
//     ASSERT_STREQ(8, v);}

// -----
// print
// -----

// TEST(KitayutaFixture, print) {
//     ostringstream w;
//     collatz_print(w, 1, 10, 20);
//     ASSERT_STREQ("1 10 20\n", w.str());}

// -----
// solve
// -----

TEST(KitayutaFixture, solve) {
    istringstream r("abc\n");
    ostringstream w;
    kitayuta_solve(r, w);
    ASSERT_STREQ("abc: NA\n", w.str().c_str());}

/*
% g++ -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Kitayuta.c++ TestKitayuta.c++ -o TestKitayuta -lgtest -lgtest_main -lpthread



% valgrind TestKitayuta                                         >  TestKitayuta.out 2>&1
% gcov -b Kitayuta.c++     | grep -A 5 "File 'Kitayuta.c++'"     >> TestKitayuta.out
% gcov -b TestKitayuta.c++ | grep -A 5 "File 'TestKitayuta.c++'" >> TestKitayuta.out



% cat TestKitayuta.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestKitayuta
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Kitayuta
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
*/
