#pragma once
#include <optional>
#include <string>
#include <vector>

enum BUILTIN_TYPE {

  VOID,
  INT8,
  UINT8,
  INT32,
  UINT32,
  DOUBLE,
  STRUCT

};

class Type {

public:
  Type(const std::string &name = "", BUILTIN_TYPE type = VOID)
      : typeName(name), tType(type){};
  std::string typeName;
  BUILTIN_TYPE tType;
  // if struct
  std::vector<Type> tField;
};
