#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main(){
  int sock;
  unsigned int len;

  struct sockaddr_in client;
  if((sock=socket(AF_INET, SOCK_STREAM, 0)) == -1){
    perror("socket creation failed : ");
    exit(-1);
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(10000);
  client.sin_addr.s_addr = INADDR_ANY;

  bzero(&client.sin_zero, 0);
  len = sizeof(struct sockaddr_in);

  if((connect(sock, (struct sockaddr *)&client, len)) == -1){
    perror("connect failed: ");
    exit(-1);
  }

  while(1){
    int a, b, c;
    string ch1 = "yes";
    string ch2;
    cout << "enter two number to add :" << endl;
    cin >> a >> b;

    send(sock, &a, sizeof(a), 0);
    send(sock, &b, sizeof(b), 0);
    recv(sock, &c, sizeof(c), 0);

    cout << "sum is : " << c << endl;
    cout << "do you want to exit...." << endl;
    cin >> ch2;

    if(ch1 == ch2) {
      close(sock);
      exit(0);
    }
  }

  return 0;
}
