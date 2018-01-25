//
//  main.c
//  Lab8
//
//  Created by serena shi on 16/5/31.
//  Copyright © 2016年 serena shi. All rights reserved.
//

#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <math.h>

//set boundary
#define WIN_LEFT -15
#define WIN_RIGHT 15
#define WIN_BOTTOM -15
#define WIN_TOP 15
#define WIN_NEAR -15
#define WIN_FAR 15

//set the order of all parts
#define ALL 0
#define TORSO 1
#define LUA 2
#define LLA 3
#define RUA 4
#define RLA 5
#define LUL 6
#define LLL 7
#define RUL 8
#define RLL 9
#define LF 10
#define RF 11




#define bendTORSOv 0.1846
#define bendLUAv 0.8
#define bendLLAv 1.23
#define bendRUAv 0.8
#define bendRLAv 0.246
#define bendLULv 0.1846
#define bendLLLv 0.0923
#define bendRULv 0.1846
#define bendRLLv 0.0923
#define bendLFv 0.04
#define bendRFv 0.04

#define rotateVelocity 1

//set rotate angle
GLfloat theta[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,0};

//set states
GLfloat transDirection=1;
GLboolean translate_state=GL_FALSE;

//set bending direction
GLfloat bendingDirection[]={0,-1,1,1,-1,-1,-1,-1,1,1,1,1};

//set states
GLboolean bending_state=GL_FALSE;
GLboolean rotate_state=GL_FALSE;
GLboolean spotLight=GL_FALSE;


//define the specifications of the figure
#define TORSO_WIDTH 3.5
#define TORSO_HEIGHT 3.3
#define TORSO_DEPTH 2.3
#define HEAD_WIDTH 2.0
#define HEAD_HEIGHT 1.3
#define HEAD_DEPTH 1.0
#define HAIR_WIDTH 2.0
#define HAIR_HEIGHT 0.6
#define HAIR_DEPTH 1.0

#define OUTER_EYE_RADIUS 0.12
#define INNER_EYE_RADIUS 0.07

#define MOUTH_WIDTH 0.8
#define MOUTH_HEIGHT 0.28
#define MOUTH_DEPTH  0.1

#define TEETH_WIDTH 0.8
#define TEETH_HEIGHT 0.12
#define TEETH_DEPTH 0.1

#define BALL_RADIUS 0.8
#define BALL_PATTERN_RADIUS 0.9
#define NECK_WIDTH 1.0
#define NECK_HEIGHT 0.8
#define NECK_DEPTH 0.5

#define NUMBER_WIDTH 0.5
#define NUMBER_HEIGHT 1.6
#define NUMBER_DEPTH 2.5

#define LOWER_ARM_HEIGHT 2.0
#define LOWER_ARM_WIDTH 0.35

#define UPPER_ARM_RADIUS 0.4
#define UPPER_ARM_HEIGHT 1.2
#define UPPER_ARM_WIDTH 0.81
#define LOWER_LEG_HEIGHT 2.0
#define LOWER_LEG_WIDTH 0.45
#define UPPER_LEG_HEIGHT 1.7
#define UPPER_LEG_WIDTH 1.4
#define FOOT_WIDTH 1.0
#define FOOT_HEIGHT 0.3

#define TOP_ARM_RADIUS 0.4

#define SPOTLIGHT_RADIUS 0.5




GLUquadricObj *p;   // pointer to quadric object

//set material structure
typedef struct materialStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} materialStruct;


//set materials

