#include "XmlParser.h"

#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <mutex>

namespace fs = boost::filesystem;
namespace cm_tool {

XmlParser::XmlParser() : is_loaded_(false) {}

bool XmlParser::Load(const std::string &path) {
  std::lock_guard<std::mutex> g_lock(mutex_);
  if (is_loaded_) {
    return false;
  }

  if (!path.empty()) {
    if (fs::exists(path)) {
      if (!fs::is_regular_file(path)) {
        std::cout << path << " exists, but is not a regular file" << std::endl;
        return false;
      }
    } else {
      std::cout << path << " does not exist" << std::endl;
      return false;
    }
  } else {
    std::cout << "path empty" << std::endl;
    return false;
  }

  try {
    pt::xml_parser::read_xml(path, tree_);
  } catch (pt::xml_parser_error &e) {
    std::cout << e.what() << std::endl;
    return false;
  }

  is_loaded_ = true;
  return is_loaded_;
}

const pt::ptree *XmlParser::GetTree() const {
  std::lock_guard<std::mutex> g_lock(mutex_);
  if (is_loaded_)
    return &tree_;
  else
    return nullptr;
}
}  // namespace cm_tool