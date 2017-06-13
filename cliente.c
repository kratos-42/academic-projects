void create_captcha_file(const char* palavra){

	mkfifo("./toServer");
	mkfifo("./fromServer", 0666);
	int fd = open("./toServer", 0666);
	pid_t pid = fork();
	char imgFile[6];
	char* buffer[16384];

	if(pid==0){
	
		write(fd, palavra, strlen(palavra));
		close(fd);

	}

	close(fd);
	waitpid(pid, &status, 0);
	fd = open("./fromServer");

	snprintf(imgFile, "./%s.png", palavra, sizeof(palavra));
	if((img = open(imgFile, O_CREAT | O_APPEND | O_WRONLY, 0666)) == -1 ){
		perror(imgFile);
		return;
	}

	n = read(fd, buffer, sizeof(buffer));
	write(img, buffer, n);
	close(imgFile); close(buffer);

}


int main(){

	char buffer[6];
	int n;

	if((n = read(0, buffer, sizeof(buffer))) > 0){
		create_captcha_file(buffer);
	}

	return 0;

}