#################################################################################
# 								Project Makefile                                #
# 						DAVAL Quentin - Benjamin HUBINET                        #
# 								ISMIN 1A - EI21                                 #
#################################################################################

#################################################################################

#################################################################################

main : main.o stat.o format.o reader_listAdj.o
	gcc main.o stat.o format.o reader_listAdj.o -o main

clean :
	rm *.o && rm main
	
#################################################################################

main.o : main.c format.h reader_listAdj.h stat.h
	gcc -c main.c -o main.o

stat.o : stat.c
	gcc -c stat.c -o stat.o

reader_listAdj.o : reader_listAdj.c
	gcc -W -c reader_listAdj.c -o reader_listAdj.o

format.o : format.c
		gcc -c format.c -o format.o

#################################################################################