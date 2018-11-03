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
	int sock;
	unsigned int len;
	int n;
	struct student t;

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

	printf("Enter roll no : ");
	cin >> n;
	send(sock, &n, sizeof(n), 0);
	cout << "Data Sent\n";
	recv(sock,&t,sizeof(t),0);

	printf("Roll = %d\n",t.roll);
	printf("Marks 1= %d\n",t.m1);
	printf("Marks 2= %d\n",t.m2);
	printf("Marks 3= %d\n",t.m3);
	printf("Average = %f\n",t.avg);

	close(sock);
  return 0;
}