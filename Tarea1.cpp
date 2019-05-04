#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#define indef -999

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
	struct TDatos * DatosPersonales;  // null
	struct TCaracteristicas * Caracteristicas; // null 
	int id;
};

struct nodo{
	struct TPersonaje pj;
	struct nodo *siguiente;
};

typedef struct nodo *lista;


lista insertarIni(lista);
lista insertarFin(lista);
lista eliminar(lista);
lista eliminarX(lista,int);
lista buscar(lista,int);

void cargarCaract(struct TCaracteristicas * CaracPers);
void mostrarCaract(struct TCaracteristicas * CaracPers);
void cargarDatos(struct TDatos *puntero);
void mostrarDatos(struct TDatos *a);
void juego(lista);


int main(void){
	
	srand(time(NULL));
	
	lista jugadores = NULL;
	int p1, p2;
	int cant;
	
	printf("Cuantos personajes desea cargar?:\n");
	scanf("%d", &cant);
	fflush(stdin);
	
	for (int t = 0; t < cant; t++)
	{	
		jugadores = insertarIni(jugadores);
	}

	juego(jugadores);

	return 0;
}

void cargarCaract(struct TCaracteristicas * CaracPers){
	CaracPers->velocidad = rand()%10 + 1;
	CaracPers->destreza = rand()%5 + 1;
	CaracPers->fuerza = rand()%10 + 1;
	CaracPers->Nivel = rand()%10 + 1;
	CaracPers->Armadura = rand()%10 + 1;
}

void mostrarCaract(struct TCaracteristicas * CaracPers){
	printf("Velocidad: %d\n", CaracPers->velocidad);
	printf("Destreza: %d\n", CaracPers->destreza);
	printf("Fuerza: %d\n", CaracPers->fuerza);
	printf("Nivel: %d\n", CaracPers->Nivel);
	printf("Armadura: %d\n", CaracPers->Armadura);
}

void cargarDatos(struct TDatos *puntero){
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

void mostrarDatos(struct TDatos *a){
	
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

//------------JUEGO-------------------------
void juego(lista l){
	
	int per1, per2, cont=0, i=1;
	float PD1, ED1, VA1, PDEF1, DAN1, PD2, ED2, VA2, PDEF2, DAN2, MDP=50000;
	
	struct nodo *p1 = NULL, *p2 = NULL;

	printf("\n Ingrese primer personaje que va a pelear: ");
	scanf("%d",&per1);
	printf("\n Ingrese segundo personaje que va a pelear: ");
	scanf("%d",&per2);
	
	p1= buscar(l,per1);
	p2= buscar(l,per2);

	mostrarDatos(p1->pj.DatosPersonales);
	mostrarCaract(p1->pj.Caracteristicas);

	mostrarDatos(p2->pj.DatosPersonales);
	mostrarCaract(p2->pj.Caracteristicas);


			
	while(i <= 3 &&  p1->pj.DatosPersonales->Salud>0 && p2->pj.DatosPersonales->Salud >0){
		
		printf("\n---------ROUND %d---------\n", i);
		
		PD1 = p1->pj.Caracteristicas->destreza * p1->pj.Caracteristicas->fuerza * p1->pj.Caracteristicas->Nivel;
		ED1 = rand()%99 +1;
		VA1 = (PD1 * ED1);
		PDEF1 = p1->pj.Caracteristicas->Armadura * p1->pj.Caracteristicas->velocidad;

		PD2 = p2->pj.Caracteristicas->destreza * p2->pj.Caracteristicas->fuerza * p2->pj.Caracteristicas->Nivel;
		ED2 = rand()%99 +1;
		VA2 = PD2 * ED2;
		PDEF2 = p2->pj.Caracteristicas->Armadura * p2->pj.Caracteristicas->velocidad;

		DAN1 = ((VA1-PDEF2)/MDP)*100;
		DAN2 = ((VA2-PDEF1)/MDP)*100;

		p1->pj.DatosPersonales->Salud = p1->pj.DatosPersonales->Salud - DAN2;
		p2->pj.DatosPersonales->Salud = p2->pj.DatosPersonales->Salud - DAN1;

		printf("\n%s\n  Danio recibido: %.2f  | Salud: %.2f ", p1->pj.DatosPersonales->ApellidoNombre, DAN2, p1->pj.DatosPersonales->Salud);
		printf("\n%s\n  Danio recibido: %.2f  | Salud: %.2f ", p2->pj.DatosPersonales->ApellidoNombre, DAN1, p2->pj.DatosPersonales->Salud);
		i = i+1;

	}
	if(p1->pj.DatosPersonales->Salud == p2->pj.DatosPersonales->Salud){
		printf("\n ========EMPATE=========");
	}else{
		if(p1->pj.DatosPersonales->Salud > p2->pj.DatosPersonales->Salud){
			printf("\n\n=========== Ganador: %s ===============", p1->pj.DatosPersonales->ApellidoNombre);
		}else{
			printf("\n\n=========== Ganador: %s ===============", p2->pj.DatosPersonales->ApellidoNombre);
		}
	}
}


//===========================================

/*struct TDatos {
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

struct nodo{
	struct TPersonaje pj;
	int id;
	struct nodo *siguiente;
};

*/

lista insertarIni(lista l){
	struct nodo *nuevo;

	nuevo= (struct nodo*) malloc(sizeof(struct nodo));

	nuevo->pj.DatosPersonales = (struct TDatos * )malloc(sizeof(struct TDatos));
	nuevo->pj.Caracteristicas = (struct TCaracteristicas * )malloc(sizeof(struct TCaracteristicas));
	
	nuevo->pj.id = rand()%999+1;
	cargarDatos(nuevo->pj.DatosPersonales); 
	cargarCaract(nuevo->pj.Caracteristicas);


	nuevo->siguiente = l;
	l = nuevo;

	return l;
}


lista insertarFin(lista l){
	struct nodo *nuevo;
	lista aux = l;
	
	nuevo = (struct nodo*) malloc(sizeof(struct nodo));

	nuevo->pj.DatosPersonales = (struct TDatos * )malloc(sizeof(struct TDatos));
	nuevo->pj.Caracteristicas = (struct TCaracteristicas * )malloc(sizeof(struct TCaracteristicas));

	nuevo->pj.id = rand()%999+1;
	cargarDatos(nuevo->pj.DatosPersonales); 
	cargarCaract(nuevo->pj.Caracteristicas);

	while(aux->siguiente != NULL ){
		aux = aux->siguiente;
	}
	nuevo->siguiente = aux->siguiente;
	aux->siguiente = nuevo;

	return l; 
}
	

lista eliminar(lista l){
	struct nodo *aux;
	aux = l;
	l = l->siguiente;
	free(aux); 

	return l; 
}


lista eliminarX(lista l,int x){
	lista aux = l;
	struct nodo *auxborrar;
	while( aux != NULL && aux->siguiente->pj.id != x && aux->pj.id !=x){
		aux = aux->siguiente;
	}

	if(aux == NULL){
		printf("\nNo se encontro %d para eliminar.", x);
	}else{
		auxborrar= aux->siguiente;
		aux->siguiente = aux->siguiente->siguiente;
		free(auxborrar);
	}
	return l; 
}


lista buscar(lista l, int x){
	lista aux = l; 
	while(aux != NULL && aux->pj.id != x ){
		aux = aux->siguiente;
	}
	return aux;
}
