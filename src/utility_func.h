
bool is_opposite_direction (char a, char b)
{
  if (a == 'a')
  {
    if (b == 'd') return true;
    else return false;
  }
  else if (a == 'w')
  {
    if (b == 's') return true;
    else return false;
  }
  else if (a == 's')
  {
    if (b == 'w') return true;
    else return false;
  }
  else if (a == 'd')
  {
    if (b == 'a') return true;
    else return false;
  }
  else return true;
}

char opposite (char a)
{
  if (a == 'a')
  {
    return 'd';
  }
  else if (a == 'w')
  {
    return 's';
  }
  else if (a == 's')
  {
    return 'w';
  }
  else if (a == 'd')
  {
    return 'a';
  }
  else return '\0';
}
