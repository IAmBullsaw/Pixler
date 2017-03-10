#ifndef IPARSER_H
#define IPARSER_H

#include <string>
#include <vector>
#include "ipixel.h"

class IParser {
 public:
  IParser();
  enum IMG {BMP};
  std::vector<IPixel*> parse( std::string image, IMG BMP);
  
 private:
  std::vector<IPixel*> parse_bmp(std::string image);  

};

#endif /* IPARSER_H */
