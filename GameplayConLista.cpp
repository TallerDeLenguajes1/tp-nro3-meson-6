#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define MDP 50000.000

enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[5][20]={"Merodeador", "Rompehuesos", "Algoritmico", "Proscripto", "Cruzamontanias"};
char Apellidos[5][20]={" Furioso", " Mistico", " Peregrino", " Galactico", " Sabio"};

struct TDatos {
	TRaza Raza; //nota 1
	char *ApellidoNombre; //nota 2
	int edad; //entre 0 a 300
	double Salud;//100
};
struct TCaracteristicas{
	int velocidad;// 1 a 10
	int destreza; //1 a 5
	int fuerza;//1 a 10
	int Nivel; //1 a 10
	int Armadura; //1 a 10
};
struct TPersonaje {
	TDatos * DatosPersonales;  // null
	TCaracteristicas * Caracteristicas; // null 
};
struct nodo {
	TPersonaje Datos;
	struct nodo * siguiente;
};

void cargarcaract(struct TCaracteristicas * CaracPers);
void mostrarcaract(struct TCaracteristicas * CaracPers);
void cargar_datos(struct TDatos *puntero);
void mostrar_datos(struct TDatos *a);

int main(void){
	srand(time(NULL));
	struct nodo * Lista, * aux, * nuevo;
	int cant,cont = 0, num;

	printf("Cuantos personajes desea cargar?:\n");
	scanf("%d", &cant);

	Lista = NULL;

	for (int t = 0; t < cant; ++t)
	{
		nuevo = (struct nodo *) malloc(sizeof(struct nodo));
		nuevo->Datos.DatosPersonales = (struct TDatos * )malloc(sizeof(struct TDatos));
		nuevo->Datos.Caracteristicas = (struct TCaracteristicas * )malloc(sizeof(struct TCaracteristicas));
		cargar_datos(nuevo->Datos.DatosPersonales); 
		cargarcaract(nuevo->Datos.Caracteristicas);
		nuevo->siguiente = Lista;
		Lista = nuevo;
	}
	aux = Lista;
	while (aux != NULL){
		mostrar_datos(aux->Datos.DatosPersonales);
		mostrarcaract(aux->Datos.Caracteristicas);
		aux = aux->siguiente;
	}
	num = rand()%cant;
	printf("%d\n", num);
	aux = Lista;
	while (aux != NULL && cont != num){
		cont++;
		aux = aux->siguiente;
	}
	struct TPersonaje personaje1 = aux->Datos;
	aux = Lista;
	num = rand()%cant;
	printf("%d\n", num);
	cont = 0;
	while (aux != NULL && cont != num){
		cont++;
		aux = aux->siguiente;
	}
	struct TPersonaje personaje2 = aux->Datos;
	mostrar_datos(personaje1.DatosPersonales);
	mostrarcaract(personaje1.Caracteristicas);
	printf("\nVS\n");
	mostrar_datos(personaje2.DatosPersonales);
	mostrarcaract(personaje2.Caracteristicas);


	printf("-------------------------FIGHT!!!!-------------------------\n");
	int PD1, PD2, ED1, ED2, VA1, VA2, PDEF1, PDEF2;
	double Danio1,Danio2;
	PD1 = personaje1.Caracteristicas->destreza * personaje1.Caracteristicas->fuerza * personaje1.Caracteristicas->Nivel;
	PD2 = personaje2.Caracteristicas->destreza * personaje2.Caracteristicas->fuerza * personaje2.Caracteristicas->Nivel;
	ED1 = rand() % 100 + 1;
	ED2 = rand() % 100 + 1;
	VA1 = PD1 * ED1;
	VA2 = PD2 * ED2;
	PDEF1 = personaje1.Caracteristicas->Armadura * personaje1.Caracteristicas->velocidad;
	PDEF2 = personaje2.Caracteristicas->Armadura * personaje2.Caracteristicas->velocidad;
	Danio1 = ((VA1 - PDEF2)/MDP)*100; //daño que se provoca al segundo jugador 
	Danio2 = ((VA2 - PDEF1)/MDP)*100; //daño que se provoca al primer jugador 
	//printf("%d\n", PDEF1);
	//printf("%d\n", PDEF2);
	personaje1.DatosPersonales->Salud = personaje1.DatosPersonales->Salud - Danio2;
	personaje2.DatosPersonales->Salud = personaje2.DatosPersonales->Salud - Danio1;
	/*printf("%lf\n", personaje1.DatosPersonales->Salud );
	printf("%lf\n", personaje2.DatosPersonales->Salud );*/
	/*for (int k = 0; k < cant; ++k)
	{
		printf("\nPersonaje %d:\n", (k+1));
		mostrar_datos(Lista[k].DatosPersonales);
		mostrarcaract(Lista[k].Caracteristicas);
	}*/
	if (personaje1.DatosPersonales->Salud > personaje2.DatosPersonales->Salud)
	{
		printf("Gana Personaje 1!!!!\n");
	}else if(personaje1.DatosPersonales->Salud < personaje2.DatosPersonales->Salud){ 
		printf("Gana Personaje 2!!!!\n");
	}else{
		printf("Menudo empate\n");
	}
	return 0;
}

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