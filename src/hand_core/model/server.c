#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc,char *argv[])
{
    struct sockaddr_in p;
    struct sockaddr_in q;
    int z,s,t,x,n,b = sizeof(q);
    char buf[64];
    char filename[64],textfile[64];
    char command[128];
    int fd, file;

    s = socket(AF_INET,SOCK_STREAM,0);
    bzero (&p,sizeof(p));
    p.sin_family = AF_INET;
    p.sin_addr.s_addr = INADDR_ANY;
    p.sin_port = htons(8080);

    bind (s,(struct sockaddr*)&p,sizeof(p));
    listen(s,13);

    while (1) {
        t = accept (s,(struct sockaddr*)&q, &b);
        n = read(t,buf,64);
        buf[n] = 0;
	close(t);
        t = accept (s,(struct sockaddr*)&q, &b);
	strcpy(filename,buf);
	printf("Size: %ld\n", strlen(filename));
	if (filename[strlen(filename)-1] == 'v') {
		printf("Wav sent: %c\n", filename[strlen(filename)-1]);
		printf("### '%s' was sent for filename\n",filename);
        	fd = open (buf,O_CREAT | O_WRONLY,S_IRUSR|S_IWUSR);
        	int idx = 0;
    		do {
        		n = read (t,buf,64);
        		idx += n;
        		write (fd,buf,n);
    		} while (n > 0);
    		close(t);
    		t = accept (s,(struct sockaddr*)&q, &b);
       	 	n = read(t,buf,64);
  	//  	printf("idx: %d\n",idx);
    		buf[n] = 0;
    		//printf("n: %d\n",n);
    		if (!strcmp(buf,"success")) {
    			close(fd);
			strcpy(command, "ffmpeg -y -i ");
			strcat(command, filename);
			strcat(command, " -ar 16000 -ac 1 -acodec pcm_s16le test.wav >nul 2>nul");
    			system(command);
    			FILE *fp;
        		char path[1035];
	//        	printf("Start vosk");
			fflush(stdout);
        	 /* Open the command for reading. */
         		fp = popen("./test_vosk", "r");
         		if (fp == NULL) {
        		        printf("Failed to run command\n" );
        	 	       exit(1);
        		}
  //      	printf("start while loop");
        	/* Read the output a line at a time - output it. */
			char nlp_text[1035];
			int text=0;
        		while (fgets(path, sizeof(path), fp) != NULL) {
//       	         	printf("%s", path);
			if (text == 1) {
				strcpy(nlp_text,path);
				text = 0;
			}
			if (!strcmp(path,"{\n")) {
				text = 1;
//				printf("#####  STRCMP #####: %s",path);
			} 
        		}
			char subbuff[1024];
			int len = strlen(nlp_text);
			memcpy( subbuff, &nlp_text[12], len-14 );
			subbuff[len-14] = '\0';
       			printf("######## NLP TEXT ########\n");
			printf("\n");
			printf("	%s\n",subbuff);
       			printf("##########################\n");
		
        		pclose(fp);
			//strcpy(textfile,filename);
			//strcat(textfile,".txt");
			FILE *f = fopen("nlp_out.txt", "w");
			if (f == NULL)
			{
			    printf("Error opening file!\n");
			    exit(1);
			}
			fprintf(f, "%s\n", subbuff);
			fclose(f);
    		} else {
    			close(fd);
    			printf("fail: %s\n",buf);
    		}
	} else {
		printf("txt sent: %c\n", filename[strlen(filename)-1]);
		fd = open ("nlp_out.txt",O_RDWR | O_CREAT | O_TRUNC,S_IRUSR|S_IWUSR);
        	int idx = 0;
    		do {
        		n = read (t,buf,64);
        		idx += n;
        		write (fd,buf,n);
    		} while (n > 0);
    		close(t);
    		close(fd);
    		int z,x = sizeof(p);
    		t = accept (s,(struct sockaddr*)&q, &b);
       	 	n = read(t,buf,64);
  	//  	printf("idx: %d\n",idx);
    		buf[n] = 0;
    		//printf("n: %d\n",n);
    		
    		if (!strcmp(buf,"success")) {
    			printf("success\n");
    			file = open ("nlp_out.txt",O_RDONLY);
    			z = lseek(file,0,SEEK_END);
    			lseek(file,0,SEEK_SET);
    			printf("z: %d\n",z);
    			do {
        			n = read (file,buf,23);
       				x += n;
    			} while (x < z);
    			buf[z] = 0;
    			printf("######## NLP TEXT ########\n");
			printf("\n");
			printf("	%s\n",buf);
       			printf("##########################\n");
       			close(file);
    		} else {
    			printf("fail: %s\n",buf);
    		}
		
		
	}
        
        fflush(stdout);
        
        close(t);
    }
}

