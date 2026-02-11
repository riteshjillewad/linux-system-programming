CC = gcc
TARGET = app
SRC = main.c
CFLAGS = -Wall -Wextra -O2

all: $(TARGET)

$(TARGET): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -f $(TARGET)

