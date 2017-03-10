#include <iostream>
#include <fstream>
#include "iparser.h"
#include "ipixel.h"
#include "bmp.h"

IParser::IParser(){
}

std::vector<IPixel*> IParser::parse_bmp(std::string image) {
  std::vector<IPixel*> vector{};
  std::vector<char> buffer{};
  
  PBITMAPFILEHEADER file_header;
  PBITMAPINFOHEADER info_header;
  
  std::fstream file{image};
  if (!file.is_open()) {
    std::cout << "failed to open " << image << '\n';
  } else {

    // Find file size
    file.seekg(0,std::ios::end);
    std::streampos length = file.tellg();
    file.seekg(0,std::ios::beg);
    
    // Resize buffer and read 
    buffer.resize(length);
    file.read(&buffer[0],length);

    std::cout << "len: " << length << std::endl;
    
    // Cast things
    file_header = (PBITMAPFILEHEADER)(&buffer[0]);
    info_header = (PBITMAPINFOHEADER)(&buffer[0] + sizeof(BITMAPFILEHEADER));

    file.seekg(file_header->bfOffBits, std::ios::beg);
    char r,g,b;
    int counter = 10;
    while(counter--) {
          
    file.get(b);
    file.get(g);
    file.get(r);

    vector.push_back(new IPixel(r,g,b));
    }
    
    // Print BM
    std::cout << buffer[0] << buffer[1] << std::endl;
    std::cout << file_header->bfSize << std::endl;
    std::cout << info_header->biWidth << " x " << info_header->biHeight << std::endl;
    std::cout << info_header->biSizeImage << std::endl;
    std::cout << "offset: " << file_header->bfOffBits << std::endl;
    
  }
  
  return vector;
}

std::vector<IPixel*> IParser::parse( std::string image, IParser::IMG img_type) {
  std::vector<IPixel*> vector{};
  if (img_type == IParser::BMP) {
    vector = parse_bmp(image);
  }
  
  return vector;
}
