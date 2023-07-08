#include"Myspider.h"

int GetNewUrl(url_t* oldurl){
	//上一个url的文件，被下载到文件里面  为 url_t 的name
	char filename[1024];
	sprintf(filename,"./path/html/%s.html",oldurl->name);
	int fd = open(filename,O_RDWR);

	//即创建一个 filename  为 ./url_t->name  打开它，然后正则它 得到url	
	//todo 正则分析+去重复+放入
	RegexRead(fd);
	//GetUrlJpg(fd);
	close(fd);
	return 0;
	//放入新的url后，删除老的url 在链表里面
}
