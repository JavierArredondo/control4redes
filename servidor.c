/* 
  Author: Javier Arredondo
  Quiz 4. Redes de Computadores  
*/
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netdb.h>
int main(int argc, char **argv){
  int port = 1313;
  socklen_t longc;
  char buffer[100];
  struct sockaddr_in server;
  struct sockaddr_in client;
  int server_connection;
  bzero((char *)&server, sizeof(server));                  // Inicializamos la estructura con ceros contiguos.
  // Inicializamos la estructura con valores utiles para la conexion del server-
  server.sin_family = AF_INET;
  server.sin_port = htons(port);
  server.sin_addr.s_addr = INADDR_ANY;




  if(strcmp(argv[1], "TCP") == 0)
  {
    server_connection= socket(AF_INET, SOCK_STREAM, 0); // Socket DGRAM->UDP | STREAM->TCP
    int congrat = bind(server_connection, (struct sockaddr *)&server, sizeof(server));
    if(congrat < 0)
    {
      printf("Error al levantar el servidor.\n");
      close(server_connection);
      return 1;
    }
    listen(server_connection, 3);
    printf("Conexion establecida en el puerto: %d\n", ntohs(server.sin_port));
    longc = sizeof(client); //  Tamaño de estructura del cliente
    int client_connection = accept(server_connection, (struct sockaddr*)&client, &longc); // Esperamos la conexion del cliente
    printf("%i\n", client_connection);
    if(client_connection < 0)
    {
      printf("Error del cliente.\n");
      close(server_connection);
      return 1;
    }
    printf("Conectado con un cliente: %s:%d\n", inet_ntoa(client.sin_addr),htons(client.sin_port));
    while(recv(client_connection, buffer, 100, 0) != 0)
    {
      printf("%s\n", buffer);
      bzero((char *)&buffer, sizeof(buffer));
      send(client_connection, "Recibido\n", 13, 0);
    }
  }
  else if(strcmp(argv[1], "UDP") == 0)
  {
    server_connection= socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Socket DGRAM->UDP | STREAM->TCP
    int congrat = bind(server_connection, (struct sockaddr *)&server, sizeof(server));
    if(congrat < 0)
    {
      printf("Error al levantar el servidor.\n");
      close(server_connection);
      return 1;
    }
  }

  int congrat = bind(server_connection, (struct sockaddr *)&server, sizeof(server));
  if(congrat < 0)
  {
    printf("Error al levantar el servidor.\n");
    close(server_connection);
    return 1;
  }
  listen(server_connection, 3);
  printf("Conexion establecida en el puerto: %d\n", ntohs(server.sin_port));
  longc = sizeof(client); //  Tamaño de estructura del cliente
  int client_connection = accept(server_connection, (struct sockaddr*)&client, &longc); // Esperamos la conexion del cliente
  printf("%i\n", client_connection);
  /*if(client_connection < 0)
  {
    printf("Error del cliente.\n");
    close(server_connection);
    return 1;
  }*
  printf("Conectado con un cliente: %s:%d\n", inet_ntoa(client.sin_addr),htons(client.sin_port));
  while(recv(client_connection, buffer, 100, 0) != 0)
  {
    printf("%s\n", buffer);
    bzero((char *)&buffer, sizeof(buffer));
    send(client_connection, "Recibido\n", 13, 0);
  }*/
  while(1)
    {
        int lenClient = sizeof(client);
        int r = recvfrom(server_connection, buffer, 100, 0, (struct sockaddr *) &client, &lenClient);
        printf("Received packet from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        printf("%s\n" , buffer);
        sendto(server_connection, "Recibido", r, 0, (struct sockaddr*) &client, lenClient);
    }
  close(server_connection);
  return 0;
}