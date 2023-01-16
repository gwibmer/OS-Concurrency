OBJS	= ReaderWriter.o
SOURCE	= ReaderWriter.c
HEADER	= thread.h
OUT	= rwmain
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

ReaderWriter.o: ReaderWriter.c
	$(CC) $(FLAGS) ReaderWriter.c 


clean:
	rm -f $(OBJS) $(OUT)