CC := gcc

CFLAGS := -std=c99 -Wall -Werror

OBJS := io.o list.o arr.o

app.exe : $(OBJS) main.o
	$(CC) $(CFLAGS) $^ -o main.exe
	
%.o : %.c %.h
	$(CC) $(CFLAGS) -c $<
	
clean :
	$(RM) *.o *.exe