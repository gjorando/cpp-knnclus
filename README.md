# C++ kNNclus module

### A clustering procedure using the kNN algorithm for general purposes

This module is an implementation of a clustering procedure based on the K-nearest neighbor rule. It is very similar to the EkNNclus algorithm, as described in "EK-NNclus: a clustering procedure based on the evidential K-nearest neighbor rule" by Thierry Denoeux, Orakanya Kanjanatarakul, and Songsak Sriboonchitta.

### Installation

First, you need to clone the git repository and `cd` into it.

	$ git clone https://gitlab.com/ltiut/cpp-knnclus-module
	$ cd cpp-knnclus-module

Then, you need to compile and install the library.

#### \*Nix systems (GNU/Linux, macOS...)

Just use the makefile.

	$ cd src
	$ make
	$ sudo make install

The static library is installed in `/usr/local/`.

#### Windows

You can use Code::Blocks to create the static library. Create a new project choosing "Static Library". Make sure your project remains empty by checking "Do not create any file". Add to your project the source and header files in `src/lib/`. Now, just build the project. To use the library, make sure you link the `libyourlibrary.a` when you compile a source code that uses it, as well as `knnclus.h`.

### Usage

Use the documentation for details on basic and advanced usage of the module. To compile it you will need doxygen.

	$ cd src
	$ doxygen doxyconf

Then just open `src/doc/html/index.html` in your favorite browser.

You can also check the small example provided in the repository.

	$ cd src/test
	$ vim main.cpp

And to test it :

	$ cd src
	$ make buildtest
	$ ./launch
