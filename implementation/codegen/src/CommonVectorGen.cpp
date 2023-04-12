#include "CommonVectorGen.h"

namespace cm_tool {

CommonVectorGen::CommonVectorGen() {}

CommonVectorGen::~CommonVectorGen() {}

void CommonVectorGen::Init(const std::shared_ptr<BaseNode> &xml_root) {}

std::vector<CodeGen::GeneratedCode> CommonVectorGen::Generate() {
  return std::vector<GeneratedCode>();
}
}  // namespace cm_tool