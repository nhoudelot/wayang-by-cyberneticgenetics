#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "movements.h"

Movements *loadMovements(const char *filename){
   FILE *movefile;
   char  line[200];
   char *time;
   char *xpos;
   char *ypos;
   Movements *movements;
   long int linenum = 0;

   movements = malloc(sizeof(Movements));
   movements->pos = NULL;
   movements->starttime = 0;
   movements->size = 0;

   movefile = fopen(filename, "r");

   while(fgets(line, 200, movefile) != NULL){
      linenum++;
      /* We parse the input line */
      time = strtok(line, " \t\n");
      xpos = strtok(NULL, " \t\n");
      ypos = strtok(NULL, " \t\n");

      /* This is the first line */
      if(movements->starttime == 0){
         movements->starttime = atoi(time);
      }

      movements->pos = realloc(movements->pos, sizeof(Pos) * linenum);
      movements->pos[linenum-1].x = atof(xpos);
      movements->pos[linenum-1].y = atof(ypos);
   }
   movements->size = linenum;

   fclose(movefile);
   return(movements);
}

void freeMovements(Movements *move){
   free(move->pos);
   free(move);
}

float getMovementsX(Movements *move, unsigned long int time){
   return(move->pos[time - move->starttime].x);
}

float getMovementsY(Movements *move, unsigned long int time){
   return(move->pos[time - move->starttime].y);
}
