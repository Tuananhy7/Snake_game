CC = gcc
CFLAGS = -pthread
OBJECTS = main.o func.o snake.o
run_one: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o run_one 

main.o: main.c main.h
	$(CC) -c main.c
func.o: func.c main.h
	$(CC) -c func.c
snake.o: snake.c main.h
	$(CC) -c snake.c

clean:
	$(RM) run_one *.o
	echo clear clear
