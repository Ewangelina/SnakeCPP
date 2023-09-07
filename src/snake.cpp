#include <iostream>
#include "screen.h"
#include "snake.h"
#include "cpoint.h"
#include "utility_func.h"

#define MAX_LEVEL 25

using namespace std; //???

void CSnake::WIN()
{
  cout << "WIN";
  cout << endl << "result: " << length;
  exit(0);
}

void CSnake::LOOSE()
{
  cout << "LOOSE";
  cout << endl << "result: " << length;
  exit(0);
}

int CSnake::generate_food()
{
  int width = geom.size.x - 2;
  int heihgt = geom.size.y - 2;

  food.y = geom.topleft.y + 1 + rand() % heihgt;
  food.x = geom.topleft.x + 1 + rand() % width;

  CPoint oryg = food;

  while(is_snake(food) || food == position)
  {
    food.x += 1;
    if (food.x >= geom.size.x + geom.topleft.x - 1)
    {
      food.x = geom.topleft.x + 1;
      food.y += 1;

      if (food.y >= geom.size.y + geom.topleft.y - 1)
      {
        food.y = geom.topleft.y + 1;
      }
    }

    if (food == oryg) return 1;
  }

  return 0;
}

void CSnake::correct_position()
{
  if (position.x == geom.topleft.x)
  {
    position.x = geom.topleft.x + geom.size.x - 2;
    flagNOT = 0;
    return;
  }

  if (position.y == geom.topleft.y)
  {
    position.y = geom.topleft.y + geom.size.y - 2;
    flagNOT = 0;
    return;
  }

  if (position.x == geom.topleft.x + geom.size.x - 1)
  {
    position.x = geom.topleft.x + 1;
    flagNOT = 0;
    return;
  }

  if (position.y == geom.topleft.y + geom.size.y - 1)
  {
    position.y = geom.topleft.y + 1;
    flagNOT = 0;
    return;
  }

}

bool CSnake::is_snake(CPoint here) //nie działa zawsze
{
  SSegment* temp = start;
  while (temp->next != NULL)
  {
    for (int i = 0; i < temp->length; i++)
    {
      if (temp == start && i == 0) i = 1;
      switch(temp->direction)
      {
        case 'w':
        {
          if (CPoint(temp->position.x, temp->position.y - i) == here) return 1;
        }
        break;

        case 's':
        {
          if (CPoint(temp->position.x, temp->position.y + i) == here) return 1;
        }
        break;
        
        case 'a':
        {
          if (CPoint(temp->position.x - i, temp->position.y) == here) return 1; //może a i d odwrotnie?
        }
        break;
        
        case 'd':
        {
          if (CPoint(temp->position.x + i, temp->position.y) == here) return 1;
        }
        break;
      }
    }
    temp = temp->next;
  }

  for (int i = 0; i <= temp->length; i++)
  {
    if (temp == start && i == 0) i = 1;
    switch(temp->direction)
    {
      case 'w':
      {
        if (CPoint(temp->position.x, temp->position.y - i) == here) return 1;
      }
      break;

      case 's':
      {
        if (CPoint(temp->position.x, temp->position.y + i) == here) return 1;
      }
      break;
      
      case 'a':
      {
        if (CPoint(temp->position.x - i, temp->position.y) == here) return 1;
      }
      break;
      
      case 'd':
      {
        if (CPoint(temp->position.x + i, temp->position.y) == here) return 1;
      }
      break;
    }
  }

  return 0;
}

CSnake::CSnake(CRect r, char _c /*=' '*/):CFramedWindow(r, _c)
{
  direction = 'd';
  extending = false;
  flagNOT = 1;
  tics = 0;
  levelNOT = MAX_LEVEL;
  length = 3;
  help = 1;
  paused = 1;

  start = new SSegment;
  start->prev = NULL;
  start->next = NULL;

  start->length = 4;
  start->direction = 'a';
  position = CPoint(geom.topleft.x + geom.size.x/2 + 2, geom.topleft.y + geom.size.y/2);
  start->position = position;

  if (generate_food() == 1) WIN();
}

CSnake::~CSnake()
{
  SSegment* temp = start;
  while (temp->next != NULL)
  {
    temp = temp->next;
    delete temp->prev;
  }
  delete temp;
}

bool CSnake::handleEvent(int c)
{
  switch (c)
  {
    //move board
  case KEY_UP:
    move (CPoint (0, -1));
    update_placement(CPoint (0, -1));
    return true;
  case KEY_DOWN:
    move (CPoint (0, 1));
    update_placement(CPoint (0, 1));
    return true;
  case KEY_RIGHT:
    move (CPoint (1, 0));
    update_placement(CPoint (1, 0));
    return true;
  case KEY_LEFT:
    move (CPoint (-1, 0));
    update_placement(CPoint (-1, 0));
    return true;

    //move snake
  case 'w': case 'a': case 's': case 'd':
  {
    if (paused) return true;
    if (c == direction) return true;
    move_snake(c); //cond
    correct_position();
  }
  return true;

    //menu
  case 'p':
  {
    if (help == 1) return true;
    if (paused == 1) paused = 0;
    else paused = 1;
  }
  return true;

  case 'h':
  {
    if (help == 0)
    {
      help = 1;
      paused = 1;
    }
    else
    {
      help = 0;
      paused = 0;
    }
    
  }
  return true;

  case 'r':
  {
    //destruktor
    SSegment* temp = start;
    while (temp->next != NULL)
    {
      temp = temp->next;
      delete temp->prev;
    }
    delete temp;
    //konstruktor
    direction = 'd';
    extending = false;
    flagNOT = 1;
    tics = 0;
    levelNOT = MAX_LEVEL;
    length = 3;

    start = new SSegment;
    start->prev = NULL;
    start->next = NULL;

    start->length = 4;
    start->direction = 'a';
    position = CPoint(geom.topleft.x + geom.size.x/2 + 2, geom.topleft.y + geom.size.y/2);
    start->position = position;

    if (generate_food() == 1) WIN();
  }
  return true;


    //debug
  case 'e':
    extending = 1;
    length++;
    return true;

  case 'f':
    generate_food();
    return true;

  case '+':
    length += 25;
    return true;

  case '-':
    length -= 25;
    return true;
  

  default:
  {
    if (paused) return true;
    tics++;
    if (tics > levelNOT)
    {
      tics = 0;
      move_snake(direction); //cond
      correct_position();
    }    
  }
  return true;

  };
  return false;
}

