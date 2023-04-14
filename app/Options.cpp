#include "Options.h"

#include <iostream>

Options::Options() : output_("../output"), options_("Options are") {
  options_.add_options()("help,h", "Print this help message")(
      "input,i", po::value<std::string>(), "Path to arxml")(
      "output,o", po::value<std::string>(),
      "Path for saving generated code, The default path is '../output'");
}

Options::~Options() {}

bool Options::Parse(int argc, char *argv[]) {
  po::variables_map vm;
  try {
    po::store(po::parse_command_line(argc, argv, options_), vm);
    po::notify(vm);
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return false;
  }

  if (vm.count("help")) {
    std::cout << options_ << std::endl;
    return false;
  }

  if (!vm.count("input")) {
    std::cout << options_ << std::endl;
    return false;
  }
  input_ = vm["input"].as<std::string>();

  if (!vm.count("output")) {
    std::cout << "Use default output path '../output'" << std::endl;
  } else {
    output_ = vm["output"].as<std::string>();
  }
  return true;
}