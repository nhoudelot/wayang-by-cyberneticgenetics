#include <SDL.h>
#include <math.h>
#include "movements.h"
#include "wayang.h"

#define MAXCLOUDS  7

#define FIRST_HIT  105666
#define SECOND_HIT 109058
#define THIRD_HIT  112501

#define ARROW_SPEED 600.0

Mesh3D *sita         = NULL;
Mesh3D *sita_arm     = NULL;
Mesh3D *logo         = NULL;
Mesh3D *clouds[]     = {NULL, NULL, NULL, NULL};
Mesh3D *cloud1       = NULL;
Mesh3D *cloud2       = NULL;
Mesh3D *cloud3       = NULL;
Mesh3D *cloud4       = NULL;
Mesh3D *tree         = NULL;
Mesh3D *tree2        = NULL;
Mesh3D *tree3        = NULL;
Mesh3D *ravana       = NULL;
Mesh3D *sword        = NULL;
Mesh3D *couch        = NULL;
Mesh3D *horse        = NULL;
Mesh3D *jatajus      = NULL;
Mesh3D *leftwing     = NULL;
Mesh3D *rightwing    = NULL;
Mesh3D *arrow        = NULL;
Mesh3D *hand         = NULL;
Mesh3D *arm          = NULL;
Mesh3D *humerus      = NULL;
Mesh3D *small_tree[] = {NULL, NULL, NULL};
Mesh3D *stick        = NULL;
Mesh3D *eyelip       = NULL;

GLuint canvas;
GLuint endscroll;

Movements *sita_move;
Movements *ravana_move;
Movements *ravana_sita_move;
Movements *ravana_couch;
Movements *flying_couch;
Movements *jatajus_move;
Movements *jatajus_attack;
Movements *ravana_attack;
Movements *jatajus_fight;

/* initialize meshes, textures, sounds */
void init_wayang(){

   canvas           = loadPNGTexture("/usr/share/wayang-by-cyberneticgenetics/data/canvas.png");
   endscroll        = loadPNGTexture("/usr/share/wayang-by-cyberneticgenetics/data/end.png");

   sita             = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/sita.obj");
   sita_arm         = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/sita_arm.obj");
   logo             = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/logo.obj");
   clouds[0]        = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/cloud1.obj");
   clouds[1]        = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/cloud2.obj");
   clouds[2]        = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/cloud3.obj");
   clouds[3]        = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/cloud4.obj");
   tree             = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/tree.obj");
   tree2            = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/tree2.obj");
   tree3            = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/tree3.obj");
   ravana           = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/ravana.obj");
   stick            = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/stick.obj");
   sword            = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/sword.obj");
   couch            = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/couch.obj");
   horse            = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/horse.obj");
   jatajus          = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/jatajus.obj");
   leftwing         = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/leftwing.obj");
   rightwing        = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/rightwing.obj");
   eyelip           = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/jatajus_eyelip.obj");
   arrow            = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/arrow.obj");
   hand             = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/hand.obj");
   arm              = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/lowarm.obj");
   humerus          = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/humerus.obj");

   /* Deadline is comming, no optimization */
   /* This trees are smaller, have lower alpha value */
   small_tree[0]    = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/tree.obj");
   small_tree[1]    = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/tree2.obj");
   small_tree[2]    = loadOBJ("/usr/share/wayang-by-cyberneticgenetics/data/tree3.obj");

   changeMeshColor(clouds[0], 1.0f, 1.0f, 1.0f, 0.2f);
   changeMeshColor(clouds[1], 1.0f, 1.0f, 1.0f, 0.2f);
   changeMeshColor(clouds[2], 1.0f, 1.0f, 1.0f, 0.2f);
   changeMeshColor(clouds[3], 1.0f, 1.0f, 1.0f, 0.2f);

   changeMeshColor(small_tree[0], 1.0f, 1.0f, 1.0f, 0.2f);
   changeMeshColor(small_tree[1], 1.0f, 1.0f, 1.0f, 0.2f);
   changeMeshColor(small_tree[2], 1.0f, 1.0f, 1.0f, 0.2f);

   sita_move        = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/sita_move.txt");
   ravana_move      = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/ravana_move.txt");
   ravana_sita_move = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/ravana_with_sita_move.txt");
   ravana_couch     = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/ravana_couch_move.txt");
   flying_couch     = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/couch_move.txt");
   jatajus_move     = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/jatajus_move.txt");
   jatajus_attack   = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/jatajus_attack_move.txt");
   ravana_attack    = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/ravana_attack_move.txt");
   jatajus_fight    = loadMovements("/usr/share/wayang-by-cyberneticgenetics/data/jatajus_fight_move.txt");
}

