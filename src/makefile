all: build buildtest
cleanall: clean cleantest
build: obj/init.o obj/util.o obj/general.o obj/quicksort.o obj/csv.o
	@echo "* Building library..."
	ar -r build/lib/libeknnwindev.a obj/*.o
buildtest: build
	@echo "* Building test..."
	gcc -Wall -o build/test test/*.c -L"./build/lib/" -leknnwindev -lm -I"./lib/"
	ln -fs build/test launch
clean:
	@echo "* Cleaning library..."
	rm -f obj/*.o
	rm -f build/lib/libeknnwindev.a
cleantest:
	@echo "* Cleaning test..."
	rm -f build/test
	rm -f launch
obj/init.o: lib/init.c lib/eknnwindev.h
	gcc -Wall -c lib/init.c -o obj/init.o
obj/util.o: lib/util.c lib/eknnwindev.h
	gcc -Wall -c lib/util.c -o obj/util.o
obj/general.o: lib/general.c lib/eknnwindev.h
	gcc -Wall -c lib/general.c -o obj/general.o
obj/quicksort.o: lib/quicksort.c lib/eknnwindev.h
	gcc -Wall -c lib/quicksort.c -o obj/quicksort.o
obj/csv.o: lib/csv.c lib/eknnwindev.h
	gcc -Wall -c lib/csv.c -o obj/csv.o
