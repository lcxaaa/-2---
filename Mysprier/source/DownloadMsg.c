#include"../include/Myspider.h"
void AddDNS(DNSNode** temp,const char*ip,const char*s){
	//保存DNS的 得到的域名结果
	DNSNode * t2 = *temp;
	*temp = (DNSNode*)malloc(sizeof(DNSNode));
	strcpy((*temp)->domain,s);
	strcpy((*temp)->ip,ip);
	(*temp)->next = t2;//头填
}
char* GetFromDNS(DNSNode* head,const char*domain){
	//从保存DNS的链表里面得到 ip
	while(head!=NULL){
		if(strcmp(head->domain,domain)==0){
			return head->ip;	
		}
		head= head->next;
	}
	return NULL;
}
int AbleDownload(char* res,int size){
	//分析状态码
	for(int j=1;j<size-1;j++){
		if(res[j]=='2'&&res[j-1]==' ') return 1;	
	}	
	return 0;
}
int GetIp(char*ip,const char*domain){
	//DNS 部分  通过DNS得到域名ip
	printf("----------getip-------------\n");
	char *temp = GetFromDNS(Dhead,domain);//看看有没有保存
	if(temp==NULL){
	struct hostent *host = gethostbyname(domain);//DNS解析
	if(host==NULL) return 0;//没有结果
	inet_ntop(AF_INET,host->h_addr_list[0],ip,16);
	AddDNS(&Dhead,ip,domain);//添加结果
	}else{
		printf("having this DNS\n");
		strcpy(ip,temp);	//有此域名的ip缓存
	}
	printf("%s\n",ip);
	return 1;
}

void MakeQuest(char* buf,int size,char* url,char*domain){
	//得到协议头，爬虫的http连接的协议头
	bzero(buf,size); 
	sprintf(buf,"GET %s HTTP/1.1\r\n"\
			"Accept:text/html,image/jpeg;q=0.9,image/webp;q=0.9\r\n"\
			"User-Agent:Mozilla/5.0 (x11; Linux x85_64)\r\n"\
			"Host:%s\r\n"\
			"Connection:close\r\n\r\n",url,domain
		   );
}

int NetInit(const char*ip,int type){
	//与服务器三次握手
	//初始化网络并且connect  TCP的
	int serverfd = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serveraddr;
	serveraddr.sin_family =AF_INET;
	if(type==1){ //看看是http 还是https
		serveraddr.sin_port = htons(443);
	}else{
		serveraddr.sin_port = htons(80);
	}
	serveraddr.sin_addr.s_addr = inet_addr(ip);
	socklen_t addrlen = sizeof(serveraddr);
	connect(serverfd,(struct sockaddr*)&serveraddr,addrlen);
	printf("connect success\n");
	return serverfd;
}   

int Download(url_t* url,char *Stype){
	//http 还是https 的标识就是 type  为1 是https
	int type =0;
	if(strcmp(url->type,"http")>0){
		printf("is https\n");
		type =1;
	}
	printf("download url is %s\n",url->originurl);
	//ssl过程
	SSL*ssl;
	SSL_CTX* ctx;

	char ip[16];
	if(!GetIp(ip,url->domain))return 0;//DNS 域名解析
	int serverfd = NetInit(ip,type);
	printf("%s\n",Stype);

	if(type ==1){
		//安全套接字  https 使用
		
		ssl =(SSL*)malloc(sizeof(SSL));
		
		ctx=(SSL_CTX*)malloc(sizeof(SSL_CTX));
		
		//-------------------ssl过程-------------------
		SSL_load_error_strings();
		SSL_library_init();
		OpenSSL_add_all_algorithms();
		ctx =SSL_CTX_new(SSLv23_method());
		ssl = SSL_new(ctx);
		SSL_set_fd(ssl,serverfd);
		SSL_connect(ssl);
		printf("connect https success\n");
	}

	//协议头
	char request[300];
	MakeQuest(request,4096,url->url,url->domain);
	int len;
	char  buf[8192];
	//发送请求  并且得到对端服务器回复
	if(type==1){
		len = SSL_write(ssl,request,strlen(request)+1);

		len =SSL_read(ssl,buf,sizeof(buf));
	}else{
		len = send(serverfd,request,strlen(request)+1,0);
		len = recv(serverfd,buf,sizeof(buf),0);
	}
	//定位资源开始的地方   这里本质是定位到的 {\r\n\r\n 数据} 的\r那里 
	char * pos = strstr(buf,"\r\n\r\n");
	char res[4096];
	snprintf(res,pos-buf+4,"%s",buf);
	printf("%s\n ==============================\n",res);
	if(!AbleDownload(res,20)){//判断状态码
		printf("---------------cannot downloading--------------\n");
		if(type==1){
		SSL_shutdown(ssl);
		SSL_free(ssl);
		SSL_CTX_free(ctx);
		close(serverfd);
		}else{
		close(serverfd);
		}
		return 0;
	}
	printf("success request\n");
	//创建文件

	char filename[1024];
	sprintf(filename,"./path/%s/%s%s",Stype+1,url->name,Stype);
	int fd =open(filename,O_RDWR|O_CREAT,0664);
	//写入回复包的残留数据 
	int ms=write(fd,pos+4,len-(pos-buf+4));
	if(type==1){
		//https循环读取数据
		while((len = SSL_read(ssl,buf,sizeof(buf)))>0){
			ms=write(fd,buf,len);
			bzero(buf,sizeof(buf));
		}
		//断开
		SSL_shutdown(ssl);
		SSL_free(ssl);
		SSL_CTX_free(ctx);
		close(serverfd);
		close(fd);

	}else{
		//http 循环读取
		while((len = recv(serverfd,buf,sizeof(buf),0))>0){
			ms = write(fd,buf,len);
			bzero(buf,sizeof(buf));
		}
		//断开
		close(serverfd);
		close(fd);
		
	}
		if(strcmp(Stype,".jpg")!=0)//只放html的url
		AddList1(url);//放到下完的队列
return 1;

}

