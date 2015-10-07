#-------------------------------------------------------
FLAGS = -std=c++11 -w
CC = g++
CC2 = antlr27
CC3 = dlg
#-------------------------------------------------------

all: antlr dlg karel

antlr: karel.g
	$(CC2) -gt karel.g
dlg: 
	$(CC3) -ci parser.dlg scan.c
karel: karel.c scan.c err.c
	$(CC) -o karel karel.c scan.c err.c $(FLAGS)

1: antlr1 dlg karel

antlr1: karel.g
	antlr -gt karel.g

