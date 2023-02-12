# options de compilation
CC = g++
CCFLAGS = -Wall
LIBS = 				
LIBSDIR = 

# fichiers du projet
SRC = main.cpp util.cpp lagrange.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = run.out


# règle initiale
all: $(EXEC)

# dépendance des .h
util.o: util.hpp lagrange.hpp
lagrange.o: lagrange.hpp
main.o: lagrange.hpp util.hpp

# règles de compilation
%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<
	
# règles d'édition de liens
$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LIBS) $(LIBSDIR)

# règles supplémentaires
clean:
	rm -f *.o
mproper:
	rm -f $(EXEC) *.o