materialStruct summerEyeMaterials={{0.01,0.01,0.01},{0.0,0.0,0.0},{0.0,0.0,0.0},15};
materialStruct summerMouthMaterials={{0.71,0.00,0.02},{0.81,0.10,0.12},{0.05,0.30,0.33},10};
materialStruct summerHeadMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.4,0.25,0.19},20};
materialStruct summerHairMaterials={{0.0,0.0,0.0},{0.02,0.02,0.02},{0.0,0.0,0.0},15};
materialStruct summerBallMaterials={{0.45,0.25,0.09},{0.65,0.45,0.29},{0.05,0.35,0.3},20};
materialStruct summerNeckMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct summerTorsoMaterials={{0.22,0.29,0.00},{0.25,0.39,0.07},{0.55,0.09,0.39},20};
materialStruct summerUpperArmMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.4,0.25,0.19},20};
materialStruct summerLowerArmMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct summerUpperLegMaterials={{0.22,0.29,0.00},{0.25,0.39,0.07},{0.55,0.09,0.39},20};
materialStruct summerLowerLegMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct summerFootMaterials={{0.55,0.59,0.39},{0.55,0.65,0.37},{0.05,0.05,0.04},20};
materialStruct summerNumberMaterials={{0.7,0.7,0.02},{0.71,0.30,0.32},{0.05,0.30,0.33},20};


materialStruct autumnEyeMaterials={{0.01,0.01,0.01},{0.0,0.0,0.0},{0.0,0.0,0.0},15};
materialStruct autumnMouthMaterials={{0.71,0.00,0.02},{0.81,0.10,0.12},{0.05,0.30,0.33},10};
materialStruct autumnHeadMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.4,0.25,0.19},20};
materialStruct autumnHairMaterials={{0.0,0.0,0.0},{0.02,0.02,0.02},{0.0,0.0,0.0},15};
materialStruct autumnBallMaterials={{0.45,0.25,0.09},{0.65,0.45,0.29},{0.05,0.35,0.3},20};
materialStruct autumnNeckMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct autumnTorsoMaterials={{0.25,0.05,0.00},{0.45,0.25,0.10},{0.05,0.05,0.49},30};
materialStruct autumnUpperArmMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.4,0.25,0.19},20};
materialStruct autumnLowerArmMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct autumnUpperLegMaterials={{0.25,0.05,0.00},{0.45,0.25,0.10},{0.05,0.05,0.49},30};
materialStruct autumnLowerLegMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},10};
materialStruct autumnFootMaterials={{0.45,0.25,0.09},{0.65,0.45,0.29},{0.05,0.05,0.49},20};
materialStruct autumnNumberMaterials={{0.45,0.25,0.09},{0.65,0.45,0.29},{0.05,0.05,0.49},20};


materialStruct winterEyeMaterials={{0.01,0.01,0.01},{0.0,0.0,0.0},{0.0,0.0,0.0},15};
materialStruct winterMouthMaterials={{0.71,0.00,0.02},{0.81,0.10,0.12},{0.05,0.30,0.33},10};
materialStruct winterHeadMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.4,0.25,0.19},20};
materialStruct winterHairMaterials={{0.0,0.0,0.0},{0.02,0.02,0.02},{0.0,0.0,0.0},15};
materialStruct winterBallMaterials={{0.45,0.25,0.09},{0.65,0.45,0.29},{0.05,0.35,0.3},20};
materialStruct winterNeckMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct winterTorsoMaterials={{0.71,0.00,0.02},{0.81,0.10,0.12},{0.05,0.30,0.33},20};
materialStruct winterUpperArmMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct winterLowerArmMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct winterUpperLegMaterials={{0.71,0.00,0.02},{0.81,0.10,0.12},{0.05,0.30,0.33},20};
materialStruct winterLowerLegMaterials={{0.71,0.57,0.52},{0.91,0.77,0.50},{0.1,0.05,0.39},20};
materialStruct winterFootMaterials={{0.71,0.00,0.02},{0.81,0.10,0.12},{0.05,0.30,0.33},20};
materialStruct winterNumberMaterials={{0.7,0.7,0.02},{0.71,0.30,0.32},{0.05,0.30,0.33},20};

//set material of every part
materialStruct *eyeMaterials;
materialStruct *headMaterials;
materialStruct *ballMaterials;
materialStruct *hairMaterials;
materialStruct *neckMaterials;
materialStruct *torsoMaterials;
materialStruct *upperArmMaterials;
materialStruct *lowerArmMaterials;
materialStruct *upperLegMaterials;
materialStruct *lowerLegMaterials;
materialStruct *footMaterials;
materialStruct *numberMaterials;
materialStruct *mouthMaterials;



