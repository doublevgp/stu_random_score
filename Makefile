CC = gcc

LFLAGS = -lm

SRC = main.c
SRC += stu_score.c

OBJ = $(patsubst %.c,%.o,$(SRC))




all:
	$(CC) -o stu_random_score $(SRC) $(LFLAGS)


clean:
	-rm -rf $(OBJ) stu_random_score
