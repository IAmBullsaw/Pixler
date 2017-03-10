#include <iostream>
#include <vector>
#include "iparser.h"
#include "ipixel.h"

void print_vector(std::vector<IPixel*> v) {
  for (IPixel* p : v) {
    std::cout << *p;
  }
}

int main() {
  IParser parser{};
  std::vector<IPixel*> vr = parser.parse("test_black_1x1.bmp", IParser::BMP);
  print_vector(vr);
  
  print_vector(parser.parse("test_black_10x10.bmp", IParser::BMP));
  
  print_vector(parser.parse("test_red_green_5x10.bmp", IParser::BMP));  
  
  return 0;
}
