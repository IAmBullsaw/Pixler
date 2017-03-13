#include <iostream>
#include "ipixel.h"

IPixel::IPixel()
  :r{0},g{0},b{0}
{}
IPixel::IPixel(int r, int g, int b)
  :r{r},g{g},b{b}
{}

void IPixel::set_red(int value) {
  r = value;
}
void IPixel::set_green(int value) {
  g = value;
}
void IPixel::set_blue(int value) {
  b = value;
}
int IPixel::get_red() {
  return r;
}
int IPixel::get_green() {
  return g;
}
int IPixel::get_blue() {
  return b;
}

std::ostream& operator<<(std::ostream& os, const IPixel& p) {
  os << "<rgb " << p.r << ", " << p.g << ", " << p.b << ">";
  return os;
} 
