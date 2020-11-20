/**
Copyright 2020 Andrey Kudryavtsev (andrewkoudr@hotmail.com)

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted, provided
that the above copyright notice appears in all copies and that both the
copyright notice and this permission notice appear in supporting
documentation, and that the same name not be used in advertising or
publicity pertaining to distribution of the software without specific,
written prior permission. 
We make no representations about the suitability of this software for any 
purpose. It is provided "as is" without any expressed or implied warranty.
*/

#include "defines.h"
#include <iostream>
#include "Triangles.h"

using namespace std;

/**
  Compiler
  --------
  VS 2019 with #define _CRT_SECURE_NO_WARNINGS in defines.h.

  Tests 
  -----
  for retrieving/saving STL files contents in TTriangles<T> class.

  NDEBUG excluded from Prepocessor definitions to make assert() working in Release.

  Test 1 tries to load two empty files. It must return false on operations.

  Test 2. <B>bricks.STL</B> file is loaded from current directory. It then save triangles in 

  brick.bin.STL (binary STL)

  brick.txt.STL (text STL)

  brick.OBJ

  - all files are written in current directory. Then the code loads the binary and text STL files
and compares loaded data with the original, loaded from brick.STL.
  In this specific case the TTriangles class must contain 152 nodes and 936 / 3 faces (triangles).
*/

int main()
{
  cout << "Test 1 : reading empty STL files; there should be no crashes" << endl;
  {
    #define T float

    TTriangles<T> tris;
    string partname;
    bool binary;
                              // tolerance is very important : it must cover gaps
                              // between same nodes
    T tolerance = TOLERANCE(T) * T(100.0);

    bool ok1 = tris.loadSTL("empty0.STL",partname,binary,tolerance);
    assert(!ok1);

    bool ok2 = tris.loadSTL("empty1.STL",partname,binary,tolerance);
    assert(!ok2);

    #undef T
  }

  cout << "Test 2 : reading text STL and save it as binary and text files; read saved files and compare with orginal data" << endl;
  {
    #define T float

    TTriangles<T> tris;
    string partname;
    bool binary;
                              // tolerance is very important : it must cover gaps
                              // between same nodes
    T tolerance = TOLERANCE(T) * T(100.0);
    bool ok = tris.loadSTL("brick.STL",partname,binary,tolerance);

    if (ok)
    {
      bool ok1 = tris.saveSTL("brick.bin.STL",partname,true);
      bool ok2 = tris.saveSTL("brick.txt.STL",partname,false);
      bool ok3 = tris.saveOBJ("brick.OBJ",partname);

      // reload saved BINARY file, compare with origial data
      if (ok1)
      {
        TTriangles<T> tris1;
        string partname1;
        bool binary1;
        bool ok2 = tris1.loadSTL("brick.bin.STL",partname1,binary1,tolerance);
     
        if (ok2)
        {
          assert(binary1);
          assert(partname == partname1);
          assert(tris.coords.size() == tris1.coords.size());
          assert(tris.corners.size() == tris1.corners.size());
        } else
        {
          cout << "Could not load binary STL file from current directory" << endl;
        }
      } else
      {
        cout << "Could not save file in current directory" << endl;
      }

      // reload saved TEXT file, compare with origial data
      if (ok2)
      {
        TTriangles<T> tris1;
        string partname1;
        bool binary1;
        bool ok2 = tris1.loadSTL("brick.txt.STL",partname1,binary1,tolerance);
     
        if (ok2)
        {
          assert(!binary1);
          assert(partname == partname1);
          assert(tris.coords.size() == tris1.coords.size());
          assert(tris.corners.size() == tris1.corners.size());
        } else
        {
          cout << "Could not load binary STL file from current directory" << endl;
        }
      } else
      {
        cout << "Could not save file in current directory" << endl;
      }
    } else
    {
      cout << "Could not find file brick.STL in current directory" << endl;
    }

    #undef T
  }

  printf("\n");
  printf("Press [ENTER]\n");

  getchar();
}