//set lighting structure
typedef struct lightingStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
} lightingStruct;

//set white light
lightingStruct whiteLighting={{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
lightingStruct yellowLighting={{0.0,0.0,0.0,1.0},{1.8,1.0,0.0,1.0},{1.0,1.0,0.0,1.0}};
lightingStruct redLighting={{0.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0}};//set current lighting

lightingStruct *currentLighting;

GLfloat sphere_color[3];
GLfloat cutoff_angle;

//set light's position
GLfloat light_pos0[]={WIN_RIGHT,WIN_TOP,WIN_FAR,-1.0};
GLfloat light_direction0[]={0,-1,0};

GLfloat light_pos1[]={WIN_RIGHT*2/3,WIN_TOP*2/3,WIN_FAR*2/3,1.0};
GLfloat light_direction1[]={-1,-1,-1};

/* codes for every part of the object*/
void torso()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*TORSO_HEIGHT, 0.0);
    glScalef(TORSO_WIDTH, TORSO_HEIGHT, TORSO_DEPTH);
    glColor3f(0.76,0.0,0.17);
    glutSolidCube(1.0);
    glPopMatrix();
}

void head()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*HEAD_HEIGHT, 0.0);
    glScalef(HEAD_WIDTH, HEAD_HEIGHT, HEAD_DEPTH);
    glColor3f(0.98,0.98,0.85);
    glutSolidCube(1.0);
    glPopMatrix();
    
}

void outereye()
{   glPushMatrix();
    gluSphere(p,OUTER_EYE_RADIUS,100,100);
    glPopMatrix();
}


void hair()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*HAIR_HEIGHT, 0.0);
    glScalef(HAIR_WIDTH, HAIR_HEIGHT, HAIR_DEPTH);
    glColor3f(0.03, 0.03, 0.03);
    glutSolidCube(1.0);
    glPopMatrix();
}

void mouth()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*MOUTH_HEIGHT, 0.0);
    glScalef(MOUTH_WIDTH, MOUTH_HEIGHT, MOUTH_DEPTH);
    glColor3f(1.0, 0.0, 0.0);
    glutSolidCube(1.0);
    glPopMatrix();
}


void teeth()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*TEETH_HEIGHT, 0.0);
    glScalef(TEETH_WIDTH, TEETH_HEIGHT, TEETH_DEPTH);
    glColor3f(1.0, 1.0, 1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void neck()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*NECK_HEIGHT, 0.0);
    glScalef(NECK_WIDTH, NECK_HEIGHT, NECK_DEPTH);
    glColor3f(0.98,0.98,0.85);
    glutSolidCube(1.0);
    glPopMatrix();
}

void basketball()
{   glPushMatrix();
    glColor3f(0.99,0.6,0.4);
    gluSphere(p,BALL_RADIUS,100,100);
    glPopMatrix();
}

void lower_arm()
{
    glPushMatrix();
    glTranslatef(0.0, -0.5*LOWER_ARM_HEIGHT, 0.0);
    glScalef(LOWER_ARM_WIDTH, LOWER_ARM_HEIGHT, LOWER_ARM_WIDTH);
    glColor3f(0.98,0.98,0.85);
    glutSolidCube(1.0);
    glPopMatrix();
}

void upper_arm()
{
    glPushMatrix();
    glTranslatef(0.0, -1.0*UPPER_ARM_HEIGHT, 0.0);
    //glScalef(UPPER_ARM_WIDTH, UPPER_ARM_HEIGHT, UPPER_ARM_WIDTH);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,UPPER_ARM_RADIUS,UPPER_ARM_RADIUS,UPPER_ARM_HEIGHT,100,100);
    gluDisk(p, 0, UPPER_ARM_RADIUS, 100, 100);
    glTranslatef(0, 0, UPPER_ARM_HEIGHT-0.2);
    gluDisk(p, 0, UPPER_ARM_RADIUS, 100, 100);
    
    glTranslatef(0, 0, UPPER_ARM_HEIGHT-0.9);
    gluSphere(p,TOP_ARM_RADIUS,100,100);
    glColor3f(0.03,0.03,0.03);
    //glutSolidCube(1.0);
    glPopMatrix();
}

