#################################################################################
# 								Project Makefile                                #
# 						DAVAL Quentin - Benjamin HUBINET                        #
# 								ISMIN 1A - EI21                                 #
#################################################################################



#################################################################################

main : main.o stat.o reader_listAdj.o format.o
	gcc ./obj/main.o ./obj/stat.o ./obj/reader_listAdj.o ./obj/format.o -o ./src/main

clean :
	rm ./obj/*.o && rm -f ./src/*
	
#################################################################################

main.o : main.c format.h reader_listAdj.h stat.h
	gcc -c main.c -o ./obj/main.o

stat.o : stat.c
	gcc -c stat.c -o ./obj/stat.o

reader_listAdj.o : reader_listAdj.c
	gcc -c reader_listAdj.c -o ./obj/reader_listAdj.o

format.o : format.c
		gcc -c format.c -o ./obj/format.o

#################################################################################