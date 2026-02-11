all: app

app: main.o helper.o
	gcc main.o helper.o -o app

main.o: main.c helper.h
	gcc -c main.c

helper.o: helper.c helper.h
	gcc -c helper.c

run: app
	./app

clean:
	rm -f app *.o

help:
	@echo "Usage:"
	@echo "make: Build the application"
	@echo "make run: Run the application "
	@echo "make clean: Remove binaries and object files"
	@echo "make help: Show the help message"