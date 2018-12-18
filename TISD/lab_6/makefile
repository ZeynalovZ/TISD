CC := gcc
CFLAGS := -std=c99 -Wall -Werror -ggdb

ifeq ($(mode), debug)
    CFLAGS += -g3
endif

main.o: main.c *.h
	$(CC) $(CFLAGS) -c $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

app.exe: main.o io.o bst.o avl.o bst_to_avl.o search.o hash_table.o
	$(CC) $^ -o $@

clean:
	rm *.o *.exe