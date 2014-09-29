/***********************************************************
 * Un template per scrivere applicazioni OpenGL con GLUT
 *
 * Descrizione:
 * Inizializza una finestra OpenGL usando GLUT.
 * Le callback di utilizzo più comune vengono registrate come vuote o
 * con funzionalità minime.
 *
 * Lo scopo di questo codice è fornire un veloce punto di partenza per
 * scrivere applicazioni OpenGL / GLUT
 *
 ***********************************************************/


#include <GL/glut.h>
#include <IL/il.h>
#include <iostream>

#include "rocks.h"
#include "flints.h"

#include "waterfall.h"
#include "sky.h"

#include "elephant.h"
#include "lake.h"
#include "grass.h"
#include "footpath.h"
#include "tree.h"
#include "forest.h"

int width = 800;
int height = 600;

GLint FPS = 30;		// Frame per Secondo. Vengono usati nella funzione di animazione
// per controllare il massimo numero di frame al secondo dell'animazione

int spin_x = 0, old_x = 0;		// spin_ indica di quanto si deve ruotare la scena
int spin_y = 0, old_y = 0;		// old_  indica la vecchia posizione del cursore5
int fase = 0;		// specifica lo stato dell' animazione


//Parametri geometrici della scena
float sky_radius = 900;
float rocks_height = 500;
float rocks_width = 500;
float rocks_length = 400;
float waterfall_width = 250;
float waterfall_height = rocks_height;
float lake_width = rocks_width;
float lake_length = rocks_length;
float wave1[3] = {15, 10, 4.95};
float wave2[3] = {5, 10, 4.95};

float flintsSmall_width = lake_width;
float flintsSmall_length = 70;
float flintsBig_length = 3*rocks_length;
float flintsBig_width = lake_length+flintsSmall_length;
float flints_height = 2*wave1[0];

float footpath_width = 200;
float footpath_length = 900;
float grass_width = 1700;
float trunk_radius = 16;
float trunk_length = 90;
float leaves_radius = 70;
int forest_width = 5;
int forest_length = 5;
float forest_space = 20;

float elephant_body_width = 60;
float elephant_body_height = 75;
float elephant_body_length = 100;
float elephant_hoof_width = 15;
float elephant_hoof_length = 70;
float elephant_head_radius = 28;
float elephant_prob_width = 8;
float elephant_prob_length = 70;

float elephant_translate = 1500;
int num_drink = 0;



//Oggetti della scena
Sky sky(sky_radius, 64, 64);

Rocks rocks(rocks_height, rocks_width, rocks_length);
Waterfall waterfall(waterfall_height, waterfall_width);
Lake lake(lake_width, lake_length, wave1, wave2);

Flints flintsBig(flintsBig_width, flintsBig_length, flints_height, 6, 6);
Flints flintsSmall(flintsSmall_width, flintsSmall_length, flints_height, 4, 1);

FootPath footpath(footpath_length, footpath_width);
Grass grass(grass_width, footpath_length);

Tree tree(trunk_radius, trunk_length, leaves_radius);
Forest forest(&tree, forest_width, forest_length, forest_space);


Elephant elephant(elephant_body_width, elephant_body_height, elephant_body_length,
                   elephant_hoof_width, elephant_hoof_length,
                   elephant_head_radius, elephant_prob_width, elephant_prob_length);



//Parametri della telecamera
float field_of_view = 10;
float eye_x = 0, eye_y = 5, eye_z = 850;
float lookat_x = 0, lookat_y = rocks_height, lookat_z = 0;
float eye_acc = 0;

/*
float field_of_view = 60;
float eye_x = 0, eye_y = 5, eye_z = 800;
float lookat_x = 0, lookat_y = 0, lookat_z = 0;
float eye_acc = 0;
*/

/* processa l'azione selezionata dal menu
 *
 * op - intero che rappresenta l'azione selezionata nel menu
 */
void menu(int op)
{

    switch(op)
    {
    case 'Q':
    case 'q':
        exit(0);
    }
}

/*
 * invocata da GLUT quando un tasto viene premuto
 *
 * key - tasto premuto
 * x, y - coordinate del cursore del mouse
 */
void keyboardDown(unsigned char key, int x, int y)
{
    if (fase < 5) {
        if (key == 's') {
            fase = 1;
        }
        return;
    }

    if (fase <= 10) {

        switch(key) {

        case 'd':
            field_of_view = 80;
            eye_x = -250; eye_y = 150; eye_z = -50;
            lookat_x = 0; lookat_y = 0; lookat_z = 70;
            break;
        case 'f':
            field_of_view = 80;
            eye_x = 250; eye_y = 150; eye_z = -50;
            lookat_x = 0; lookat_y = 0; lookat_z = 70;
            break;
        case 'g':
            field_of_view = 80;
            eye_x = 0; eye_y = 250; eye_z = 300;
            lookat_x = 0; lookat_y = 0; lookat_z = 70;
            break;
        case 'h':
            field_of_view = 80;
            eye_x = 0; eye_y = 400; eye_z = 600;
            lookat_x = 0; lookat_y = 0; lookat_z = 70;
            break;
        case '+':
            field_of_view--;
            break;
        case '-':
            field_of_view++;
            break;
        case 'r':
            if (fase == 10)
                fase = 6;
            break;
        }

    }


    switch(key)
    {
    case 'Q':
    case 'q':
    case  27:   // ESC
        exit(0);
    }
}

/*
 * invocata da GLUT quando un tasto viene rilasciato
 *
 * key - tasto premuto
 * x, y - coordinate del cursore del mouse
 */
void keyboardUp(unsigned char key, int x, int y) {}

/*
 * invocata quando la finestra cambia dimensione, oppure è occlusa da un'altra finestra
 *
 * width. height - dimensioni attuali della finestra
 */
void reshape(int width, int height)
{
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(field_of_view, (GLfloat) width/(GLfloat) height, 0.1, 2000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*
 * invocata quando uno dei bottoni del mouse cambia stato (viene premuto o rilasciato)
 *
 * button - bottone che ha cambiato stato
 * state - stato attuale del bottone
 * x, y - coordinate del cursore del mouse
 */
void mouseClick(int button, int state, int x, int y)
{
    old_x = x;
    old_y = y;

    glutPostRedisplay();
}

/*
 * invocata ogni volta che il cursore del mouse viene mosso
 *
 * x, y - coordinate del cursore del mouse
 *
 * nota: sulla maggior parte dei sistemi, la posizione del cursore del mouse viene rilevata (campionata)
 *       con una frequenza di almeno 1/30 secondi
 */
void mouseMotion(int x, int y)
{
    if (fase < 5) return;
    spin_x = x - old_x;
    spin_y = y - old_y;

    glutPostRedisplay();
}

/*
 * disegna gli assi
 *
 * lenght - lunghezza degli assi
 */
void DrawAxes(float length)
{
    glPushMatrix();
    glScalef(length, length, length);

    glLineWidth(2.f);
    glBegin(GL_LINES);

    // x red
    glColor3f(1.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(1.f, 0.f, 0.f);

    // y green
    glColor3f(0.f, 1.f, 0.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 1.f, 0.f);

    // z blue
    glColor3f(0.f, 0.f, 1.f);
    glVertex3f(0.f, 0.f, 0.f);
    glVertex3f(0.f, 0.f, 1.f);

    glEnd();
    glLineWidth(1.f);

    glPopMatrix();
}

/*
 * disegna la scena
 */
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(  eye_x, eye_y, eye_z,		// da dove si guarda
                lookat_x, lookat_y, lookat_z,		// dove si guarda
                0, 1, 0);		// su

    //glTranslatef(-3.f, -3.f, -3.f);
    glRotatef(spin_y, 1.0, 0.0, 0.0);
    glRotatef(spin_x, 0.0, 1.0, 0.0);


    sky.draw();

    glTranslatef(0, 0, -sky_radius/2);

    // codice per il disegno qui
    glPushMatrix();
    glTranslatef(0, -2*wave1[0], 0);
    rocks.draw(0, 0, 0);
    waterfall.draw(0, rocks_height/2, 3);
    glPopMatrix();

    lake.draw(-rocks_width/2, -wave1[0], 0);

    flintsSmall.draw(0, 0, lake_length);

    glPushMatrix();
    glTranslatef(lake_width/2, 0, flintsBig_width/2);
    glRotatef(90, 0, 1, 0);
    flintsBig.draw(0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-lake_width/2, 0, flintsBig_width/2);
    glRotatef(-90, 0, 1, 0);
    flintsBig.draw(0, 0, 0);
    glPopMatrix();

    footpath.draw(0, 2, footpath_length/2+rocks_length+flintsSmall_length);
    grass.draw(0, 0, footpath_length/2+rocks_length+flintsSmall_length);

    forest.draw(footpath_width/2+tree.getWidth(), 0, rocks_length+flintsSmall_length+tree.getWidth());
    glPushMatrix();
    glScalef(-1, 1, 1);
    forest.draw(footpath_width/2+tree.getWidth(), 0, rocks_length+flintsSmall_length+tree.getWidth());
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, elephant_hoof_length, elephant_translate);
    glScalef(1, 1, -1);
    elephant.draw(0, 0, 0);
    glPopMatrix();

    glFlush();
    glutSwapBuffers();

    reshape(width, height);
}

/*
 * invocata ogni volta che non ci sono eventi pendenti da processare
 */
void idle()
{
    glutPostRedisplay();
}

/*
 * inizializza lo stato di OpenGL
 *
 * width, height - larghezza e altezza della finestra OpenGL
 */
void initGL(int width, int height)
{
    ilInit();

    // colore e tipo delle luci
    GLfloat light_ambient_0[] =	{0.65, 0.65, 0.65, 1.0};// colore ambiente della luce 0
    GLfloat light_diffuse_0[] = {1.0, 1.0, 1.0, 1.0};	// colore diffusione della luce 0
    GLfloat light_specular_0[] = {1.0, 1.0, 1.0, 1.0};	// colore speculare della luce 0
    GLfloat light_position_0[] = {5.0, 5.0, 0.0, 0.0};	// posizione della luce 0

    glLightfv (GL_LIGHT0, GL_AMBIENT,	light_ambient_0);
    glLightfv (GL_LIGHT0, GL_DIFFUSE,	light_diffuse_0);
    glLightfv (GL_LIGHT0, GL_SPECULAR,	light_specular_0);
    glLightfv (GL_LIGHT0, GL_POSITION,	light_position_0);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    reshape(width, height);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);


    //ilEnable(IL_ORIGIN_SET);
    //ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

    //ilEnable(IL_TYPE_SET);
    //ilTypeFunc(IL_UNSIGNED_BYTE);

    //ilEnable(IL_FORMAT_SET);
    //ilFormatFunc(IL_RGB);


    glEnable(GL_TEXTURE_2D);


     if (!sky.init((char *)"./data/sky.jpg"))
        {
            printf("Errore nell'inizializzazione del cielo\n");
            exit(1);
        }

    if (!waterfall.init((char *)"./data/waterfall.jpg"))
    {
        printf("Errore nel caricamento della texture della cascata\n");
        exit(1);
    }


    if (!flintsBig.init((char *)"./data/flints.jpg"))
    {
        printf("Errore nell'inizializzazione dei sassi\n");
        exit(1);
    }

    if (!flintsSmall.init((char *)"./data/flints.jpg"))
    {
        printf("Errore nell'inizializzazione dei sassi\n");
        exit(1);
    }


    if (!rocks.init((char *)"./data/rocks.jpg"))
    {
        printf("Errore nell'inizializzazione delle rocce\n");
        exit(1);
    }

    if (!elephant.init((char *)"./data/elephant.jpg"))
    {
        printf("Errore nell'inizializzazione dell'elefante\n");
        exit(1);
    }

    if (!lake.init((char *)"./data/lake.jpg"))
    {
        printf("Errore nell'inizializzazione del lago\n");
        exit(1);
    }

    if (!grass.init((char *)"data/grass.jpg"))
    {
        printf("Errore nell'inizializzazione dell'erba\n");
        exit(1);
    }

    if (!footpath.init((char *)"data/footpath.jpg"))
    {
        printf("Errore nell'inizializzazione del sentiero\n");
        exit(1);
    }

    if (!tree.init((char *)"./data/trunk.jpg", (char *)"data/leaves.jpg"))
    {
        printf("Errore nell'inizializzazione dell'albero\n");
        exit(1);
    }

    if (!forest.init())
    {
        printf("Errore nell'inizializzazione della foresta\n");
        exit(1);
    }

}

