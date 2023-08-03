 #include"../include/Myspider.h"

void GetTrueUrl(url_t*url){
	//得到是http 还是https
	int i=0;
	bzero(url->type,sizeof(url->type));
	bzero(url->domain,sizeof(url->domain));
	bzero(url->name,sizeof(url->name));
	bzero(url->url,sizeof(url->name));
	
	for(i;url->originurl[i]!=':'&&i<6;i+=1){
		url->type[i]=url->originurl[i];	
	}
	url->type[i] ='\0';
	//跳过 : //  
	i+=3;
	//得到域名
	int j=0;
	for(j=0;url->originurl[i]!='/';i+=1,j++){
		url->domain[j] = url->originurl[i];	
	}
	url->domain[j]='\0';
	j=0;
	int len = strlen(url->originurl);
	int m=i;
	
	//得到url
	for(j=0;i<len+1;i+=1,j+=1){
		if(url->originurl[i]=='/') m=i+1;
		url->url[j] = url->originurl[i];	
	}
	url->url[j]='\0';
	//得到文件名字
	
	for(j=0;m<len+1;m++,j++){
		url->name[j] = url->originurl[m];
	}
		url->name[j]='\0';
	
	printf("name :%s\nurl:%s\n",url->name,url->url);
}
