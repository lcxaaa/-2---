 #include"../include/Myspider.h"

void Thread_Pool_Create(int max,int min){
	//锁和容器初始化
	pthread_mutex_init(&mutex1,NULL);	
	pthread_mutex_init(&mutex,NULL);
	pthread_cond_init(&CR,NULL);
	pthread_cond_init(&PR,NULL);
	pthread_cond_init(&MA,NULL);


	pool = (pool_t*)malloc(sizeof(pool_t));
	pool->max= max;
	pool->min = min;
	pool->busy = min+(max-min)/2;
	pool->work = 0;
	pool->able = 1;
	pool->cur =0;
	pool->dead =0;
	pthread_create(&pool->Mt,NULL,manageWork,NULL);
	sleep(0);
	pthread_create(&pool->Pt,NULL,producerWork,NULL);
	printf("create success\n");

	while(1){
		printf("thread pool work....\n");
		pthread_mutex_lock(&mutex);
		if(!pool->able){
			pthread_mutex_unlock(&mutex);
			break;
		}
		printf("cur:%d   busy:%d   work:%d\n",pool->cur,pool->busy,pool->work);

		pthread_mutex_unlock(&mutex);
		sleep(10);
	}
	printf("destory pool\n");
	//线程池的销毁
	thread_pool_destroy();
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&CR);
	pthread_cond_destroy(&PR);
	pthread_cond_destroy(&MA);
	//DNS hash 还需删除
}

