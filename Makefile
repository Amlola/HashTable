SANIT_FLAGS = #-fsanitize=address,alignment,undefined
CMP_FLAG = #-D COMPARISON
OPT_FLAG = -O2
DEBUG = #-D DEBUG_LIST -D DEBUG_TABLE

all: asm hash

hash: main.o list.o hash_table.o read.o hash_func.o
	@g++ -g -mavx2 -masm=intel -no-pie $(DEBUG) $(OPT_FLAG) $(SANIT_FLAGS) -o hash2.exe obj/main.o List_Index/list.o obj/hash_table.o obj/read.o obj/hash_func.o obj/inline_crc32.o

main.o: src/main.cpp
	@g++ -g -mavx2 -masm=intel $(DEBUG) $(OPT_FLAG) $(SANIT_FLAGS) -c src/main.cpp -o obj/main.o

list.o: List_Index/list.cpp
	@g++ -g -mavx2 -masm=intel $(DEBUG) $(OPT_FLAG) $(SANIT_FLAGS) -c List_Index/list.cpp -o List_Index/list.o

hash_table.o: src/hash_table.cpp
	@g++ -g -mavx2 -masm=intel $(DEBUG) $(OPT_FLAG) $(SANIT_FLAGS) -c src/hash_table.cpp -o obj/hash_table.o

read.o: src/read.cpp
	@g++ -g -mavx2 -masm=intel $(DEBUG) $(OPT_FLAG) $(SANIT_FLAGS) -c src/read.cpp -o obj/read.o

hash_func.o: src/hash_func.cpp
	@g++ -g -mavx2 -masm=intel $(DEBUG) $(OPT_FLAG) $(SANIT_FLAGS) -c src/hash_func.cpp -o obj/hash_func.o

asm:
	@nasm -f elf64 src/inline_crc32.asm -o obj/inline_crc32.o

clean:
	rm obj/* hash2.exe