int CSnake::move_snake(int c)
{
  if (is_opposite_direction(c, direction)) return 1;

  if (direction == c && flagNOT) start->length++;
  else
  {
    SSegment* head = new SSegment;
    head->next = start;
    head->prev = NULL;
    start->prev = head;
    head->length = 1;
    if (c == 'a' || c == 'd') head->direction = opposite(c);
    else head->direction = c;
    head->position = position; //so if below works
    start = head;
  }

  if (c == 'a')
  {
    start->position = start->position + CPoint (-1, 0);      
  }
  else if (c == 'w')
  {
    start->position = start->position + CPoint (0, -1);
  }
  else if (c == 's')
  {
    start->position = start->position + CPoint (0, 1);
  }
  else if (c == 'd')
  {
    start->position = start->position + CPoint (1, 0);
  }

  position = start->position;
  direction = c;

  if (position == food) 
  {
    extending = true;
    length++;
    if (generate_food() == 1) WIN();
  }

  if (extending == false)
  {
    SSegment* last = start;
    while (last->next != NULL)
    {
      last = last->next;
    }

    if (last->length == 1)
    {
      last = last->prev;

      delete last->next;
      last->next = NULL;
    }
    else
    {
      last->length--;
    }
  }
  else extending = false;

  if (is_snake(position)) LOOSE();   


  return 0;
}



void CSnake::update_placement(CPoint p)
{
  position += p;

  food += p;

  SSegment* current = start;
  while (current != NULL)
  {
    current->position += p;    
    current = current->next;
  }
}

void CSnake::paint()
{
  CFramedWindow::paint();

  //przenieść \|/
  levelNOT = MAX_LEVEL - length + 52;
  levelNOT /= 3;
  if (levelNOT < 1) levelNOT = 1;
  if (levelNOT > MAX_LEVEL) levelNOT = MAX_LEVEL;

  gotoyx(geom.topleft.y - 1, geom.topleft.x);
  printl("|LEVEL %i|", MAX_LEVEL - levelNOT);

  if (help == 1)
  {
    paint_help();
    return;
  }

  unsigned int row = 0;
  for(int y = geom.topleft.y+1; y < geom.topleft.y + geom.size.y-1; y++, row++)
  {
    unsigned int letter = row * (geom.size.x-2);
    for (int x = geom.topleft.x+1; x < geom.topleft.x + geom.size.x-1; x++, letter++)
    {
      gotoyx(y, x);
      printl("%c", letter < text.size() ? text[letter] : c);
    }
  }

  gotoyx(position.y, position.x);
  char out = '@';

  switch (direction)
  {
    case 'a':
    out = '<';
    break;

    case 's':
    out = 'v';
    break;

    case 'd':
    out = '>';
    break;

    case 'w':
    out = '^';
    break;
  }
  printl("%c", out);

  SSegment* temp = start;
  while (temp != NULL)
  {
    for (int i = 1; i <= temp->length; i++)
    {
      //print segment
      switch(temp->direction)
      {
        case 'd':
        {
          gotoyx(temp->position.y, temp->position.x + i);
          printl("O");
        }
        break;

        case 'a':
        {
          gotoyx(temp->position.y, temp->position.x - i);
          printl("O");
        }
        break;
        
        case 's':
        {
          gotoyx(temp->position.y - i, temp->position.x);
          printl("O");
        }
        break;
        
        case 'w':
        {
          gotoyx(temp->position.y + i, temp->position.x);
          printl("O");
        }
        break;
      }
    }
    temp = temp->next;
  }

  gotoyx(food.y, food.x);
  printl("*");
}

void CSnake::paint_help()
{
  CFramedWindow::paint();

  unsigned int row = 0;
  for(int y = geom.topleft.y+1; y < geom.topleft.y + geom.size.y-1; y++, row++)
  {
    unsigned int letter = row * (geom.size.x-2);
    for (int x = geom.topleft.x+1; x < geom.topleft.x + geom.size.x-1; x++, letter++)
    {
      gotoyx(y, x);
      printl("%c", letter < text.size() ? text[letter] : c);
    }
  }

  gotoyx(geom.topleft.y + 2, geom.topleft.x + 2);
  printl("q - quit");

  gotoyx(geom.topleft.y + 3, geom.topleft.x + 2);
  printl("r - restart");

  gotoyx(geom.topleft.y + 4, geom.topleft.x + 2);
  printl("p - toggle pause");

  gotoyx(geom.topleft.y + 5, geom.topleft.x + 2);
  printl("h - toggle help");

  gotoyx(geom.topleft.y + 7, geom.topleft.x + 2);
  printl("arrows - move window");

  gotoyx(geom.topleft.y + 8, geom.topleft.x + 2);
  printl("awsd - move snake");

}