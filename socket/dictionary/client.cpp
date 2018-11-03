#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main() {
  int sock;
  unsigned int length = sizeof(struct sockaddr_in);
  struct sockaddr_in client;

  if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("Socket connection failed");
    exit(-1);
  } else{
    cout << "socket created" << endl;
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(10001);
  client.sin_addr.s_addr = INADDR_ANY;

  bzero(&client.sin_zero, 0);

  if((connect(sock, (struct sockaddr *)&client, length)) == -1) {
    perror("Connection failed");
    exit(-1);
  } else {
    cout << "connected successfully" << endl ;
  }

  while(1) {
    string n;
    int l1, l2;
    char s[100], w[100];
    cout << "Enter length of the string : ";
    cin >> l1;
    cout << "Enter a string : ";
    for(int i = 0; i < l1; i ++){
      cin >> s[i];
    }

    send(sock, &l1, sizeof(l1), 0);
    send(sock, &s, sizeof(s), 0);
    recv(sock, &l2, sizeof(l2), 0);
    recv(sock, &w, sizeof(w), 0);

    cout << "server returns : ";
    if( l2 == -1){
      cout << " Not found" << endl;
    }
    else {
      for(int i = 0; i < l2; i ++){
        cout << w[i];
      }
    }

    cout << endl << "Do you want to continue ....." ;
    cin >> n;
    if(n != "yes") break;
  }

  close(sock);
  return 0;
}