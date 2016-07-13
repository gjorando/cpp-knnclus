all: build buildtest
cleanall: clean cleantest
build: obj/kNNPoint.o obj/kNNSystem.o  obj/kNNUtils.o obj/kNNQuicksort.o
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
obj/kNNPoint.o: lib/kNNPoint.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNPoint.cpp -o obj/kNNPoint.o
obj/kNNSystem.o: lib/kNNSystem.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNSystem.cpp -o obj/kNNSystem.o
obj/kNNUtils.o: lib/kNNUtils.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNUtils.cpp -o obj/kNNUtils.o
obj/kNNQuicksort.o: lib/kNNQuicksort.cpp lib/knnclus.h
	g++ -Wall -c lib/kNNQuicksort.cpp -o obj/kNNQuicksort.o
install: build
	@echo "* Installing knnclus..."
	cp build/lib/libknnclus.a /usr/local/lib/
	chmod 777 /usr/local/lib/libknnclus.a
	cp lib/*.h /usr/local/include
