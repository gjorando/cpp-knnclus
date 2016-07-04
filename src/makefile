all: build buildtest
cleanall: clean cleantest
build: obj/EkNNPoint.o obj/EkNNSystem.o  obj/EkNNUtils.o obj/EkNNQuicksort.o
	@echo "* Building library..."
	ar -r build/lib/libeknnclus.a obj/*.o
buildtest: build
	@echo "* Building test..."
	g++ -Wall -o build/test test/*.cpp -L"./build/lib/" -leknnclus -lm -I"./lib/"
	ln -fs build/test launch
clean:
	@echo "* Cleaning library..."
	rm -f obj/*.o
	rm -f build/lib/libeknnclus.a
cleantest:
	@echo "* Cleaning test..."
	rm -f build/test
	rm -f launch
obj/EkNNPoint.o: lib/EkNNPoint.cpp lib/eknnclus.h
	g++ -Wall -c lib/EkNNPoint.cpp -o obj/EkNNPoint.o
obj/EkNNSystem.o: lib/EkNNSystem.cpp lib/eknnclus.h
	g++ -Wall -c lib/EkNNSystem.cpp -o obj/EkNNSystem.o
obj/EkNNUtils.o: lib/EkNNUtils.cpp lib/eknnclus.h
	g++ -Wall -c lib/EkNNUtils.cpp -o obj/EkNNUtils.o
obj/EkNNQuicksort.o: lib/EkNNQuicksort.cpp lib/eknnclus.h
	g++ -Wall -c lib/EkNNQuicksort.cpp -o obj/EkNNQuicksort.o
