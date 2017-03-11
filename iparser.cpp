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
	    << "Type " << file_header.bfType[0] << file_header.bfType[1] << " (6677 means BM)\n"
	    << "Size " << file_header.bfSize << "\n"
	    << "Reserved1 " << file_header.bfReserved1 << "\n"
	    << "Reserved2 " << file_header.bfReserved2 << "\n"
	    << "Offset " << file_header.bfOffBits << std::endl << std::endl;
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

void read_bytes_short(unsigned short* value,std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  if (it == end)
    return;
  int byte = *it;
  *value = static_cast<unsigned short>(byte);
  std::advance(it,1);
}

void read_bytes_int(unsigned int* value, int n_bytes, std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  // make sure vessels are empty before reading
  *value = 0;
  unsigned int shift{0};

  while (n_bytes--) {
    if (it == end) {
      std::cout << "End of line!" << std::endl;
      return;
    }
    int byte = *it;
    
    if (byte == EOF) {
      std::cout << "End of file!" << std::endl;
      return;
    }
	*value += static_cast<unsigned int>(byte << shift);
      shift += 8;
      std::advance(it,1);
  }
}
  
  void read_bytes_long(int* value, int n_bytes, std::vector<char>::iterator & it,std::vector<char>::iterator end) {

    union sign_converter {
      unsigned int _uint;
      int _int;
    } converter;

    read_bytes_int(&converter._uint, n_bytes, it, end);
    *value = converter._int;
    
  }
std::vector<IPixel*> IParser::parse_bmp(std::string image) {
  std::vector<IPixel*> vector{};
  
  BMP_file_header file_header;

  std::ifstream input(image, std::ios::binary);
  
  std::vector<char> buffer((std::istreambuf_iterator<char>(input)), 
			   (std::istreambuf_iterator<char>())
			   );
  input.close();
  // Building data
  auto iit = buffer.begin();
  
  // header is 14 bytes
  // see Todo below
  read_bytes_short(&file_header.bfType[0], iit, buffer.end()); // 1 byte
  read_bytes_short(&file_header.bfType[1], iit, buffer.end()); // 1 byte
  read_bytes_int(&file_header.bfSize, 4, iit, buffer.end()); // 4 bytes
  // Todo: make function to read 2 bytes into short
  read_bytes_short(&file_header.bfReserved1, iit, buffer.end()); // 1 byte
  read_bytes_short(&file_header.bfReserved2, iit, buffer.end()); // 1 byte
  read_bytes_short(&file_header.bfReserved1, iit, buffer.end()); // 1 byte
  read_bytes_short(&file_header.bfReserved2, iit, buffer.end()); // 1 byte
  read_bytes_int(&file_header.bfOffBits, 4, iit, buffer.end()); // 4 bytes
  // total bytes read: 14

  unsigned int header_size{0};
  read_bytes_int(&header_size, 4, iit, buffer.end()); // 4 bytes


  // TODO:
  // Learned that I've been trying to parse the wrong header.
  // Trying to fix it.
  
  if (header_size == 108) {
    BMP_info_header_V4 info_header;
  
    read_bytes_long(&info_header., 4, iit, buffer.end()); // 4 bytes
    read_bytes_long(&info_header., 4, iit, buffer.end()); // 4 bytes
    
    read_bytes_short(&file_header., iit, buffer.end()); // 1 byte
    read_bytes_short(&file_header., iit, buffer.end()); // 1 byte
    
    read_bytes_short(&file_header., iit, buffer.end()); // 1 byte
    read_bytes_short(&file_header., iit, buffer.end()); // 1 byte
    
    read_bytes_int(&info_header., 4, iit, buffer.end());
    read_bytes_int(&info_header., 4, iit, buffer.end());
    read_bytes_long(&info_header., 4, iit, buffer.end());
    read_bytes_long(&info_header., 4, iit, buffer.end());
    read_bytes_int(&info_header., 4, iit, buffer.end());
    read_bytes_int(&info_header., 4, iit, buffer.end());
  }

  // old header parse...
  // read_bytes_long(&info_header.biWidth, 4, iit, buffer.end()); // 4 bytes
  // read_bytes_long(&info_header.biHeight, 4, iit, buffer.end()); // 4 bytes
    
  // read_bytes_short(&file_header.bfReserved1, iit, buffer.end()); // 1 byte
  // read_bytes_short(&file_header.bfReserved2, iit, buffer.end()); // 1 byte
    
  // read_bytes_short(&file_header.bfReserved1, iit, buffer.end()); // 1 byte
  // read_bytes_short(&file_header.bfReserved2, iit, buffer.end()); // 1 byte
    
  // read_bytes_int(&info_header.biCompression, 4, iit, buffer.end());
  // read_bytes_int(&info_header.biSizeImage, 4, iit, buffer.end());
  // read_bytes_long(&info_header.biXPelsPerMeter, 4, iit, buffer.end());
  // read_bytes_long(&info_header.biYPelsPerMeter, 4, iit, buffer.end());
  // read_bytes_int(&info_header.biClrUsed, 4, iit, buffer.end());
  // read_bytes_int(&info_header.biClrImportant, 4, iit, buffer.end());

  
  // This is ... efficient?
  // info_header.biSize = buffer[17] + buffer[16] + buffer[15] + buffer[14]; // 15-18
  // info_header.biWidth = buffer[21] + buffer[20] + buffer[19] + buffer[18]; // 19-22
  // info_header.biHeight = buffer[25] + buffer[24] + buffer[23] + buffer[22]; // 23-26
  // info_header.biPlanes = buffer[27] + buffer[26]; // 27,28
  // info_header.biBitCount = buffer[29] + buffer[28]; // 29,30
  // info_header.biCompression = buffer[33] + buffer[32] + buffer[31] + buffer[30]; // 31-34
  // info_header.biSizeImage = buffer[37] + buffer[36] + buffer[35] + buffer[34]; // 35-38
  // info_header.biXPelsPerMeter = buffer[41] + buffer[40] + buffer[39] + buffer[38]; // 39-42
  // info_header.biYPelsPerMeter = buffer[45] + buffer[44] + buffer[43] + buffer[42]; // 43-46
  // info_header.biClrUsed = buffer[49] + buffer[48] + buffer[47] + buffer[46]; // 47-50
  // info_header.biClrImportant = buffer[53] + buffer[52] + buffer[51] + buffer[50]; // 51-54

  print_bmp_file_header(file_header);
  print_bmp_info_header(info_header);

  // auto it = buffer.begin() + file_header.bfOffBits;
  // int pixels = info_header.biSizeImage;
  // while (pixels--){
  //   vector.push_back( new IPixel(*(it+2),*(it+1),*it) );
  //   it += 4;
  // }
  
  return vector;
}

std::vector<IPixel*> IParser::parse( std::string image, IParser::IMG img_type) {
  std::vector<IPixel*> vector{};
  if (img_type == IParser::BMP) {
    vector = parse_bmp(image);
  }
  
  return vector;
}
