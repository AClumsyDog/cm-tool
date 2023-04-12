#pragma once

#include "CommonGen.h"

namespace cm_tool {

class CommonVectorGen : public CommonGen {
 public:
  struct DataTypeVector {
    std::string base_type;
    std::string base_name;
  };

  CommonVectorGen();

  ~CommonVectorGen() override;

  void Init(const std::shared_ptr<BaseNode> &xml_root) override;

  virtual std::vector<GeneratedCode> Generate() override;
};
}  // namespace cm_tool