void lower_leg()
{
    glPushMatrix();
    glTranslatef(0.0, -0.5*LOWER_LEG_HEIGHT, 0.0);
    glScalef(LOWER_LEG_WIDTH, LOWER_LEG_HEIGHT, LOWER_LEG_WIDTH);
    glColor3f(0.98,0.98,0.85);
    glutSolidCube(1.0);
    glPopMatrix();
}

void upper_leg()
{
    glPushMatrix();
    glTranslatef(0.0, -0.5*UPPER_LEG_HEIGHT, 0.0);
    glScalef(UPPER_LEG_WIDTH, UPPER_LEG_HEIGHT, UPPER_LEG_WIDTH);
    glColor3f(0.03, 0.03, 0.03);
    glutSolidCube(1.0);
    glPopMatrix();
}

void foot()
{
    glPushMatrix();
    glTranslatef(0.0, -0.5*FOOT_HEIGHT, 0.0);
    glScalef(FOOT_WIDTH, FOOT_HEIGHT, FOOT_WIDTH);
    glColor3f(0.76,0.0,0.17);
    glutSolidCube(1.0);
    glPopMatrix();
}

void number()
{
    glPushMatrix();
    glTranslatef(0.0, 0.5*NUMBER_HEIGHT, 0.0);
    glScalef(NUMBER_WIDTH, NUMBER_HEIGHT,NUMBER_DEPTH);
    glColor3f(0.03,0.03,0.03);
    glutSolidCube(1.0);
    glPopMatrix();
}

//make a function to set material of every part
void chooseMaterial(materialStruct *material)
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,material->ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,material->diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,material->specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,&material->shininess);
    return;
}

