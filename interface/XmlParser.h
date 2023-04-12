#pragma once

#include <map>
#include <memory>
#include <string>

namespace tinyxml2 {

class XMLElement;
class XMLDocument;
}  // namespace tinyxml2

namespace cm_tool {

class BaseNode;
template <typename T>
class DataNode;

enum class XMLP_ret { XML_ERROR, XML_OK, XML_NOK };

class XMLParser {
 public:
  static XMLP_ret LoadXML(const std::string &filename,
                          std::unique_ptr<BaseNode> &root);

 protected:
  static XMLP_ret ParseXML(tinyxml2::XMLDocument &xml_doc,
                           std::unique_ptr<BaseNode> &root);

  static XMLP_ret ParseDataTypes(tinyxml2::XMLElement *xml_root,
                                 std::unique_ptr<BaseNode> &root);

  static XMLP_ret ParseImplementationDataTypes(tinyxml2::XMLElement *xml_root,
                                               std::unique_ptr<BaseNode> &root);

  static XMLP_ret ParseDataTypeVector(tinyxml2::XMLElement *xml_root,
                                      std::unique_ptr<BaseNode> &root);
};
}  // namespace cm_tool