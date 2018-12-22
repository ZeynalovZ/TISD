CC := gcc

CFLAGS := -std=c99 -Wall -Werror

OBJS := io.o search.o

ifeq ($(mode), debug)
    CFLAGS += -g3
endif

app.exe : $(OBJS) main.o
	$(CC) $^ -o app.exe

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o *.exe
