CC := gcc

CFLAGS := -std=c99 -Wall -Werror

OBJS := arr.o list.o

app.exe : $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o app.exe

%.o : %.c *.h
	$(CC) $(CFLAGS) -c $<

clean :
	$(RM) *.o *.exe
