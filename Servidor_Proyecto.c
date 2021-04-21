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

MYSQL *conn;
int err;
MYSQL_RES *resultado;
MYSQL_ROW row;
char consulta [200];

typedef struct {
	char nombre [20];
	int socket;
}Conectado;


typedef struct {
	Conectado conectados [100];
	int num;
}ListaConectados;

void *AtenderCliente (void *socket) {
	ListaConectados milista;
	milista.num=0;
	int sock_conn;
	int *s;
	s= (int *) socket;
	sock_conn= *s;
	
	//int socket_conn = * (int *) socket;
	
	char peticion[512];
	char respuesta[512];
	int ret;
	
	//Bucle de atencion al cliente
	int terminar = 0;
	while (terminar==0)
	{
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
		
		if ((codigo <=2) && (codigo !=0))
		{
			p = strtok(NULL,"/");
			strcpy(nombre, p);
		}
		
		if (codigo==0)
		{
			terminar = 1;
		}
		
		if (codigo==1) //Consulta 1
		{
			consulta1(consulta, conn, resultado, err, row, respuesta);
		}
		else if (codigo==2) //Consulta 2
		{
			consulta2(consulta, conn, resultado, err, row, respuesta, p, nombre);
		}
		else if (codigo==3) //Consulta 3
		{
			consulta3(consulta, conn, resultado, err, row, respuesta, p, sock_conn, milista);
		}
		else if (codigo==4) //4, registra a un jugador
		{
			consulta4(consulta, conn, resultado, err, row, respuesta, p);
		}
		else if (codigo==5)
		{
			
			DameConectados(&milista, respuesta);
			printf("%s\n",respuesta);
		}
		
		if (codigo !=0)
		{
			printf("Respuesta: %s\n", respuesta);
			write(sock_conn,respuesta,strlen(respuesta));
		}
		
	}	
	close(sock_conn);
}


void consulta1(char consulta[200], MYSQL *conn, MYSQL_RES *resultado, int err, MYSQL_ROW row, char respuesta[512]){
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
		sprintf(respuesta,"El jugador con mas puntos en el ranking es: %s. Con estos puntos: %d\n", ganador, puntuacion2);
	}
}


void consulta2(char consulta[200], MYSQL *conn, MYSQL_RES *resultado, int err, MYSQL_ROW row, char respuesta[512], char *p, char nombre[20]){
	char user[20];
	p = strtok(NULL,"/");
	strcpy(user, p);
	
	
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
		sprintf(respuesta,"No existe ningun jugador registrado con ese nombre de usuario\n");
	}
	else
	{
		printf ("La puntuacion actual de este usuario es de: %s\n", row[0] );
		sprintf(respuesta,"La puntuacion actual de este usuario es de: %s\n", row[0]);
	}
}


void consulta3(char consulta[200], MYSQL *conn, MYSQL_RES *resultado, int err, MYSQL_ROW row, char respuesta[512], char *p, int sock_conn, ListaConectados *lista){
	char user[20];
	p = strtok(NULL,"/");
	strcpy(user, p);
	
	
	// construimos consulta SQL
	strcpy (consulta,"SELECT contraseña FROM JUGADORES WHERE usuario = '"); 
	strcat (consulta, user);
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
		sprintf(respuesta,"No existe ningun jugador registrado con ese nombre de usuario\n");
	}
	else
	{
		int res= Pon(&lista, user, sock_conn);
		printf ("La contraseña de ese usuario es: %s\n", row[0] );
		sprintf(respuesta,"%s", row[0]);
		
	}
}


void consulta4(char consulta[200], MYSQL *conn, MYSQL_RES *resultado, int err, MYSQL_ROW row, char respuesta[512], char *p){
	char password[20];
	char usuario[20];
	char prueba[1];
	sprintf(prueba,"%d",0);
	p = strtok(NULL,"/");
	strcpy(usuario, p);
	p = strtok(NULL,"/");
	strcpy(password, p);
	printf("%s\n",usuario);

	
	
	// construimos consulta SQL
	strcpy (consulta,"INSERT INTO JUGADORES VALUES ("); 
	strcat (consulta, prueba);
	strcat (consulta, ",'");
	strcat (consulta, usuario);
	strcat (consulta, "','");
	strcat (consulta, password);
	strcat (consulta,"',");
	strcat (consulta, prueba);
	strcat (consulta, ",");
	strcat (consulta, prueba);
	strcat (consulta, ");");
	// hacemos la consulta 
	err=mysql_query (conn, consulta); 
	if (err!=0) {
		printf ("Error al introducir datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	sprintf(respuesta,"Te has registrado correctamente\n");
}







int Pon (ListaConectados *lista, char nombre[20], int socket){
	//Añade el nuevo conectado y informa si está llena o no 
	if (lista->num== 100)
		return -1;
	else{
		strcpy (lista->conectados[lista->num].nombre , nombre);
		lista->conectados[lista->num].socket = socket;
		lista->num= lista->num + 1;
		return 0;
	}
}


int DameSocket (ListaConectados *lista, char nombre[20]){
	//Devueleve el socket
	int i=0;
	int encontrado = 0;
	while ((i< lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
			encontrado =1;
		if (!encontrado)
			i=i+1;
	}
		if (encontrado)
			return lista->conectados[i].socket;
		else
			return -1;
}


int DamePosicion (ListaConectados *lista, char nombre[20]){
	//Devueleve la posicion
	int i=0;
	int encontrado = 0;
	while ((i< lista->num) && !encontrado)
	{
		if (strcmp(lista->conectados[i].nombre, nombre) == 0)
			encontrado =1;
		if (!encontrado)
			i=i+1;
	}
	if (encontrado)
		return i;
	else
		return -1;
}


int Eliminar (ListaConectados *lista, char nombre[20]){
	//Retorna 0 si elimina y -1 si el usuario no está en la lista
	int pos = DamePosicion (lista, nombre);
	if (pos == -1)
		return -1;
	else
    {
		int i;
		for (i=pos; i< lista->num-1; i++)
		{
	     strcpy (lista->conectados[i].nombre, lista->conectados[i+1].nombre);
		 lista->conectados[i].socket = lista->conectados[i+1].socket;          
	    }
		lista->num--;
		return 0;
	}
}


void DameConectados (ListaConectados *lista, char conectados[512]){
	//Devuelve los nombres de los conectados separados por /.
	sprintf (conectados, "%d", lista->num);
	int i;
	for (i=0; i-1< lista->num; i++)
	{
		sprintf (conectados, "%s/%s", conectados, lista->conectados[i].nombre);
	}
	
}
	

int main(int argc, char *argv[]){
	
	
	int sock_conn, sock_listen;
	struct sockaddr_in serv_adr;
	
	// INICIALITZACIONS
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Error al crear el socket");
	
	// Fem el bind al port
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	//asocia el socket a cualquiera de las IP de la maquina
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); /* El fica IP local */
	//escuchamos el puerto correspondiente:
	serv_adr.sin_port = htons(9060); //AQUI SE PONE EL PUERTO
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		error("Error al bind");
	
	// Limitem el nombre de connexions pendents
	if (listen(sock_listen, 3) < 0)
		printf("Error de Listen");
	
	//NOS CONECTAMOS A LA BASE DE DATOS:
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexion: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BDD_Servidor_Proyecto",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexionn: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
   //Variables para sockets:
	int i=0;
	int sockets[100];
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
