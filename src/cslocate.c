/*======================================================================
 * cslocate
 * cslocate.c 
 * Copyright (c)2019 Kevin Boone, GPL v3.0
 * =====================================================================*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>
#include "defs.h" 
#include "area.h" 
#include "cslocate.h" 

/*======================================================================
 * get_all_matches
 * Iterate the callsign specification table, and call the function
 *   cb for each potential match 
 * =====================================================================*/
void cslocate_get_all_matches (const char *_callsign,
     CallsignLookupCallback cb, void *user_data)
  {
  char *callsign = strdup (_callsign);
  int l = strlen (callsign);
  for (int i = 0; i < l; i++) callsign[i] = toupper (callsign[i]);

  int i = 0;
  Area *a = &areas[0];
  do
    {
    regex_t regex;
    int ret = regcomp(&regex, a->regex, 0);
    if (ret) 
      {
      // There isn't much we can do if the area data parser can't make
      //   a viable regular expression from the input data
      }
    else
      {
      regmatch_t pmatch;
      ret = regexec(&regex, callsign, 1, &pmatch, 0);
        {
        if (ret == 0) 
          {
          int len = pmatch.rm_eo;
          cb (callsign, a->desc, len, user_data);
          }
        }
      }
    i++;
    a = &areas[i]; 
    } while (a->regex); 
  free (callsign);
  }


/*======================================================================
 * get_best_match 
 * Gets the description from the callsign that corresponding to
 *   the longest matching regular expression
 * Caller should free the returned string, if non-null
 * =====================================================================*/
char *cslocate_get_best_match (const char *_callsign)
  {
  int i = 0;
  Area *a = &areas[0];
  int max_len = 0;
  char *best_desc = NULL;
  char *callsign = strdup (_callsign);
  int l = strlen (callsign);
  for (int i = 0; i < l; i++) callsign[i] = toupper (callsign[i]);
  do
    {
    regex_t regex;
    int ret = regcomp(&regex, a->regex, 0);
    if (ret) 
      {
      // There isn't much we can do if the area data parser can't make
      //   a viable regular expression from the input data
      }
    else
      {
      regmatch_t pmatch;
      ret = regexec(&regex, callsign, 1, &pmatch, 0);
        {
        if (ret == 0) 
          {
          int len = pmatch.rm_eo;
          if (len >= max_len)
            {
            max_len = len;
            if (best_desc) free (best_desc);
            best_desc = strdup (a->desc);
            }
          }
        }
      }
    i++;
    a = &areas[i]; 
    } while (a->regex); 
  free (callsign);
  return best_desc;
  }

#ifdef frig

BOOL cslocate_get_best_match (const char *callsign)
  {
  int i = 0;
  Area *a = &areas[0];
  int max_len = 0;
  const char *best_desc = NULL;
  BOOL matched = FALSE;

  do
    {
    regex_t regex;
    int ret = regcomp(&regex, a->regex, 0);
    if (ret) 
      {
      //fprintf(stderr, "Could not compile regex %s\n", a->regex);
      // There isn't much we can do if the area data parser can't make
      //   a viable regular expression from the input data
      }
    else
      {
      regmatch_t pmatch;
      ret = regexec(&regex, cs, 1, &pmatch, 0);
        {
        if (ret == 0) 
          {
          matched = TRUE;
          int len = pmatch.rm_eo;
          if (len >= max_len)
            {
            max_len = len;
            best_desc = a->desc;
            }
          if (show_all)
            {
            //printf ("Match %s, %s\n", a->regex, a->desc);
            printf ("%s: %s\n", cs, a->desc);
            }
          }
        }
      }
    i++;
    a = &areas[i]; 
    } while (a->regex); 
  if (matched)
    {
    if (!show_all)
      printf ("%s: %s\n", cs, best_desc);
    }
  else
    {
    fprintf (stderr, "%s: not matched: %s\n", argv[0], cs);
    }
  }


#endif 


