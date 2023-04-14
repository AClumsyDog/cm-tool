#pragma once

#include <boost/program_options.hpp>
#include <string>

namespace po = boost::program_options;

class Options {
 public:
  Options();

  ~Options();

  bool Parse(int argc, char *argv[]);

 public:
  std::string input_;
  std::string output_;

 private:
  po::options_description options_;
};