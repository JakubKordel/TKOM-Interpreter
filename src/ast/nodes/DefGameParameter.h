#pragma once 

#include "../AstNode.h"

class DefGameParameter : public AstNode {

public:

	enum class ValueType {
		Pair,
		Integer,
		Word
	};

	ValueType valueType;
	std::string parameterName;

	std::pair<int, int> pairValue;
	int intValue;
	std::string wordValue;

	void setParameterName(std::string name) {
		parameterName = name;
	}

	void setValueType(ValueType type) {
		valueType = type;
	}

	void setPairValue(std::pair<int, int> pair) {
		pairValue = pair;
	}

	void setIntValue(int intVal) {
		intValue = intVal;
	}

	void setWordValue(std::string word) {
		wordValue = word;
	}

	ValueType getValueType() {
		return valueType;
	}

	virtual Type getType() {
		return AstNode::Type::DefGameParameter;
	}
};