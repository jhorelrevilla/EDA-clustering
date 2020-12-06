#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#define max 9999999
#define adicional 1
typedef long double ld;
using namespace std;

class Punto{
public:
	ld x,y;
	int cluster=-1;
	Punto(ld t_x=0,ld t_y=0){
		x=t_x;y=t_y;
	}
	void imprimir(){
		cout<<x<<" , "<<y<<" \t\tgrupo: "<<cluster<<endl;
	}

};
//////////////////////////////////////////
template<size_t size>
class Text {
protected:
	ifstream *archivo_db;
public:
	Punto min_total;
	Punto max_total;
	Text(string name_file):min_total(max,max),max_total(-max,-max){
		archivo_db=new ifstream(name_file);
	}
	///
	Punto* get_db(){
		Punto *temp=new Punto[size];
		int cont=0;
		if(archivo_db->is_open()){
			string linea;
			string::size_type sz;
			while(getline(*archivo_db,linea) && cont<=size){
				if(cont==0){
					cont++;
					continue;
				}
				for(int i=0;i<5;++i){
					int pos=linea.find(",");
					linea=linea.substr(pos+1,linea.size());
				}
				string temporal;
				long double n_temp;
				int pos=linea.find(",");
				///primer valor
				temporal=linea.substr(0,pos);
				n_temp=stod(temporal,&sz);
				linea=linea.substr(pos+1,linea.size());
				///segundo valor
				pos=linea.find(",");
				temporal=linea.substr(0,pos);
				if(n_temp==0 && stod(temporal,&sz)==0){
					continue;
				}
				temp[cont-1].y=stod(temporal,&sz);
				temp[cont-1].x=n_temp;
				///

				if(temp[cont-1].x < min_total.x){
					min_total.x=temp[cont-1].x;
				}
				if(temp[cont-1].y < min_total.y){
					min_total.y=temp[cont-1].y;
				}
				
				if(temp[cont-1].x > max_total.x){
					max_total.x=temp[cont-1].x;
				}
				if(temp[cont-1].y > max_total.y){
					max_total.y=temp[cont-1].y;
				}
				cont++;
			}
			return temp;
		}
		min_total.x-=adicional;
		min_total.y-=adicional;
		
		max_total.x+=adicional;
		max_total.y+=adicional;
		//el espacio 6 y 7 pickip_long y pickup_latitud
	}
	///
	void mostrar(){
		cout<<"--------minimo---------"<<endl;	
		min_total.imprimir();
		cout<<"--------maximo---------"<<endl;	
		max_total.imprimir();
	}
	///
	~Text(){
		delete archivo_db;
	}
private:
};

#endif



















