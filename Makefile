all: run

build:
	# https://gist.github.com/jrelo/f5c976fdc602688a0fd40288fde6d886
	# -fstrict-aliasing -Wstrict-aliasing=1  -funsafe-loop-optimizations
	g++ -std=c++20 \
	-Wall -Wextra -Wpedantic -Wdouble-promotion -Wformat=2 -Wformat-overflow=2 -Wformat-security -Wformat-nonliteral -Wformat-signedness -Wformat-truncation=2 -Wformat-y2k -Wnull-dereference -Wuninitialized -Winit-self -Wimplicit-fallthrough=5 -Wmissing-include-dirs -Wswitch-enum -Wunused-parameter -Wunused-const-variable=2 -Wuninitialized -Wmaybe-uninitialized -Winit-self -Wstrict-overflow=5 -Wstringop-overflow=4 -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format -Wsuggest-attribute=cold -Wsuggest-attribute=malloc -Wmissing-noreturn -Wmissing-format-attribute -Walloc-zero -Walloca -Warith-conversion -Warray-bounds=2 -Wattribute-alias=2 -Wduplicated-branches -Wduplicated-cond -Warray-bounds -Wtrampolines -Wfloat-equal -Wshadow=global -Wunsafe-loop-optimizations -Wno-aggressive-loop-optimizations -Wundef -Wunused-macros -Wcast-qual -Wcast-align=strict -Wconversion -Wsign-conversion -Wparentheses -Wdate-time -Wlogical-op -Waggregate-return -Wno-builtin-declaration-mismatch -Wmissing-declarations -Wpacked -Wpadded -Wredundant-decls -Winline -Wvector-operation-performance -Wdisabled-optimization -Wstack-protector -Werror \
	-fstrict-overflow -pie -fPIE src/bin/server/main.cpp -o server
	
run: build
	./server