/* free all resources */
void free_wayang(){
   freeMesh3D(sita);
   freeMesh3D(sita_arm);
   freeMesh3D(logo);
   freeMesh3D(clouds[0]);
   freeMesh3D(clouds[1]);
   freeMesh3D(clouds[2]);
   freeMesh3D(clouds[3]);
   freeMesh3D(tree);
   freeMesh3D(tree2);
   freeMesh3D(tree3);
   freeMesh3D(ravana);
   freeMesh3D(stick);
   freeMesh3D(sword);
   freeMesh3D(couch);
   freeMesh3D(horse);
   freeMesh3D(jatajus);
   freeMesh3D(leftwing);
   freeMesh3D(rightwing);
   freeMesh3D(eyelip);
   freeMesh3D(arrow);
   freeMesh3D(hand);
   freeMesh3D(arm);
   freeMesh3D(humerus);
   freeMesh3D(small_tree[0]);
   freeMesh3D(small_tree[1]);
   freeMesh3D(small_tree[2]);

   freeMovements(sita_move);
   freeMovements(ravana_move);
   freeMovements(ravana_sita_move);
   freeMovements(ravana_couch);
   freeMovements(flying_couch);
   freeMovements(jatajus_move);
   freeMovements(ravana_attack);
   freeMovements(jatajus_fight);
}

/* EFFECTS */
void zoomTo(float x, float y, float width, float percentage){
   float original_x     = -2000.0f;
   float original_y     = -1500.0f;
   float original_width = 4000.0f;
   float aspect_ration  = 3.0f/4.0f;

   float actual_minx, actual_maxx, actual_miny, actual_maxy;

   actual_minx = original_x + ( (x - original_x) * percentage);
   actual_miny = original_y + ( (y - original_y) * percentage);
   actual_maxx = actual_minx + original_width - (original_width - width) * percentage;
   actual_maxy = actual_miny + original_width * aspect_ration - (original_width - width) * percentage * aspect_ration;

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho( actual_minx, actual_maxx, actual_miny, actual_maxy, -800.0f, 800.0f);
}
/* END EFFECTS */

/* ATOMIC DRAWING UNITS */

/* This function draw the canvas and the red light */
void drawCanvas(){

   glBindTexture(GL_TEXTURE_2D, canvas);
   glPushMatrix();
   glBegin(GL_QUADS);
   glTexCoord2f(0.0,0.0);
   glVertex3f(-2000.0, -1500.0, -600.0);
   glTexCoord2f(0.0,1.0);
   glVertex3f(-2000.0,  1500.0, -600.0);
   glTexCoord2f(1.0,1.0);
   glVertex3f( 2000.0,  1500.0, -600.0);
   glTexCoord2f(1.0,0.0);
   glVertex3f( 2000.0, -1500.0, -600.0);
   glEnd();
   glPopMatrix();

}

void EndScroll(Uint32 time){
   glBindTexture(GL_TEXTURE_2D, endscroll);
   glPushMatrix();
   glColor4f(1.0,1.0,1.0,1.0);
   glTranslatef(0.0,-14000.0 + (float)(time - 181990),0.0);
   glBegin(GL_QUADS);
     glTexCoord2f(0.0, 0.0);
     glVertex3f(-2000.0, -1500.0, -70.0);

     glTexCoord2f(0.0, 1.0);
     glVertex3f(-2000.0,  13000.0, -70.0);

     glTexCoord2f(1.0, 1.0);
     glVertex3f( 2000.0,  13000.0, -70.0);

     glTexCoord2f(1.0, 0.0);
     glVertex3f( 2000.0, -1500.0, -70.0);
   glEnd();
   glPopMatrix();
}

/* Pupet control drawing */
void drawRavanaStick(float posx, float posy){

      glPushMatrix();
        glTranslatef(posx + 1250.0, 0.0, posy - 1370.0);
        drawMesh3D(stick);
      glPopMatrix();

}

