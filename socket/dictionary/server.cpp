#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

struct dic {
  char w[100];
  char m[100];
};

bool strc(char a[],char b[])
{
  int q1=strlen(a);
  int q2=strlen(b);
  if(q1 != q2) return false;
  for(int j=0;j <q2; j++) {
    if(a[j] != b[j])
      return false;
  }
  return true;
}

int main(){
  unsigned int length = sizeof(struct sockaddr_in);
  struct dic D[100];
  struct sockaddr_in server, client;
  int ssock, csock;

  char c[] = "pen";
  char m[] = "hen";

  strcpy(D[0].w, c);
  strcpy(D[0].m, m);

  strcpy(D[1].w, c);
  strcpy(D[1].m, m);

  strcpy(D[2].w, c);
  strcpy(D[2].m, m);

  if((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket failed");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(10001);
  server.sin_addr.s_addr =INADDR_ANY;

  bzero(&server.sin_zero, 0);

  if((bind(ssock, (struct sockaddr *)&server, length)) == -1) {
    perror("bind failed");
    exit(-1);
  }

  if((listen(ssock, 5)) == -1) {
    perror("server is not listening");
    exit(-1);
  }

  if((csock = accept(ssock, (struct sockaddr *)& client, &length)) == -1) {
    perror("falied");
    exit(-1);
  }

  while(1) {
    char w[100];
    int l1, l2, index = -1;
    recv(csock, &l1, sizeof(l1), 0);
    recv(csock, &w, sizeof(w), 0);

    cout << "client sent : ";
    for(int i = 0; i < l1; i ++){
        cout << w[i];
    }

    cout << endl;

    for(int i = 0; i < 3; i++) {
      int res = strc(D[i].w, w);
      cout << res << endl;
      if(res ==  0){
        index = i;
        break;
      }
    }

    if(index  == -1) {
      cout << "word not found" << endl;
      send(csock, &index, sizeof(index), 0);
      send(csock, &w, sizeof(w), 0);
    }
    else{
      l2 = strlen(D[index].m);
      for(int i = 0; i < l2; i ++){
        cout << D[index].m[i];
      }
      send(csock, &l2, sizeof(l2), 0);
      send(csock, &D[index].m, sizeof(D[index].m), 0);
    }
    cout << endl;

  }

  close(ssock);
  return 0;
}