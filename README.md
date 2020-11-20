# 3DTriangles

  Class TTriangles to load/save STL files
  ---------------------------------------
  https://en.wikipedia.org/wiki/STL_(file_format)

  Simple templated class to keep a surface as a set of 3D triangles represented by node coordinates <I>coords</I>
and connectivity array <I>corners</I> (3 coordinate indices for every triangle (face)). So, the
three coordinates for an i-th triangle can be extracted as

    coord0 = coords[corners[i * 3]];  
    coord1 = coords[corners[i * 3 + 1]];
    coord2 = coords[corners[i * 3 + 2]];
  
  Triangles can be loaded and saved from/into STL files. No checks about node numeration :
it is supposed that face normal is defined by counter-clockwise numeration of nodes when
looking from the normal sharp end (see faceNormal()).

  When loading, duplicate nodes are excluded with a tolerance and face corners renumbered.
The tolerance specified in loadSTL() is important, it must be large enough - it is
used in exclusion of duplicate coordinates. If tolerance too large, degenerated triangles 
may appear; if too small - duplicate nodes may not be all excluded.

  STL files in the binary form may contain multiple parts by simply glueing multiple STL files
together; there is a provision in the code for that; not well tested though. Binary STL
files contain floats in only 4-byte format.

  In text STL files the code selects proper number of digits in text representation for
templated float and double classes.

  Using fopen() on binary files is a little bit old, and VS compiler wants #define _CRT_SECURE_NO_WARNINGS
mentioned in defines.h. But text input uses fstream.

  Compiler
  --------
  VS 2019 with #define _CRT_SECURE_NO_WARNINGS in defines.h.

  Tests 
  -----
  for retrieving/saving STL files contents in TTriangles<T> class.

  NDEBUG excluded from Prepocessor definitions to make assert() working in Release.

  Test 1 tries to load two empty files. It must return false on operations.

  Test 2. <B>bricks.STL</B> file is loaded from current directory. It then save triangles in 

  - brick.bin.STL (binary STL)
  - brick.txt.STL (text STL)
  - brick.OBJ

  All files are written in current directory. Then the code loads the binary and text STL files
and compares loaded data with the original, loaded from brick.STL.
  In this specific case the TTriangles class must contain 152 nodes and 936 / 3 faces (triangles).
