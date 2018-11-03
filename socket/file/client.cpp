#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

int main()
{
  int sock;
  unsigned int length = sizeof(struct sockaddr_in);
  struct sockaddr_in client;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket failed");
    exit(-1);
  }
  client.sin_family = AF_INET;
  client.sin_port = htons(10000);
  client.sin_addr.s_addr = INADDR_ANY;

  bzero(&client.sin_zero, 0);

  if ((connect(sock, (struct sockaddr *)&client, length)) == -1)
  {
    perror("connection falied");
    exit(-1);
  }

  char buffer[100];
  FILE *f;
  int c, n;
  f = fopen("file.txt", "r");
  fscanf(f, "%[^\n]", buffer);
  send(sock, &buffer, sizeof(buffer), 0);
  recv(sock, &c, sizeof(c), 0);
  printf("%s\n", buffer);
  if (c == 1)
    cout << " File uploaded on server successfully" << endl;
  else
    cout << "file uploading failed :" << endl;

  return 0;
}