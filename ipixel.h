#ifndef IPIXEL_H
#define IPIXEL_H
#include <iostream>
class IPixel {
 public:
  IPixel();
  IPixel(int r,int g,int b);

  void set_red(int value);
  void set_green(int value);
  void set_blue(int value);
  int get_red();
  int get_green();
  int get_blue();
  friend std::ostream& operator<<(std::ostream& os, const IPixel& p); 
  
 private:
  int r;
  int g;
  int b;
};

#endif /* IPIXEL_H */
