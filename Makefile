#################################################################################
# 								Project Makefile                                #
# 						DAVAL Quentin - Benjamin HUBINET                        #
# 								ISMIN 1A - EI21                                 #
#################################################################################

main : main.o
	gcc main.o -o main
#################################################################################

main.o : main.c format.h
	gcc -c main.c -o main.o

#################################################################################