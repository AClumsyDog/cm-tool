#pragma once

#include "CommonGen.h"

namespace cm_tool {

class DataTypeGen : public CommonGen {
 public:
  DataTypeGen();

  ~DataTypeGen() override;

  virtual bool Init(const pt::ptree *xml_tree) override;

  virtual std::vector<GeneratedCode> Generate() override;

 private:
  static std::unordered_map<std::string, std::string> getVector(
      const pt::ptree *xml_tree);

  std::string vector_str_;
  std::unordered_map<std::string, std::string> vec_maps_;
};
}  // namespace cm_tool