#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <mysql.h>
int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
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
	serv_adr.sin_port = htons(9080); //AQUI SE PONE EL PUERTO
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		error("Error al bind");
	
	// Limitem el nombre de connexions pendents
	if (listen(sock_listen, 3) < 0)
		printf("Error de Listen");	
	
	//Atendemos solo 5 peticiones
	int i;
	for(i=0;i<15;i++){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("Se ha recibido la conexión\n");
		//sock_conn es el socket que usaremos para este cliente
		
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
			
			if ((codigo <=3) && (codigo !=0))
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
				//NOS CONECTAMOS A LA BASE DE DATOS:
				MYSQL *conn;
				int err;
				MYSQL_RES *resultado;
				MYSQL_ROW row;
				char consulta [200];
				conn = mysql_init(NULL);
				if (conn==NULL)
				{
					printf ("Error al crear la conexion: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				conn = mysql_real_connect (conn, "localhost","root", "mysql", "Ejindividual2",0, NULL, 0);
				if (conn==NULL)
				{
					printf ("Error al inicializar la conexionn: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
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
					int usuario = 0;
					int ganador= 0;
					int puntuacion1 = 0;
					int puntuacion2 = 0;
					while (row !=NULL)
					{
						
						printf ("Usuario: %s Puntuacion: %s\n", row[0], row[1]);
						usuario= row[0];
						puntuacion1= row[1];
						if (puntuacion1>puntuacion2){
							puntuacion2=puntuacion1;
							ganador=usuario;
						}
						row = mysql_fetch_row (resultado);
					}
					printf("Persona con mas puntos es: %s Con estos puntos: %s\n", ganador, puntuacion2);
					sprintf(respuesta,"El jugador con mas puntos en el ranking es: %s. Con estos puntos: %s\n", ganador, puntuacion2);
				}
				mysql_close (conn);
			}
			else if (codigo==2) //Consulta 2
			{
				//NOS CONECTAMOS A LA BASE DE DATOS:
				MYSQL *conn;
				int err;
				MYSQL_RES *resultado;
				MYSQL_ROW row;
				char consulta [200];
				conn = mysql_init(NULL);
				if (conn==NULL)
				{
					printf ("Error al crear la conexion: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				conn = mysql_real_connect (conn, "localhost","root", "mysql", "Ejindividual2",0, NULL, 0);
				if (conn==NULL)
				{
					printf ("Error al inicializar la conexionn: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
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
				mysql_close (conn);
			}
			else if (codigo==3) //Consulta 3
			{
				//NOS CONECTAMOS A LA BASE DE DATOS:
				MYSQL *conn;
				int err;
				MYSQL_RES *resultado;
				MYSQL_ROW row;
				char consulta [200];
				conn = mysql_init(NULL);
				if (conn==NULL)
				{
					printf ("Error al crear la conexion: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				conn = mysql_real_connect (conn, "localhost","root", "mysql", "Ejindividual2",0, NULL, 0);
				if (conn==NULL)
				{
					printf ("Error al inicializar la conexionn: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
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
					printf ("La contraseña de ese usuario es: %s\n", row[0] );
					sprintf(respuesta,"%s", row[0]);
				}
				mysql_close (conn);
					
			}
			else if (codigo==4) //4, registra a un jugador
			{
				//NOS CONECTAMOS A LA BASE DE DATOS:
				MYSQL *conn;
				int err;
				MYSQL_RES *resultado;
				MYSQL_ROW row;
				char consulta [200];
				conn = mysql_init(NULL);
				if (conn==NULL)
				{
					printf ("Error al crear la conexion: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
				conn = mysql_real_connect (conn, "localhost","root", "mysql", "Ejindividual2",0, NULL, 0);
				if (conn==NULL)
				{
					printf ("Error al inicializar la conexionn: %u %s\n",
							mysql_errno(conn), mysql_error(conn));
					exit (1);
				}
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
				mysql_close (conn);
			}
			
			if (codigo !=0)
			{
				printf("Respuesta: %s\n", respuesta);
				write(sock_conn,respuesta,strlen(respuesta));
			}
		}
		
		close(sock_conn); /* Necessari per a que el client detecti EOF */
	}
}
		
		
		
		
		
		
		
		
		
