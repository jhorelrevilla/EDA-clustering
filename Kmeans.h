#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenGL/glu.h>
# include <GLUT/glut.h>
#else
# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>
#endif
#ifndef KMEANS_H
#define KMEANS_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include "Text.h"

struct gl_puntos{
	int r,g,b;
	gl_puntos(int t_r=0,int t_g=0,int t_b=0){
		r=t_r;g=t_g;b=t_b;
	}
	void n_color(int t_r,int t_g,int t_b){
		r=t_r;g=t_g;b=t_b;
	}
};
////////////////////////////////
template<size_t num_puntos>
class Kmeans {
public:
	int num_cluster;
	int max_iteraciones;
	vector<Punto> grupos;
	Punto *conj_puntos;
	Text<num_puntos> *archivo;
	vector<gl_puntos> c;
	///
	Kmeans(string file_name, int k,int max_it){
		num_cluster=k;
		max_iteraciones=max_it;
		archivo=new Text<num_puntos>(file_name);
		conj_puntos=archivo->get_db();
		grupos.resize(k);
		c.resize(4);
		
		c[0].n_color(255,0,0);//rojo
		c[1].n_color(0,255,0);//verde
		c[2].n_color(0,0,255);//azul
		c[3].n_color(255,255,0);//amarillo
	}
	///
	void imprimir(int pos){
		(conj_puntos+pos)->imprimir();
	}
	///
	void imprimir(){
		for(int i=0;i<num_puntos;++i){
			(conj_puntos+i)->imprimir();
		}
	}
	///
	void mostrar_rango_puntos(){
		archivo->mostrar();
	}
	///
	void iniciar(){
		///que este dentro de los puntos 
		
		for(int i=0;i<num_cluster;++i){
			grupos[i].x = rand() % (int)(archivo->max_total.x  - archivo->min_total.x +1) + archivo->min_total.x;
			
			grupos[i].y = rand() % (int)(archivo->max_total.y  - archivo->min_total.y +1) + archivo->min_total.y;;
		}
		///
		for(int i=0;i<max_iteraciones;++i){
			for(int j=0;j<num_puntos;++j){
				double* dists = new double[num_cluster];
				for (int p = 0; p < num_cluster; ++p) {
					
					double a = std::abs((conj_puntos+j)->y - grupos[p].y);	// length in y-axis
					double b = std::abs((conj_puntos+j)->x - grupos[p].x);	// length in x-axis
					dists[p] = std::sqrt(std::pow(a, 2) + std::pow(b, 2));	// distance from point to center
				}
				// colocar al mas cercano
				(conj_puntos+j)->cluster = std::min_element(dists, dists + num_cluster) - dists;
				delete[] dists;
			}
			double s_x[num_cluster]={0},s_y[num_cluster]={0};
			int cont[num_cluster]={0};
			for(int w=0;w<num_puntos;++w){
				s_x[ (conj_puntos+w)->cluster]+=(conj_puntos+w)->x;
				s_y[ (conj_puntos+w)->cluster]+=(conj_puntos+w)->y;
				cont[(conj_puntos+w)->cluster]++;
			}
			for(int w=0;w<num_cluster;++w){
				grupos[w].x=s_x[w]/cont[w];
				grupos[w].y=s_y[w]/cont[w];
			}
		}
	}
	void mostrar_puntos(){
		glPointSize(2);
		glBegin(GL_POINTS);
			
			for(int i=0;i<num_puntos;++i){
				int clus=(conj_puntos+i)->cluster;
				if(clus==-1){
					glColor3f(1,1,1);
					glVertex2d((conj_puntos+i)->x,(conj_puntos+i)->y);
				}
				glColor3f(c[clus].r,c[clus].g,c[clus].b);
				glVertex2d((conj_puntos+i)->x,(conj_puntos+i)->y);
			}
			
		glEnd();
		glutSwapBuffers();
	}
	~Kmeans(){
		delete archivo;
	}
private:
};

#endif































