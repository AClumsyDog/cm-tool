#include "CodeGen.h"

#include "CommonGen.h"

namespace cm_tool {

CodeGen::CodeGen() { code_gens_["common"] = std::make_unique<CommonGen>(); }

CodeGen::~CodeGen() {}

void CodeGen::Init(const std::shared_ptr<BaseNode> &xml_root) {
  code_gens_["common"]->Init(xml_root);
}

std::vector<CodeGen::GeneratedCode> CodeGen::Generate() {
  GeneratedCode common_code;
  common_code.name = "Common";
  common_code.content = code_gens_["common"]->generate();

  std::vector<GeneratedCode> codes;
  codes.push_back(std::move(common_code));

  return codes;
}

std::string CodeGen::generate() { return std::string(); }
}  // namespace cm_tool