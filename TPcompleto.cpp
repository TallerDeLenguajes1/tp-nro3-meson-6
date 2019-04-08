#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Declaracion de estructuras
enum TRaza{Orco, Humano, Mago, Enano, Elfo};
char Nombres[5][20]={"Merodeador", "Rompehuesos", "Algoritmico", "Proscripto", "Cruzamontanias"};
char Apellidos[5][20]={" Furioso", " Mistico", " Peregrino", " Galactico", " Sabio"};
//Estructura de Datos
struct TDatos {
	TRaza Raza; //nota 1
	char *ApellidoNombre; //nota 2
	int edad; //entre 0 a 300
	double Salud;//100
}typedef DATOS;
//Estructura de Caracteristicas
struct TCaracteristicas{
	int velocidad;// 1 a 10
	int destreza; //1 a 5
	int fuerza;//1 a 10
	int Nivel; //1 a 10
	int Armadura; //1 a 10
}typedef CARACTERISTICAS;
//Estructura de Personaje
struct TPersonaje {
	TDatos * DatosPersonales;  // null
	TCaracteristicas * Caracteristicas; // null 
}typedef PERSONAJE;
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
		//Asigno la memoria a las dos estructuras pertenecientes a personajes
		personajes[i].DatosPersonales = (DATOS*) malloc(sizeof(DATOS));
		personajes[i].Caracteristicas = (CARACTERISTICAS*) malloc(sizeof(CARACTERISTICAS));
		cargar_datos(personajes[i].DatosPersonales);
		cargarcaract(personajes[i].Caracteristicas);
	}
	//Muestro los datos
	for (int j = 0; j < cant; ++j)
	{
		mostrar_datos(personajes[j].DatosPersonales);
		mostrarcaract(personajes[j].Caracteristicas);
	}
	//Implementacion del juego
	int pers1,pers2;
	printf("Comenzará el juego!\n");
	printf("Jugador 1, seleccione a su personaje:(Ingrese un numero hasta %d)\n", cant);
	scanf("%d",&pers1);
	printf("Jugador 2, seleccione a su personaje:(Ingrese un numero hasta %d)\n", cant);
	scanf("%d",&pers2);
	//Combate
	combate(personajes,pers1,pers2);
	//Fin del main
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
//Funcion de combate (Me parecio mas conveniente hacer una funcion antes que hacer todo en el main)
//Esta funcion toma la lista de personajes y los valores ingresados por los jugadores
void combate(PERSONAJE * lista_de_personajes, int pers1, int pers2){
	//Daño maximo
	int dm = 50000;
	//Variable para guardar el daño
	int damage;
	//Calculo previamente el poder de disparo de ambos personajes
	int poder_de_disparo1 = lista_de_personajes[pers1].Caracteristicas.destreza * lista_de_personajes[pers1].Caracteristicas.fuerza * lista_de_personajes[pers1].Caracteristicas.Nivel;
	int poder_de_disparo2 = lista_de_personajes[pers2].Caracteristicas.destreza * lista_de_personajes[pers2].Caracteristicas.fuerza * lista_de_personajes[pers2].Caracteristicas.Nivel;
	//Hago lo mismo con el poder defensivo
	int poder_defensivo1 = lista_de_personajes[pers1].Caracteristicas.Armadura * lista_de_personajes[pers1].Caracteristicas.velocidad;
	int poder_defensivo2 = lista_de_personajes[pers2].Caracteristicas.Armadura * lista_de_personajes[pers2].Caracteristicas.velocidad;
	//Implementacion de los valores
	printf("El combate comienza!\n");
	//Muestro la salud de ambos personajes antes del combate
	printf("La salud de %s es: %d\n", lista_de_personajes[pers1].DatosPersonales.ApellidoNombre, lista_de_personajes[pers1].DatosPersonales.Salud);
	printf("La salud de %s es: %d\n", lista_de_personajes[pers2].DatosPersonales.ApellidoNombre, lista_de_personajes[pers2].DatosPersonales.Salud);
	for (int i = 0; i < 3; ++i)
	{	
		//Ataca el primer personaje
		printf("%s Ataca!\n",lista_de_personajes[pers1].DatosPersonales.ApellidoNombre);
		//Calculo el daño que causará
		damage = (((poder_de_disparo1 * 1+rand()%100) - poder_defensivo2)/dm) * 100;
		printf("%s ha causado %d puntos de daño!\n", lista_de_personajes[pers1].DatosPersonales.ApellidoNombre, damage);
		//Resto el daño a la salud del segundo personaje
		lista_de_personajes[pers2].DatosPersonales.Salud = lista_de_personajes[pers2].DatosPersonales.Salud - damage;
		//Controlo la condicion de victoria
		if (lista_de_personajes[pers2].DatosPersonales.Salud <= 0)
		{
			printf("La salud de %s es ahora: %d\n", lista_de_personajes[pers2].DatosPersonales.ApellidoNombre, lista_de_personajes[pers2].DatosPersonales.Salud);
			printf("%s ha perdido!!\n", lista_de_personajes[pers2].DatosPersonales.ApellidoNombre);
			break;
		}
		//Continua el combate
		printf("La salud de %s es ahora: %d\n", lista_de_personajes[pers2].DatosPersonales.ApellidoNombre, lista_de_personajes[pers2].DatosPersonales.Salud);
		//Pausa
		printf("Presione enter para continuar...\n");
		getch();
		//Ataca el segundo personaje
		printf("%s Ataca!\n",lista_de_personajes[pers2].DatosPersonales.ApellidoNombre);
		//Calculo el daño que causará
		damage = (((poder_de_disparo2 * 1+rand()%100) - poder_defensivo1)/dm) * 100;
		printf("%s ha causado %d puntos de daño!\n", lista_de_personajes[pers2].DatosPersonales.ApellidoNombre, damage);
		//Resto el daño a la salud del primer personaje
		lista_de_personajes[pers1].DatosPersonales.Salud = lista_de_personajes[pers1].DatosPersonales.Salud - damage;
		//Controlo la condicion de victoria
		if (lista_de_personajes[pers1].DatosPersonales.Salud <= 0)
		{
			printf("La salud de %s es ahora: %d\n", lista_de_personajes[pers1].DatosPersonales.ApellidoNombre, lista_de_personajes[pers1].DatosPersonales.Salud);
			printf("%s ha perdido!!\n", lista_de_personajes[pers1].DatosPersonales.ApellidoNombre);
			break;
		}
		//Continua el combate
		printf("La salud de %s es ahora: %d\n", lista_de_personajes[pers1].DatosPersonales.ApellidoNombre, lista_de_personajes[pers1].DatosPersonales.Salud);
		//Pausa
		printf("Presione enter para continuar...\n");
		getch();
	}
}
