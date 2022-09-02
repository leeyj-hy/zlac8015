#include <stdio.h>
#include <string>
#include <string.h>
#include <fcntl.h> 
#include <errno.h> 
#include <termios.h> 
#include <unistd.h> 
#include <iostream>


#define MAX_BUF 1024
using namespace std;
class Serial{
	
	public:
		Serial(string port_name,int baud_rate);
		Serial();
		~Serial();
		int swrite(const char* item,int size);
		int sread(uint8_t* buf,int size = sizeof(char));
		bool good;
		int serial_port;
	private:
};

Serial::Serial(){
	serial_port = -1;
}
Serial::Serial(string port_name,int baud_rate){
	serial_port = open(port_name.c_str(), O_RDWR);
	cout<<"Opening "<<port_name<<" port..."<<endl;
    if (serial_port < 0) {
    	good = false;
		printf("Error %i from open: %s\n", errno, strerror(errno));
    }
    printf("Succesed open port...\n");
    // Create new termios struc, we call it 'tty' for convention
    struct termios tty;

    // Read in existing settings, and handle any error
    printf("Setting port tty...\n");
    if(tcgetattr(serial_port, &tty) != 0) {
    	good = false;
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }
	printf("Succesed set port tty...\n");
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;  
    tty.c_cflag &= ~CSIZE; 
    tty.c_cflag |= CS8;
    tty.c_cflag &= ~CRTSCTS;
    tty.c_cflag |= CREAD | CLOCAL;
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; 
    tty.c_lflag &= ~ECHOE;
    tty.c_lflag &= ~ECHONL;
    tty.c_lflag &= ~ISIG;
    tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
    tty.c_oflag &= ~OPOST; 
    tty.c_oflag &= ~ONLCR; 
    tty.c_cc[VTIME] = 10;   
    tty.c_cc[VMIN] = 0;
    if(baud_rate == 9600){
		cfsetispeed(&tty, B9600);
		cfsetospeed(&tty, B9600);
    }
    else if(baud_rate == 115200){
    	cfsetispeed(&tty, B115200);
		cfsetospeed(&tty, B115200);	
    }
    printf("Setting tty serial...\n");
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
    	good = false;
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
    }
    printf("!! ALL setting end !!\n");
    good = true;
}

Serial::~Serial(){
	close(serial_port);
}

int Serial::swrite(const char* item,int size){
	if(serial_port >= 0){
		int write_byte = write(serial_port,item,size);
		if(write_byte<0){
			cout<<"Write Error!!"<<endl;
			return -1;
		}
		else
			return write_byte;
	}
	else{
		cout<<"Can't use port!!"<<endl;
		return false;
	}
}

int Serial::sread(uint8_t* buf,int size){
	if(serial_port >= 0){
		int read_byte = read(serial_port,buf,size);
		if(read_byte<0){
			cout<<"Read Error!!"<<endl;
			return -1;
		}
		else
			return read_byte;
	}
	else{
		cout<<"Can't use port!!"<<endl;
		return -1;
	}
}