void drawSitaStick(float posx, float posy){

      glPushMatrix();
         glTranslatef(posx - 1335.0, 0.0, posy - 1500.0);
         drawMesh3D(stick);
      glPopMatrix();

}

/* Ravan with his sword. Later we can animate Ravana with xxx_angle variables */
void drawRavana(float posx, float posy, float humerus_angle, float arm_angle, float hand_angle, int hassword){

   glPushMatrix();

   glTranslatef(posx, 0.0f, posy);              /* Position of the whole Ravana */
   drawMesh3D(ravana);

   /* Humerus drawing */
   glTranslatef(1090.0f,0.0f,330.0f);           /* Connect the hand to the body */
   glRotatef(180.0f, 0.0f, 0.0f, 1.0f);         /* Correct the hand orientation */
   glRotatef( humerus_angle, 0.0f, 1.0f, 0.0f); /* Rotate shoulders*/
   glTranslatef(-640.0f,0.0f,-540.0f);          /* Set the rotation center*/
   drawMesh3D(humerus);

   /* Arm drawing */
   glTranslatef(650.0f,0.0f,270.0f);
   glRotatef( arm_angle, 0.0f, 1.0f, 0.0f);
   glTranslatef(-640.0f,0.0f,-250.0f);
   drawMesh3D(arm);

   /* Hand drawing */
   glTranslatef(660.0f,0.0f,0.0f);
   glRotatef( hand_angle, 0.0f, 1.0f, 0.0f);
   glTranslatef(-660.0f,0.0f,0.0f);
   drawMesh3D(hand);

   /* Sword drawing */
   if(hassword){
      glTranslatef(-990.0f,0.0f, 230.0f);
      glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
      glRotatef(120.0,0.0f,1.0f,0.0f);
      glTranslatef(-2750.0f,0.0f,1040.0f);
      drawMesh3D(sword);
   }

   glPopMatrix();
}

void drawJatajus(float posx, float posy, int mode, Uint32 time){
   static Uint32 prev_time  = 0;
   static float angle       = 40.0f;
   static float orientation = 1.0f;
   static float speed       = 5.0f;
   float d;


   glPushMatrix();
   glTranslatef(posx,0.0f,posy);
   drawMesh3D(jatajus);

   if(mode == WITH_WINGS){
      /* static drawing, nothing more */
      drawMesh3D(leftwing);
      drawMesh3D(rightwing);
   }
   else if(mode == FLY){
      /* move the wings to fly */
      d = ((float)(time - prev_time) / speed) * orientation ;
      angle += d;

      /* set the orientation and speed of the wings */
      if(angle >  40.0f) {
         orientation = -1.0f;
         speed       = 2.0f;
         angle       = 40.0f;
      }
      if(angle < -40.0f){
         orientation =  1.0f;
         speed       =  5.0f;
         angle       = -40.0f;
      }

      /* draw the left wing */
      glPushMatrix();
        glTranslatef(-300.0f,0.0f,-20.0f);
        glRotatef(angle, 0.0, 1.0, 0.0);
        glTranslatef(240.0f,0.0,15.0f);
        drawMesh3D(leftwing);
      glPopMatrix();

      /* draw the right wing */
      glPushMatrix();
        glRotatef(angle * -1.0f, 0.0, 1.0, 0.0);
        drawMesh3D(rightwing);
      glPopMatrix();
   }

   glPopMatrix();
   prev_time = time;
}

/* END OF ATOMIC DRAWING UNITS */

/* BASIC MOVEMENTS */

void RavanaStick(float x, float y, float percentage){
   float huma, arma, hana;

   if(percentage > 1.0f) percentage = 1.0f;
   if(percentage < 0.0f) percentage = 0.0f;

   huma =  0.0f  - (80.0f * percentage);
   arma = -90.0f + (80.0f * percentage);
   hana =  110.0f;

   drawRavana(x,y,huma,arma,hana,WITH_SWORD);
}

