CC = gcc
CFLAGS = -Wall -Wextra -pedantic
INCLUDES = -Iinclude
OBJ = $(patsubst %.c, %.o, $(wildcard *.c))
LIBS =

TARGET = serialConnect

all:	$(TARGET)

$(TARGET):	$(OBJ)
	$(CC) -o $@ $(OBJ) $(LIBS)

%.o:	%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c  $^ -o $@

clean:
	rm -f $(TARGET) $(OBJ)
