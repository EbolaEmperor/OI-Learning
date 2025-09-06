all: slink genAlpha genBeta drawPermeate

slink: checker.cpp slitherlink.cpp
	g++ checker.cpp slitherlink.cpp -o slink -O3 -ffast-math -std=c++20 -DLOCAL

genAlpha: genAlpha.cpp
	g++ genAlpha.cpp -o genAlpha -O3 -ffast-math -std=c++20

genBeta: genBeta.cpp slitherlink.cpp permeate.cpp
	g++ genBeta.cpp slitherlink.cpp permeate.cpp -o genBeta -O3 -ffast-math -std=c++20

drawPermeate: drawPermeate.cpp permeate.cpp pnglib/miniz.hpp pnglib/pnglib.hpp
	g++ drawPermeate.cpp permeate.cpp -o drawPermeate -O3 -ffast-math -std=c++20

clean: slink genAlpha genBeta drawPermeate
	rm slink genAlpha genBeta drawPermeate