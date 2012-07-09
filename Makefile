all:
	g++ -o main *.cpp -Wall -Wextra -lallegro -lallegro_primitives \
		-lallegro_image -ggdb
