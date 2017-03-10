struct BMP_file_header {
  unsigned short  bfType{0};
  unsigned int bfSize{0};
  unsigned short  bfReserved1{0};
  unsigned short  bfReserved2{0};
  unsigned int bfOffBits{0};
};

struct BMP_info_header {
  unsigned int biSize{0};
  int  biWidth{0};
  int  biHeight{0};
  unsigned short  biPlanes{0};
  unsigned short  biBitCount{0};
  unsigned int biCompression{0};
  unsigned int biSizeImage{0};
  int  biXPelsPerMeter{0};
  int  biYPelsPerMeter{0};
  unsigned int biClrUsed{0};
  unsigned int biClrImportant{0};
};
