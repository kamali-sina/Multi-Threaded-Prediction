CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

BUILD_DIR=build

all: StoreCalculator.out

StoreCalculator.out: rm mk ${BUILD_DIR}/main.o ${BUILD_DIR}/parser.o ${BUILD_DIR}/forker.o
	$(CC) ${BUILD_DIR}/main.o ${BUILD_DIR}/parser.o ${BUILD_DIR}/forker.o -o ./StoreCalculator.out

${BUILD_DIR}/main.o: parser.hpp main.cpp
	$(CC) -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/parser.o: parser.cpp
	$(CC) -c parser.cpp -o ${BUILD_DIR}/parser.o

${BUILD_DIR}/forker.o: parser.hpp forker.cpp
	$(CC) -c forker.cpp -o ${BUILD_DIR}/forker.o


mk:
	mkdir ./${BUILD_DIR}
	mkdir ./namedpipes

rm:
	rm -rf ${BUILD_DIR}/ ./StoreCalculator.out namedpipes
.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}/*o ./StoreCalculator.out result.out
run: StoreCalculator.out
	./StoreCalculator.out ./commands.txt assets
