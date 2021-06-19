#include <GL/glut.h>
#include <stdio.h>

float theta = 30.0;
float width = 200.0;
float height = 200.0;
float n = 4.0;
float f = 20.0;

float X_AXIS = 0.0;
float Y_AXIS = 0.0;
float Z_AXIS = 0.0;

void displayCube();
void changeSize(float width,float height);
void InitGL();
void keyPressed(unsigned char key, int x, int y);

int main(int argc, char **argv) {

    if(argc > 1 && argc < 7){
        theta = strtol(argv[1],NULL,10);
        width = strtol(argv[2],NULL,10);
        height = strtol(argv[3],NULL,10);
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
	glutMainLoop();
    return 0;
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

void changeSize(float width,float height){
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glViewport(0, 0, width, height);

    gluPerspective((float)theta, (float) width / (float) height, (float) n, (float) f);

    glMatrixMode(GL_MODELVIEW);
    
    printf("Theta %f, Width: %f, Height: %f, n: %f, f: %f",theta,width,height,n,f);
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
    gluPerspective((float)theta, (float)width / (float)height, (float)n, (float)f);
    glMatrixMode(GL_MODELVIEW);
    return;
}

void keyPressed(unsigned char key, int x, int y){
    // a - d change theta value
    // w - s change f value
    // b - n change n value
    // c - v CONTROL THE WIDTH -> ASPECT RATIO
    width = glutGet(GLUT_WINDOW_WIDTH);

    if(key == 'w'){
        f = (float)(f + 2.0);
    }
    else if(key == 's'){
        f = (float)(f - 2.0);
    }
    else if(key == 'a'){
        theta = (float)(theta + 5.0);
    }
    else if(key == 'd'){
        theta = (float)(theta - 5.0);
    }
    else if(key == 'b'){
        n = (float)(n - 0.05);
    }
    else if(key == 'n'){
        n = (float)(n + 0.05);
    }
    else if(key == 'c'){
        width = width + 20.0;
    }
    else if(key == 'v'){
        width = 400;
        changeSize(width, glutGet(GLUT_WINDOW_HEIGHT));
    }
}
