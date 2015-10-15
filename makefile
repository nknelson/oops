CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall -I.
LDFLAGS    := -L. -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunKitayuta
	rm -f RunKitayuta.tmp
	rm -f TestKitayuta
	rm -f TestKitayuta.tmp

config:
	git config -l

scrub:
	make  clean
	rm -f  Kitayuta.log
	rm -rf collatz-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: RunKitayuta.tmp TestKitayuta.tmp

Ballot: Ballot.c++
	g++ -std=c++11 -g -o Ballot Ballot.c++

dijkstra: dijkstra.c++
	g++ -std=c++11 -g -o dijkstra dijkstra.c++

dijkstra_test: dijkstra
	for i in 1 2 3 4 5 6 7 8 9 ; do echo input$$i ; ./dijkstra < input$$i | diff - result$$i ; done

RunKitayuta: Kitayuta.h Kitayuta.c++ RunKitayuta.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Kitayuta.c++ RunKitayuta.c++ -o RunKitayuta

RunKitayuta.tmp: RunKitayuta
	./RunKitayuta < RunKitayuta.in > RunKitayuta.tmp
	diff RunKitayuta.tmp RunKitayuta.out

TestKitayuta: Kitayuta.h Kitayuta.c++ TestKitayuta.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Kitayuta.c++ TestKitayuta.c++ -o TestKitayuta $(LDFLAGS)

TestKitayuta.tmp: TestKitayuta
	$(VALGRIND) ./TestKitayuta                                       >  TestKitayuta.tmp 2>&1
	$(GCOV) -b Kitayuta.c++     | grep -A 5 "File 'Kitayuta.c++'"     >> TestKitayuta.tmp
	$(GCOV) -b TestKitayuta.c++ | grep -A 5 "File 'TestKitayuta.c++'" >> TestKitayuta.tmp
	cat TestKitayuta.tmp
