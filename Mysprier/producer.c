#include"./Myspider.h"
void* producerWork(void*val){
	while(pool->able){
	
	printf("having events\n");

		url_t* url = GetList1();//从写完队列得到新的
		GetNewUrl(url);
		curnum --;
		printf("==================%d================\n",curnum);
		if(url!=NULL){
			printf("producer :free url\n");
		free(url);
		url = NULL;
		}
		pthread_mutex_lock(&mutex);

		printf("=================\n");
		printf("cur=%d\n",pool->cur);
		printf("=================\n");

		if(pool->cur!=0){
			printf("producer wait\n");
			pthread_cond_signal(&MA);
			pthread_cond_wait(&PR,&mutex);
			printf("producer wake up\n");
		}
		pthread_mutex_unlock(&mutex);
	}
}

