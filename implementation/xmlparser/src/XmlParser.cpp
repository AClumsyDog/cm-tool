#include "XmlParser.h"

#include <cstdlib>
#include <iostream>
#include <unordered_map>

#include "XMLTree.h"
#include "XmlParserCommon.hpp"
#include "tinyxml2.h"

namespace cm_tool {

XMLP_ret XMLParser::ParseXML(tinyxml2::XMLDocument &xml_doc,
                             std::unique_ptr<BaseNode> &root) {
  XMLP_ret ret = XMLP_ret::XML_OK;
  tinyxml2::XMLElement *p_root = xml_doc.FirstChildElement(ROOT);
  if (nullptr == p_root) {
    std::cout << "Not found root tag" << std::endl;
    ret = XMLP_ret::XML_ERROR;
  } else {
    root.reset(new BaseNode{NodeType::ROOT});
    tinyxml2::XMLElement *node = p_root->FirstChildElement();
    const char *tag = nullptr;
    while ((nullptr != node) && (ret == XMLP_ret::XML_OK)) {
      if (nullptr != (tag = node->Value())) {
        if (strcmp(tag, AR_PACKAGE) == 0) {
          tag = node->FirstChildElement()->GetText();
          if (strcmp(tag, DATA_TYPES) == 0) {
            auto data_types_node =
                std::make_unique<BaseNode>(NodeType::DATA_TYPES);
            if (XMLP_ret::XML_OK ==
                (ret = ParseDataTypes(
                     node->FirstChildElement()->NextSiblingElement(),
                     data_types_node))) {
              root->AddChild(std::move(data_types_node));
            }
          }
        } else if (strcmp(tag, AR_PACKAGES) == 0) {
          node = node->FirstChildElement();
          continue;
        }
      }

      node = node->NextSiblingElement();
    }
  }

  return ret;
}

XMLP_ret XMLParser::ParseDataTypes(tinyxml2::XMLElement *xml_root,
                                   std::unique_ptr<BaseNode> &root) {
  XMLP_ret ret = XMLP_ret::XML_OK;
  tinyxml2::XMLElement *node = xml_root->FirstChildElement();
  const char *tag = nullptr;
  while ((nullptr != node) && (ret == XMLP_ret::XML_OK)) {
    if (nullptr != (tag = node->Value())) {
      tag = node->FirstChildElement()->GetText();
      if (strcmp(tag, IMPLEMENTATION_DATA_TYPES) == 0) {
        if (XMLP_ret::XML_OK !=
            (ret = ParseImplementationDataTypes(
                 node->FirstChildElement()->NextSiblingElement(), root))) {
          std::cout << "parse data type error" << std::endl;
          break;
        }
      }

      node = node->NextSiblingElement();
    }
  }

  return ret;
}

XMLP_ret XMLParser::ParseImplementationDataTypes(
    tinyxml2::XMLElement *xml_root, std::unique_ptr<BaseNode> &root) {
  XMLP_ret ret = XMLP_ret::XML_OK;
  tinyxml2::XMLElement *node = xml_root->FirstChildElement();
  const char *tag = nullptr;
  while ((nullptr != node) && (ret == XMLP_ret::XML_OK)) {
    if (nullptr != (tag = node->Value())) {
      tag = node->FirstChildElement()->NextSiblingElement()->GetText();
      if (strcmp(tag, VECTOR) == 0) {
        if (XMLP_ret::XML_OK !=
            (ret = ParseDataTypeVector(node->FirstChildElement(), root))) {
          std::cout << "parse type vector error" << std::endl;
        }
      }

      node = node->NextSiblingElement();
    }
  }

  return ret;
}

XMLP_ret XMLParser::ParseDataTypeVector(tinyxml2::XMLElement *xml_root,
                                        std::unique_ptr<BaseNode> &root) {
  XMLP_ret ret = XMLP_ret::XML_OK;

  // DataTypeVector data_type_vec;
  // data_type_vec.base_name = xml_root->GetText();
  // std::cout << data_type_vec.base_name << std::endl;
  // auto vector_node = std::make_unique<DataNode<DataTypeVector>>();
  // vector_node->

  return ret;
}

XMLP_ret XMLParser::LoadXML(const std::string &filename,
                            std::unique_ptr<BaseNode> &root) {
  if (filename.empty()) {
    std::cout << "Error loading XML file, filename empty" << std::endl;
    return XMLP_ret::XML_ERROR;
  }

  tinyxml2::XMLDocument xml_doc;
  if (tinyxml2::XMLError::XML_SUCCESS != xml_doc.LoadFile(filename.c_str())) {
    std::cout << "Error opening '" << filename << "'" << std::endl;
    return XMLP_ret::XML_ERROR;
  }

  std::cout << "File '" << filename << "' opend successfully" << std::endl;
  return ParseXML(xml_doc, root);
}
}  // namespace cm_tool