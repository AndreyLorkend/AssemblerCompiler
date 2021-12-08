#include <iostream>
#include "Compiler.h"
using namespace std;

int main(int argc, char* argv[]) {
	Compiler compiler;
	if (argc >= 2) {
		compiler.compileFile(argv[1]);
	}
	return 0;
}