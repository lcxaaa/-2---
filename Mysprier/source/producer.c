 #include"../include/Myspider.h"

void* producerWork(void*val){
	while(pool->able){
	
	printf("having events\n");

		url_t* url = GetList1();//得到已经下载完毕的jpg
		GetNewUrl(url);//解析得到新的url
		curnum --;
		printf("==================%d================\n",curnum);
		if(url!=NULL){
			//删除url占用的空间
			printf("producer :free url\n");
		free(url);
		url = NULL;
		}
		pthread_mutex_lock(&mutex);

		printf("=================\n");
		printf("cur=%d\n",pool->cur);
		printf("=================\n");
		//线程池的状态
		if(pool->cur!=0){
			printf("producer wait\n");
			pthread_cond_signal(&MA);
			pthread_cond_wait(&PR,&mutex);
			printf("producer wake up\n");
		}
		pthread_mutex_unlock(&mutex);
	}
}

