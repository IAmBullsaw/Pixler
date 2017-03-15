#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include "iparser.h"
#include "ipixel.h"
#include "bmp.h"

#include <bitset>

typedef unsigned short word;
typedef unsigned int dword;


IParser::IParser() {}

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
void print_bmp_info_header_V4(BMP_info_header_V4 h) {
  std::cout << "info_header:\n"
	    << "Size " << h.bV4Size << "\n"
	    << "Width " << h.bV4Width << "\n"
	    << "Height " << h.bV4Height << "\n"
	    << "Planes " << h.bV4Planes << "\n"
	    << "BitCount " << h.bV4BitCount << "\n";
  std::string comp{""};
  switch (h.bV4Compression) {
  case BI_RGB: comp = "BI_RGB"; break;
  case BI_RLE8: comp = "BI_RLE8"; break;
  case BI_RLE4: comp = "BI_RLE4"; break;
  case BI_JPEG: comp = "BI_JPEG"; break;
  case BI_PNG: comp = "BI_PNG"; break;
  case BI_CMYK: comp = "BI_CMYK"; break;
  case BI_CMYKRLE8: comp = "BI_CMYKRLE8"; break;
  case BI_CMYKRLE4: comp = "BI_CMYKRLE4"; break;
  default: comp = "No freaking idea";
  }
  std::cout << "Compression " << comp << " " << std::hex << h.bV4Compression << std::dec << "\n"
	    << "SizeImage " << h.bV4SizeImage << "\n"
	    << "XPelspermeter " << h.bV4XPelsPerMeter << "\n"
	    << "YPelspermeter " << h.bV4YPelsPerMeter << "\n"
	    << "Clrused " << h.bV4ClrUsed << "\n"
	    << "Clrimportant " << h.bV4ClrImportant << "\n"
	    << "RedMask " << h.bV4RedMask << "\n"
	    << "GreenMask " << h.bV4GreenMask << "\n"
	    << "BlueMask " << h.bV4BlueMask << "\n"
	    << "AlphaMask " << h.bV4AlphaMask << "\n"
	    << "CSType " << h.bV4CSType << "\n"
    //<< "Endpoints " << h.bV4Endpoints << "\n"
	    << "GammaRed " << h.bV4GammaRed << "\n"
	    << "GammaGreen " << h.bV4GammaGreen << "\n"
	    << "GammaBlue " << h.bV4GammaBlue << std::endl;
}
bool is_valid_bmp(std::vector<char>::iterator & it) {
  char b{*it};
  std::advance(it,1);
  char m{*it};
  std::advance(it,1);
  return (b == 'b' && m == 'm');
}

bool read_word(word & w, std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  // Char is 1 byte, 8 bits.
  // Word is 2 bytes, ergo we need to shift 8 bits.
  
  int shift{0};
  w = 0;
  bool success{true};
  for (int i{0}; i < 2; i++) {
    if (it == end) {
      success = false;
      break;
    }
    w += static_cast<word>(*it << shift);
    shift += 8;
    std::advance(it,1);
  }
  return success;
}
bool read_dword(dword & dw, std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  int shift{0};
  dw = 0;
  bool success{true};
  for (int i{0}; i < 4; i++) {
    if (it == end) {
      success = false;
      break;
    }
    dw += static_cast<dword>(*it << shift);
    shift += 8;
    std::advance(it,1);
  }
  return success;
}
/*
IPixel read_pixel(std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  ; // TODO
}
 */

