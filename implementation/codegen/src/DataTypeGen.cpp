#include "DataTypeGen.h"

static const std::string VECTOR_PATH = "../etc/common_h_vector.tpl";

namespace cm_tool {

DataTypeGen::DataTypeGen() { LoadTpl(VECTOR_PATH, vector_str_); }

DataTypeGen::~DataTypeGen() {}

bool DataTypeGen::Init(const pt::ptree *xml_tree) {
  const auto &packages = xml_tree->get_child("AUTOSAR.AR-PACKAGES");

  pt::ptree data_types;
  for (const auto &v : packages) {
    auto short_name = v.second.get<std::string>("SHORT-NAME");
    if (short_name == "DataTypes") {
      data_types = v.second.get_child("AR-PACKAGES");
    }
  }

  pt::ptree implementation_data_types;
  for (const auto &v : data_types) {
    auto short_name = v.second.get<std::string>("SHORT-NAME");
    if (short_name == "ImplementationDataTypes") {
      implementation_data_types = v.second.get_child("ELEMENTS");
    }
  }

  vec_maps_ = getVector(&implementation_data_types);

  return true;
}

std::vector<CodeGen::GeneratedCode> DataTypeGen::Generate() {
  GeneratedCode generated_code;
  generated_code.name = "definecontent";
  for (const auto &vec : vec_maps_) {
    generated_code.content += vector_str_ + "\n";
    if (vec.second == "string") {
      StringReplace(generated_code.content, "$(BaseType)",
                    "std::" + vec.second);
    } else {
      StringReplace(generated_code.content, "$(BaseType)", vec.second);
    }
    StringReplace(generated_code.content, "$(BaseName)", vec.first);
  }

  std::vector<GeneratedCode> generated_codes;
  generated_codes.push_back(std::move(generated_code));
  return generated_codes;
}

std::unordered_map<std::string, std::string> DataTypeGen::getVector(
    const pt::ptree *xml_tree) {
  auto getTypeRef = [](const pt::ptree *xml_tree) {
    std::string ret =
        xml_tree
            ->get_child(
                "SUB-ELEMENTS.IMPLEMENTATION-DATA-TYPE-ELEMENT.SW-DATA-DEF-"
                "PROPS.SW-"
                "DATA-DEF-PROPS-VARIANTS.SW-DATA-DEF-PROPS-CONDITIONAL")
            .front()
            .second.get_value<std::string>();

    auto index = ret.find_last_of("/");
    ret = ret.substr(index + 1);
    return ret;
  };

  std::string base_type;
  std::string base_name;
  std::unordered_map<std::string, std::string> ret;
  for (const auto &v : *xml_tree) {
    base_name = v.second.get<std::string>("SHORT-NAME");
    auto type_name = v.second.get<std::string>("CATEGORY");
    if (type_name == "VECTOR") {
      base_type = getTypeRef(&v.second);
      ret[base_name] = std::move(base_type);
    }
  }

  return ret;
}
}  // namespace cm_tool