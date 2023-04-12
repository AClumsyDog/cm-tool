#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace cm_tool {

class BaseNode;

class CodeGen {
 public:
  struct GeneratedCode {
    std::string name;
    std::string content;
  };

  CodeGen();

  virtual ~CodeGen();

  virtual void Init(const std::shared_ptr<BaseNode> &xml_root);

  std::vector<GeneratedCode> Generate();

 protected:
  virtual std::string generate();

  std::unordered_map<std::string, std::unique_ptr<CodeGen>> code_gens_;
};
}  // namespace cm_tool