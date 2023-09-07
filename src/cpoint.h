#ifndef __CPOINT_H__
#define __CPOINT_H__

#include <list>

using namespace std;

struct CPoint
{
  int x;
  int y;
  CPoint(int _x=0, int _y=0): x(_x), y(_y) {};

  bool operator==(const CPoint& delta)
  {
    if (delta.x == x && delta.y == y) return true;
    else return false;
  }

  CPoint& operator+=(const CPoint& delta)
  {
    x+=delta.x;
    y+=delta.y;
    return *this;
  }

  CPoint& operator-=(const CPoint& delta)
  {
    x-=delta.x;
    y-=delta.y;
    return *this;
  }

  CPoint operator+ (const CPoint& co) const
  {
      CPoint n;
      n.x = this->x + co.x;
      n.y = this->y + co.y;
      return n;
  }

  CPoint operator- (const CPoint& co) const
  {
      CPoint n;
      n.x = this->x - co.x;
      n.y = this->y - co.y;
      return n;
  }
};

struct CRect
{
  CPoint topleft;
  CPoint size;
  CRect(CPoint t1=CPoint(), CPoint s=CPoint()):
    topleft(t1), size(s) {};
};



#endif
