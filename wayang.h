#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glext.h>
#include "mesh3d.h"
#include "texture.h"

/*Ravana drawing modes */
#define WITH_SWORD    1
#define WITHOUT_SWORD 0

/*Djatajus drawing modes */
#define WITHOUT_WINGS 0
#define WITH_WINGS    1
#define FLY           2

typedef struct ArrowParams {
   float start_x;
   float start_y;
   float end_x;
   float end_y;
   float angle;
} ArrowParams;

extern Mesh3D *sita;
extern Mesh3D *sita_arm;
extern Mesh3D *logo;
extern Mesh3D *cloud1;
extern Mesh3D *cloud2;
extern Mesh3D *cloud3;
extern Mesh3D *cloud4;
extern Mesh3D *tree;
extern Mesh3D *tree2;
extern Mesh3D *tree3;
extern Mesh3D *ravana;
extern Mesh3D *sword;
extern Mesh3D *couch;
extern Mesh3D *horse;
extern Mesh3D *jatajus;
extern Mesh3D *leftwing;
extern Mesh3D *rightwing;
extern Mesh3D *arrow;
extern Mesh3D *hand;
extern Mesh3D *arrow;
extern Mesh3D *humerus;

extern GLuint canvas;

/* Very important functions */
void init_wayang();
void show_wayang(Uint32 time);
void free_wayang();

