#################################################################################
# 								Project Makefile                                #
# 						DAVAL Quentin - Benjamin HUBINET                        #
# 								ISMIN 1A - EI21                                 #
#################################################################################



#################################################################################

main : main.o stat.o reader_listAdj.o format.o
	gcc main.o stat.o reader_listAdj.o format.o -o main.exe

clean :
	rm *.o && rm main.exe 
	
#################################################################################

main.o : main.c format.h reader_listAdj.h stat.h
	gcc -c main.c -o main.o

stat.o : stat.c
	gcc -c stat.c -o stat.o

reader_listAdj.o : reader_listAdj.c
	gcc -c reader_listAdj.c -o reader_listAdj.o

format.o : format.c
		gcc -c format.c -o format.o

#################################################################################