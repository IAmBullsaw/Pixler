CC = g++ 
CFLAGS = -std=c++11 -Wextra -Wall -Werror
NAME = Pixler
IMGTYPES = bmp.h

make: iparser pixel
	$(CC) $(CFLAGS) -o $(NAME) main.cpp *.o $(IMGTYPES)
iparser: 
	$(CC) $(CFLAGS) -c iparser.cpp iparser.h
pixel:
	$(CC) $(CFLAGS) -c ipixel.cpp ipixel.h
run: make
	./$(NAME)
rerun: clean make run

clean:
	rm $(NAME) *.o
