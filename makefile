#Makefile contains 3 targets

CC=gcc

mytree: mytree.c
	$(CC) -o mytree mytree.c

mytime: mytime.c
	$(CC) -o mytime mytime.c

mymtimes: mymtimes.c
	$(CC) -o mymtimes mymtimes.c -lm
