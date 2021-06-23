#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
#include <pthread.h>
     
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

MYSQL *conn;
int err;
MYSQL_RES *resultado;
MYSQL_ROW row;
char consulta [200];
int contador;
int i;
int sockets[100];


typedef struct {
	char nombre [20];
	int socket;
}Conectado;

typedef struct{
	Conectado conectados [100];
	int num;
}ListaConectados;

ListaConectados milista;

<<<<<<< HEAD
<<<<<<< HEAD
void *AtenderCliente (void *socket) {
=======
=======
>>>>>>> dev-v5
typedef struct{
	int Id;
	char jugadores[200];
	int numerojugadores;
	int turno;
}Partida;

typedef struct{
	Partida partidas[100];
	int num;
}ListaPartidas;

ListaPartidas mispartidas;

void *AtenderCliente (void *socket){
<<<<<<< HEAD
>>>>>>> dev-v4
=======
>>>>>>> dev-v5
	
	int sock_conn;
	int *s;
	s= (int *) socket;
	sock_conn= *s;
	
	//int socket_conn = * (int *) socket;
	
	char peticion[512];
	char peticion2[512];
	char respuesta[512];
	int ret;
	
	//Bucle de atencion al cliente
	int terminar = 0;
	
<<<<<<< HEAD
<<<<<<< HEAD
	while (terminar == 0)
	{
=======
	while (terminar == 0){
>>>>>>> dev-v4
=======
	while (terminar == 0){
>>>>>>> dev-v5
		
		//Dejamos la consulta en la variable peticion

		ret=read(sock_conn,peticion, sizeof(peticion));

		
		
		printf("Recibido\n");
		
		
		//Ponemos marca de fin de string para que no escriba lo que hay despues del buffer
		peticion[ret]='\0';
		
		//Escribimos la peticion en consola
		printf("La peticion es: %s\n", peticion);
		
		//que quieren
		char *p = strtok(peticion,"/");
		printf("TEST\n");
		int codigo = atoi(p);
		char nombre[20];
		char usuarioconn[20];
		char contrasena[20];
<<<<<<< HEAD
<<<<<<< HEAD
	
		
		if (codigo != 0)
 		{
=======
		int numerojugadores;
		int numForm;
		
		if ((codigo != 0) && (codigo <= 5)){
>>>>>>> dev-v4
=======
		int numerojugadores;
		int numForm;
		
		if ((codigo != 0) && (codigo <= 5)){
>>>>>>> dev-v5
			p = strtok(NULL,"/");
			strcpy(nombre, p);
			p = strtok(NULL,"/");
			strcpy(contrasena, p);
		}
		
<<<<<<< HEAD
<<<<<<< HEAD
		if (codigo == 0)
		{
			
			pthread_mutex_lock(&mutex);
			int res= Eliminar(&milista, usuarioconn);
=======
		if (codigo == 0){ //Desconecta al usuario
		

			char conectados[512];
			pthread_mutex_lock(&mutex);
			int res= Eliminar(&milista, usuarioconn);
			DameConectados(&milista, conectados);
			printf("Los conectados son: %s\n", conectados);
>>>>>>> dev-v4
=======
		if (codigo == 0){ //Desconecta al usuario
		

			char conectados[512];
			pthread_mutex_lock(&mutex);
			int res= Eliminar(&milista, usuarioconn);
			DameConectados(&milista, conectados);
			printf("Los conectados son: %s\n", conectados);
>>>>>>> dev-v5
			pthread_mutex_unlock(&mutex);
			if (res == 0)
				printf("Eliminado correctamente\n"); 
			else
				printf("No eliminado\n");  
			
			sprintf(respuesta, "0/Desconectado");
			printf("%s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
			terminar = 1;
		}
		
<<<<<<< HEAD
<<<<<<< HEAD
		if (codigo==1) //Consulta 1
		{
=======
		if (codigo==1){ //Consulta 1
		
>>>>>>> dev-v5
			pthread_mutex_lock(&mutex);
			consulta1(respuesta);
			pthread_mutex_unlock(&mutex);
			
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
		}
		else if (codigo == 2){ //Consulta 2
		
			pthread_mutex_lock(&mutex);
<<<<<<< HEAD
			consulta2(consulta, resultado, respuesta, nombre);
=======
		if (codigo==1){ //Consulta 1
		
			pthread_mutex_lock(&mutex);
			consulta1(respuesta);
>>>>>>> dev-v4
=======
			consulta2(respuesta, nombre);
>>>>>>> dev-v5
			pthread_mutex_unlock(&mutex);
			
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
		}
<<<<<<< HEAD
<<<<<<< HEAD
		else if (codigo == 3) //Consulta 3
		{
=======
		else if (codigo == 3){ //Consulta 3
		
>>>>>>> dev-v5
			strcpy(usuarioconn, nombre);
			pthread_mutex_lock(&mutex);
			int rescon3= consulta3(respuesta, nombre);
			pthread_mutex_unlock(&mutex);
			if(rescon3 == 0){
				printf("Usuario en la base de datos\n");
			}
			else
			   printf("Usuario no se encuentra en la base de datos\n");
			
=======
		else if (codigo == 2){ //Consulta 2
		
			pthread_mutex_lock(&mutex);
			consulta2(respuesta, nombre);
			pthread_mutex_unlock(&mutex);
>>>>>>> dev-v4
			
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
		}
<<<<<<< HEAD
<<<<<<< HEAD
		else if (codigo == 4)
			{   
=======
		else if (codigo == 4){ //Autentifica y conecta a un usuario
			   
>>>>>>> dev-v5
				strcpy(usuarioconn, nombre);
				char password[50];
				consulta3(password, nombre);
				
				char *c = strtok(password,"/");
				c = strtok(NULL,"/");
				strcpy(password, c);
				
				
				if (strcmp(password, contrasena)==0)
				{
					pthread_mutex_lock(&mutex);
					int respon= Pon(&milista, nombre, sock_conn);
					pthread_mutex_unlock(&mutex);
					if(respon == 0){
						printf("Usuario añadido\n");
					}
					else
					   printf("Usuario no añadido\n");
					
					sprintf(respuesta, "4/%s", contrasena);
				}
				else
				{
					
					sprintf(respuesta, "4/La contrasena no corresponde a la del usuario", contrasena);
				}
				printf("Respuesta: %s\n", respuesta);
				write(sock_conn,respuesta,strlen(respuesta));
			}
			
	
		else if (codigo == 5){ //Registra a un jugador
		
			
			
			printf("%s\n",nombre);
			printf("%s\n",contrasena);
			
			pthread_mutex_lock(&mutex);
			Registro(respuesta, nombre, contrasena);
			pthread_mutex_unlock(&mutex);
			
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
			terminar = 1;
		
					
=======
		else if (codigo == 3){ //Consulta 3
		
			strcpy(usuarioconn, nombre);
			pthread_mutex_lock(&mutex);
			int rescon3= consulta3(respuesta, nombre);
			pthread_mutex_unlock(&mutex);
			if(rescon3 == 0){
				printf("Usuario en la base de datos\n");
			}
			else
			   printf("Usuario no se encuentra en la base de datos\n");
			
			
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
>>>>>>> dev-v4
		}
<<<<<<< HEAD
		else if (codigo == 7){ //Función para la invitación a una partida
=======
<<<<<<< HEAD
		else if (codigo == 4){ //Autentifica y conecta a un usuario
			   
				strcpy(usuarioconn, nombre);
				char password[50];
				consulta3(password, nombre);
				
				char *c = strtok(password,"/");
				c = strtok(NULL,"/");
				strcpy(password, c);
				
				
				if (strcmp(password, contrasena)==0)
				{
					pthread_mutex_lock(&mutex);
					int respon= Pon(&milista, nombre, sock_conn);
					pthread_mutex_unlock(&mutex);
					if(respon == 0){
						printf("Usuario añadido\n");
					}
					else
					   printf("Usuario no añadido\n");
					
					sprintf(respuesta, "4/%s", contrasena);
				}
				else
				{
					
					sprintf(respuesta, "4/La contrasena no corresponde a la del usuario", contrasena);
				}
				printf("Respuesta: %s\n", respuesta);
				write(sock_conn,respuesta,strlen(respuesta));
			}
			
	
		else if (codigo == 5){ //Registra a un jugador
		
<<<<<<< HEAD
		
		if ((codigo == 4) || (codigo == 0))
		{
=======
		else if (codigo == 7){//Función para la invitación a una partida
>>>>>>> dcab0d39f1896e39dc9a84e8f9999a61b9ada09f
			char jugador[20];
			p = strtok(NULL,"/");
			strcpy(nombre, p);
			pthread_mutex_lock(&mutex);
			int socketanfitrion = DameSocket(&milista, nombre);
			pthread_mutex_unlock(&mutex);
			p = strtok(NULL,"/");
			numerojugadores= atoi(p);
			printf("Numero jugadores: %d\n", numerojugadores);
			int res1 = CrearPartida(&mispartidas, nombre, numerojugadores); 
			sprintf(respuesta, "7/%s-%d", nombre, res1);
			write(socketanfitrion,respuesta,strlen(respuesta));
			printf("%d\n", res1);
			if (res1 == -1){
				printf("La lista está llena\n");
			}
			else{
				int i=0;
				while(i<numerojugadores){
					p = strtok(NULL,"/");
					strcpy(jugador, p);
					printf("Jugador: %s\n", jugador);
					pthread_mutex_lock(&mutex);
					int socketjugador = DameSocket(&milista, jugador);
					pthread_mutex_unlock(&mutex);
					printf("Socket: %d\n", socketjugador);
					if (socketjugador != 0){
					sprintf(respuesta, "7/%s-%d", nombre, res1);
					printf("Invitación: %s\n", respuesta);
					write(socketjugador,respuesta,strlen(respuesta));

					}
					i++;
				}
			}
		}
		else if (codigo == 8){ //Aceptar o rechazar partida
			p = strtok( NULL, "/");
			numForm =  atoi(p);
			char invitado[20];
			p = strtok(NULL,"/");
			strcpy(invitado, p);
			char usuario[20];
			p = strtok(NULL,"/");
			strcpy(usuario, p);
			p = strtok(NULL,"/");
			int Id= atoi(p);
			p = strtok(NULL,"/");
			int acepta= atoi(p);
			
			pthread_mutex_lock(&mutex);
			int socketjugador = DameSocket(&milista, invitado);
			pthread_mutex_unlock(&mutex);
			printf("Socket: %d\n", socketjugador);
			
			if(acepta == 0){
				printf("El jugador no ha aceptado la partida\n");
				sprintf(respuesta, "8/%d/NO/%s", numForm, usuario);
				printf("Acepta?: %s\n", respuesta);
				write(socketjugador,respuesta,strlen(respuesta));
			}
			else{
				int res= PonerEnPartida(&mispartidas, Id, usuario);
				if (res == 0){
					printf("Añadido a la partida\n");
					sprintf(respuesta, "8/%d/SI/%s", numForm, usuario);
					printf("Añadido a la partida: %s\n", respuesta);
					write(socketjugador,respuesta,strlen(respuesta));
				}
			}
		}	
		else if (codigo == 9){ // Chat de partida
			p = strtok( NULL, "/");
			numForm =  atoi(p);
			char texto[500];
			p = strtok(NULL,"/");
			strcpy(texto, p);
			char usuario[20];
			p = strtok(NULL,"/");
			strcpy(usuario, p);
			p = strtok(NULL,"/");
			int Id= atoi(p);
			
			char jugadores[200];
			strcpy(jugadores, mispartidas.partidas[Id].jugadores);
			
			char *u = strtok(jugadores,"/");
			while (u != NULL)
			{
				int socketjugador = DameSocket(&milista, u);
				sprintf (respuesta, "9/%s-%s-%d", usuario, texto, Id);
				printf("Respuesta: %s\n", respuesta);
				write(socketjugador,respuesta,strlen(respuesta));
				u = strtok(NULL,"/");
			}
		}
		
		if (codigo == 10){ // Matriz de cartas
			p = strtok( NULL, "/");
			numForm =  atoi(p);
			char Tu[20];
			p = strtok(NULL,"/");
			strcpy(Tu, p);
			char lista[1000];
			p = strtok(NULL,"/");
			strcpy(lista, p);
			p = strtok(NULL,"/");
			int Id= atoi(p);
			
			char jugadores[200];
			strcpy(jugadores, mispartidas.partidas[Id].jugadores);
			
			char *u = strtok(jugadores,"/");
			while (u != NULL)
			{
				if (strcmp(u, Tu)!=0){
				int socketjugador = DameSocket(&milista, u);
				sprintf (respuesta, "10/%s:%d", lista, Id);
				printf("Respuesta: %s\n", respuesta);
				write(socketjugador,respuesta,strlen(respuesta));
				}
				u = strtok(NULL,"/");
			}
			
		}
		
		if (codigo == 11){ // Jugada que se envia a todos los jugadores
			p = strtok( NULL, "/");
			numForm =  atoi(p);
			char Tu[20];
			p = strtok(NULL,"/");
			strcpy(Tu, p);
			p = strtok(NULL,"/");
			int Id= atoi(p);
			char pos1[20];
			p = strtok(NULL,"/");
			strcpy(pos1, p);
			char pos2[20];
			p = strtok(NULL,"/");
			strcpy(pos2, p);
			int res;
			p = strtok(NULL,"/");
			res= atoi(p);
			int puntuacionmax;
			p = strtok(NULL,"/");
			puntuacionmax= atoi(p);
			char ganador[20];
			p = strtok(NULL,"/");
			strcpy(ganador, p);
			int puntos;
			int acertado;
			
			if (res == 1)
			{
				acertado = 1;;
			}
			else
			{
				acertado = 0;
			}
			
			char jugadores[200];
			strcpy(jugadores, mispartidas.partidas[Id].jugadores);
			
			char *u = strtok(jugadores,"/");
			while (u != NULL)
			{
				if (strcmp(u, Tu)!=0){
					int socketjugador = DameSocket(&milista, u);
					sprintf (respuesta, "11/%d/%s/%s/%d/%d/%s", Id, pos1, pos2, acertado, puntuacionmax, ganador);
					printf("Respuesta: %s\n", respuesta);
					write(socketjugador,respuesta,strlen(respuesta));
				}
				u = strtok(NULL,"/");
			}
			
		}
		if (codigo == 12){ // Siguiente turno
		
			p = strtok(NULL,"/");
			int Id= atoi(p);
			char jugadores[200];
			strcpy(jugadores, mispartidas.partidas[Id].jugadores);
			
			if  (mispartidas.partidas[Id].turno == mispartidas.partidas[Id].numerojugadores + 2)
			{
				mispartidas.partidas[Id].turno = 1;
			}
			char *z = strtok(jugadores,"/");
			int i =  mispartidas.partidas[Id].turno;
			while (i > 1)
			{
				z = strtok(NULL,"/");
				i=i-1;
			}
			char turnode[20];
			strcpy(turnode, z);	   
			mispartidas.partidas[Id].turno =  mispartidas.partidas[Id].turno + 1;
			strcpy(jugadores, mispartidas.partidas[Id].jugadores);
		
			printf("Turno de %s en la partida %d\n",turnode, Id);
			
			char jugadoress[200];
			sprintf(jugadoress,"%s/",jugadores);
			
			char *u = strtok(jugadoress,"/");
			while (u != NULL)
			{
				int socketjugador = DameSocket(&milista, u);
				sprintf (respuesta, "12/%s:%d", turnode, Id);
				printf("Respuesta: %s\n", respuesta);
				write(socketjugador,respuesta,strlen(respuesta));
				u = strtok(NULL,"/");
			}
		}
		if (codigo == 13){ //Darse de baja del sistema
			p = strtok(NULL,"/");
			strcpy(nombre, p);
			
			pthread_mutex_lock(&mutex);
			Desregistro(respuesta, nombre);
			pthread_mutex_unlock(&mutex);
			
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
		}
		if (codigo == 14){ //Inserta una partida a la base de datos
			
			int Id;
			char Id2[10];
			p = strtok(NULL,"/");
			strcpy(Id2, p);
			Id = atoi(p);
			char tiempo[20];
			p = strtok(NULL,"/");
			strcpy(tiempo,p);
			printf("%s\n",tiempo);
			char jugadores[200];
			strcpy(jugadores, mispartidas.partidas[Id].jugadores);
			
			pthread_mutex_lock(&mutex);
			InsertaPartida(respuesta, Id2, tiempo, jugadores);
			pthread_mutex_unlock(&mutex);
		}
		if ((codigo == 4) || (codigo == 0)){ // Para 0 y 4, quita y añade los jugadores a la lista de conectados respectivamente (NOTIFICACION)
		
>>>>>>> dev-v5
			pthread_mutex_lock(&mutex);
			contador = contador + 1;
			pthread_mutex_unlock(&mutex);
			char conectados[512];
			char notificacion[512];
			pthread_mutex_lock(&mutex);
			DameConectados(&milista, conectados);
			pthread_mutex_unlock(&mutex);
			strcpy (notificacion, "6/");
			strcat(notificacion, conectados);
			//sprintf(notificacion, "6/%s", conectados);
			printf("Los conectados son: %s\n", notificacion);
			int j;
			for (j=0; j<i; j++)
			{
			write(sockets[j] , notificacion , strlen(notificacion));
			}
=======
			
			
			printf("%s\n",nombre);
			printf("%s\n",contrasena);
			
			pthread_mutex_lock(&mutex);
			Registro(respuesta, nombre, contrasena);
			pthread_mutex_unlock(&mutex);
			
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
			terminar = 1;
		
					
>>>>>>> dev-v4
		}
<<<<<<< HEAD
		else if (codigo == 7){//Función para la invitación a una partida
			char jugador[20];
			p = strtok(NULL,"/");
			strcpy(nombre, p);
			p = strtok(NULL,"/");
			numerojugadores= atoi(p);
			printf("Numero jugadores: %d\n", numerojugadores);
			int res1 = CrearPartida(&mispartidas, nombre, numerojugadores); 
			printf("%d\n", res1);
			if (res1 == -1){
				printf("La lista está llena\n");
			}
			else{
				int i=0;
				while(i<numerojugadores){
					p = strtok(NULL,"/");
					strcpy(jugador, p);
					printf("Jugador: %s\n", jugador);
					pthread_mutex_lock(&mutex);
					int socketjugador = DameSocket(&milista, jugador);
					pthread_mutex_unlock(&mutex);
					printf("Socket: %d\n", socketjugador);
					if (socketjugador != 0){
					sprintf(respuesta, "7/%s-%d", nombre, res1);
					printf("Invitacción: %s\n", respuesta);
					write(socketjugador,respuesta,strlen(respuesta));
					}
					i++;
				}
			}
		}
		else if (codigo == 8){
			p = strtok( NULL, "/");
			numForm =  atoi(p);
			char invitado[20];
			p = strtok(NULL,"/");
			strcpy(invitado, p);
			char usuario[20];
			p = strtok(NULL,"/");
			strcpy(usuario, p);
			p = strtok(NULL,"/");
			int Id= atoi(p);
			p = strtok(NULL,"/");
			int acepta= atoi(p);
			
			pthread_mutex_lock(&mutex);
			int socketjugador = DameSocket(&milista, invitado);
			pthread_mutex_unlock(&mutex);
			printf("Socket: %d\n", socketjugador);
			
			if(acepta == 0){
				printf("El jugador no ha aceptado la partida\n");
				sprintf(respuesta, "8/%d/NO", numForm);
				printf("Acepta?: %s\n", respuesta);
				write(socketjugador,respuesta,strlen(respuesta));
			}
			else{
				int res= PonerEnPartida(&mispartidas, Id, usuario);
				if (res == 0){
					printf("Añadido a la partida\n");
					sprintf(respuesta, "8/%d/SI", numForm);
					printf("Añadido a la partida: %s\n", respuesta);
					write(socketjugador,respuesta,strlen(respuesta));
				}
			}
		}
		if ((codigo == 4) || (codigo == 0)){ // Para 0 y 4, quita y añade los jugadores a la lista de conectados respectivamente (NOTIFICACION)
		
<<<<<<< HEAD
		
=======
			pthread_mutex_lock(&mutex);
			contador = contador + 1;
			pthread_mutex_unlock(&mutex);
			char conectados[512];
			char notificacion[512];
			pthread_mutex_lock(&mutex);
			DameConectados(&milista, conectados);
			pthread_mutex_unlock(&mutex);
			strcpy (notificacion, "6/");
			strcat(notificacion, conectados);
			//sprintf(notificacion, "6/%s", conectados);
			printf("Los conectados son: %s\n", notificacion);
			int j;
			for (j=0; j<i; j++)
			{
			write(sockets[j] , notificacion , strlen(notificacion));
			}
		}
>>>>>>> dev-v4
=======
>>>>>>> dev-v5
	}	
	close(sock_conn);
}


<<<<<<< HEAD
<<<<<<< HEAD
void consulta1(char consulta[200], MYSQL_RES *resultado, char respuesta[512]){
	int err;
	MYSQL_ROW row;
	
	
=======
int consulta1(char respuesta[512]){ //Nos da el jugador con mas puntuacion del ranking global. (0 al mostrarla y -1 si no hay datos de la consulta)
	
	char consulta [200];
	int err;
	MYSQL_ROW row;
	MYSQL_RES *resultado;
>>>>>>> dev-v4
=======
int consulta1(char respuesta[512]){ //Nos da el jugador con mas puntuacion del ranking global. (0 al mostrarla y -1 si no hay datos de la consulta)
	
	char consulta [200];
	int err;
	MYSQL_ROW row;
	MYSQL_RES *resultado;
>>>>>>> dev-v5
	
	sprintf (consulta, "SELECT DISTINCT JUGADORES.USUARIO, RANKING.PUNTUACION_MAXIMA FROM (PARTIDA, JUGADORES, RANKING) WHERE JUGADORES.ID = RANKING.ID_U");
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	
	if (row == NULL)
	{
		printf ("No se han obtenido datos en la consulta\n");
		return -1;
	}
	else
	{
		char usuario [20];
		char ganador[20];
		int puntuacion1 = 0;
		int puntuacion2 = 0;
		while (row !=NULL)
		{
			
			printf ("Usuario: %s Puntuacion: %s\n", row[0], row[1]);
			strcpy(usuario,row[0]);
			puntuacion1= atoi (row[1]);
			if (puntuacion1>puntuacion2){
				puntuacion2=puntuacion1;
				strcpy(ganador,usuario); 
			}
			row = mysql_fetch_row (resultado);
		}
		printf("Persona con mas puntos es: %s Con estos puntos: %d\n", ganador, puntuacion2);
		sprintf(respuesta,"1/El jugador con mas puntos en el ranking es: %s. Con estos puntos: %d\n", ganador, puntuacion2);
		printf("%s\n", respuesta);
<<<<<<< HEAD
<<<<<<< HEAD
=======
		return 0;
>>>>>>> dev-v4
=======
		return 0;
>>>>>>> dev-v5
		
	}
}


<<<<<<< HEAD
<<<<<<< HEAD
void consulta2(char consulta[200], MYSQL_RES *resultado, char respuesta[512], char nombre[20]){
=======
int consulta2(char respuesta[512], char nombre[20]){ //Nos da la puntuacion actual del jugador seleccionado. (0 al mostrarla y -1 si el jugador seleccionado no existe)
>>>>>>> dev-v5
	
	consulta[200];
	int err;
	MYSQL_ROW row;
<<<<<<< HEAD
=======
int consulta2(char respuesta[512], char nombre[20]){ //Nos da la puntuacion actual del jugador seleccionado. (0 al mostrarla y -1 si el jugador seleccionado no existe)
	
	consulta[200];
	int err;
	MYSQL_ROW row;
	MYSQL_RES *resultado;
>>>>>>> dev-v4
=======
	MYSQL_RES *resultado;
>>>>>>> dev-v5
	
	// construimos consulta SQL
	strcpy (consulta,"SELECT puntuacion_actual FROM JUGADORES WHERE usuario = '"); 
	strcat (consulta, nombre);
	strcat (consulta,"'");
	// hacemos la consulta 
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	if (row == NULL)
	{
		printf ("No existe ningun jugador registrado con ese nombre de usuario\n");
		sprintf(respuesta,"2/No existe ningun jugador registrado con ese nombre de usuario\n");
<<<<<<< HEAD
<<<<<<< HEAD
=======
		return -1;
>>>>>>> dev-v4
=======
		return -1;
>>>>>>> dev-v5
	}
	else
	{
		printf ("La puntuacion actual de este usuario es de: %s\n", row[0] );
		sprintf(respuesta,"2/La puntuacion actual de este usuario es de: %s\n", row[0]);
<<<<<<< HEAD
<<<<<<< HEAD
=======
		return 0;
>>>>>>> dev-v4
=======
		return 0;
>>>>>>> dev-v5
	}
}


<<<<<<< HEAD
<<<<<<< HEAD
int consulta3(char consulta[200], MYSQL_RES *resultado, char respuesta[512], char nombre[20]){
=======
int consulta3(char respuesta[512], char nombre[20]){ //Nos da la contraseña del usuario seleccionado. (0 al mostrarla y -1 si no existe el jugador)
>>>>>>> dev-v5
	
	char consulta[200];
	int err;
	MYSQL_ROW row;
<<<<<<< HEAD
=======
int consulta3(char respuesta[512], char nombre[20]){ //Nos da la contraseña del usuario seleccionado. (0 al mostrarla y -1 si no existe el jugador)
>>>>>>> dev-v4
	
	char consulta[200];
	int err;
	MYSQL_ROW row;
=======
>>>>>>> dev-v5
	MYSQL_RES *resultado;
	
	// construimos consulta SQL
	strcpy (consulta,"SELECT contraseña FROM JUGADORES WHERE usuario = '"); 
	strcat (consulta, nombre);
	strcat (consulta,"'");
	// hacemos la consulta 
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//recogemos el resultado de la consulta 
	resultado = mysql_store_result (conn); 
	row = mysql_fetch_row (resultado);
	if (row == NULL)
	{
		printf ("No existe ningun jugador registrado con ese nombre de usuario\n");
<<<<<<< HEAD
<<<<<<< HEAD
		sprintf(respuesta,"No existe ningun jugador registrado con ese nombre de usuario\n");
=======
		sprintf(respuesta,"3/No existe ningun jugador registrado con ese nombre de usuario\n");
>>>>>>> dev-v4
=======
		sprintf(respuesta,"3/No existe ningun jugador registrado con ese nombre de usuario\n");
>>>>>>> dev-v5
		return -1;
	}
	else
	{
<<<<<<< HEAD
<<<<<<< HEAD
		
		printf ("La contraseña de ese usuario es: %s\n", row[0] );
		sprintf(respuesta,"3/%s", row[0]);
		return 0;
		
=======
		printf ("La contraseña de ese usuario es: %s\n", row[0] );
		sprintf(respuesta,"3/%s", row[0]);
		return 0;
>>>>>>> dev-v4
=======
		printf ("La contraseña de ese usuario es: %s\n", row[0] );
		sprintf(respuesta,"3/%s", row[0]);
		return 0;
>>>>>>> dev-v5
	}
}


<<<<<<< HEAD
<<<<<<< HEAD
int consulta4(char consulta[200], MYSQL_RES *resultado, char respuesta[512], char nombre[20], char contrasena[20]){
=======
int Registro(char respuesta[512], char nombre[20], char contrasena[20]){ //Funcion que registra a un jugador nuevo. (0 al añadirlo y -1 si ha ocurrido algun error)
>>>>>>> dev-v5
	
	int err;	
	char instruccion[200];
	char prueba[1];
	sprintf(prueba,"%d",0);
	// construimos consulta SQL
<<<<<<< HEAD
	strcpy (consulta,"INSERT INTO JUGADORES VALUES ("); 
	strcat (consulta, prueba);
	strcat (consulta, ",'");
	strcat (consulta, nombre);
	strcat (consulta, "','");
	strcat (consulta, contrasena);
	strcat (consulta,"',");
	strcat (consulta, prueba);
	strcat (consulta, ",");
	strcat (consulta, prueba);
	strcat (consulta, ");");
=======
int Registro(char respuesta[512], char nombre[20], char contrasena[20]){ //Funcion que registra a un jugador nuevo. (0 al añadirlo y -1 si ha ocurrido algun error)
	
	int err;	
	char instruccion[200];
	char prueba[1];
	sprintf(prueba,"%d",0);
	// construimos consulta SQL
=======
>>>>>>> dev-v5
	strcpy (instruccion,"INSERT INTO JUGADORES VALUES ("); 
	strcat (instruccion, "0");
	strcat (instruccion, ",'");
	strcat (instruccion, nombre);
	strcat (instruccion, "','");
	strcat (instruccion, contrasena);
	strcat (instruccion,"',");
	strcat (instruccion, "0");
	strcat (instruccion, ",");
	strcat (instruccion, "0");
	strcat (instruccion, ");");
<<<<<<< HEAD
>>>>>>> dev-v4
=======
>>>>>>> dev-v5
	// hacemos la consulta 
	err=mysql_query (conn, instruccion); 
	if (err!=0)
	{
		printf ("Error al introducir datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
		return -1;
<<<<<<< HEAD
	}
	else
	{
		sprintf(respuesta,"Te has registrado correctamente\n");
		return 0;
=======
>>>>>>> dev-v5
	}
<<<<<<< HEAD
	else
<<<<<<< HEAD
	   sprintf(respuesta,"5/Te has registrado correctamente\n");
=======
>>>>>>> dev-v4
=======
	{
		sprintf(respuesta,"Te has registrado correctamente\n");
		return 0;
	}
>>>>>>> dev-v5
}
void Desregistro(char respuesta[512], char nombre[20]){ //Funcion que elimina a un jugador de la base de datos
	
	consulta[200];
	int err;
	MYSQL_ROW row;
	MYSQL_RES *resultado;
	
	// construimos consulta SQL
	strcpy (consulta,"DELETE FROM JUGADORES WHERE usuario = '"); 
	strcat (consulta, nombre);
	strcat (consulta,"'");
	// hacemos la consulta 
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}

	printf ("Usuario eliminado del sistema: %s\n", nombre );
	sprintf(respuesta,"2/Usuario dado de baja: %s\n", nombre);
}
int InsertaPartida(char respuesta[512], char id[10], char tiempo[20], char jugadores[200]){ //Funcion que registra a un jugador nuevo. (0 al añadirlo y -1 si ha ocurrido algun error)
	
	int err;	
	char instruccion2[200];
	char prueba[1];
	// construimos consulta SQL
	strcpy (instruccion2,"INSERT INTO PARTIDA VALUES ("); 
	strcat (instruccion2, id);
	strcat (instruccion2, ",'");
	strcat (instruccion2, "Jugando");
	strcat (instruccion2, "','");
	strcat (instruccion2, tiempo);
	strcat (instruccion2,"',");
	strcat (instruccion2, "100");
	strcat (instruccion2, ",'");
	strcat (instruccion2, "Nadie");
	strcat (instruccion2,"','");
	strcat (instruccion2, jugadores);
	strcat (instruccion2, "');");
	// hacemos la consulta 
	err=mysql_query (conn, instruccion2); 
	if (err!=0)
	{
		printf ("Error al introducir datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
		return -1;
	}
	else
	{
		sprintf(respuesta,"14/OK\n");
		return 0;
	}
}

<<<<<<< HEAD
int Pon (ListaConectados *milista, char nombre[20], int socket){ //Añade el nuevo conectado y informa si está llena o no 
=======

<<<<<<< HEAD
<<<<<<< HEAD




=======
>>>>>>> dev-v4
=======
>>>>>>> dev-v5
int Pon (ListaConectados *milista, char nombre[20], int socket){
>>>>>>> dcab0d39f1896e39dc9a84e8f9999a61b9ada09f
	//Añade el nuevo conectado y informa si está llena o no 
	if (milista->num== 100)
		return -1;
	else{
		strcpy (milista->conectados[milista->num].nombre , nombre);
		milista->conectados[milista->num].socket = socket;
		milista->num= milista->num + 1;
		return 0;
	}
}
int DameSocket (ListaConectados *milista, char nombre[20]){ //Devueleve el socket de un jugador
	//Devueleve el socket
	int i=0;
	int encontrado = 0;
	while ((i< milista->num) && !encontrado)
	{
		if (strcmp(milista->conectados[i].nombre, nombre) == 0)
			encontrado =1;
		if (!encontrado)
			i=i+1;
	}
		if (encontrado)
			return milista->conectados[i].socket;
		else
			return 0;
}


int DamePosicion (ListaConectados *milista, char nombre[20]){ //Devueleve la posicion
	//Devueleve la posicion
	int i=0;
	int encontrado = 0;
	while ((i< milista->num) && !encontrado)
	{
		if (strcmp(milista->conectados[i].nombre, nombre) == 0)
			encontrado =1;
		if (!encontrado)
			i=i+1;
	}
	if (encontrado)
		return i;
	else
		return -1;
}


int Eliminar (ListaConectados *milista, char nombre[20]){ // Elimina a un jugador de la lista de conectados (retorna 0 si elimina y -1 si el usuario no está en la lista)
	//Retorna 0 si elimina y -1 si el usuario no está en la lista
	int pos = DamePosicion (milista, nombre);
	if (pos == -1)
		return -1;
	else
    {
		int i;
		for (i=pos; i< milista->num-1; i++)
		{
	     strcpy (milista->conectados[i].nombre, milista->conectados[i+1].nombre);
		 milista->conectados[i].socket = milista->conectados[i+1].socket;          
	    }
		milista->num--;
		return 0;
	}
}


void DameConectados (ListaConectados *milista, char conectados[512]){ //Devuelve los jugadores conectados
	//Devuelve los nombres de los conectados separados por /.
<<<<<<< HEAD
<<<<<<< HEAD
	
=======
>>>>>>> dev-v5
	int i;
	strcpy (conectados, "-");
	for (i=0; i< milista->num; i++)
	{
		sprintf (conectados, "%s-%s", conectados, milista->conectados[i].nombre);
		printf("%s\n", conectados);
	}
}

int CrearPartida(ListaPartidas *mispartidas, char nombre[20], int numerojugadores){//Añade una partida a la lista de partidas (devuelve la ID de la partida)
	
	if(mispartidas->num== 100){
		printf("La lista de partidas está llena\n");
		return -1;
	}
	else{
		strcpy (mispartidas->partidas[mispartidas->num].jugadores, nombre);
		mispartidas->partidas[mispartidas->num].Id = mispartidas->num;
		mispartidas->partidas[mispartidas->num].numerojugadores = numerojugadores;
		mispartidas->partidas[mispartidas->num].turno = 1;
		mispartidas->num= mispartidas->num + 1;
		int identificador = (mispartidas->num - 1);
		return identificador;
	}
}

<<<<<<< HEAD
=======
	int i;
	strcpy (conectados, "-");
	for (i=0; i< milista->num; i++)
	{
		sprintf (conectados, "%s-%s", conectados, milista->conectados[i].nombre);
		printf("%s\n", conectados);
	}
}

int CrearPartida(ListaPartidas *mispartidas, char nombre[20], int numerojugadores){//Añade una partida a la lista de partidas
	
	if(mispartidas->num== 100){
		printf("La lista de partidas está llena\n");
		return -1;
	}
	else{
		strcpy (mispartidas->partidas[mispartidas->num].jugadores, nombre);
		mispartidas->partidas[mispartidas->num].Id = mispartidas->num;
		mispartidas->partidas[mispartidas->num].numerojugadores = numerojugadores;
		mispartidas->num= mispartidas->num + 1;
		return mispartidas->partidas[mispartidas->num].Id;
	}
}

=======
>>>>>>> dev-v5
int PonerEnPartida(ListaPartidas *mispartidas, int Id, char jugador[20]){//Añade un jugador a la partida seleccionada
	
	int i=0;
	int encontrado=0;
	while((i<mispartidas->num) && (!encontrado)){
		if(mispartidas->partidas[i].Id == Id){
			encontrado = 1;
		}
		else{
			i++;
		}
	}
	if (encontrado){
		strcat (mispartidas->partidas[i].jugadores , "/");
		strcat (mispartidas->partidas[i].jugadores , jugador);
		printf("Los jugadores en la partida son: %s\n", mispartidas->partidas[i].jugadores);
		return 0;
	}
	else{
		return -1;
	}
}
<<<<<<< HEAD
>>>>>>> dev-v4
=======
>>>>>>> dev-v5

int main(int argc, char *argv[]){
	
	milista.num=0;
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	contador=0;
	
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error al crear el socket\n");
	
	// Fem el bind al port
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	//asocia el socket a cualquiera de las IP de la maquina
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); /* El fica IP local */
	//escuchamos el puerto correspondiente:
<<<<<<< HEAD
	serv_adr.sin_port = htons(4003); //AQUI SE PONE EL PUERTO
=======
<<<<<<< HEAD
	serv_adr.sin_port = htons(50064); //AQUI SE PONE EL PUERTO
=======
	serv_adr.sin_port = htons(5008); //AQUI SE PONE EL PUERTO
>>>>>>> dev-v4
>>>>>>> dcab0d39f1896e39dc9a84e8f9999a61b9ada09f
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf("Error al bind\n");
	    
	// Limitem el nombre de connexions pendents
	if (listen(sock_listen, 3) < 0)
		printf("Error de Listen\n");
	
	//NOS CONECTAMOS A LA BASE DE DATOS:
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
<<<<<<< HEAD
	conn = mysql_real_connect (conn, "localhost", "root", "mysql", "M5_DB",0, NULL, 0);
=======
<<<<<<< HEAD
	conn = mysql_real_connect (conn, "shiva2.upc.es", "root", "mysql", "M5_DB",0, NULL, 0);
=======
	conn = mysql_real_connect (conn, "localhost", "root", "mysql", "M5_DB",0, NULL, 0);
>>>>>>> dev-v4
>>>>>>> dcab0d39f1896e39dc9a84e8f9999a61b9ada09f
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexionn: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
   //Variables para sockets:
	i=0;
	pthread_t thread[100];
	
	
	for(;;)
	{
		printf ("Escuchando\n");
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("Se ha recibido la conexión\n");
		
		sockets[i] = sock_conn;
		//sock_conn es el socket que usaremos para este cliente
		
		// Crear thread y decirle lo que tiene que hacer
		pthread_create (&thread[i], NULL, AtenderCliente, &sockets[i]);
		i=i+1;
	}
	mysql_close (conn);   
}
