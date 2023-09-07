#ifndef __SNAKE_H__
#define __SNAKE_H__

#include "winsys.h"

struct SSegment
{
  SSegment* next;
  SSegment* prev;

  int length;
  char direction;
  CPoint position;
};

class CSnake:public CFramedWindow
{
  string text;

  SSegment* start;
  CPoint position;
  CPoint food;
  char direction;
  bool extending;
  bool flagNOT;
  bool paused;
  bool help;
  int levelNOT;
  int tics;
  int length;

  //float max_length = geom.size.x * geom.size.y;

  void update_placement(CPoint);
  int move_snake(int c);
  int generate_food();
  bool is_snake(CPoint);
  void correct_position();
  void paint_help();

public:
  CSnake(CRect r, char _c = ' ');
  ~CSnake();

  void paint();
  bool handleEvent(int c);

  void WIN();
  void LOOSE();

};

#endif
