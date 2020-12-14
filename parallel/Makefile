CC := g++ -std=c++11 -pthread
CCFLAGS += -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

BUILD_DIR=build

all: PhonePricePrediction.out

PhonePricePrediction.out: rm mk ${BUILD_DIR}/main.o
	$(CC) ${BUILD_DIR}/main.o -o ./PhonePricePrediction.out

${BUILD_DIR}/main.o: main.cpp
	$(CC) -c main.cpp -o ${BUILD_DIR}/main.o

mk:
	mkdir ./${BUILD_DIR}

rm:
	rm -rf ${BUILD_DIR}/ ./PhonePricePrediction.out
.PHONY: clean
clean:
	rm -rf ${BUILD_DIR}/ ./PhonePricePrediction.out
run: StoreCalculator.out
	./StoreCalculator.out ./commands.txt assets