void RavanaStrike(float x, float y, float percentage){
   float huma, arma, hana;

   if(percentage > 1.0f) percentage = 1.0f;
   if(percentage < 0.0f) percentage = 0.0f;

   huma = -140.0f + (90.0f * percentage);
   arma = -50.0f  - (30.0f * percentage);
   hana = -10.0f  + (90.0f * percentage);

   drawRavana(x,y,huma,arma,hana,WITH_SWORD);
}

void RavanaStick2Strike(float x, float y, float percentage){
   float huma, arma, hana;

   if(percentage > 1.0f) percentage = 1.0f;
   if(percentage < 0.0f) percentage = 0.0f;

   huma = -80.0f  - (60.0f * percentage);
   arma = -10.0f  - (40.0f * percentage);
   hana =  110.0f - (120.0f * percentage);

   drawRavana(x,y,huma,arma,hana,WITH_SWORD);
}

void RavanaStrike2Stick(float x, float y, float percentage){
   float huma, arma, hana;

   if(percentage > 1.0f) percentage = 1.0f;
   if(percentage < 0.0f) percentage = 0.0f;

   huma = -50.0f  + (50.0f * percentage);
   arma = -80.0f  - (10.0f * percentage);
   hana =  80.0f  + (30.0f * percentage);

   drawRavana(x,y,huma,arma,hana,WITH_SWORD);
  
}

void ArrowFly(Uint32 start, Uint32 time, ArrowParams ap, float x, float y){
   float arrow_x, arrow_y;

   if(time - start < ARROW_SPEED){
      /* If the arrow not hit Jatajus calculate the fly */
      arrow_x = ap.start_x + (ap.end_x - ap.start_x) * 
                (float)(time - start) / ARROW_SPEED;
      arrow_y = ap.start_y + (ap.end_y - ap.start_y) *
                (float)(time - start) / ARROW_SPEED;
   }
   else{
      /* Arrow hit Jatajus, so the arrow movin with his */
      arrow_x = x;
      arrow_y = y;
   }

   glPushMatrix();
     glTranslatef(arrow_x * -1.0f,0.0f,arrow_y);
     glRotatef(ap.angle,0.0,1.0,0.0);
     glTranslatef(-1575.0f, 0.0f, -450.0f);
     drawMesh3D(arrow);
   glPopMatrix();
}

void PanningClouds(Uint32 time){
   static float xpos[MAXCLOUDS] = {  710.0, -770.0f,-1720.0f,-1295.0f, 1570.0, 1580.0, -250.0};
   static float ypos[MAXCLOUDS] = { -765.0, 1165.0f,  800.0f,-1205.0f,  895.0,-1345.0, -660.0};
   float speeds[MAXCLOUDS]      = {1.0, 2.0, 10.0, 0.7, 1.2, 1.6, 15.0};
   static Uint32 prev_time = 0;
   int i;

   /* Initialization. */
   if(prev_time == 0) prev_time = time;

   for(i = 0; i < MAXCLOUDS; i++){

      xpos[i] += (float)(time - prev_time) / speeds[i];

      if(xpos[i] > 3500.0f) xpos[i] = -2200.0f;

      glPushMatrix();
        glTranslatef(xpos[i], 0.0f, ypos[i]);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        drawMesh3D(clouds[i & 3]);
      glPopMatrix();

   }

   /* Very important time syncronization step */
   prev_time = time;

}

/* END OF BASIC MOVEMENTS */

/* EPISODES OF THE STORY */


