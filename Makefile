SANIT_FLAGS = -fsanitize=address,alignment,undefined
DUMP_FLAG = -D HASH_DUMP

all: hash

hash: main.o list.o hash_table.o read.o hash_func.o
	@g++ -g  $(SANIT_FLAGS) $(DUMP_FLAG) -o hash.exe obj/main.o List_Index/list.o obj/hash_table.o obj/read.o obj/hash_func.o

main.o: src/main.cpp
	@g++ -g  $(SANIT_FLAGS) $(DUMP_FLAG) -c src/main.cpp -o obj/main.o

list.o: List_Index/list.cpp
	@g++ -g  $(SANIT_FLAGS) -c List_Index/list.cpp -o List_Index/list.o

hash_table.o: src/hash_table.cpp
	@g++ -g  $(SANIT_FLAGS) -c src/hash_table.cpp -o obj/hash_table.o

read.o: src/read.cpp
	@g++ -g  $(SANIT_FLAGS) -c src/read.cpp -o obj/read.o

hash_func.o: src/hash_func.cpp
	@g++ -g  $(SANIT_FLAGS) -c src/hash_func.cpp -o obj/hash_func.o

clean:
	rm obj/* hash.exe