#include "serial.hpp"
#include <unistd.h>
#include <iostream>
#include <string>
#include "crcModbus.hpp"

unsigned short crc;

int main(int argc, char **argv){
	using namespace std;
	
	Serial driver("/dev/ttyUSB2", 115200);
	crcModbus crc_obj;

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
    buf[6] = 0x00;      //0xE2
	buf[7] = 0x00;      //0x06

    crc = crc_obj.crc_modbus(buf, 6);
    memcpy(&buf[6], (char*)&crc, 2);
    // cout << (unsigned short)buf[6] << endl;
    // cout << (unsigned short)buf[7] << endl;
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
	buf[6] = 0x00;      //D2
	buf[7] = 0x00;      //03
    crc = crc_obj.crc_modbus(buf, 6);
    memcpy(&buf[6], (char*)&crc, 2);
    // cout << (unsigned short)buf[6]<< endl;
    // cout << (unsigned short)buf[7] << endl;
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
	buf[6] = 0x00;      //A2
	buf[7] = 0x00;      //4A
    crc = crc_obj.crc_modbus(buf, 6);
    memcpy(&buf[6], (char*)&crc, 2);
    // cout << (unsigned short)buf[6]<< endl;
    // cout << (unsigned short)buf[7] << endl;
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
	buf[6] = 0x00;      //0E
	buf[7] = 0x00;      //02
    crc = crc_obj.crc_modbus(buf, 6);
    memcpy(&buf[6], (char*)&crc, 2);
    // cout << (unsigned short)buf[6]<< endl;
    // cout << (unsigned short)buf[7] << endl;
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
