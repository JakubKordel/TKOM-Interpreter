#pragma once

#include <string>


class ObjValue {
public:
	std::string value;

	ObjValue();
	ObjValue(std::string v);
	bool operator==(const ObjValue & rhs) const;

};

