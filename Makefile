ep1_matriz_13672860.exe: grafo_matrizadj.o ep1.o 
	gcc -o ep1_matriz_13672860.exe grafo_matrizadj.o ep1.o 

ep1_lista_13672860.exe: grafo_listaadj.o ep1.o
	gcc -o ep1_lista_13672860.exe grafo_listaadj.o ep1.o 

grafo_matrizadj.o: grafo_matrizadj.c grafo_matrizadj.h
	gcc -c grafo_matrizadj.c

grafo_listaadj.o: grafo_listaadj.c grafo_listaadj.h
	gcc -c grafo_listaadj.c

ep1.o: ep1.c
	gcc -c ep1.c

clean:
	rm -f *.o *.exe