#include <iostream>

#include "CodeGen.h"
#include "Options.h"
#include "XmlParser.h"

using namespace cm_tool;

int main(int argc, char **argv) {
  Options options;
  if (!options.Parse(argc, argv)) {
    return 1;
  }

  XmlParser xml_parser;
  if (!xml_parser.Load(options.input_)) {
    return 1;
  }

  try {
    CodeGen code_gen;
    code_gen.Init(xml_parser.GetTree());
    auto codes = code_gen.Generate();
    for (const auto &code : codes) {
      if (code.name == "common") {
        std::cout << code.content << std::endl;
      }
    }
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}