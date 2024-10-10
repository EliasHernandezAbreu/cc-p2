OUT=apvp

build:
	mkdir -p ./bin
	g++ -o ${OUT} ./src/*.cpp