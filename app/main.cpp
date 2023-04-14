#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>

#include "CodeGen.h"
#include "Options.h"
#include "XmlParser.h"

using namespace cm_tool;

static void SaveCode(const std::vector<CodeGen::GeneratedCode> &codes,
                     const std::string &path);

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
    SaveCode(codes, options.output_);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
  return 0;
}

void SaveCode(const std::vector<CodeGen::GeneratedCode> &codes,
              const std::string &path) {
  namespace fs = boost::filesystem;

  if (fs::exists(path)) {
    if (!fs::is_directory(path)) {
      throw std::runtime_error(path + " exists, but is not a directory");
    }
    fs::remove_all(path);
  }
  fs::create_directories(path);

  for (const auto &code : codes) {
    std::ofstream o_file(path + "/" + code.name);
    o_file.write(code.content.data(), code.content.size());
    o_file.close();
  }
}