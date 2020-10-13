#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <pthread.h>


int obd_fd;
pthread_t tstbrd_thread;

void *TSTBRD_thread_callback(void *data)
{
	int beforeSize = 0;
	int size;
	
	char buffer[32] ;
	char beforebuffer[32] ;

	tcflush(obd_fd,TCIFLUSH);
	printf( "read TSTBRD_thread_callback  :%d \n", obd_fd);
//	usleep(1000);

	while (1) {
		size = read(obd_fd, buffer, 32);
		if (size > 0) 
		{
			if(buffer[size-1] != '\n')
			{
				memcpy(beforebuffer+beforeSize,buffer,size);
				beforeSize = beforeSize+size;
				printf( "TSTBRD_callback1:0x%02X 0x%02X 0x%02X 0x%02X 0x%02X 0x%02X,%d\n", buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],size);
			} else {
				memcpy(beforebuffer+beforeSize,buffer,size);
				printf( "TSTBRD callback:%s,%d\n", beforebuffer,size);
				memset(buffer,0,32);
				memset(beforebuffer,0,32);
				beforeSize = 0;
				size = 0;
			}
		}	
		else
			printf( "TSTBRD_callback size 0\n");
			
	}
	printf( "TSTBRD_callback exit\n");

	return NULL;
}


int jimi_uart_open(void)
{
	int fd;
	speed_t speed;

	/* Opening device */
	{
		const char *path_utf ="/dev/ttyS1";
		fd = open(path_utf, O_RDWR | O_NOCTTY );  // O_SYNC  O_NDELAY
		printf("open() fdn = %d\n", fd);
		if (fd == -1)
		{
			/* Throw an exception */
			printf("Cannot open port\n");
			/* TODO: throw an exception */
			return -1;
		}
	}

	/* Configure device */
	{
		struct termios cfg,newtio;
		printf("Configuring serial port\n");
		if (tcgetattr(fd, &cfg))
		{
			printf("tcgetattr() failed \n");
			close(fd);
			/* TODO: throw an exception */
			return -1;
		}

		fcntl(fd, F_SETFL, 0);

		bzero(&newtio, sizeof(newtio));

		newtio.c_cflag |= CLOCAL | CREAD;
		newtio.c_cflag &= ~CSIZE;
		newtio.c_cflag |= CS8;
		
		newtio.c_cflag &= ~(PARENB|PARODD);
		newtio.c_iflag &= ~INPCK;
		newtio.c_cflag &= ~CSTOPB;

	//	newtio.c_lflag |= ICANON;
	//	newtio.c_lflag &=~( ECHO | ECHOE|ECHONL|ISIG);
	//	newtio.c_oflag |= OPOST;
	//	newtio.c_lflag |= ICANON | ECHO | ECHOE;
		newtio.c_lflag &=~( ICANON | ECHO | ECHOE|ECHONL|ISIG);
		newtio.c_iflag &=~(INLCR|IGNCR|ICRNL|IXON|IXOFF);
		newtio.c_oflag &=~(ONLCR|OCRNL);
		newtio.c_oflag &= ~OPOST;

		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		//cfsetispeed(&newtio, B19200);
		//cfsetospeed(&newtio, B19200);

		
		newtio.c_cc[VTIME] = 0;
		newtio.c_cc[VMIN] = 1;

		tcflush(fd,TCIFLUSH);

		if (tcsetattr(fd, TCSANOW, &newtio))
		{
			printf("tcsetattr() failed \n");
			close(fd);
			/* TODO: throw an exception */
			return -1;
		}
	}

	printf("Configuring serial port--end \n");

	return fd;
}


int main(int argc, char *argv[])
{
	int ret = 0;
	char buff[] = {0xAA, 0xA5, 0x02, 0x2F, 0x00, 0x2F};
	obd_fd = jimi_uart_open();
	if (obd_fd < 0) {
		printf("open uart error!\n");
		return 0;
	}
	
	pthread_create(&tstbrd_thread, NULL, TSTBRD_thread_callback, NULL);
	
	tcflush(obd_fd,TCOFLUSH);
	usleep(2000);
	
	ret = write(obd_fd, buff, sizeof(buff));
	printf("write ret:%d \n",ret);
	
	pthread_join(tstbrd_thread, NULL);
		
	return 0;
}
