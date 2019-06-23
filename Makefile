all:
	@echo "Compiling main..."
	@g++ src/main.cpp src/poissonSOR.cpp -o main

clean:
	@rm main