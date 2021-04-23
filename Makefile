all: run

build:
	# -fstrict-aliasing -Wstrict-aliasing=1
	g++ -std=c++20 -Wall -Wextra -Wpedantic -Wabi -Wdouble-promotion -Wformat=2 -Wformat-overflow=2 -Wformat-security -Wformat-nonliteral -Wformat-signedness -Wformat-truncation=2 -Wformat-y2k -Wnull-dereference -Wuninitialized -Winit-self -Wimplicit-fallthrough=5 -Wmissing-include-dirs -Wswitch-enum -Wunused-parameter -Wunused-const-variable=2 -Wuninitialized -Wmaybe-uninitialized -Winit-self -Wstrict-overflow=5 -Wstringop-overflow=4 -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wsuggest-attribute=cold -Wsuggest-attribute=malloc -Werror src/bin/server/main.cpp -o server
	
run: build
	./server