#include "ObjValue.h"

ObjValue::ObjValue(){
	value = "empty";
}

ObjValue::ObjValue(std::string v){
	value = v;
}

bool ObjValue::operator==(const ObjValue & rhs) const{
	return value == rhs.value ;
}
