
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdio.h>

int KEYS_NORMAL[256];
int KEYS_SPECIAL[256];


float theta = 30.0;
float Width = 200.0;
float Height = 200.0;
float n = 4.0;
float f = 20.0;

float X_AXIS = 0.0;
float Y_AXIS = 0.0;
float Z_AXIS = 0.0;

int DIRECTION = 1;

void check_special_keys(int key, int x, int y) {
     KEYS_SPECIAL[key] = 1; //true
}
void check_special_keys_up(int key, int x, int y) { 
    KEYS_SPECIAL[key] = 0;  //false
}


void displayCube(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glRotatef(0.0, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.0, -6.0);

    glRotatef(X_AXIS, 1.0, 0.0, 0.0);
    glRotatef(Y_AXIS, 0.0, 1.0, 0.0);
    glRotatef(Z_AXIS, 0.0, 0.0, 1.0);

    glBegin(GL_QUADS);

    glColor3f(1.0, 0.5, 0.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);

    
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    
    glEnd();
    X_AXIS = X_AXIS - 0.30;
    Z_AXIS = Z_AXIS - 0.30;
    
    glutSwapBuffers();
    return;
}

void changeSize(float Width,float Height){
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, Width, Height);

    gluPerspective((float)theta, (float) Width / (float) Height, (float) n, (float) f);

    glMatrixMode(GL_MODELVIEW);
    
    printf("Theta %f, Width: %f, Height: %f, n: %f, f: %f",theta,Width,Height,n,f);
    return;
}

void InitGL(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective((float)theta, (float)Width / (float)Height, (float)n, (float)f);
    glMatrixMode(GL_MODELVIEW);
    return;
}

    
void keyPressed(){
    // LEFT - RIGHT KEYS CONTROL THE THETA VALUE
    // UP - DONW KEYS CONTROL THE F VALUE
    // w- s KEYS CONTROL THE N VALUE
    // a - d CONTROL THE WIDTH WHICH RESULTS TO CHANGE OF THE ASPECT RATIO
    
    Width = glutGet(GLUT_WINDOW_WIDTH);
     if(KEYS_SPECIAL[GLUT_KEY_LEFT] == 1){
         theta = (float)(theta + 5.0);
     }
        

    if(KEYS_SPECIAL[GLUT_KEY_RIGHT] == 1){
        theta = (float)(theta - 5.0);
    }
        
    if(KEYS_SPECIAL[GLUT_KEY_DOWN] == 1){
        f = (float)(f + 2.0);
    }

    if(KEYS_SPECIAL[GLUT_KEY_UP] == 1){
        f = (float)(f - 2.0);
    }

    if(KEYS_NORMAL['w'] == 1){
        n = (float)(n - 0.05);
    }

    if(KEYS_NORMAL['s'] == 1){
        n = (float)(n + 0.05);
    }

    if(KEYS_NORMAL['a'] == 1)
        Width = Width + 20.0;

    if(KEYS_NORMAL['d'] == 1){
        Width = 400;
        changeSize(Width, glutGet(GLUT_WINDOW_HEIGHT));
    }

}
    

int main(int argc, char **argv) {

    if(argc > 1 && argc < 7){
        theta = strtol(argv[1],NULL,10);
        Width = strtol(argv[2],NULL,10);
        Height = strtol(argv[3],NULL,10);
        n = strtol(argv[4],NULL,10);
        f = strtol(argv[5],NULL,10);
    }
    else{
        printf( "\033[31;1m[-]Default mode!\nUsing default values [30,200,200,4,30]\nUsage for custom inputs: ./<output_filename> [Theta] [Width] [Height] [n] [f]\033[0m\n");
    }
    

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Cube live projection");
    glMatrixMode(GL_PROJECTION);
    glutDisplayFunc(displayCube);
    glutIdleFunc(displayCube);
	InitGL();
    
    glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyPressed);
    glutSpecialFunc(check_special_keys);
	// glutSpecialUpFunc(check_special_keys_up);

	glutMainLoop();
    return 0;
}


    