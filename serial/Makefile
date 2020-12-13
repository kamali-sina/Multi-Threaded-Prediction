CC := g++ -std=c++11
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

BUILD_DIR=build

all: PhonePricePrediction.out

PhonePricePrediction.out: rm mk ${BUILD_DIR}/main.o ${BUILD_DIR}/parser.o ${BUILD_DIR}/regression.o
	$(CC) ${BUILD_DIR}/main.o ${BUILD_DIR}/parser.o ${BUILD_DIR}/regression.o -o ./PhonePricePrediction.out

${BUILD_DIR}/main.o: parser.hpp main.cpp
	$(CC) -c main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/parser.o: parser.cpp
	$(CC) -c parser.cpp -o ${BUILD_DIR}/parser.o

${BUILD_DIR}/regression.o: regression.cpp
	$(CC) -c regression.cpp -o ${BUILD_DIR}/regression.o


mk:
	mkdir ./${BUILD_DIR}

rm:
	rm -rf ${BUILD_DIR}/ ./PhonePricePrediction.out
.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}/*o ./StoreCalculator.out result.out
run: StoreCalculator.out
	./StoreCalculator.out ./commands.txt assets
