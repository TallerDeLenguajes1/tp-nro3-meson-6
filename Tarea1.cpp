#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

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
void cargarcaract(struct TCaracteristicas * CaracPers);
void mostrarcaract(struct TCaracteristicas * CaracPers);
void cargar_datos(struct TDatos *puntero);
void mostrar_datos(struct TDatos *a);
void juego(struct TPersonaje, struct TPersonaje);

int main(void){
	
	srand(time(NULL));
	
	struct TPersonaje * Lista, p1, p2;
	int cant;
	
	printf("Cuantos personajes desea cargar?:\n");
	scanf("%d", &cant);
	
	Lista = (struct TPersonaje *) malloc(sizeof(struct TPersonaje)*cant);
	
	for (int t = 0; t < cant; ++t)
	{
		fflush(stdin);
		Lista[t].DatosPersonales = (struct TDatos * )malloc(sizeof(struct TDatos));
		Lista[t].Caracteristicas = (struct TCaracteristicas * )malloc(sizeof(struct TCaracteristicas));
		cargar_datos(Lista[t].DatosPersonales); // (personaje . datospersonales) (* Tdatos)
		cargarcaract(Lista[t].Caracteristicas);
	}
	

	p1= Lista[rand()%cant];
	p2= Lista[rand()%cant];

	juego(p1,p2);


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

//------------JUEGO-------------------------
void juego(struct TPersonaje p1, struct TPersonaje p2){
	
	int i=1;
	float PD1, ED1, VA1, PDEF1, DAN1, PD2, ED2, VA2, PDEF2, DAN2, MDP=50000;

	mostrar_datos(p1.DatosPersonales);
	mostrarcaract(p1.Caracteristicas);

	mostrar_datos(p2.DatosPersonales);
	mostrarcaract(p2.Caracteristicas);
			
	while(i <= 3 &&  p1.DatosPersonales->Salud>0 && p2.DatosPersonales->Salud >0){
		
		printf("\n---------ROUND %d---------\n", i);
		
		PD1 = p1.Caracteristicas->destreza * p1.Caracteristicas->fuerza * p1.Caracteristicas->Nivel;
		ED1 = rand()%99 +1;
		VA1 = (PD1 * ED1);
		PDEF1 = p1.Caracteristicas->Armadura * p1.Caracteristicas->velocidad;

		PD2 = p2.Caracteristicas->destreza * p2.Caracteristicas->fuerza * p2.Caracteristicas->Nivel;
		ED2 = rand()%99 +1;
		VA2 = PD2 * ED2;
		PDEF2 = p2.Caracteristicas->Armadura * p2.Caracteristicas->velocidad;

		DAN1 = ((VA1-PDEF2)/MDP)*100;
		DAN2 = ((VA2-PDEF1)/MDP)*100;

		p1.DatosPersonales->Salud = p1.DatosPersonales->Salud - DAN2;
		p2.DatosPersonales->Salud = p2.DatosPersonales->Salud - DAN1;

		printf("\n%s\n  Danio recibido: %.2f  | Salud: %.2f ", p1.DatosPersonales->ApellidoNombre, DAN2, p1.DatosPersonales->Salud);
		printf("\n%s\n  Danio recibido: %.2f  | Salud: %.2f ", p2.DatosPersonales->ApellidoNombre, DAN1, p2.DatosPersonales->Salud);
		i = i+1;

	}
	if(p1.DatosPersonales->Salud == p2.DatosPersonales->Salud){
		printf("\n ========EMPATE=========");
	}else{
		if(p1.DatosPersonales->Salud > p2.DatosPersonales->Salud){
			printf("\n\n=========== Ganador: %s ===============", p1.DatosPersonales->ApellidoNombre);
		}else{
			printf("\n\n=========== Ganador: %s ===============", p2.DatosPersonales->ApellidoNombre);
		}
	}
}



// Daño provocado en formula el EP no va