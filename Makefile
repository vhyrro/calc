build:
	clang++ -std=c++20 src/**.cpp -o a.out
	chmod +x a.out

run:
	./a.out
