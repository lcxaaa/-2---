#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <netdb.h>
#include<string.h>
#include<fcntl.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include<arpa/inet.h>
#include<openssl/bio.h>
#include<regex.h>
#include<sys/mman.h>
typedef struct Myurl{
	char originurl[4096];
	char  type[6];
	char domain[1024];
	char url[1024];
	char name[1024];
}url_t;

typedef struct LIST{
	url_t* val;
}container;

typedef struct node{
	struct node * next;
	char vak[10];//百科的网址的编号都小于10
}Node;

typedef struct IpNode{
	char domain[1024];
	char ip[16];
	struct IpNode* next;
}DNSNode;

DNSNode *Dhead;
Node hash[10];

//待下载的队列
container c[30];
int rear ;
int head;
//已经下载的队列
container c2[30];
int head1 ;
int rear1;
int curnum;
void Inithash();
void addHash(int j,char *s);
int FindHash(int j,char*s);
int GetIp(char* ip,const char* domain);
void MakeQuest(char*buf,int size,char*url,char*domain);
int NetInit(const char*ip,int type);
int Download(url_t*url,char*Stype);
void GetTrueUrl(url_t* url);
int CheakUrl(char * s,int size);
int GetNewUrl(url_t* oldurl);
void RegexRead(int fd);
url_t* GetList();
void AddList(url_t*u);
void GetUrlJpg(int fd);
int picnum;
char* GetFromDNS(DNSNode* head,const char*domain);
void AddDNS(DNSNode**temp,const char*ip,const char*s);
url_t* GetList1();
void AddList1(url_t* u);
//==========================================
typedef struct thread_pool{
	int max;
	int min;
	int busy;
	int work;
	pthread_t Mt;
	pthread_t Pt;
	pthread_t*ct;
	int able;
	int cur;
	int dead;
}pool_t;
pthread_mutex_t mutex;
pthread_mutex_t mutex1;
pthread_cond_t MA;
pthread_cond_t CR;
pthread_cond_t PR;

pool_t* pool;

void *customerWork(void* val);
void *producerWork(void* val);
void *manageWork(void* val);
void Thread_Pool_Create(int max,int min);
void thread_pool_destroy();

void FreeList();
void FreeHash();
void FreeDNSList();