void PanningForest(Uint32 time){

   static float tree_positions[20] = {4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300,-4300};
   static Uint32 start_times[10]   = {0,0,0,0,0,0,0,0,0,0};
   static Uint32 previous_tree_start_time = 0;
   static float small_tree_pos[] = {-2795.0, -1325.0, -4700.0, -1330.0, -6700.0, -1320.0};
   static Uint32 prev_time = 5000;
   int i;

   for(i = 0; i < 10; i++){

      if(tree_positions[i * 2] > 2000.0){
         if(time > 30618) continue; /* no more trees */
         if((time - previous_tree_start_time) > (3000 + drand48() * 900)){
            tree_positions[i * 2]     = -4300.0f;
            tree_positions[i * 2 + 1] = drand48() * 200.0f - 1420.0f;
            start_times[i] = time;
            previous_tree_start_time = time;
         }
         continue;
      }

      glPushMatrix();
      tree_positions[i * 2] += (time - start_times[i]) / 2.0;
      start_times[i] = time;
      glTranslatef(tree_positions[i * 2], 0.0f, tree_positions[i * 2 + 1]);
      if(i == 0 || i == 2 || i == 5 || i == 6){
         drawMesh3D(tree);
      }
      else if(i == 1 || i == 4 || i == 8){
         glPushMatrix();
         glRotatef(270.0, 1.0, 0.0, 0.0);
         drawMesh3D(tree2);
         glPopMatrix();
      }
      else {
         glPushMatrix();
         glRotatef(270.0, 1.0, 0.0, 0.0);
         drawMesh3D(tree3);
         glPopMatrix();
      }
      glPopMatrix();

   }

   /* Small trees */
   for(i = 0; i < 3; i++){
      small_tree_pos[i*2] += (float)(time - prev_time) / 4.0f;
      glPushMatrix();
        glTranslatef(small_tree_pos[i*2],0.0,small_tree_pos[i*2+1]);
        glScalef(0.5, 0.5, 0.5);
        /* I hate these meshes. Next time my meshes will be directed the same way */
        if(i > 0) glRotatef(270.0, 1.0, 0.0, 0.0);
        drawMesh3D(small_tree[i]);
      glPopMatrix();
   }
   prev_time = time;
}


void SitaAndRavanaMeetInTheForest(Uint32 time){

      /* Sita and Ravana meet in the forest */
      drawSitaStick(getMovementsX(sita_move, time), getMovementsY(sita_move, time));
      glPushMatrix();
        glTranslatef(getMovementsX(sita_move, time), 0.0f, getMovementsY(sita_move, time));
        drawMesh3D(sita);
        drawMesh3D(sita_arm);
      glPopMatrix();

      drawRavanaStick(getMovementsX(ravana_move, time), getMovementsY(ravana_move, time));
      drawRavana(getMovementsX(ravana_move, time), getMovementsY(ravana_move, time), 340, 340, 340, WITHOUT_SWORD);

      glPushMatrix();
        glTranslatef(550.0,0.0f,-1295.0);
        drawMesh3D(tree);
      glPopMatrix();

      glPushMatrix();
        glTranslatef(-2625.0,0.0f,-1295.0);
        glRotatef(180.0, 0.0, 0.0, 1.0);
        glTranslatef(-2240.0f,0.0f,-25.0f);
        drawMesh3D(tree);
      glPopMatrix();
}

void JatajusWakeUp(Uint32 start, Uint32 time){
   float angle;
   float percent = ((float)(time - start) / 2000.0f);

   if(percent > 1.0) percent = 1.0;
   if(percent < 0.0) percent = 0.0;

   glPushMatrix();
     glTranslatef(-790.0,0.0,-535.0);
     glRotatef(180.0, 0.0, 0.0, 1.0);
     angle = 40.0 * percent;
     glRotatef(angle, 0.0, 1.0, 0.0);
     drawJatajus(350.0f,-130.0f,WITHOUT_WINGS, time);
   glPopMatrix();
}


void RavanaTakeOnToHisCouch(Uint32 time){
   /* We use this variable, to delay Sita's movements */
   Uint32 delay;

   /* Couch drawing */
   glPushMatrix();
     glTranslatef(490.0f,0.0f,-1195.0f);
     drawMesh3D(couch);
     drawMesh3D(horse);
   glPopMatrix();

   /* Ravana movement settings */
   glPushMatrix();
     glRotatef(180.0f, 0.0,0.0,1.0);
     drawRavanaStick(getMovementsX(ravana_sita_move, time), getMovementsY(ravana_sita_move, time));
     drawRavana(getMovementsX(ravana_sita_move, time),
                getMovementsY(ravana_sita_move, time),
                290,340,340,WITHOUT_SWORD);
   glPopMatrix();

   /* Sita movements settings */
   /* With this trick we use one movement file to control two mesh */
   if(ravana_sita_move->starttime + 150 < time){
      delay = time - 150;
   }
   else{
      delay = time;
   }

   drawSitaStick(800.0f - getMovementsX(ravana_sita_move, delay), getMovementsY(ravana_sita_move, delay));

   glPushMatrix();
     glTranslatef(800.0 - getMovementsX(ravana_sita_move, delay),
                   0.0,
                  getMovementsY(ravana_sita_move, delay));
     drawMesh3D(sita);
     drawMesh3D(sita_arm);
   glPopMatrix();

}

