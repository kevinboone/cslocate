/*===========================================================================
  cslocate 
  area.h 
  Copyright (c)2019 Kevin Boone, GPL v3.0
===========================================================================*/

#pragma once

typedef struct _Area
  {
  char *regex;
  char *desc; 
  } Area;

extern Area areas[];
