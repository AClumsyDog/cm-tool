#pragma once

#include "CodeGen.h"

namespace cm_tool {

class CommonGen : public CodeGen {
 public:
  CommonGen();

  virtual ~CommonGen() override;

  virtual bool Init(const pt::ptree *xml_tree) override;

  virtual std::vector<GeneratedCode> Generate() override;

 private:
  static std::string getModuleName(const pt::ptree *xml_tree);

  std::string src_str_;

  std::string module_name_;
};
}  // namespace cm_tool