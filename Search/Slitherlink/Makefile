all: slink genAlpha genBeta

slink: checker.cpp slitherlink.cpp
	g++ checker.cpp slitherlink.cpp -o slink -O3 -ffast-math -std=c++20 -DLOCAL

genAlpha: genAlpha.cpp
	g++ genAlpha.cpp -o genAlpha -O3 -ffast-math -std=c++20

genBeta: genBeta.cpp slitherlink.cpp
	g++ genBeta.cpp slitherlink.cpp -o genBeta -O3 -ffast-math -std=c++20

clean: slink genAlpha genBeta
	rm slink genAlpha genBeta