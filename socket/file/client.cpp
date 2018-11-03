#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <usistd.h>
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

  if ((conect(sock, (struct sockaddr *)&client, length)) == -1)
  {
    perror("connection falied");
    exit(-1);
  }

  while (1)
  {
    FILE *f;
    char s[100];
    cout << "Please enter file name : ";
    cim >> s;
    f = fopen(s, "r");
    if (f == 0)
    {
      cout << "file can't be opend" << endl;
      exit(-1);
    }
    x = fgetc(f);
  }

  return 0;
}