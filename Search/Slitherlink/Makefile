all: slink genAlpha genBeta

slink: checker.cpp slitherlink.cpp
	g++ checker.cpp slitherlink.cpp -o slink -O2 -std=c++20 -DLOCAL

genAlpha: genAlpha.cpp
	g++ genAlpha.cpp -o genAlpha -O2 -std=c++20

genBeta: genBeta.cpp
	g++ genBeta.cpp -o genBeta -O2 -std=c++20

clean: slink genAlpha genBeta
	rm slink genAlpha genBeta