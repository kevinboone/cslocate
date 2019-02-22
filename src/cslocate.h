/*===========================================================================
  cslocate 
  defs.h 
  Copyright (c)2019 Kevin Boone, GPL v3.0
===========================================================================*/

#pragma once
#include "defs.h"

/* A callback function called by cslocate_get_all_matches as
 *   it iterates the table of callsign specifications. The
 *   'len' argument is the number of characters in callsign
 *   that match the spec -- more is usually better */
typedef void (*CallsignLookupCallback)(const char *callsign, 
          const char *desc, int len, void *user_data);

/* Get the callsign description that is the best (largest number
 *   of matching characters) to the callsign */
char *cslocate_get_best_match (const char *callsign);

/* Iterate the callsign specification table, and call the function
 *   cb for each potential match */
void  cslocate_get_all_matches (const char *_callsign,
         CallsignLookupCallback cb, void *user_data);

