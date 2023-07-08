#include"./Myspider.h"

void RegexRead(int fd){
	int size = lseek(fd,0,SEEK_END);
	lseek(fd,0L,SEEK_SET); 
	regex_t reg;
	//regcomp(&reg,"data-lemmaid=\"\\([^\"]\\+\\)\">\\([^<]\\+\\)</a>",0);
	regcomp(&reg,"/lemma/ShowInnerLink\\.htm?lemmaId=\\([0-9]\\+\\)&amp;",0);
	char * m = mmap(NULL,size,PROT_READ,MAP_SHARED,fd,0);
	regmatch_t ma[2];
	char * ptr =m;
	char link[1024];
	int i=0;
	while(regexec(&reg,ptr,2,ma,0)==0){//bai du gai cheng 3
		//sprintf(link,"%s","https://baike.baidu.com/item/");
		sprintf(link,"%s","https://baike.sogou.com");
		//snprintf(link+strlen(link),ma[2].rm_eo-ma[2].rm_so+1,"%s",ptr+ma[2].rm_so);
		snprintf(link+strlen(link),ma[1].rm_eo-ma[1].rm_so+3,"/v%s",ptr+ma[1].rm_so);
		 sprintf(link,"%s.htm",link);
		
		if(!CheakUrl(ptr+ma[1].rm_so , ma[1].rm_eo-ma[1].rm_so+1)){
			ptr+= ma[0].rm_eo;
			printf("-----------url is exists-------------\n");
			continue;
		}else{
			//放入
			//新的url
			if(i++>10) break;
			printf("url is %s\n",link);
			pthread_mutex_lock(&mutex);
			pool->cur++;
			pthread_mutex_unlock(&mutex);
			url_t * newurl = (url_t*)malloc(sizeof(url_t));
			strcpy(newurl->originurl,link);
			AddList(newurl);//放到待分析队列
		}   
		bzero(link,sizeof(link));
		ptr+= ma[0].rm_eo;
	}
	if(m!=NULL){
	munmap(m,size);
	m=NULL;
	}
	regfree(&reg);
}