void spotlight()
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3fv(sphere_color);
    
    glutSolidSphere(SPOTLIGHT_RADIUS, 100, 100);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    return;
}
void object()
{
    
    glRotatef(theta[ALL], 0, 1, 0);//all part should rotate some angles
    
    
    //make torso neck head and hair
    glPushMatrix(); //save present model-view matrix
    glRotatef(theta[TORSO], 1, 0, 0);
    chooseMaterial(torsoMaterials);
    torso();
    
    glTranslatef(0.0, TORSO_HEIGHT , 0.0); //update model-view matrix for head
    chooseMaterial(neckMaterials);
    neck();
    glPushMatrix();
    
    glTranslatef(0.0, NECK_HEIGHT , 0.0);//update model-view matrix for head
    chooseMaterial(headMaterials);
    head();
    glPushMatrix();
    
    glTranslatef(0.0, HEAD_HEIGHT, 0.0);
    chooseMaterial(hairMaterials);
    hair();
    glPushMatrix();
    
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
    glPopMatrix(); //recover original model-view matrix
    
    //make the eye
    glPushMatrix();
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(-HEAD_WIDTH*0.28 , TORSO_HEIGHT+NECK_HEIGHT+0.75*HEAD_HEIGHT-0.04, 0.25*HEAD_WIDTH);//update model-view matrix for left outer eye ;
    chooseMaterial(eyeMaterials);
    outereye();
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(HEAD_WIDTH*0.28 , TORSO_HEIGHT+NECK_HEIGHT+0.75*HEAD_HEIGHT, 0.25*HEAD_WIDTH);//update model-view matrix for right outer eye ;
    chooseMaterial(eyeMaterials);
    outereye();
    glPopMatrix();
    
    //make the mouth
    glPushMatrix();
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(-HEAD_WIDTH*0.01 , TORSO_HEIGHT+NECK_HEIGHT+0.2*HEAD_HEIGHT, 0.25*HEAD_WIDTH);//update model-view matrix for mouth ;
    chooseMaterial(mouthMaterials);
    mouth();
    glPopMatrix();
    

    
    //make the number decorated on clothes
    glPushMatrix();
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(-TORSO_WIDTH*0.2 , 0.4*TORSO_HEIGHT, 0.01*TORSO_WIDTH);//update model-view matrix for left front number
    chooseMaterial(numberMaterials);
    number();
    glPopMatrix();
    
    
    glPushMatrix();
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(TORSO_WIDTH*0.2 , 0.4*TORSO_HEIGHT, 0.01*TORSO_WIDTH);//update model-view matrix for right front number
    chooseMaterial(numberMaterials);
    number();
    glPopMatrix();
    
    //make the left upper and lower arm and ball
    glPushMatrix(); //save it again
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(-TORSO_WIDTH/2 - UPPER_ARM_WIDTH/2, 0.88*TORSO_HEIGHT, 0.0); //update model-view matrix for left upper arm
    glRotatef(theta[LUA], 1, 0, 0);
    chooseMaterial(upperArmMaterials);
    upper_arm();
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0); //update model-view matrix for left lower arm
    glRotatef(theta[LLA], 1, 0, 0);
    chooseMaterial(lowerArmMaterials);
    lower_arm();
    glTranslatef(0.0, -LOWER_ARM_HEIGHT-0.2, 0.0); //update model-view matrix for left lower arm
    
    chooseMaterial(ballMaterials);
    basketball();
    glPopMatrix(); //recover original model-view matrix
    
    
    //make the right upper and lower arm
    glPushMatrix();
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(TORSO_WIDTH/2 + UPPER_ARM_WIDTH/2 , 0.88*TORSO_HEIGHT, 0.0); //update model-view matrix for right upper arm
    glRotatef(theta[RUA], 1 ,0, 0);
    chooseMaterial(upperArmMaterials);
    upper_arm();
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0); //update model-view matrix for right lower arm
    glRotatef(theta[RLA], 0, 0, 1);
    chooseMaterial(lowerArmMaterials);
    lower_arm();
    glPopMatrix();
    
    
    //make the left upper and lower leg and left feet
    glPushMatrix(); //save it again
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(-TORSO_WIDTH/2 + UPPER_LEG_WIDTH/2 , 0.0, 0.0); //update model-view matrix for left upper leg
    glRotatef(theta[LUL], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    upper_leg();
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0); //update model-view matrix for left lower leg
    glRotatef(theta[LLL], 1, 0, 0);
    chooseMaterial(lowerLegMaterials);
    lower_leg();
    glTranslatef(0.0, -LOWER_LEG_HEIGHT, 0.0);//update model-view matrix for left foot
    glRotatef(theta[LF], 1, 0, 0);
    chooseMaterial(footMaterials);
    foot();
    glPopMatrix(); //recover original model-view matrix
    
    
    //make the right upper and lower leg and right feet
    glPushMatrix();
    glRotatef(theta[TORSO], 1, 0, 0);
    glTranslatef(TORSO_WIDTH/2 - UPPER_LEG_WIDTH/2 , 0.0, 0.0); //update model-view matrix for right upper leg
    glRotatef(theta[RUL], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    upper_leg();
    glTranslatef(0.0, -UPPER_LEG_HEIGHT, 0.0); //update model-view matrix for right lower leg
    glRotatef(theta[RLL], 1, 0, 0);
    chooseMaterial(lowerLegMaterials);
    lower_leg();
    glTranslatef(0.0, -LOWER_LEG_HEIGHT, 0.0); //update model-view matrix for right foot
    glRotatef(theta[RF], 1, 0, 0);
    chooseMaterial(footMaterials);
    foot();
    glPopMatrix();
}


