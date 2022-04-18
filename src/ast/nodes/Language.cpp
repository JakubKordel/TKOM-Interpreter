#include "Language.h"


Language::~Language() {
	for (auto it = definitions.begin(); it != definitions.end(); ++it) {
		std::visit([](auto a) { delete a; }, *it);
	}
}