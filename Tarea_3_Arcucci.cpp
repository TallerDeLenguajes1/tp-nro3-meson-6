#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Declaracion de estructuras
enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[5][20]={"Merodeador", "Rompehuesos", "Algoritmico", "Proscripto", "Cruzamontanias"};
char Apellidos[5][20]={" Furioso", " Mistico", " Peregrino", " Galactico", " Sabio"};
//Estructura de Datos
typedef struct TDatos {
	TRaza Raza; //nota 1
	char *ApellidoNombre; //nota 2
	int edad; //entre 0 a 300
	double Salud;//100
}DATOS;
//Estructura de Caracteristicas
typedef struct TCaracteristicas{
	int velocidad;// 1 a 10
	int destreza; //1 a 5
	int fuerza;//1 a 10
	int Nivel; //1 a 10
	int Armadura; //1 a 10
}CARACTERISTICAS;
//Estructura de Personaje
typedef struct TPersonaje {
	TDatos * DatosPersonales;  // null
	TCaracteristicas * Caracteristicas; // null 
}PERSONAJE;
//Declaracion de funciones
void cargarcaract(struct TCaracteristicas * CaracPers);
void mostrarcaract(struct TCaracteristicas * CaracPers);
void cargar_datos(struct TDatos *puntero);
void mostrar_datos(struct TDatos *a);
//Main
int main(void){
	srand(time(NULL));//Randomiza la seed
	//Declaro un puntero de tipo PERSONAJE
	PERSONAJE *personajes = NULL;
	int cant;
	printf("Cuantos personajes desea crear?");
	scanf("%d",&cant);
	//Asigno la memoria correspondiente a la lista de personajes
	personajes = (PERSONAJE*) malloc(sizeof(PERSONAJE)*cant);
	//Cargo los personajes
	for (int i = 0; i < cant; ++i)
	{
		personajes[i].DatosPersonales = (DATOS*) malloc(sizeof(DATOS));
		personajes[i].Caracteristicas = (CARACTERISTICAS*) malloc(sizeof(CARACTERISTICAS));
		cargar_datos(personajes[i].DatosPersonales);
		cargarcaract(personajes[i].Caracteristicas);
	}
	//Muestro los datos
	for (int j = 0; j < cant; ++j)
	{
		motrar_datos(personajes[j].DatosPersonales);
		mostrarcaract(personajes[j].Caracteristicas);
	}
	return 0;
}


//Definicion de funciones
//Funciones de Caracteristicas
void cargarcaract(struct TCaracteristicas * CaracPers){
	CaracPers->velocidad = rand()%10 + 1;
	CaracPers->destreza = rand()%5 + 1;
	CaracPers->fuerza = rand()%10 + 1;
	CaracPers->Nivel = rand()%10 + 1;
	CaracPers->Armadura = rand()%10 + 1;
}
void mostrarcaract(struct TCaracteristicas * CaracPers){
	printf("Velocidad: %d\n", CaracPers->velocidad);
	printf("Destreza: %d\n", CaracPers->destreza);
	printf("Fuerza: %d\n", CaracPers->fuerza);
	printf("Nivel: %d\n", CaracPers->Nivel);
	printf("Armadura: %d\n", CaracPers->Armadura);
}
//Funciones de Datos
void cargar_datos(struct TDatos *puntero){
	char AM[100];
	strcpy(AM, Nombres[rand()%5]);
	strcat(AM, Apellidos[rand()%5]);
	puntero->ApellidoNombre = (char*) malloc(sizeof(char) * strlen(AM) + 2);
	switch(rand()%5){
		case 0:
			puntero->Raza = Orco;
			break;
		case 1:
			puntero->Raza = Humano;
			break;
		case 2:
			puntero->Raza = Mago;
			break;
		case 3:
			puntero->Raza = Enano;
			break;
		case 4:
			puntero->Raza = Elfo;
			break;
	}
	strcpy(puntero->ApellidoNombre, AM);
	puntero->edad = rand()%301;
	puntero->Salud = 100;
	printf("\n");
}
void mostrar_datos(struct TDatos *a){
	printf("\nRaza:");
	switch(a->Raza){
		case 0:
			printf("Orco\n");
			break;
		case 1:
			printf("Humano\n");
			break;
		case 2:
			printf("Mago\n");
			break;
		case 3:
			printf("Enano\n");
			break;
		case 4:
			printf("Elfo\n");
			break;
	}
	printf("Apellido y Nombre: %s \n", a->ApellidoNombre);
	printf("Edad: %d", a->edad);
	printf("\nSalud: %.2lf", a->Salud);
	printf("\n");
}
//Daño provocado (VA-PDEF)/MDP)*100