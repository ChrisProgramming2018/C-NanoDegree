// Copyright 2020-present pytorch-cpp Authors
#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

namespace data_utils {
class Dictionary {
 public:
    int64_t add_word(const std::string& word);
    std::string word_at_index(int64_t index) const;
    size_t size() const { return word2idx_.size(); }
    int getIndexFromWord(std::string word) const { 
      std::unordered_map<std::string, size_t>::const_iterator got = word2idx_.find (word);
      if (got == word2idx_.end()) {
        std::cout << "Not found" << std::endl;
        return -1;
      }
      return got->second;
    }
 private:
    std::unordered_map<std::string, size_t> word2idx_;
    std::vector<std::string> idx2word_;
};
}  // namespace data_utils
