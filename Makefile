#################################################################################
# 								Project Makefile                                #
# 						DAVAL Quentin - Benjamin HUBINET                        #
# 								ISMIN 1A - EI21                                 #
#################################################################################

#################################################################################

#################################################################################

main : main.o stat.o format.o reader_matAdj.o sort.o
	gcc main.o stat.o format.o reader_matAdj.o sort.o -o main

clean :
	rm *.o && rm main
	
#################################################################################

main.o : main.c format.h reader_matAdj.h stat.h
	gcc -c main.c

stat.o : stat.c stat.h format.h sort.h
	gcc -c stat.c

reader_matAdj.o : reader_matAdj.c reader_matAdj.h
	gcc -c reader_matAdj.c

format.o : format.c format.h
		gcc -c format.c

sort.o : sort.c sort.h
	gcc -c sort.c

#################################################################################