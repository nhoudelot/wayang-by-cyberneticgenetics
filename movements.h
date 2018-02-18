typedef struct Pos {
   float x;
   float y;
} Pos;

typedef struct Movements{
   unsigned long int starttime;
   unsigned long int size;
   Pos *pos;
} Movements;

Movements *loadMovements(const char *filename);
void freeMovements(Movements *move);
float getMovementsX(Movements *move, unsigned long int time);
float getMovementsY(Movements *move, unsigned long int time);
