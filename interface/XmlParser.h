#pragma once

#include <boost/property_tree/ptree.hpp>
#include <functional>
#include <mutex>
#include <string>

namespace pt = boost::property_tree;
namespace cm_tool {

class XmlParser {
 public:
  XmlParser();

  bool Load(const std::string &path);

  const pt::ptree *GetTree() const;

 private:
  bool is_loaded_;
  mutable std::mutex mutex_;
  pt::ptree tree_;
};
}  // namespace cm_tool