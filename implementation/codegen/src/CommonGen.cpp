#include "CommonGen.h"

#include <algorithm>
#include <cctype>

#include "DataTypeGen.h"

static const std::string COMMON_H_PATH = "../etc/common_h.tpl";

namespace cm_tool {

CommonGen::CommonGen() { LoadTpl(COMMON_H_PATH, src_str_); }

CommonGen::~CommonGen() {}

bool CommonGen::Init(const pt::ptree *xml_tree) {
  code_gens_["data_type"] = std::make_unique<DataTypeGen>();
  if (!code_gens_["data_type"]->Init(xml_tree)) {
    return false;
  }

  module_name_ = getModuleName(xml_tree);

  return true;
}

std::vector<CodeGen::GeneratedCode> CommonGen::Generate() {
  GeneratedCode generated_code;
  generated_code.name = module_name_ + "Common.h";
  generated_code.content = src_str_;

  auto data_type_codes = code_gens_["data_type"]->Generate();
  for (const auto &code : data_type_codes) {
    if (code.name == "definecontent") {
      StringReplace(generated_code.content, "$(DEFINECONTENTS)", code.content);
    }
  }

  StringReplace(generated_code.content, "$(MODULENAME)", module_name_);

  std::string up_module_name = module_name_;
  std::transform(up_module_name.cbegin(), up_module_name.cend(),
                 up_module_name.begin(),
                 [](unsigned char c) { return std::toupper(c); });
  StringReplace(generated_code.content, "$(UPMODULENAME)", up_module_name);

  std::vector<GeneratedCode> generated_codes;
  generated_codes.push_back(std::move(generated_code));

  return generated_codes;
}

std::string CommonGen::getModuleName(const pt::ptree *xml_tree) {
  std::string module_name;
  const auto &packages = xml_tree->get_child("AUTOSAR.AR-PACKAGES");

  pt::ptree service_interfaces;
  for (const auto &v : packages) {
    auto short_name = v.second.get<std::string>("SHORT-NAME");
    if (short_name == "ServiceInterfaces") {
      service_interfaces = v.second.get_child("ELEMENTS");
    }
  }

  for (const auto &v : service_interfaces) {
    module_name = v.second.get<std::string>("SHORT-NAME");
    break;
  }

  return module_name;
}
}  // namespace cm_tool