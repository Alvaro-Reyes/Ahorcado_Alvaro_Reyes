#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cstring>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

void Dibujo(char [10][10],char*,int);
void DibujoPalabra(int);
void PrintMatrix(char [10][10],char*,int ,int );
char* Copiar(char* ,const char* );
int Menu();

int main(int argc,char* argv[]){
	srand(time(0));
	char resp='s';
	
	cout<<"Bienvenido al juego de AHORCADO"<<endl;
	while(resp=='s'||resp=='S'){//while juego
		int contador=0,random=rand()%10+1;
		char* strng=new char[20];
		char* strngtemp=new char[20];
		char* adivina;
		switch(Menu()){
			case 1:{
				ifstream file("Facil.txt");

				while(file.getline(strng,20)){
					contador++;
					if (contador==random)
					{
						//cout<<"String "<<strng<<" "<<strlen(strng)<<endl;
						break;
					}
				}
					file.close();
				break;
			}
			case 2:{
				ifstream file("Intermedio.txt");

				while(file.getline(strng,20)){
					contador++;
					if (contador==random)
					{
						//cout<<"String "<<strng<<" "<<strlen(strng)<<endl;
						break;
					}
				}
					file.close();
				break;
			}
			case 3:{
				ifstream file("Dificil.txt");

				while(file.getline(strng,20)){
					contador++;
					if (contador==random)
					{
						//cout<<"String "<<strng<<" "<<strlen(strng)<<endl;
						break;
					}
				}
					file.close();
				break;
			}
		}
		Copiar(strngtemp ,strng );
		adivina=new char[strlen(strng)];
		for (int i = 0; i < strlen(strng); ++i)
		{
			adivina[i]='_';
		}
		char dibujo[10][10],again='s';
		bool win=false;
		int opcion,tries=0;
		
		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 10; ++j)
			{
				dibujo[i][j]=' ';
			}
		}
	
		for (int i = 2; i < 8; ++i)
		{
			dibujo[i][0]='|';
		}
		for (int i = 1; i < 5; ++i)
		{
			dibujo[1][i]='_';
		}
		dibujo[1][5]='_';
		dibujo[2][5]='|';
		Dibujo(dibujo,adivina,tries);

		while(tries<6&&win==false){
			//cout<<"String "<<strng<<endl;
			//cout<<"String Temp "<<strngtemp<<endl;
			
			cout<<"Elija una opcion\n1. Ingresar letra\n2. Adivinar la palabra\nIngrese su opcion: ";
			cin>>opcion;
			while(opcion<1||opcion>2){
				cout<<"Usted ha ingresado una opcion que no existe XD"<<endl;
				cout<<"Elija una opcion\n1. Ingresar letra\n2. Adivinar la palabra\nIngrese su opcion: ";
				cin>>opcion;
			}
			switch(opcion){
				case 1:
				{
					
					int error=0;
					char letra[20];
					cout<<"Ingrese la letra que desea probar: ";
					cin>>letra;
					while(strlen(letra)>1){
						cout<<"Se le pidio solo una letra\nIngrese la letra que desea probar: ";
						cin>>letra;
					}
					letra[0]=tolower(letra[0]);
					for (int i = 0; i < strlen(strngtemp); ++i)
					{
						if (strng[i]==letra[0])
						{
							adivina[i]=strngtemp[i];
							strngtemp[i]='*';
						}else{
							error++;
						}
					}
					if (error>=strlen(strngtemp))
					{
						tries++;
					}
					
					break;
				}
				case 2:
				{
					int error=0;
					char palabra[20];
					cout<<"Ingrese la palabra que desee probar: ";
					cin>>palabra;
					while(strlen(palabra)>strlen(strng)||strlen(palabra)<strlen(strng)){
						cout<<"La palabra que usted ingreso es muy corta o muy larga\nIngrese la palabra que desee probar: ";
						cin>>palabra;
					}
					palabra[strlen(palabra)]='\0';
					for (int i = 0; i < strlen(palabra); ++i)
					{
						palabra[i]=tolower(palabra[i]);
					}

					for (int i = 0; i < strlen(strng); ++i)
					{
						if (strng[i]!=palabra[i])
						{
							error++;
						}
					}
					if (error>0)
					{
						cout<<palabra<<" No es la palabra"<<endl;
						tries++;
					}else if(error==0){
						for (int i = 0; i < strlen(adivina); ++i)
						{
							adivina[i]=palabra[i];
						}
						win=true;
					}
					break;
				}
			}
			int contadorfinal=0;
			for (int i = 0; i < strlen(strng); ++i)
			{
				if (strng[i]==adivina[i])
				{
					contadorfinal++;
				}
			}
			if (contadorfinal>=strlen(strng))
			{
				win=true;
			}
			Dibujo(dibujo,adivina,tries);
			
		}
		if (tries==6)
		{
			cout<<"PERDIO "<<endl;		
			cout<<"La palabra era: \""<<strng<<"\" mejor suerte para la proxima :)"<<endl;
		}else if(win==true){
			cout<<"GANO!!! FELICIDADES"<<endl;

		}else{
			cout<<"Usted Abandono"<<endl;
			cout<<"La palabra era: \""<<strng<<"\" mejor suerte para la proxima :)"<<endl;
		}	
		cout<<"Desea volver a jugar? (s/n): "<<endl;
		cin>>resp;
		delete[] strng;
		delete[] adivina;
		delete[] strngtemp;
	}//fin while juego
		

	return 0;
}
void PrintMatrix(char ahorcado[10][10],char* adivina,int n,int m){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cout<<ahorcado[i][j];
		}
		cout<<endl;
	}
	cout<<"[ ";
	for (int i = 0; i < strlen(adivina); ++i)
	{
		cout<<adivina[i]<<" ";
	}
	cout<<" ]";
	cout<<endl<<endl;

}

void Dibujo(char dibujo[10][10],char* adivina,int fail){
	
	
	switch(fail){
		case 1:
		{
			dibujo[3][4]='(';
			dibujo[3][6]=')';
			dibujo[3][5]='"';
			break;
		}
		case 2:
		{
			dibujo[4][5]='|';
			dibujo[5][5]='|';
			break;
		}
		case 3:
		{
			dibujo[4][4]='/';
			break;
		}
		case 4:
		{
			dibujo[4][6]='\\';
			break;
		}
		case 5:
		{
			dibujo[6][4]='/';
			break;
		}
		case 6:
		{
			dibujo[3][4]='(';
			dibujo[3][6]=')';
			dibujo[3][5]='X';
			dibujo[6][6]='\\';
			break;
		}
	}
	PrintMatrix(dibujo,adivina,10,10);
}

char* Copiar(char* dst,const char* src){//version mera mera
	
	for (int i = 0; dst[i]=src[i]; ++i);
	
	return dst;
}
int Menu(){
	int opcion;
	cout<<"Nivel de Dificultad\n1. Facil\n2. Intermedio\n3. Dificil\nElija su opcion: ";
	cin>>opcion;
	while(opcion>3||opcion<1){
		cout<<"Usted no ingreso una opcion vailda\nNivel de Dificultad\n1. Facil\n2. Intermedio\n3. Dificil\nElija su opcion: ";
		cin>>opcion;
	}
	return opcion;
}
