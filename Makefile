CC  = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
INC = $(wildcard *.h)

all : bataille_navale

%.o : %.c $(INC)
	$(CC) -c $< -o $@
   
bataille_navale : $(OBJ)
	$(CC) $^ -o $@
	
clean :
	rm -f *.o
	rm -f bataille_navale
