all: slink gen

slink: checker.cpp slitherlink.cpp
	g++ checker.cpp slitherlink.cpp -o slink -O2 -std=c++20 -DLOCAL

gen: genPuzzle.cpp genSplit.cpp
	g++ genPuzzle.cpp -o genPuzzle -O2 -std=c++20
	g++ genSplit.cpp -o genSplit -O2 -std=c++20