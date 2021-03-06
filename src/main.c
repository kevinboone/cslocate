/*======================================================================
 * cslocate
 * main.c 
 * Copyright (c)2019 Kevin Boone, GPL v3.0
 * =====================================================================*/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>
#include "defs.h" 
#include "area.h" 
#include "cslocate.h" 

/* Try to extract just the country part from the description field.
 *   This is generally not very reliable, as the data in the regions
 *   table was not really designed to be parsed this way */
void truncate_to_country (char *desc)
  {
  char *p = strchr (desc, ',');
  if (p) *p = 0; 
  p = strstr (desc, " -");
  if (p) *p = 0;
  p = strstr (desc, " VHF C");
  if (p) *p = 0;
  }

/* Callback function for cslocate_get_all_matches -- just
 *   dump the data */
void lookup_callback (const char *callsign, const char *desc, 
     int len, void *user_data)
  {
  printf ("%s: (%d) %s\n", callsign, len, desc);
  }

/* Start here */
int main (int argc, char **argv)
  {
  BOOL show_version = FALSE;
  BOOL show_usage = FALSE;
  BOOL show_all = FALSE;
  BOOL quiet = FALSE;

  static struct option long_options[] = 
   {
     {"version", no_argument, NULL, 'v'},
     {"all", no_argument, NULL, 'a'},
     {"help", no_argument, NULL, '?'},
     {"quiet", no_argument, NULL, 'q'},
     {0, 0, 0, 0}
   };

  int opt;
  while (1)
   {
   int option_index = 0;
   opt = getopt_long (argc, argv, "v?aq",
     long_options, &option_index);

   if (opt == -1) break;

   switch (opt)
     {
     case 0:
        if (strcmp (long_options[option_index].name, "version") == 0)
          show_version = TRUE;
        else if (strcmp (long_options[option_index].name, "help") == 0)
          show_usage = TRUE;
        else if (strcmp (long_options[option_index].name, "all") == 0)
          show_all = TRUE;
        else if (strcmp (long_options[option_index].name, "quiet") == 0)
          quiet = TRUE;
	else
          exit (-1);
        break;

     case 'v': show_version = TRUE; break;
     case '?': show_usage = TRUE; break;
     case 'a': show_all = TRUE; break;
     case 'q': quiet = TRUE; break;
     default:  exit(-1);
     }
   }

  if (show_usage)
    {
    printf ("Usage %s [options]\n", argv[0]);
    printf ("  -a, --all       show all matches\n");
    printf ("  -q, --quiet     print only country\n");
    printf ("  -v, --version   show version information\n");
    printf ("  -?              show this message\n");
    exit (0);
    }
 
  if (show_version)
    {
    printf ("cslocate " VERSION "\n");
    printf ("Copyright (c)2019 Kevin Boone\n");
    printf ("Distributed according to the terms of the GPL, v3.0\n");
    exit (0);
    }

  int args = argc - optind;

  if (args == 0)
    {
    printf ("A callsign must be specified\n");
    exit (-1);
    }

  const char *cs = argv[optind];
  
  if (show_all)
    {
    cslocate_get_all_matches (cs, lookup_callback, NULL);
    }
  else
    {
    char *desc = cslocate_get_best_match (cs);
    if (desc)
      {
      if (quiet)
        {
        truncate_to_country (desc); 
        printf ("%s\n", desc);
        }
      else
        printf ("%s: %s\n", cs, desc);
      free (desc);
      }
    else
      {
      fprintf (stderr, "%s: not matched: %s\n", argv[0], cs);
      }
    }
  return 0;
  }

