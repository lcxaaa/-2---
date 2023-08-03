 #include"../include/Myspider.h"

void* customerWork(void*val){
	char asktype[] = ".html\0";
	//爬虫任务处理
	while(pool->able){
		url_t* url;
		pthread_mutex_lock(&mutex);
		while(pool->cur==0&&!pool->dead)
			pthread_cond_wait(&CR,&mutex);//任务的等待
	
		if(!pool->dead&&pool->cur!=0){
			pool->cur --;
			pool->work++;
			pool->busy--;
			pthread_mutex_unlock(&mutex);
			//任务 得到html里面的其他url jpg可以选择也放到线程池里面
			//producer负责解析html  这个负责download

			url = GetList();//从已经得到的html队列中得到任务
			if(url==NULL) continue;
			GetTrueUrl(url);//url 解析
			pthread_mutex_lock(&mutex);
			Download(url,asktype);//使用客户端套接字下载
			pthread_mutex_unlock(&mutex);
			
			//前面已经下载了url
			char filename[1024];
			sprintf(filename,"./path/html/%s.html",url->name);
			int fd = open(filename,O_RDWR);
			
			GetUrlJpg(fd);//下载jpg文件
			close(fd);

			//这里不可以先free 这里的url要到生产者里面分析后在删除
			if(curnum--<=0) pool->able =0; //任务数量到了，线程池退出
			if(!pool->able){
				break;	
			}
			pool->work--;
			pool->busy++;
		}else{
			pool->dead --;
			pthread_mutex_unlock(&mutex);
			printf("dead \n");
			break;
		}
		//pthread_mutex_unlock(&mutex);
	}
	pthread_mutex_lock(&mutex);
	pool->busy--;
	pthread_mutex_unlock(&mutex);

}

