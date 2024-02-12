TARGET = zshhy
SRC_DIRS := ./src
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address --pedantic-errors

# Find all C files to compile
SRCS := $(wildcard $(SRC_DIRS)/*.c)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(TARGET)

re: fclean all