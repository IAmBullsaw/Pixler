CC = g++ 
CFLAGS = -std=c++11 -Wextra -Wall -Werror
MAIN = Pixler
IMGTYPES = bmp.h
RM = rm -v
SOURCES = iparser.cpp ipixel.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(MAIN)
	@echo Made all:  ./$(MAIN) to run
$(MAIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(MAIN) main.cpp $(OBJECTS) $(IMGTYPES)
# Converting .cpp into .o, GNU magic.
.cpp.o:
	$(CC) $(CFLAGS) -c $<  -o $@
run: all
	@echo Running...
	./$(MAIN)
clean:
	@echo Cleaning...
	$(RM) $(NAME) *.o
