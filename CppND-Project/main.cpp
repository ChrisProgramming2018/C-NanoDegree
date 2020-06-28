// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>


// #include <torch/script.h> // One-stop header.
#include <torch/torch.h>
#include <iostream>
#include <memory>
#include <string>
#include "lstmModel.h"

using torch::indexing::Slice;





int main(int argc, const char* argv[]) {
  // Hyper parameters
  const int64_t embed_size = 128;
  const int64_t hidden_size = 1024;
  const int64_t num_layers = 1;
  const int64_t num_samples = 1000;  // the number of words to be
  const int64_t batch_size = 20;
  const int64_t sequence_length = 30;
  const size_t num_epochs = 5;
  const double learning_rate = 0.002;
  const int64_t vocab_size = 30;
  
  RNNLM model(vocab_size, embed_size, hidden_size, num_layers);
  // model->to(device);

  std::cout << "Hello pytorch" << std::endl;
  std::cout << "end pytorch" << std::endl;
  std::string start = "A";
  auto cuda_available = torch::cuda::is_available();
  torch::Device device(cuda_available ? torch::kCUDA : torch::kCPU);
  std::cout << (cuda_available ? "CUDA available. Training on GPU." : "Training on CPU.") << '\n';
  std::cout << start << std::endl;
}
