/* 
  Author: Javier Arredondo
  Quiz 4. Redes de Computadores  
*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
int main(int argc, char **argv){
  if(argv[1] == NULL)
  {
    printf("Ingrese protocolo TCP o UDP\n");
    return 1;
  }
  struct sockaddr_in client; 
  struct hostent* server;
  server = gethostbyname("localhost");
  char buffer[100];
  int connection;
  if(strcmp(argv[1], "TCP") == 0)
    connection = socket(AF_INET, SOCK_STREAM, 0);
  else if(strcmp(argv[1], "UDP") == 0)
    connection = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  else
  {
    printf("Protocolo no aceptado\n");
    return 1;
  }
  int port = 1313;
  bzero((char *)&client, sizeof((char *)&client)); // Atributos de la estructura seteados en 0
  client.sin_family = AF_INET;
  client.sin_port = htons(port);
  bcopy((char *)server->h_addr, (char *)&client.sin_addr.s_addr, sizeof(server->h_length));
  int congrat = connect(connection, (struct sockaddr *)&client, sizeof(client));
  if(congrat < 0)
  {
    printf("No se encontro host\n");
    close(connection);
    return 1;
  }
  printf("Conexion establecida con %s:%d\n",inet_ntoa(client.sin_addr), htons(client.sin_port));
  char* messagge = "Hola mundo";
  int i;
  for(i = 0; i < 10; i++)
  {

    send(connection, messagge, 100, 0); // Envio de hola mundo
    bzero(buffer, 100);              // Seteamos el bufffer de ceros. Rpta
    recv(connection, buffer, 100, 0); // Mensaje de recibido
    printf("%s\n", buffer);
  }
  return 0;
}