struct BMP_file_header {
  unsigned short  bfType[2];
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

struct BMP_info_header_V4 {
  unsigned int bV4Size;
  int bV4Width;
  int bV4Height;
  unsigned short bV4Planes;
  unsigned short bV4BitCount;
  unsigned int bV4Compression;
  unsigned int bV4SizeImage;
  int bV4XPelsPerMeter;
  int bV4YPelsPerMeter;
  unsigned int bV4ClrUsed;
  unsigned int bV4ClrImportant;
  unsigned int bV4RedMask;
  unsigned int bV4GreenMask;
  unsigned int bV4BlueMask;
  unsigned int bV4AlphaMask;
  unsigned int bV4CSType;
  //CIEXYZTRIPLE bV4Endpoints; // Oh lord what is this coordinate triplet?
  unsigned int bV4GammaRed;
  unsigned int bV4GammaGreen;
  unsigned int bV4GammaBlue;
};

enum Compression {
   BI_RGB = 0x0000,
   BI_RLE8 = 0x0001,
   BI_RLE4 = 0x0002,
   BI_BITFIELDS = 0x0003,
   BI_JPEG = 0x0004,
   BI_PNG = 0x0005,
   BI_CMYK = 0x000B,
   BI_CMYKRLE8 = 0x000C,
   BI_CMYKRLE4 = 0x000D
};
