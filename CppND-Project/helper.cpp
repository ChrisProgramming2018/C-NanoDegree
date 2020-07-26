// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>


#include "helper.h"
#include "corpus.h"
#include <torch/torch.h>
#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <tuple>
#include "rnn_lm.h"
#include <unistd.h>
#include <glob.h>
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
  _path.append("../data/*");
   std::vector<std::string> files = globVector("/home/architect/cpp/juli/save/data/*");
   std::cout << files[0] << std::endl;
  _penn_treebank_data_path = files[0];
}

// ______________________________________________________________
void LSTMModel::loadModel() {
  // Hyper parameters
  torch::Device device(_cuda_available ? torch::kCUDA : torch::kCPU);
  std::cout << (_cuda_available ? "CUDA available. Training on GPU." : "Training on CPU.") << '\n';
   std::cout << _penn_treebank_data_path <<  " loc " << std::endl;
  Corpus corpus(_penn_treebank_data_path);
  auto vocab_size = corpus.get_dictionary().size();
  std::cout << "dict size " << vocab_size << std::endl;
  RNNLM model(vocab_size, _embed_size, _hidden_size, _num_layers);
  model->to(device);
  std::cout << "Load trained model ...\n";
  std::string model_path = "model-trained.pt";
  torch::load(model, model_path);
  model->eval();
  torch::NoGradGuard no_grad;
  // Initialize hidden- and cell-states.
  auto h = torch::zeros({_num_layers, 1, _hidden_size}).to(device);
  auto c = torch::zeros({_num_layers, 1, _hidden_size}).to(device);
  std::string inputWord = "next";
  auto indexInput =  corpus.get_dictionary().getIndexFromWord(inputWord);
  auto prob = torch::tensor(indexInput);
  auto data = prob.unsqueeze(0).to(device);
  data = data.unsqueeze(0);
  torch::Tensor output;
  std::forward_as_tuple(output, std::tie(h, c)) = model->forward(data, std::make_tuple(h, c));
}

// ______________________________________________________________
QString LSTMModel::predict() {
  return "predited word";
}
  
// ______________________________________________________________
void LSTMModel::readWord(std::string word) {
  std::cout << word << std::endl;
}

// ______________________________________________________________
void LSTMModel::cuda_available() {
  std::cout << _cuda_available << std::endl;
}


std::string LSTMModel::get_current_dir() {
   char buff[FILENAME_MAX]; //create string buffer to hold path
   getcwd( buff, FILENAME_MAX );
   std::string current_working_dir(buff);
   return current_working_dir;
}


// ______________________________________________________________
std::vector<std::string> LSTMModel::globVector(const std::string& pattern){
  glob_t glob_result;
  glob(pattern.c_str(),GLOB_TILDE,NULL,&glob_result);
  std::vector<std::string> files;
  for(unsigned int i=0;i<glob_result.gl_pathc;++i){
    files.push_back(std::string(glob_result.gl_pathv[i]));
  }
  globfree(&glob_result);
  return files;
}

