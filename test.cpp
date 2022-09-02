#include "serial.hpp"
#include <unistd.h>
#include <iostream>
#include <string>

int main(int argc, char **argv){
	using namespace std;
	
	Serial driver("/dev/ttyUSB1", 115200);
	
	uint8_t read_buf;
	string read;

	uint8_t buf[8];

 // motor mode
	buf[0] = 0x01;
	buf[1] = 0x06;
	buf[2] = 0x20;
	buf[3] = 0x32;
	buf[4] = 0x00;
	buf[5] = 0x03;
	buf[6] = 0xE2;
	buf[7] = 0x06;
	if(write(driver.serial_port, buf, 8)>0){
		cout<<"I send"<<endl;
	}
	sleep(2);
    int a = 0;
	read = "";
	cout<<"I'm ready to read"<<endl;
	for(int i={};i<8;i++){
		if(driver.sread(&read_buf, sizeof(uint8_t))>0){
			read += to_string(read_buf);
            cout<<to_string(read_buf)<<endl;
            a++;
		}			
	}
    cout<<"I read : "<<read<<endl;
    cout<<a<<endl;

// power on	
	buf[0] = 0x01;
	buf[1] = 0x06;
	buf[2] = 0x20;
	buf[3] = 0x31;
	buf[4] = 0x00;
	buf[5] = 0x08;
	buf[6] = 0xD2;
	buf[7] = 0x03;
	if(write(driver.serial_port, buf, 8)>0){
		cout<<"I send"<<endl;
	}
	sleep(2);
    a = 0;
	read = "";
	cout<<"I'm ready to read"<<endl;
	for(int i={};i<8;i++){
		if(driver.sread(&read_buf, sizeof(uint8_t))>0){
			read += to_string(read_buf);
            cout<<to_string(read_buf)<<endl;
            a++;
		}			
	}
    cout<<"I read : "<<read<<endl;
    cout<<a<<endl;
	
// speed 300
	buf[0] = 0x01;
	buf[1] = 0x06;
	buf[2] = 0x20;
	buf[3] = 0x3A;
	buf[4] = 0x01;
	buf[5] = 0x2C;
	buf[6] = 0xA2;
	buf[7] = 0x4A; 
	if(write(driver.serial_port, buf, 8)>0){
		cout<<"I send:"<<endl;
	}
    sleep(2);
    a = 0;
	read = "";
	cout<<"I'm ready to read"<<endl;
	for(int i={};i<8;i++){
		if(driver.sread(&read_buf, sizeof(uint8_t))>0){
			read += to_string(read_buf);
            cout<<to_string(read_buf)<<endl;
            a++;
		}			
	}
    cout<<"I read : "<<read<<endl;
    cout<<a<<endl;

	buf[0] = 0x01;
	buf[1] = 0x03;
	buf[2] = 0x20;
	buf[3] = 0x2C;
	buf[4] = 0x00;
	buf[5] = 0x02;
	buf[6] = 0x0E;
	buf[7] = 0x02; 
	if(write(driver.serial_port, buf, 8)>0){
		cout<<"I send:"<<endl;
	}
    sleep(2);
    a = 0;
	read = "";
	cout<<"I'm ready to read"<<endl;
	for(int i={};i<9;i++){
		if(driver.sread(&read_buf, sizeof(uint8_t))>0){
			read += to_string(read_buf);
            cout<<to_string(read_buf)<<endl;
            a++;
		}			
	}
    cout<<"I read : "<<read<<endl;
    cout<<a<<endl;
    
	 	
	 

	return 0;
}

