CC := gcc

CFAGS := -std=c99 -Wall -Werror

OBJS := io.o operations.o

app.exe : $(OBJS) main.o
	$(CC) $^ -o $@

%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe
