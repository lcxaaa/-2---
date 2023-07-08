#include"./Myspider.h"

void Inithash(){
	for(int i=0;i<9;i++){
		hash[i].next= NULL;	
	}
	for(int i=0;i<30;i++){
		c[i].val =NULL;	
	}
}

void addHash(int j,char *s){
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;
	for(int i=0;i<10;i++){
		if(s[i]<'0'||s[i]>'9'){
			temp->vak[i]='\0';
			break;
			}
		temp->vak[i] = s[i];	
	}
	Node** n = &hash[j].next;
	if(*n==NULL) {
		*n=temp;
		return;
	}
	Node* ps =  hash[j].next;
	hash[j].next = temp;
	temp->next = ps;
}
int FinHash(int j,char*s){
	Node* temp = hash[j].next;
	while(temp){
		if(strcmp(temp->vak,s)==0) return 0;
		temp = temp->next;
	}
	return 1;
}
int CheakUrl(char * s,int size){
	//去重模块   使用哈希表记录url?
	if(s==NULL)return 0;
	int j=0;

	char* n = (char*)malloc(size);
	for(int i=0;i<size-1;i++){
		j+= s[i]-'0';
		n[i]=s[i];
	}
	n[size-1]='\0';
	j%=10;
	if(!FinHash(j,n)) return 0;
	addHash(j,s);
	free(n);
	return 1;	
}