void display()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //enable light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    
    //set light
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    //glRotatef(-theta[ALL], 0, 1, 0);//rotate the light with reverse direction
    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);//set current light ambient
    glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);//set current light diffuse
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);//set current specular
    
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_direction1);//set current light direction
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff_angle);//set current light cutoff angle
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos1);
    
    if(spotLight)
    {glTranslatef(WIN_RIGHT*1/3,WIN_TOP*1/3,WIN_FAR*1/3);//move the spot sphere to where spot light is
        spotlight();}//draw spot light
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //create an isometric view of the object
    
    object();
    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h); //let the image be shown in the window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (h <= w)
        glOrtho(-7.0*w/h, 7.0*w/h, -7.0, 7.0, -10.0, 10.0);
    else
        glOrtho(-7.0, 7.0, -7.0*h/w, 7.0*h/w, -10.0, 10.0); //make sure the whole object appears in the middle of the window and preserves its shape and proportions even in the event that the window°Øs aspect ratio has been changed
}

//use keyboard function to change color
void changeLightByKey(unsigned char key,int x,int y)
{
    if (key=='w'||key=='W')
    {
        currentLighting=&whiteLighting;//change current lighting
        cutoff_angle=45;//cutoff angle
        //set sphere color
        sphere_color[0]=1.0;
        sphere_color[1]=1.0;
        sphere_color[2]=1.0;
        return;
    }
    if (key=='y'||key=='Y')
    {
        currentLighting=&yellowLighting;
        cutoff_angle=20;
        sphere_color[0]=1.0;
        sphere_color[1]=1.0;
        sphere_color[2]=0.0;
        return;
    }
    if (key=='r'||key=='R')
    {
        currentLighting=&redLighting;
        cutoff_angle=10;
        sphere_color[0]=1.0;
        sphere_color[1]=0.0;
        sphere_color[2]=0.0;
        return;
    }
    return;
}

void init()
{
    bending_state=GL_TRUE;
    rotate_state=GL_TRUE;
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    p = gluNewQuadric();
    
    currentLighting = &whiteLighting;
    
    sphere_color[0]=1.0;
    sphere_color[1]=1.0;
    sphere_color[2]=1.0;
    cutoff_angle=45;
    
    eyeMaterials=&winterEyeMaterials;
    mouthMaterials=&winterMouthMaterials;
    headMaterials=&winterHeadMaterials;
    hairMaterials=&winterHairMaterials;
    neckMaterials=&winterNeckMaterials;
    torsoMaterials=&winterTorsoMaterials;
    ballMaterials=&winterBallMaterials;
    upperArmMaterials=&winterUpperArmMaterials;
    lowerArmMaterials=&winterLowerArmMaterials;
    upperLegMaterials=&winterUpperLegMaterials;
    lowerLegMaterials=&winterLowerLegMaterials;
    footMaterials=&winterFootMaterials;
    numberMaterials=&winterNumberMaterials;
    
    return;}


void bendFunc(GLint order, GLfloat MinAngle, GLfloat MaxAngle)
{
    if (theta[order]>=MaxAngle)
        bendingDirection[order]=-1;
    if (theta[order]<=MinAngle)
        bendingDirection[order]=1;
    return;
}

//run the function if there is no event
void myidle()
{
    if (translate_state==GL_TRUE)
    {
        theta[ALL]+=rotateVelocity;}
    
    
    if (bending_state==GL_TRUE)
    {
        
        theta[LUA]+=bendLUAv*bendingDirection[LUA];
        bendFunc(LUA,-130,0);
        theta[LLA]+=bendLUAv*bendingDirection[LLA];
        bendFunc(LLA,-70,0);
        theta[RUA]+=bendRUAv*bendingDirection[RUA];
        bendFunc(RUA,-130,0);
        theta[RLA]+=bendRLAv*bendingDirection[RLA];
        bendFunc(RLA,-40,0);
        
        theta[TORSO]+=bendTORSOv*bendingDirection[TORSO];
        bendFunc(TORSO,-30,0);
        
        theta[LUL]+=bendLULv*bendingDirection[LUL];
        bendFunc(LUL,-30,0);
        theta[LLL]+=bendLLLv*bendingDirection[LLL];
        bendFunc(LLL,-15,0);
        theta[RUL]+=bendRULv*bendingDirection[RUL];
        bendFunc(RUL,-30,0);
        theta[RLL]+=bendRLLv*bendingDirection[RLL];
        bendFunc(RLL,-15,0);
        
    }
    
    if (rotate_state==GL_TRUE)
    {
        theta[ALL]+=rotateVelocity;
        if (theta[ALL]>360)
            theta[ALL]=0;
    }
    glutPostRedisplay();
    return;
}