void JatajusOpenWideWings(Uint32 time){
   float angle;

   glPushMatrix();

     glTranslatef(350.0f, 0.0f, -130.0f);
     drawMesh3D(jatajus);

     angle = -60.0f + (float)(time - 82255) / 60.0f;

     glPushMatrix();
       glTranslatef(-300.0f, 0.0f, -20.0f);
       glRotatef(angle, 0.0, 1.0, 0.0);
       glTranslatef(240.0f ,0.0f, 15.0f);
       drawMesh3D(leftwing);
     glPopMatrix();

     glPushMatrix();
       glRotatef(angle * -1.0f, 0.0, 1.0, 0.0);
       drawMesh3D(rightwing);
     glPopMatrix();

   glPopMatrix();
}

void CouchOfRavanaIsFly(Uint32 time){
   glPushMatrix();
     glTranslatef(490.0f, 0.0f, -1196.0f);
     drawMesh3D(couch);
     drawMesh3D(horse);
   glPopMatrix();

   glPushMatrix();
     drawRavana(getMovementsX(ravana_couch, time),
                getMovementsY(ravana_couch, time),340,340,340,WITHOUT_SWORD);
   glPopMatrix();
}

void JatajusFollowTheCouch(Uint32 time){
   int i;
   float jatajus_x, jatajus_y, ravana_x, ravana_y;
   Uint32 hit_times[3] = {FIRST_HIT,SECOND_HIT,THIRD_HIT};
   static int parameter_lock[3] = {0,0,0};
   static ArrowParams arrows[3];


   /*Jatajus*/
   jatajus_x = 1035.0;
   jatajus_y = getMovementsY(jatajus_move, time);
   glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
   drawJatajus(jatajus_x, jatajus_y, FLY, time);

   /*Ravana and his couch*/
   glPushMatrix();
     glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
     ravana_x = getMovementsX(flying_couch, time);
     ravana_y = getMovementsY(flying_couch, time);

     glTranslatef(ravana_x,0.0,ravana_y);
     drawMesh3D(couch);
     drawMesh3D(horse);
     drawRavana(-2065.0f,565.0f,340,340,340,WITHOUT_SWORD);
   glPopMatrix();

   /* Arrows hit body of jatajus */
   for(i = 0; i < 3; i++){

      if(time > hit_times[i]){
         if(parameter_lock[i] == 0){
            /* We lock the arrow fly parameters */
            parameter_lock[i] = 1;
            arrows[i].start_x = ravana_x;
            arrows[i].start_y = ravana_y;
            arrows[i].end_x   = jatajus_x - 1820.0;/*Some offset. We do not want to hit the center of the mesh*/
            arrows[i].end_y   = jatajus_y - 150.0;
            arrows[i].angle   = 360.0 - (atanf( (arrows[i].start_x - arrows[i].end_x) / 
                                                (arrows[i].start_y - arrows[i].end_y)) / 
                                         M_PI * 180.0);
         }
         else{
            /*ArrowFly is an automatic arrow drawing unit*/
            ArrowFly(hit_times[i], time, arrows[i], jatajus_x - 1820.0f, jatajus_y - 150.0);
         }
      }

   }

   /* Moving clouds on the background */
   PanningClouds(time);
}

void JatajusAttackTheHorse(Uint32 time){
  glPushMatrix();
    drawJatajus(getMovementsX(jatajus_attack,time),
                getMovementsY(jatajus_attack,time),WITHOUT_WINGS,time);
  glPopMatrix();

  glPushMatrix();
     glTranslatef(-480.0f,0.0f,190.0f);
     drawMesh3D(horse);
  glPopMatrix();
}

void FallingCouch(Uint32 time){
   float x,y;

   x = -2385.0 + (1570.0 + 2385.0) * (float)(time - 119254) / 6700.0f;
   y = 1480.0 + (-1460.0 - 1480.0) * (float)(time - 119254) / 6700.0f;

   glPushMatrix();
      glTranslatef(x,0.0f,y);
      glRotatef(40.0f, 0.0f, 1.0f, 0.0f);
      drawMesh3D(couch);
      drawMesh3D(horse);
      drawRavana(-2065.0f,565.0f,340,340,340,WITHOUT_SWORD);
   glPopMatrix();

   glPushMatrix();
     glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
     PanningClouds(time);
   glPopMatrix();
}