/*
 * invocata ogni 1000/FPS millisecondi.
 * all' interno di questa funzione va cambiato lo stato degli oggetti della scena al fine, ad esempio, di animarli.
 * quando lo stato cambia, si deve chiamare glutPostRedisplay() per aggiornare la visualizzazione il prima possibile
 * (cioè quando tutti gli eventi pendenti sono stati processati).
 *
 * t - è il parametro definito dall' utente specificato per ultimo nella glutTimerFunc
 */
void animation(int t)
{
    switch (fase)
    {
    case 0: // fase di pausa
        break;

    case 1: //zoom out dal sole

        field_of_view +=0.6;
        waterfall.move();
        lake.move();
        glutPostRedisplay();

        if (field_of_view >= 80)
            fase++;

        break;

    case 2: //la telecamera si abbassa
        lookat_y -= 10;
        waterfall.move();
        lake.move();
        glutPostRedisplay();

        if (lookat_y <= 1) {
            lookat_y = 0;
            lookat_z = -sky_radius/3;
            fase++;
        }

        break;

    case 3: //avanti veloce fino al lago

        eye_z -= eye_acc;
        waterfall.move();
        lake.move();
        elephant.walk(5);
        glutPostRedisplay();

        if (eye_acc < 20)
            eye_acc += 0.3;

        if (eye_z <= -sky_radius/3) {
            elephant_translate = 1300;
            fase++;
        }
        break;

    case 4: //vista sul sentiero dove si avvicina l'elefante

        lookat_z += 1;
        waterfall.move();
        lake.move();
        elephant.walk(1000);
        glutPostRedisplay();

        if(lookat_z >= -220) {
            eye_x = -250; eye_y = 150; eye_z = -50;
            lookat_x = 0; lookat_y = 0; lookat_z = 70;
            elephant_translate = 900;
            fase++;
        }
        break;

    case 5: //nuova visuale, l'elefante arriva fino al lago
        waterfall.move();
        lake.move();
        if (elephant.walk(350)) fase++;
        glutPostRedisplay();
        break;

    case 6: //l'elefante si abbassa per bere
        waterfall.move();
        lake.move();
        if (elephant.goDown()) fase++;
        glutPostRedisplay();
        break;

    case 7: //l'elefante porta la proboscide alla bocca per bere
        waterfall.move();
        lake.move();
        if (elephant.probToMouth()) fase++;
        glutPostRedisplay();
        break;

    case 8: //l'elefante riporta la proboscide in posizione di riposo
        waterfall.move();
        lake.move();
        if (elephant.probNormal()) {
            num_drink++;
            if (num_drink < 4) fase = 7;
            else fase++;
        }
        glutPostRedisplay();
        break;

    case 9: //l'elefante si tira su
        waterfall.move();
        lake.move();
        if (elephant.goUp()) fase++;
        glutPostRedisplay();
        break;

    case 10:
        waterfall.move();
        lake.move();
        glutPostRedisplay();
        break;

    }
    glutTimerFunc((int) 1000/FPS, animation, 0);
// La glutTimerFunc funziona come una sveglia che squilla una volta dopo x millisecondi.
// Se si vuole che suoni (si richiami) di nuovo bisogn ri-invocarla
}

/*
 * inizializza GLUT, registra le callback, entra nel main loop
 *
 * argc : numero di parametri di ingresso
 * argv : vettore degli argomenti di ingresso
 *
 * nota: argc e argv aiutano a capire quali sono i parametri di ingresso passati da linea di comando
 */
int main(int argc, char** argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Perspective's GLUT Template");

    // registra le callback
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouseClick);
    glutMotionFunc(mouseMotion);
    glutReshapeFunc(reshape);
    glutDisplayFunc(draw);
    glutIdleFunc(idle);
    glutTimerFunc((int) 1000/FPS, animation, 0);
    glutIgnoreKeyRepeat(false); // process keys held down

    // crea un sottomenu
    int subMenu = glutCreateMenu(menu);
    glutAddMenuEntry("Do nothing", 0);
    glutAddMenuEntry("Really Quit", 'q');

    // crea il menu principale (apribile con click destro)
    glutCreateMenu(menu);
    glutAddSubMenu("Sub Menu", subMenu);
    glutAddMenuEntry("Quit", 'q');
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    // inizializza lo stato di OpenGL
    initGL(width, height);

    // entra nel rendering loop
    glutMainLoop();
    return 0;
}
