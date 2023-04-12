#include "CommonGen.h"

#include "CommonVectorGen.h"

namespace cm_tool {

CommonGen::CommonGen() {
  code_gens_["common_vector"] = std::make_unique<CommonVectorGen>();
}

CommonGen::~CommonGen() {}

void CommonGen::Init(const std::shared_ptr<BaseNode> &xml_root) {
  code_gens_["common_vector"]->Init(xml_root);
}

std::vector<CodeGen::GeneratedCode> CommonGen::Generate() {
  return std::vector<GeneratedCode>();
}
}  // namespace cm_tool