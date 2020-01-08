#include <stdio.h>
#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400
void *thread(void* vargp);
void proxy(int connfd);
void clienterror(int fd, char *cause,char *errnum, char *shortmsg, char *longmsg);
int parse_uri(char* uri, char* host, char* path, int* port);
void read_requesthdrs(rio_t *rp);
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *connection_hdr = " Connection: close\r\n";
static const char *proxy_connection_hdr="Proxy-Connection: close\r\n\r\n";
int main(int argc, char **argv)
{
	//printf("start of main\n");
	char hostname[MAXLINE], port[MAXLINE];
	int listenfd,*connfd;
	socklen_t clientlen;
	struct sockaddr_storage clientaddr;
	pthread_t tid;

	if(argc !=2){
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	//printf("aaaa\n");
	listenfd=Open_listenfd(argv[1]);
	while(1){
		clientlen=sizeof(struct sockaddr_storage);
		//printf("while of main\n");
		connfd=Malloc(sizeof(int));
		*connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
		Getnameinfo((SA *)&clientaddr,&clientlen,hostname,MAXLINE,port,MAXLINE,0);
		printf("Accepted connection from (%s %s)\n",hostname,port);
		Pthread_create(&tid,NULL, thread,connfd);
	}
	Close(listenfd);
	exit(0);



}

void* thread(void* vargp){
	//printf("start of thread\n");
	int connfd=*((int *)vargp);
	Pthread_detach(pthread_self());
	Free(vargp);
	proxy(connfd);
	//printf("come back to thread\n");
	Close(connfd);
	return NULL;
}

void proxy(int connfd){
	char cbuf[MAXLINE],method[MAXLINE],uri[MAXLINE],version[MAXLINE],host[MAXLINE],path[MAXLINE],sbuf[MAXLINE],pstr[MAXLINE],buf[MAXLINE];
	rio_t client_rio,rio;
	
	int proxyfd,port;
	size_t n;
	//printf("start of proxy\n");
	Rio_readinitb(&client_rio,connfd);
	Rio_readlineb(&client_rio,cbuf,MAXLINE);
	printf("%s",cbuf);
	
	sscanf(cbuf, "%s %s %s", method,uri,version);
	if(strcasecmp(method,"GET")){
		clienterror(connfd,method,"501", "Not implemented","Proxy does not implement this method");
		return;
	}
	//printf("wow\n");	
	read_requesthdrs(&client_rio);
	//printf("fuck");
	
	if(parse_uri(uri,host,path,&port)==-1){
		clienterror(connfd,uri,"404","Not found","Proxy couldn't parse the request");
		return;
	}
	rio_t rios;
	printf("adfasddfa\n");
	
	sprintf(pstr,"%d",port);
	proxyfd=Open_clientfd(host,pstr);
	Rio_readinitb(&rios,proxyfd);
	sprintf(sbuf, "GET %s HTTP/1.0\r\n",path);
	Rio_writen(proxyfd,sbuf,strlen(sbuf));
	sprintf(sbuf,"Host: %s\r\n", host);
	Rio_writen(proxyfd,sbuf,strlen(sbuf));
	Rio_writen(proxyfd,user_agent_hdr,strlen(user_agent_hdr));
	Rio_writen(proxyfd,connection_hdr,strlen(connection_hdr));
	Rio_writen(proxyfd,proxy_connection_hdr,strlen(connection_hdr));
	printf("aproxy");
	while((n=Rio_readlineb(&rios,sbuf,MAXLINE))!=0){
		Rio_writen(connfd,sbuf,n);
	}
	printf("proxy after while");
	Close(proxyfd);
	return;
}

void clienterror(int fd, char *cause, char *errnum,char *shortmsg, char *longmsg){
	char buf[MAXLINE], body[MAXBUF];
	
	/* Build the HTTP response body */
	sprintf(body, "<html><title>Proxy Error</title>");
	sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
	sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
	sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
	sprintf(body, "%s<hr><em>The Proxy Web server</em>\r\n", body);

	
 	/* Print the HTTP response */
	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
	Rio_writen(fd, buf, strlen(buf));
	Rio_writen(fd, body, strlen(body));
}

int parse_uri(char* uri, char* host, char* path, int* port){
	char* hostp;
	char* portp;
	char* pathp;
	char p[10];
	int l;
	printf("start of parse\n");
	if(!strstr(uri,"http://")){
		host[0]='\0';
		return -1;
	}
	hostp=uri+7;
	portp=strchr(hostp,':');
	pathp=strchr(hostp,'/');
	printf("uri:%p\n",uri);
	printf("hostp:%p\n",hostp);
	printf("portp:%p\n",portp);
	printf("pathp:%p\n",pathp);
	printf("host:%s",hostp);
	if(portp!=NULL){
		l=portp-hostp;
		strncpy(host,hostp,l);
		host[l]='\0';
		strncpy(p,portp+1,pathp-1-portp);
		p[pathp-1-portp]='\0';
		*port= atoi(p);
	}
	else{
		l=pathp-hostp;
		strncpy(host,hostp,l);
		host[l]='\0';
		*port=atoi("80\0");
	}
	strcpy(path,pathp);
	return 0;
}


void read_requesthdrs(rio_t *rp){
	printf("start of read\n");
	char buf[MAXLINE];
	
	while(strcmp(buf, "\r\n")) {
		printf("while in read!");
		Rio_readlineb(rp, buf, MAXLINE);
		printf("%s", buf);
	}
	return;
}



