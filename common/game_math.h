#pragma once
struct fvec2 {
  float x;
  float y;
 
  constexpr fvec2(float x = 0, float y = 0) : x(x), y(y) {
    // Empty
  }
 
  fvec2 operator+(const fvec2& a) const { return fvec2(x + a.x, y + a.y); }
  fvec2 operator-(const fvec2& a) const { return fvec2(x - a.x, y - a.y); }
  fvec2 operator*(const fvec2& a) const { return fvec2(x * a.x, y * a.y); }
  fvec2& operator=(const fvec2& a) {
    x = a.x;
    y = a.y;
    return *this;
  }
  fvec2& operator+=(const fvec2& a) {
    x = x + a.x;
    y = y + a.y;
    return *this;
  }
  fvec2& operator-=(const fvec2& a) {
    x = x - a.x;
    y = y - a.y;
    return *this;
  }
  fvec2& operator*=(const fvec2& a) {
    x = x * a.x;
    y = y * a.x;
    return *this;
  }
  fvec2& operator*=(const float m){
    x = x*m;
    y = y*m;
  }
  bool operator==(const fvec2& a) const { return (x == a.x && y == a.y); }
};
