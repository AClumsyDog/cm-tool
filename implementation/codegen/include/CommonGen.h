#pragma once

#include "CodeGen.h"

namespace cm_tool {

class CommonGen : public CodeGen {
 public:
  CommonGen();

  virtual ~CommonGen() override;

  void Init(const std::shared_ptr<BaseNode> &xml_root) override;

 protected:
  std::string generate() override;
};
}  // namespace cm_tool