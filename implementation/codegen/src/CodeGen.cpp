#include "CodeGen.h"

#include "CommonGen.h"

namespace cm_tool {

CodeGen::CodeGen() : is_init_(false) {}

CodeGen::~CodeGen() {}

bool CodeGen::Init(const pt::ptree *xml_tree) {
  std::lock_guard<std::mutex> g_lock(mutex_);

  code_gens_["common"] = std::make_unique<CommonGen>();
  if (!code_gens_["common"]->Init(xml_tree)) {
    return false;
  }

  is_init_ = true;
  return is_init_;
}

std::vector<CodeGen::GeneratedCode> CodeGen::Generate() {
  std::lock_guard<std::mutex> g_lock(mutex_);
  if (!is_init_) {
    throw std::runtime_error("codegen uninitialized");
  }

  auto common_code = code_gens_["common"]->Generate()[0];

  std::vector<GeneratedCode> codes;
  codes.push_back(std::move(common_code));

  return codes;
}

void CodeGen::StringReplace(std::string &src_str, const std::string &src,
                            const std::string &rep) {
  auto index = src_str.find(src);
  while (index != std::string::npos) {
    src_str.replace(index, src.size(), rep);
    index = src_str.find(src, index + src.size());
  }
}
}  // namespace cm_tool