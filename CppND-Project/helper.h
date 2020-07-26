// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>


#include <QString>
#include <string>
#include <stdio.h>
#include <string.h>
#include <vector>

#ifndef THREAD_H_
#define THREAD_H_

class LSTMModel {
 public:
 LSTMModel();
 QString  predict();
 void loadModel();
 void readWord(std::string word);
 void cuda_available();
 bool _cuda_available;
 int64_t _embed_size;
 int64_t _hidden_size;
 int64_t _num_layers;
 int64_t _batch_size;
 char *_fn;
 std::string _path;
 std::string get_current_dir();
 std::string _penn_treebank_data_path;
 std::vector<std::string> globVector(const std::string& pattern);
};
#endif //

