#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(){
  int ssock, csock;
  unsigned int length;

  struct sockaddr_in server, client;

  if((ssock=socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket: not created");
    exit(-1);
  }
  else{
    cout << "socket created successfullly" << endl;
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  server.sin_addr.s_addr = INADDR_ANY;

  bzero(&server.sin_zero,0);
  length = sizeof(struct sockaddr_in);

  if((bind(ssock, (struct sockaddr *)&server, length)) == -1){
    perror("bind error: binding falied ");
    exit(-1);
  }
  else {
    cout << "bind completed" << endl;
  }

  if((listen(ssock, 5)) == -1){
    perror("listen error: server is not listening ");
    exit(-1);
  }
  else {
    cout << "server is listening" << endl;
  }

  if((csock=accept(ssock, (struct sockaddr *)&client, &length)) == -1){
    perror("accept error: server is not accepting any packet ");
    exit(-1);
  }
  else {
    cout << "server is ready to accept packet" << endl;
  }

  while(1){
    int a, b, c;
    recv(csock, &a, sizeof(a), 0);
    recv(csock, &b, sizeof(b), 0);
    c = a + b;
    send(csock, &c, sizeof(c), 0);
    cout << endl << "sent sum=: " << c << endl;
  }

  close(ssock);
  return 0;
}