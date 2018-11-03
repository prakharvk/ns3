#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

struct student{
	int roll;
	int m1;
	int m2;
	int m3;
	double avg;
};

int main(){
  int ssock, csock;
  unsigned int length;
	struct student a[20];
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

  for(int i=0; i<=19; i++){
  	a[i].roll = i;
		a[i].m1 = (i * i + 5) % 10;
		a[i].m2 = (i * i + 6) % 10;
		a[i].m3 = (i * i + 4) % 10;
		a[i].avg = (a[i].m1 + a[i].m2 + a[i].m3) / 3.0;
  }

  int n;
	recv(csock,&n,sizeof(n),0);
	send(csock,&a[n],sizeof(a[n]),0);

  close(ssock);
  return 0;
}