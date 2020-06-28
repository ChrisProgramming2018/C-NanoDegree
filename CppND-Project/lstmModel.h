// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>


#pragma once

#include <torch/torch.h>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>

        
class RNNLMImpl : public torch::nn::Module {
 public:
  RNNLMImpl(int64_t vocab_size, int64_t embed_size, int64_t hidden_size, int64_t num_layers);
 std::tuple<torch::Tensor, std::tuple<torch::Tensor, torch::Tensor>> forward(torch::Tensor x, std::tuple<torch::Tensor, torch::Tensor> hx);
 private:
  torch::nn::LSTM lstm;
  torch::nn::Embedding embed;
  torch::nn::Linear linear;
};

TORCH_MODULE(RNNLM);
