CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -Wpedantic -pedantic-errors
OBJS = main.o graph.o

.PHONY : all clean distclean

all : run

run : $(OBJS)
	$(CXX) -o run $(OBJS)

main.o : main.cpp graph.h

graph.o : graph.cpp graph.h

clean :
	$(RM) $(OBJS)

distclean : clean
	$(RM) run
