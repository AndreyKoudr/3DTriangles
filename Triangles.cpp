#include "defines.h"
                              // class header
#include "Triangles.h"


std::string upCase(std::string str)
{
  std::transform(str.begin(),str.end(),str.begin(),::toupper);
  return str;
}

std::string trimLeft(std::string str, std::string chars)
{
  str.erase(0,str.find_first_not_of(chars));
  return str;
};

std::string trimRight(std::string str, std::string chars)
{
  str.erase(str.find_last_not_of(chars)+1);
  return str;
};

std::string trim(std::string str, std::string chars)
{
  return trimRight(trimLeft(str,chars),chars);
};

int parseWords(std::string str, char divider, int pos1[], int pos2[], int maxcount)
{
  int numwords = 0;
  int len = static_cast<int>(str.length());
  if (len > 0)
  {
		int curpos1 = NOT_DEFINED;
		if (str[0] != divider) curpos1 = 0;
		for (int i = 0; i < len; i++)
		{
			if (str[i] == divider)
      {
				if (curpos1 != NOT_DEFINED)
				{
          if (numwords < maxcount)
          {
            pos1[numwords] = curpos1;
            pos2[numwords] = i - 1;
					  curpos1 = NOT_DEFINED;
					  numwords++;
          } else
          {
            break;
          };
				};
			} else
			{
				if (curpos1 == NOT_DEFINED)
				{
          curpos1 = i;
				}
			}
		}

		if (curpos1 != NOT_DEFINED)
		{
      if (numwords < maxcount)
      {
        pos1[numwords] = curpos1;
        pos2[numwords] = len;
			  numwords++;
      }
		}
  }

  return numwords;
}
