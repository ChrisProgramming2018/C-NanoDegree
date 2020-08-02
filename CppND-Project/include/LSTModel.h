// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>


#ifndef CPPND_PROJECT_INCLUDE_LSTMODEL_H_
#define CPPND_PROJECT_INCLUDE_LSTMODEL_H_

#include <stdio.h>
#include <string.h>
#include <QString>
#include <string>
#include <vector>


class LSTMModel {
 public:
  LSTMModel();
  void loadModel();
  void cuda_available();
  bool _cuda_available;
  int64_t _embed_size;
  int64_t _hidden_size;
  int64_t _num_layers;
  int64_t _batch_size;
  char *_fn;
  bool _predictBool;
  bool _donePredict;
  void setWordPath(std::string path);
  std::string _path;
  std::string get_current_dir();
  std::string _penn_treebank_data_path;
  std::vector<std::string> globVector(const std::string& pattern);
  std::string _wordToPredict;
  std::string _wordpredicted1;
  std::string _wordpredicted2;
  std::string _wordpredicted3;
  std::string _wordpredicted4;
  std::vector<std::string> _wordsPredicted;
};
#endif  // CPPND_PROJECT_INCLUDE_LSTMODEL_H_
