#include"./Myspider.h"

void GetUrlJpg(int fd){
	lseek(fd,0,SEEK_SET);
	int size = lseek(fd,0,SEEK_END);
	printf("%d\n",size);
	char * ptr = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	char * m = ptr;
	regex_t reg;
	regcomp(&reg,"src=[^\"]\\?\"\\([^\"]\\+\\)\\.jpg/\\([0-9]\\+\\)",0);
	regmatch_t ma[3];

	char stype[]=".jpg";
	while(regexec(&reg,m,3,ma,0)==0){
	url_t node;
	snprintf(node.originurl,ma[1].rm_eo-ma[1].rm_so+1,"%s",m+ma[1].rm_so);
	sprintf(node.originurl,"%s.jpg/",node.originurl);
	snprintf(node.originurl+strlen(node.originurl),ma[2].rm_eo-ma[2].rm_so+1,"%s",m+ma[2].rm_so);
	printf("url is:%s\n",node.originurl);
	GetTrueUrl(&node);
	bzero(node.name,sizeof(node.name));
	sprintf(node.name,"picture%d",picnum++);
	m+=ma[0].rm_eo;
	pthread_mutex_lock(&mutex);
	Download(&node,stype);
	pthread_mutex_unlock(&mutex);
	}
	if(ptr!=NULL){
		printf("jpg:munmap ptr\n");
	munmap(ptr,size);
	ptr =NULL;
	}
}
