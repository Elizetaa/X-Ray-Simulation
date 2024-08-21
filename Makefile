CC = gcc
CFLAGS = -W -Wall -ansi -pedantic -std=c99

SRCS = main.c Exames.c Pacientes.c queue.c

OBJS = $(SRCS:.c=.o)

TARGET = trabalhoed

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
