#include <iostream>
#include "Compiler.h"
#include <locale>
using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");
	Compiler compiler;
	if (compiler.compileFile("example.asm")) {
		cout << "The file have been compiled." << endl;
	} else {
		cout << "The file can't be compiled." << endl;
	}
	//if (argc >= 2) {
	//	if (compiler.compileFile(argv[1])) {
	//		cout << "Файл скомпилирован!\n";
	//	} else {
	//		cout << "Не удалось открыть файл!\n";
	//	}
	//} else {
	//	cout << "Недостаточно аргументов!\n";
	//}
	return 0;
}