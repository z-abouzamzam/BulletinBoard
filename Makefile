
#makefile
COMPILE=g++
FLAGS=-W -Wall -Werror -ansi -pedantic
all: BBoard.o Message.o User.o Reply.o Topic.o main.cpp
	$(COMPILE) $(FLAGS) main.cpp Message.o BBoard.o User.o Topic.o Reply.o -o main.out
BBoard.o: Message.o Reply.o Topic.o User.o BBoard.cpp BBoard.h
	$(COMPILE) $(FLAGS) -c BBoard.cpp
Message.o: Message.cpp Message.h
	$(COMPILE) $(FLAGS) -c Message.cpp
User.o: User.cpp User.h
	$(COMPILE) $(FLAGS) -c User.cpp
Topic.o: Topic.h Topic.cpp Message.o
	$(COMPILE) $(FLAGS) -c Topic.cpp
Reply.o: Reply.h Reply.cpp Message.o
	$(COMPILE) $(FLAGS) -c Reply.cpp
clean:
	rm *.o *.out