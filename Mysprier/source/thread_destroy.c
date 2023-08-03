 #include"../include/Myspider.h"

void FreeList(){
	//清空队列
	printf("FreeList========\n");
	for(head;head<rear;head++){
		if(c[head%30].val!=NULL){
			free(c[head%30].val);
			c[head%30].val=NULL;
		}
	}
	for(head;head<rear;head++){
		if(c[head%30].val!=NULL){
			free(c[head%30].val);
			c[head%30].val=NULL;
		}
	}

}

void FreeHash(){
	//清空哈希
	printf("FreeHash========\n");
	for(int i=0;i<=9;i++){
		 Node* n =  hash[i].next;
		 Node* temp =NULL;
		 if(n==NULL) continue;
		 else if(n->next!=NULL) temp = n->next;
		 else if(n->next==NULL){
			 printf("11111\n");
			 free(n);
			 n =NULL;
		 	continue;	
		 }
		printf("hash.next:%p  n %p  n->next:%p\n",hash[i].next,n,n->next);
	
		 while(temp){
			 printf("n: %p temp %p\n",n,temp);
			free(n);
			printf("free: %p\n",n);
			n= temp;
			temp = temp->next;
		 }
		 printf("out  n:%p  i=%d\n",n,i);
		 free(n);
		 printf("================\n");
	}
}

void FreeDNSList(){
	//清空DNS的容器
	printf("FreeDNSList========\n");
	DNSNode * temp = Dhead;
	if(temp==NULL) return;
	else if(temp->next==NULL){
		free(temp);
		temp=NULL;
		return;
	}
	DNSNode * Stemp = temp->next;
	while(Stemp){
		free(temp);
		temp = Stemp;
		Stemp = Stemp->next;
	}
	free(temp);
}

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
	FreeList();
	FreeHash();
	FreeDNSList();
	pthread_mutex_destroy(&mutex);
	pthread_mutex_destroy(&mutex);
}

