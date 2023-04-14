#include "CommonGen.h"

#include <algorithm>
#include <boost/filesystem.hpp>
#include <cctype>
#include <fstream>

static const std::string COMMON_H_PATH = "../etc/common_h.tpl";

namespace fs = boost::filesystem;
namespace cm_tool {

CommonGen::CommonGen() {
  if (!fs::exists(COMMON_H_PATH)) {
    throw std::runtime_error(COMMON_H_PATH + " does not exist");
  }

  auto file_size = fs::file_size(COMMON_H_PATH);
  src_str_.resize(file_size);

  std::ifstream i_file(COMMON_H_PATH);
  i_file.read(const_cast<char *>(src_str_.data()), file_size);
  i_file.close();
}

CommonGen::~CommonGen() {}

bool CommonGen::Init(const pt::ptree *xml_root) {
  module_name_ = getModuleName(xml_root);

  auto code = src_str_;

  return true;
}

std::vector<CodeGen::GeneratedCode> CommonGen::Generate() {
  GeneratedCode generated_code;
  generated_code.name = module_name_ + "Common.h";
  generated_code.content = src_str_;

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