void read_bytes_ushort(unsigned short* value, std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  if (it == end)
    return;
  int byte = *it;
  *value = static_cast<unsigned short>(byte);
  std::advance(it,1);
}
void read_2_bytes_ushort(unsigned short* value,std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  *value = 0;
  unsigned short vessel{0};
  read_bytes_ushort(&vessel,it,end);
  *value += vessel;
  read_bytes_ushort(&vessel,it,end);
  *value += vessel;
}
void read_bytes_uint(unsigned int* value, int n_bytes, std::vector<char>::iterator & it,std::vector<char>::iterator end) {
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
void read_bytes_int(int* value, int n_bytes, std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  
  union sign_converter {
    unsigned int _uint;
    int _int;
  } converter;
  
  read_bytes_uint(&converter._uint, n_bytes, it, end);
  *value = converter._int;
  
}

void parse_bmp_header(BMP_file_header & header,std::vector<char>::iterator & it,std::vector<char>::iterator end) {
  // 14 bit header
  header.bfType[0] = *it;
  std::advance(it,1);
  header.bfType[1] = *it;
  read_dword(header.bfSize,it,end);
  read_word(header.bfReserved1,it,end);
  read_word(header.bfReserved2,it,end);
  read_dword(header.bfOffBits,it,end);

  std::cout << std::bitset<32>(138) << std::endl;
  std::cout << std::bitset<32>(header.bfSize) << std::endl;
  
}

std::vector<IPixel*> IParser::parse_bmp(std::string image) {  
  std::vector<IPixel*> vector{};
  std::ifstream input(image, std::ios::binary);
  std::vector<char> buffer((std::istreambuf_iterator<char>(input)), 
			   (std::istreambuf_iterator<char>())
			   );
  input.close();
  // Building data
  auto iit = buffer.begin();       
  BMP_file_header file_header;
  parse_bmp_header(file_header, iit, buffer.end());

  print_bmp_file_header(file_header);
  
  unsigned int header_size{0};
  read_bytes_uint(&header_size, 4, iit, buffer.end()); // 4 bytes

  if (header_size == 108) {
    BMP_info_header_V4 info_header;
    info_header.bV4Size = header_size; // 4 bytes
    read_bytes_int(&info_header.bV4Width, 4, iit, buffer.end()); // 4 bytes
    read_bytes_int(&info_header.bV4Height, 4, iit, buffer.end()); // 4 bytes
    
    read_2_bytes_ushort(&info_header.bV4Planes, iit, buffer.end()); // 2 bytes
    read_2_bytes_ushort(&info_header.bV4BitCount, iit, buffer.end()); // 2 bytes

    // Why is size so terribly horrbily wrong?
    read_bytes_uint(&info_header.bV4Compression, 4, iit, buffer.end());
    read_bytes_uint(&info_header.bV4SizeImage, 6, iit, buffer.end());

    print_bmp_file_header(file_header);
    print_bmp_info_header_V4(info_header);

    iit = buffer.begin() + file_header.bfOffBits;
    while (iit != buffer.end()) {

      unsigned short r{0};
      unsigned short g{0};
      unsigned short b{0};      

      read_bytes_ushort(&b,iit,buffer.end());
      read_bytes_ushort(&g,iit,buffer.end());
      read_bytes_ushort(&r,iit,buffer.end());
      
      vector.push_back(new IPixel(r,g,b));

      std::bitset<16> test_r{r};
      std::bitset<16> test_g{g};
      std::bitset<16> test_b{b};

      std::cout << test_r << std::endl;
      std::cout << test_g << std::endl;
      std::cout << test_b << std::endl << std::endl;

      read_bytes_ushort(&r,iit,buffer.end()); // and the fourth...
    }
  } else if (header_size == 876) { // this is the wrong number
    /*
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
    */
  }
  

  
  // auto it = buffer.begin() + file_header.bfOffBits;
  // int pixels = info_header.biSizeImage;
  // while (pixels--){
  //   vector.push_back( new IPixel(*(it+2),*(it+1),*it) );
  //   it += 4;
  // }
  std::cout << buffer.size() << std::endl;
  return vector;
}

std::vector<IPixel*> IParser::parse( std::string image, IParser::IMG img_type) {
  std::vector<IPixel*> vector{};
  if (img_type == IParser::BMP) {
    vector = parse_bmp(image);
  }

  std::cout << vector.size() << std::endl;
  
  return vector;
}