void FightInTheGround(Uint32 time){
   float rx, ry;
   /* Couch */
   glPushMatrix();
     glTranslatef(2055.0f,0.0f,-1625.0f);
     glRotatef(40.0f, 0.0f, 1.0f, 0.0f);
     drawMesh3D(couch);
   glPopMatrix();

   /* Sita */
   glPushMatrix();
     glTranslatef(-340.0f,0.0,-1120.0f);
     drawMesh3D(sita);
     drawMesh3D(sita_arm);
   glPopMatrix();

   rx = getMovementsX(ravana_attack, time);
   ry = getMovementsY(ravana_attack, time);

   drawRavanaStick(rx, ry);

   if(time > 127713 && time < 128213){
      RavanaStick(rx,ry, (float)(time - 127713) / 300.0);
   }
   else if(time > 128213 && time < 128713){
      RavanaStick(rx, ry, 1.0 - ((float)(time - 128213) / 300.0));
   }
   else if(time > 129500 && time < 130000){
      RavanaStick2Strike(rx, ry, (float)(time - 129500) / 300.0);
   }
   else if(time > 130000 && time < 131500){
      RavanaStrike(rx, ry, (float)(time - 130000) / 300.0);
   }
   else if(time > 131500 && time < 132000){
      RavanaStrike2Stick(rx, ry, ((float)(time - 131500) / 300.0));
   }
   else if(time > 133000 && time < 133300){
      RavanaStick2Strike(rx, ry, ((float)(time - 133000) / 300.0));
   }
   else if(time > 133300 && time < 133600){
      RavanaStrike(rx, ry, ((float)(time - 133300) / 300.0));
   }
   else if(time > 133600 && time < 133900){
      RavanaStrike2Stick(rx, ry, ((float)(time - 133300) / 300.0));
   }
   else
      drawRavana(rx, ry, 0.0f, -90.0f, 110.0f,WITH_SWORD);


   glRotatef(180.0f, 0.0f, 0.0f, 1.0f);
   drawJatajus(getMovementsX(jatajus_fight, time), getMovementsY(jatajus_fight, time), FLY, time);
}

void FatalStrike(Uint32 time){
   if(time < 136534)
      RavanaStrike(-1044.0, -1189.0, (float)(time - 135234) / 1300.0);
   else
      RavanaStrike2Stick(-1044.0, -1189.0, (float)(time - 136534) / 1300.0);
}

void LoosingWings(Uint32 time){
   glTranslatef(-160.0,0.0, 2000.0 - (float)(time - 137000) / 5.0f);
   glRotatef((time - 137000) / 10.0, 0.0, 1.0, 0.0);
   glTranslatef(365.0,0.0,-10.0);
   drawMesh3D(leftwing);
}

void DyingJatajus(Uint32 time){
   float cloudpos[] = {-555.0f, 570.0f, 755.0f, 845.0f, -1470.0f, 1085.0f, -1505.0f, -180.0f};
   int i;
   float openeye;

   if(time > 145724 && time < 149084)  openeye = -175.0 + (float)(time - 145724) / 45.0;
   if(time > 149084 && time < 152444)  openeye = -113.2 - (float)(time - 149084) / 54.36;
   if(time > 152444 && time < 155805)  openeye = -175.0 + (float)(time - 152444) / 37.33;

   if(time > 155805) openeye = -85.0f; /* The eye is closed */

   glPushMatrix();
     glTranslatef(2055.0f,0.0f,-1625.0f);
     glRotatef(40.0f, 0.0f, 1.0f, 0.0f);
     drawMesh3D(couch);
   glPopMatrix();

   glPushMatrix();
     glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
     /* Eye of the volture */
     glPushMatrix();
       glTranslatef(1431.0f, 0.0f, 358.0f);
       glRotatef(openeye, 1.0f, 0.0f, 0.0f);
       glTranslatef(-135.0f, -385.0f, 0.0f);
       drawMesh3D(eyelip);
     glPopMatrix();

     drawJatajus(1475.0f, -40.0f, WITHOUT_WINGS, time);
   glPopMatrix();

   /* Draw clouds */
   for(i = 0; i < 4; i++){

      glPushMatrix();
        glTranslatef(cloudpos[i*2],0.0f,cloudpos[i*2+1]);
        glRotatef(90.0, 1.0, 0.0, 0.0);
        drawMesh3D(clouds[i]);
      glPopMatrix();

   }

   /* Cutted wing */
   glTranslatef(-375.0,0.0,-1470.0);
   drawMesh3D(leftwing);
}

