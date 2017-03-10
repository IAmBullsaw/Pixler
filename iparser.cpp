#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "iparser.h"
#include "ipixel.h"
#include "bmp.h"

IParser::IParser(){
}

void print_bmp_file_header(BMP_file_header file_header) {
  std::cout << "file_header:\n"
	    <<"type " << file_header.bfType << "\n"
	    <<"size " << file_header.bfSize << "\n"
	    <<"reserved1 " << file_header.bfReserved1 << "\n"
	    <<"reserved2 " << file_header.bfReserved2 << "\n"
	    <<"offset " << file_header.bfOffBits << std::endl << std::endl;
}

void print_bmp_info_header(BMP_info_header info_header) {
  std::cout << "info_header:\n"
	    << "Size " << info_header.biSize << "\n"
	    << "Width " << info_header.biWidth << "\n"
	    << "Height " << info_header.biHeight << "\n"
	    << "Planes " << info_header.biPlanes << "\n"
	    << "BitCount " << info_header.biBitCount << "\n"
	    << "Compression " << info_header.biCompression << "\n"
	    << "SizeImage " << info_header.biSizeImage << "\n"
	    << "XPelsPerMeter " << info_header.biXPelsPerMeter << "\n"
	    << "YPelsPerMeter " << info_header.biYPelsPerMeter << "\n"
	    << "ClrUsed " << info_header.biClrUsed << "\n"
	    << "ClrImportant " << info_header.biClrImportant << std::endl << std::endl;
}

std::vector<IPixel*> IParser::parse_bmp(std::string image) {
  std::vector<IPixel*> vector{};
  
  BMP_file_header file_header;
  BMP_info_header info_header;

  std::ifstream input(image, std::ios::binary);
  
  std::vector<char> buffer((std::istreambuf_iterator<char>(input)), 
			   (std::istreambuf_iterator<char>())
			   );
  input.close();
  // Building data  
  file_header.bfType = buffer[0] + buffer[1]; // Byte 1,2
  file_header.bfSize = buffer[5] + buffer[4] + buffer[3] + buffer[2]; // 3-6
  file_header.bfReserved1 = buffer[6] + buffer[7]; // 7,8
  file_header.bfReserved2 = buffer[8] + buffer[9]; // 9,10
  file_header.bfOffBits = buffer[13] + buffer[12] + buffer[11] + buffer[10]; // 11-14

  // This is ... efficient?
  info_header.biSize = buffer[17] + buffer[16] + buffer[15] + buffer[14]; // 15-18
  info_header.biWidth = buffer[21] + buffer[20] + buffer[19] + buffer[18]; // 19-22
  info_header.biHeight = buffer[25] + buffer[24] + buffer[23] + buffer[22]; // 23-26
  info_header.biPlanes = buffer[27] + buffer[26]; // 27,28
  info_header.biBitCount = buffer[29] + buffer[28]; // 29,30
  info_header.biCompression = buffer[33] + buffer[32] + buffer[31] + buffer[30]; // 31-34
  info_header.biSizeImage = buffer[37] + buffer[36] + buffer[35] + buffer[34]; // 35-38
  info_header.biXPelsPerMeter = buffer[41] + buffer[40] + buffer[39] + buffer[38]; // 39-42
  info_header.biYPelsPerMeter = buffer[45] + buffer[44] + buffer[43] + buffer[42]; // 43-46
  info_header.biClrUsed = buffer[49] + buffer[48] + buffer[47] + buffer[46]; // 47-50
  info_header.biClrImportant = buffer[53] + buffer[52] + buffer[51] + buffer[50]; // 51-54

  print_bmp_file_header(file_header);
  print_bmp_info_header(info_header);

  auto it = buffer.begin() + file_header.bfOffBits;
  int pixels = info_header.biSizeImage;
  while (pixels--){
    vector.push_back( new IPixel(*(it+2),*(it+1),*it) );
    it += 3;
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
