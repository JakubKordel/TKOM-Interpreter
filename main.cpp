#include "src/Scanner/Scanner.h"
#include "src/Parser/Parser.h"

#include <fstream>

#include "src/Interpreter/Interpreter.h"

#include <vector>


int main(int argc, char *argv[]) {

	std::vector<Language*> files;
	if (argc == 1) {
		throw std::invalid_argument("You must specify files for interpreter");
	}
	Interpreter interpreter;
	for (int i = 1; i < argc; ++i) {
		std::ifstream in(argv[i]);
		auto s = std::make_unique<Scanner>(in);
		Parser parser(std::move(s));
		parser.advance();
		Language * lang = parser.parseLanguage();
		files.push_back(lang);
		interpreter.load(lang);
	}

	interpreter.run();

	for (auto f : files) {
		delete f;
	}
	return 0;
}