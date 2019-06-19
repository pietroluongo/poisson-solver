all:
	@echo "Compiling main..."
	@g++ src/main.cpp -o main

clean:
	@rm main