all: build buildtest
cleanall: clean cleantest
build: obj/kNNclus_Point.o obj/kNNclus_System.o  obj/kNNclus_Utils.o obj/kNNclus_Quicksort.o
	@echo "* Building library..."
	ar -r build/lib/libknnclus.a obj/*.o
buildtest: build
	@echo "* Building test..."
	g++ -Wall -o build/test test/*.cpp -L"./build/lib/" -lknnclus -lm -I"./lib/"
	ln -fs build/test launch
clean:
	@echo "* Cleaning library..."
	rm -f obj/*.o
	rm -f build/lib/libknnclus.a
cleantest:
	@echo "* Cleaning test..."
	rm -f build/test
	rm -f launch
obj/kNNclus_Point.o: lib/kNNclus_Point.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNclus_Point.cpp -o obj/kNNclus_Point.o
obj/kNNclus_System.o: lib/kNNclus_System.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNclus_System.cpp -o obj/kNNclus_System.o
obj/kNNclus_Utils.o: lib/kNNclus_Utils.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNclus_Utils.cpp -o obj/kNNclus_Utils.o
obj/kNNclus_Quicksort.o: lib/kNNclus_Quicksort.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNclus_Quicksort.cpp -o obj/kNNclus_Quicksort.o
install: build
	@echo "* Installing knnclus..."
	cp build/lib/libknnclus.a /usr/local/lib/
	chmod 777 /usr/local/lib/libknnclus.a
	cp lib/*.h /usr/local/include
uninstall:
	@echo "* Cleaning knnclus install..."
	rm -f /usr/local/lib/libknnclus.a
	rm -f /usr/local/include/knnclus.h
