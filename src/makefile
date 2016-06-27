all: buildtest
cleanall: clean cleantest
build:
	@echo "* Building library..."
	ar -r build/libeknnwindev.a obj/*.o
buildtest: build
	@echo "* Building test..."
	gcc -Wall -o build/test test/*.c -L"./build/" -leknnwindev
clean:
	@echo "* Cleaning library..."
	rm -f obj/*.o
	rm -f build/libeknnwindev.a
cleantest:
	@echo "* Cleaning test..."
	rm -f build/test
