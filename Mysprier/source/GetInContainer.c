 #include"../include/Myspider.h"

url_t* GetList(){
	// 得到爬出的html的url
	if(c[head%30].val!=NULL){
		url_t* temp = c[head%30].val;
		c[head++%30].val=NULL;
		return temp;
	}
	return NULL;
}

void AddList(url_t* u){
	//放入爬到的html的新的url
	if(rear+1-head<0)return;
	if(c[rear%30].val!=NULL){
		//如果存在url，则不接受此url

		//free(c[rear%30].val);//rear 为30时，出现错误
		//c[rear%30].val=NULL;
		return;
	}
	//addlist 后不可以直接free
	c[rear++%30].val = u; 
}

url_t* GetList1(){
	//得到下完的 html1的url  用于得到新的url
	if(c2[head1%30].val!=NULL){
		url_t* temp = c2[head1%30].val;
		c2[head1++%30].val=NULL;
		return temp;
	}
	return NULL;
}

void AddList1(url_t* u){
	//添加 已经下完的html
	if(rear1+1-head1<0)return;
	if(c2[rear1%30].val!=NULL){
		//free(c2[rear1%30].val);//rear 为30时，出现错误
		//c2[rear1%30].val=NULL;
		return;
	}
	c2[rear1++%30].val = u;
}

