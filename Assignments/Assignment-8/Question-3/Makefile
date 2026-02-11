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

help:
	@echo "Usage"
	@echo " make 	    -> Build the application"
	@echo " make run 	-> Run the application"
	@echo " make clean	-> Remove the project binaries"
	@echo " make help 	-> Show the help message"
