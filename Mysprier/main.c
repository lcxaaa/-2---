#include"./Myspider.h"
int main(void){
	curnum=5;
	signal(SIGPIPE, SIG_IGN);
	Inithash();
	rear =0;
	head =0;
	rear1 =0;
	head1=0;
	picnum=0;
	url_t* url = (url_t*)malloc(sizeof(url_t));
	strcpy(url->originurl,"https://baike.sogou.com/v1284804.htm");

	//循环得到url,把新的url放到容器队列里面
	Dhead = (DNSNode*)malloc(sizeof(DNSNode));
	Dhead->next =NULL;
	GetTrueUrl(url);
	Download(url,".html");

	Thread_Pool_Create(8,4);
	//因为每个url是 从html得到的，url的数组长度为4096 记得在Regex里面让url末尾变成
	// \0 防止读取多余的html
	//一共执行100次
	
	/*
	for(int j=0;j<3;j++){
		printf("------------get true url --------------\n");
	GetTrueUrl(url);//拆解 url
	printf("------------downloading--------------\n");
	if(Download(url,asktype)){ //下载 后期可以考虑加个线程优化
	//todo 得到队列里面的url	
	printf("--------download num:%d--------------\n",j);
	GetNewUrl(url); //正则分析+去重，并且放到队列里面
	}
	free(url);
	url=NULL;
	url = GetList();
	printf("new url is :%s\n",url->originurl);

	if(url==NULL) break;
	}	
	free(url);
	return 0;
	*/
}
