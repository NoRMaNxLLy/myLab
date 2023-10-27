hfcal.o: hfcal.c
	gcc -c hfcal.c -I./include

elliptical.o: elliptical.c
	gcc -c elliptical.c -I./include

./lib/libhfcal.a: hfcal.o
	mkdir ./lib
	ar -rcs ./lib/libhfcal.a hfcal.o

./lib/libhfcal.so:
	gcc -fPIE -c hfcal.c -o hfcal.o
	gcc -shared hfcal.o -o ./lib/libhfcal.so

elliptical: elliptical.o ./lib/libhfcal.so
	gcc elliptical.o -L./lib -lhfcal -o elliptical
