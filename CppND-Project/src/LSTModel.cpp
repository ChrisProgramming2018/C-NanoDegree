// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>


#include <unistd.h>
#include <glob.h>
#include <torch/torch.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <tuple>
#include <string>
#include <thread>
#include <chrono>
#include "../include/LSTModel.h"
#include "../include/RNNLm.h"
#include "../include/Corpus.h"


using namespace std::chrono_literals;
using data_utils::Corpus;

// ______________________________________________________________
LSTMModel::LSTMModel() {
  _cuda_available = torch::cuda::is_available();
  _embed_size = 128;
  _hidden_size = 1024;
  _num_layers = 1;
  _batch_size = 20;
  _penn_treebank_data_path = "../data/test.txt";
  _path = get_current_dir();
  _path.append("/../data/*");
  std::cout << "model  " << _path << std::endl;
  std::vector<std::string> files = globVector(_path);
  std::cout << files[0] << std::endl;
  _penn_treebank_data_path = files[0];
  _predictBool = false;
  _donePredict = false;
  _wordToPredict = "";
  _wordsPredicted = {};
}

// ______________________________________________________________
void LSTMModel::loadModel() {
  // Hyper parameters
  torch::Device device(torch::kCPU);

  // check if path name is not empty
  if (_penn_treebank_data_path.empty()) {
    std::cout << "select the path before load the model" << std::endl;
    return;
  }

  Corpus corpus(_penn_treebank_data_path);
  auto ids = corpus.get_data(32);
  auto vocab_size = corpus.get_dictionary().size();
  std::cout << "dict size " << vocab_size << std::endl;
  RNNLM model(vocab_size, _embed_size, _hidden_size, _num_layers);
  model->to(device);
  std::cout << "Load trained model ...\n";
  std::string model_path = "../model/model-trained.pt";
  torch::load(model, model_path);
  model->eval();
  torch::NoGradGuard no_grad;
  // Initialize hidden- and cell-states.
  auto h = torch::zeros({_num_layers, 1, _hidden_size}).to(device);
  auto c = torch::zeros({_num_layers, 1, _hidden_size}).to(device);


  // stay and what for predictio
  while (true) {
    std::cout << " wait predict trained model ...\n";
    while (!_predictBool) {
      std::this_thread::sleep_for(2s);
    }
    _predictBool = false;
    std::string inputWord = _wordToPredict;
    auto indexInput =  corpus.get_dictionary().getIndexFromWord(inputWord);
    auto prob = torch::tensor(indexInput);
    auto data = prob.unsqueeze(0).to(device);
    data = data.unsqueeze(0);
    torch::Tensor output;
    std::cout << "Input network " << inputWord <<" " <<  data  << std::endl;
    try {
      std::forward_as_tuple(output, std::tie(h, c)) = model->forward(data, std::make_tuple(h, c));
    } catch (...) {
      std::cout << "index error "  << std::endl;
      continue;
    }
    prob = output.exp();
    auto word_id = prob.multinomial(1).item();
    auto word = corpus.get_dictionary().word_at_index(word_id.toLong());
    for (int i = 0; i < 4; i++) {
      word_id = prob.multinomial(1).item();
      word = corpus.get_dictionary().word_at_index(word_id.toLong());
      _wordsPredicted.push_back(word);
      std::cout  << inputWord <<  " next word "  << word << std::endl;
    }
    _donePredict = true;
  }
}


// ______________________________________________________________
void LSTMModel::setWordPath(std::string path) {
  std::cout  << "set path " << path << std::endl;
  _penn_treebank_data_path = path;
}

// ______________________________________________________________
void LSTMModel::cuda_available() {
  std::cout << _cuda_available << std::endl;
}


// ______________________________________________________________
std::string LSTMModel::get_current_dir() {
  char buff[FILENAME_MAX];  // create string buffer to hold path
  getcwd(buff, FILENAME_MAX);
  std::string current_working_dir(buff);
  return current_working_dir;
}


// ______________________________________________________________
std::vector<std::string> LSTMModel::globVector(const std::string& pattern) {
  glob_t glob_result;
  glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
  std::vector<std::string> files;
  for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
    files.push_back(std::string(glob_result.gl_pathv[i]));
  }
  globfree(&glob_result);
  return files;
}

