all: 1 2 3
.PHONY:all
CFLAGS = -lrt
OBJS1 = 1.o
OBJS2 = 2.o
OBJS3 = 3.o

1:1.o
	gcc -O2 -o 1 1.c -lrt

2:2.o
	gcc -O2 -o 2 2.c -lrt

3:3.o
	gcc -O2 -o 3 3.c -lrt

$(OBJS1):1.c

$(OBJS2):2.c

$(OBJS3):3.c
