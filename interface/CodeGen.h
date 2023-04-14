#pragma once

#include <boost/property_tree/ptree.hpp>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace pt = boost::property_tree;
namespace cm_tool {

class CodeGen {
 public:
  struct GeneratedCode {
    std::string name;
    std::string content;
  };

  CodeGen();

  virtual ~CodeGen();

  virtual bool Init(const pt::ptree *xml_tree);

  virtual std::vector<GeneratedCode> Generate();

 protected:
  static void LoadTpl(const std::string &path, std::string &dst);

  static void StringReplace(std::string &src_str, const std::string &src,
                            const std::string &rep);

 protected:
  bool is_init_;
  std::mutex mutex_;
  std::unordered_map<std::string, std::unique_ptr<CodeGen>> code_gens_;
};
}  // namespace cm_tool