/* END OF EPISODES OF THE STORY */

/* MAIN SCENE

   This is the main drawing and syncronising unit 
   In this function we create the whole scene.
*/

void show_wayang(Uint32 time){
   float p; /*percentage for zoom effect*/

   /* Zoom effect sould be the first */
   if(time > 82255 && time < 85671){
      /* Zoom to Jatajus when open wide his wigs */
      zoomTo(-440.0,-525.0,1400.0,1.0);
   } 
   else if(time > 75232 && time < 77232){
      /* Zoom to head of Jatajus */
      zoomTo(-1390.0f,-755.0f,700.0,1.0);
   }
   else if(time > 117047 && time < 119254){
      /*Jatajus hit the eye of the horse*/
      zoomTo(555.0f, 205.0f, 700.0f, 1.0f);
   }
   else if(time > 135234 && time < 138000){
      /* You can see the fatal strike */
      zoomTo(-780.0, -885.0, 700.0, 1.0);
   }
   else if(time > 138000 && time < 145724){
      /* Jatajus loose his wings */
      zoomTo(-470.0, 775, 700.0, 1.0);
   }
   else if(time > 145724 && time < 155805){
      /* Jatajus close his eyes */
      zoomTo(-95.0f, -1500.0f, 700.0f, 1.0f);
   }
   else if(time > 155805 && time < 181990){
      /* Zoom out from the dead Jatajus */
      p = 1.0f - (float)(time - 155805) / 26185.0f;
      if(p < 0.0f) p = 0.0f;
      zoomTo(-95.0f, -1500.0f, 700.0f, p);
   }
   else{
      /* See the whole screen. Default action */
      zoomTo(-1390.0f, -755.0f, 700.0f,0.0f);
   }

   /* Blending functions. We need two different method. One for the meshes one for the endscroll */
   if(time > 181990) glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); /* Changing blending during the endscroll */
   else glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);

   /* We draw the canvas all the time */
   drawCanvas();
   if(time > 181990)                     EndScroll(time);/* Deadline is coming, no optimization :-(*/
   /* All the meses must be rotated the same way */
   glPushMatrix();
     glRotatef(270.0f, 1.0f, 0.0f, 0.0f);

     /* Syncronization steps */
     if(time < 17365)                    drawMesh3D(logo);
     if(time > 5000   && time < 40504)   PanningForest(time);

     if(time > 32918  && time < 40504){
        /* In this time the second part floating into the screen */
        if(-3800 + (time - 32918) / 2.0 < 0.0){
          glTranslatef(-3800 + (time - 32918) / 2.0, 0.0, 0.0);
        }
        glPushMatrix();
          SitaAndRavanaMeetInTheForest(time);
        glPopMatrix();
     }

     if(time > 40504  && time < 75232)   SitaAndRavanaMeetInTheForest(time);
     if(time > 75232  && time < 77232)   JatajusWakeUp(75232, time);
     if(time > 77232  && time < 82255)   RavanaTakeOnToHisCouch(time);
     if(time > 82255  && time < 85671)   JatajusOpenWideWings(time);
     if(time > 85671  && time < 90299)   CouchOfRavanaIsFly(time);
     if(time > 90299  && time < 117047)  JatajusFollowTheCouch(time);
     if(time > 117047 && time < 119254)  JatajusAttackTheHorse(time);
     if(time > 119254 && time < 127313)  FallingCouch(time);
     if(time > 127313 && time < 135234)  FightInTheGround(time);
     if(time > 135234 && time < 138000)  FatalStrike(time);
     if(time > 138000 && time < 145724)  LoosingWings(time);
     if(time > 145724)                   DyingJatajus(time);

   glPopMatrix();
}

