#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>   
#include <errno.h>   
#include <termios.h> 

int open_port(const char *str, speed_t baud) {
	struct termios options;
	int fd;

	fd = open(str, O_RDWR | O_NOCTTY | O_NONBLOCK);

	if (fd == -1) {
		perror("open");
	}
	else {
		fcntl(fd, F_SETFL, 0);
	}

	/* getting current options */
	tcgetattr(fd, &options);

	/* setting new options */
	cfsetispeed(&options, baud); /* set input baudrate */
	cfsetospeed(&options, baud); /* set output baudrate */

	options.c_iflag &= ~INPCK; /* disable input parity checking */
	options.c_iflag &= ~IXON; /* disable flow control on output */
	options.c_iflag &= ~IXOFF; /* disable flow control on input */
	options.c_iflag &= ~IXANY; /* disable restart stopped output when typing */

	options.c_oflag |= OPOST; /* enable implementation-defined output processing */

	options.c_cflag |= CLOCAL; /* enable receiver */ 
	options.c_cflag |= CREAD; /* set to local mode (ignore modem control lines)  */
	options.c_cflag &= ~PARENB; /* no parity bit */
	options.c_cflag &= ~CSTOPB; /* set one stop bit*/
	options.c_cflag &= ~CSIZE;  /* clear character size mask */
	options.c_cflag |= CS8;    /* set character size mask to 8 bit */

	options.c_lflag &= ~ICANON; /* disable canonical mode -> raw data */ 
	options.c_lflag &= ~ECHO; /* disable echoing input characters -> raw data*/
	options.c_lflag &= ~ECHOE; /* disable erase -> raw data*/
	options.c_lflag &= ~ISIG; /* disale signal generation -> raw data*/  

	options.c_cc[VMIN] = 0; /* none-blocking mode */
	options.c_cc[VTIME] = 0; /* non-blocking mode */

	/* apply new options */
	tcsetattr(fd, TCSANOW, &options);

	return (fd);
}

int main(int argc, char **argv) {
    char data[7] = {'\n',17,' ',5,' ',13,'\n'}; /* random data */ 
	int check;
	int writeport = open_port("/dev/ttymxc3", 9600); 

	check = write(writeport, data, sizeof(data));
	if (check < 0) {
		perror("write");
	}

	close(writeport);

	(void)argc;
	(void)argv;
	return EXIT_SUCCESS;
}
