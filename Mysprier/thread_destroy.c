#include"./Myspider.h"

void thread_pool_destroy(){
	for(int i=0;i<pool->max;i++){
		pool->dead =100;
		pthread_cond_signal(&CR);
	}

	for(int i=0;i<pool->max;i++){
		if(pool->ct[i]!=-1)
			pthread_join(pool->ct[i],NULL);
	}
	printf("destory M\n");
	pthread_cond_signal(&MA);
	pthread_join(pool->Mt,NULL);
	printf("destory P\n");
	pthread_cond_signal(&PR);
	pthread_join(pool->Pt,NULL);

	free(pool->ct);
	free(pool);
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex);
}

