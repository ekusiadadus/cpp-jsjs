#include "Tokenizer.h"
#include <iostream>
using namespace std;
using namespace simpleparser;

int main() {
  std::cout << "simple parser 0.1" << std::endl;

  FILE *fp = fopen("/Users/matsuri/CLionProjects/untitled/test.myc", "r");
  if (fp == nullptr) {
    std::cout << "Error opening file" << std::endl;
    return 1;
  }

  fseek(fp, 0, SEEK_END);
  size_t fileSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  string fileContents(fileSize, ' ');
  fread(&fileContents[0], 1, fileSize, fp);

  cout << fileContents << endl;

  Tokenizer tokenizer;
  vector<Token> tokens = tokenizer.parse(fileContents);

  for (auto &token: tokens) {
    token.DebugPrint();
  }

  return 0;
}
