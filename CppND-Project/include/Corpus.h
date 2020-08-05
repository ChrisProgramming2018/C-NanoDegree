// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>

#include <torch/torch.h>
#include <string>
#include "Dictionary.h"

#ifndef CPPND_PROJECT_INCLUDE_CORPUS_H_
#define CPPND_PROJECT_INCLUDE_CORPUS_H_

namespace data_utils {
class Corpus {
 public:
  explicit Corpus(const std::string& path) : path_(path) {}
  torch::Tensor get_data(int64_t batch_size);
  Dictionary& get_dictionary()  { return dictionary_; }
 private:
  std::string path_;
  Dictionary dictionary_;
};
}  // namespace data_utils

#endif // CPPND_PROJECT_INCLUDE_CORPUS_H_