//use menu to change materials
void mymenu(int id)
{
    if (id==1)
    {
        
        eyeMaterials=&summerEyeMaterials;
        mouthMaterials=&summerMouthMaterials;
        headMaterials=&summerHeadMaterials;
        hairMaterials=&summerHairMaterials;
        neckMaterials=&summerNeckMaterials;
        torsoMaterials=&summerTorsoMaterials;
        ballMaterials=&summerBallMaterials;
        upperArmMaterials=&summerUpperArmMaterials;
        lowerArmMaterials=&summerLowerArmMaterials;
        upperLegMaterials=&summerUpperLegMaterials;
        lowerLegMaterials=&summerLowerLegMaterials;
        footMaterials=&summerFootMaterials;
        numberMaterials=&summerNumberMaterials;
        
        return;
    }
    if (id==2)
    {   eyeMaterials=&autumnEyeMaterials;
        mouthMaterials=&autumnMouthMaterials;
        headMaterials=&autumnHeadMaterials;
        hairMaterials=&autumnHairMaterials;
        neckMaterials=&autumnNeckMaterials;
        torsoMaterials=&autumnTorsoMaterials;
        ballMaterials=&autumnBallMaterials;
        upperArmMaterials=&autumnUpperArmMaterials;
        lowerArmMaterials=&autumnLowerArmMaterials;
        upperLegMaterials=&autumnUpperLegMaterials;
        lowerLegMaterials=&autumnLowerLegMaterials;
        footMaterials=&autumnFootMaterials;
        numberMaterials=&autumnNumberMaterials;
        return;
    }
    if (id==3)
    {
        eyeMaterials=&winterEyeMaterials;
        mouthMaterials=&winterMouthMaterials;
        headMaterials=&winterHeadMaterials;
        hairMaterials=&winterHairMaterials;
        neckMaterials=&winterNeckMaterials;
        torsoMaterials=&winterTorsoMaterials;
        ballMaterials=&winterBallMaterials;
        upperArmMaterials=&winterUpperArmMaterials;
        lowerArmMaterials=&winterLowerArmMaterials;
        upperLegMaterials=&winterUpperLegMaterials;
        lowerLegMaterials=&winterLowerLegMaterials;
        footMaterials=&winterFootMaterials;
        numberMaterials=&winterNumberMaterials;
        return;
    }
    return;
}

void lightmenu( int choice)
{ if(choice==1)
{   currentLighting = &whiteLighting;
    
    spotLight=GL_FALSE;
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, currentLighting -> ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, currentLighting -> diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, currentLighting -> specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);}
    
    if (choice==2){
        
        spotLight=GL_TRUE;
        glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting -> ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting -> diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting -> specular);
        glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
        
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT0);}
    
}

//create menu
void createMenu()
{
    int id;
    id=glutCreateMenu(mymenu);
    glutAddMenuEntry("Summer",1);
    glutAddMenuEntry("Autumn",2);
    glutAddMenuEntry("Winter",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}

//create menu
void createMenu1()
{
    int choice;
    choice=glutCreateMenu(lightmenu);
    glutAddMenuEntry("Sun",1);
    glutAddMenuEntry("Spotlight",2);
 
    glutAttachMenu(GLUT_LEFT_BUTTON);
    return;
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 700);
    glutCreateWindow("YaoMing");
    glutKeyboardFunc(changeLightByKey);
   	glutReshapeFunc(reshape);
    glutIdleFunc(myidle);
    glutDisplayFunc(display);
    
    
    glEnable(GL_DEPTH_TEST);
    init();
    createMenu();
    createMenu1();
    glutMainLoop();
}
