#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif

#include <string>
#include "Kmeans.h"
#define n_datos 7291703
using namespace std;

#define window_x 1000
#define window_y 1000
using namespace std;

double cam_x=0,cam_y=0;
string n_file="taxi.csv";
Kmeans<n_datos> k_means(n_file,4,100);


/////////////////////////////////////////////////////////
void centro(){
	glRotatef( cam_x, 0.0, 0.0, 1.0 );//A-ABA
	glRotatef( cam_y, 0.0, 1.0, 0.0 );//D-I
	cam_x=0;
	cam_y=0;
}
////////////////////////////////////////////////////////
void displayCoord(){
	glBegin(GL_LINES);
	glColor3d(255,0,0);//x
	glVertex3d(0, 0,0);
	glVertex3d(window_x, 0,0);
	glColor3d(0, 255, 0);//y	
	glVertex3d(0, 0,0);
	glVertex3d(0, window_x,0);
	glColor3d(0, 0, 255);//z
	glVertex3d(0, 0,0);
	glVertex3d(0, 0,window_x);
	glEnd();
	glutSwapBuffers();
}
/////////////////////////////////////////////////////////
void Pintar() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	///colocar_objetos_a_dibujar
//	glPointSize(7);
//	glBegin(GL_POINTS);
//		glColor3f(1,1,1);
//		glVertex2d(20,20);
//		glVertex2d(120,120);
//	glEnd();
	k_means.mostrar_puntos();
	
	///
	displayCoord();
	centro();	
}
/////////////////////////////////////////////////////////
void specialKeys( int key, int x, int y ) {
	if (key == GLUT_KEY_RIGHT)
		cam_y -= 3;
	else if (key == GLUT_KEY_LEFT)
		cam_y += 3;
	else if (key == GLUT_KEY_UP)
		cam_x += 3;
	else if (key == GLUT_KEY_DOWN)
		cam_x -= 3;
	glutPostRedisplay();
}
/////////////////////////////////////////////////////////
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, window_x, window_y );
	glMatrixMode(GL_PERSPECTIVE_CORRECTION_HINT);
	double over=5;
	double x_min=k_means.archivo->min_total.x-over;
	double x_max=k_means.archivo->max_total.x+over;
	double y_min=k_means.archivo->min_total.y-over;
	double y_max=k_means.archivo->max_total.y+over;
	
	
	glOrtho(x_min,x_max,y_min,y_max,-120-200,120+200);
	//punto_bajo_x,punto_alto_x,punto_bajo_y,punto_alto_y,fondo,delante
	
	
	
	

}
int main (int argc, char **argv) {
	
	
	
	k_means.iniciar();
	//k_means.imprimir();
	k_means.mostrar_rango_puntos();
	
	
	
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize (window_x,window_y);
	glutInitWindowPosition (0,0);
	glutCreateWindow ("Plantilla");
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(&window_redraw);
	///
	glutDisplayFunc (Pintar);
	///
	glutSpecialFunc(specialKeys);
	glClearColor(0,0,0,0);
	glutMainLoop();
	
	return 0;
}
