TARGET = htop.exe
CC = gcc
MAIN = ./htop.c
SRCS = $(MAIN) ./get_pids.h ./get_pids.c ./get_pid_name.h ./get_pid_name.c ./get_process.h ./get_process.c ./split.c ./split.h
OBJS = $(SRCS:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror -lncurses
VAL = valgrind --leak-check=full --tool=memcheck --log-file=./.log --vgdb=yes
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

run: all
	$(VAL) ./$(TARGET)

clean:
	rm $(OBJS)

fclean: clean
	rm -f $(TARGET)