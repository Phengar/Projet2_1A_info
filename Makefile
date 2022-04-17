#################################################################################
# 								Project Makefile                                #
# 						DAVAL Quentin - Benjamin HUBINET                        #
# 								ISMIN 1A - EI21                                 #
#################################################################################

#################################################################################

#################################################################################

main : ./obj/main.o ./obj/stat.o ./obj/format.o ./obj/reader_matAdj.o ./obj/sort.o
	gcc ./obj/main.o ./obj/stat.o ./obj/format.o ./obj/reader_matAdj.o ./obj/sort.o -o main

clean :
	rm ./obj/*.o && rm main
	
#################################################################################

./obj/main.o : main.c format.h reader_matAdj.h stat.h
	gcc -c main.c -o ./obj/main.o

./obj/stat.o : stat.c stat.h format.h sort.h
	gcc -c stat.c -o ./obj/stat.o

./obj/reader_matAdj.o : reader_matAdj.c reader_matAdj.h
	gcc -c reader_matAdj.c -o ./obj/reader_matAdj.o

./obj/format.o : format.c format.h
		gcc -c format.c -o ./obj/format.o

./obj/sort.o : sort.c sort.h
	gcc -c sort.c -o ./obj/sort.o

#################################################################################