#include"./Myspider.h"

url_t* GetList(){
	if(c[head%30].val!=NULL){
		url_t* temp = c[head%30].val;
		c[head++%30].val=NULL;
		return temp;
	}
	return NULL;
}

void AddList(url_t* u){
	if(rear+1-head<0)return;
	if(c[rear%30].val!=NULL){
		//free(c[rear%30].val);//rear 为30时，出现错误
		//c[rear%30].val=NULL;
		return;
	}
	c[rear++%30].val = u; 
}

url_t* GetList1(){
	//
	if(c2[head1%30].val!=NULL){
		url_t* temp = c2[head1%30].val;
		c2[head1++%30].val=NULL;
		return temp;
	}
	return NULL;
}

void AddList1(url_t* u){
	// yi jing wang chen dui lie
	if(rear1+1-head1<0)return;
	if(c2[rear1%30].val!=NULL){
		//free(c2[rear1%30].val);//rear 为30时，出现错误
		//c2[rear1%30].val=NULL;
		return;
	}
	c2[rear1++%30].val = u;
}

