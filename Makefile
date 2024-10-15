OUT=apvp

build:
	mkdir -p ./bin
	g++ -o ./bin/${OUT} ./src/*.cpp
