#include <iostream>
#include <vector>
#include "iparser.h"
#include "ipixel.h"

void print_vector(std::vector<IPixel*> v) {
  for (IPixel* p : v) {
    std::cout << *p << std::endl;
  }
}

int main() {
  IParser parser{};
  std::cout << "1x1:" << std::endl;
  std::vector<IPixel*> vr = parser.parse("test_black_1x1.bmp", IParser::BMP);
  print_vector(vr);
  
  std::cout << "\n10x10:" << std::endl;
  print_vector(parser.parse("test_black_10x10.bmp", IParser::BMP));
  
  
  return 0;
}
