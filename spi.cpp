/* 
 * File:   spi.cpp
 * Author: Purinda Gunasekara <purinda@gmail.com>
 * 
 * Created on 24 June 2012, 11:00 AM
 * 
 * Inspired from spidev test in linux kernel documentation
 * www.kernel.org/doc/Documentation/spi/spidev_test.c 
 */

#include "spi.h"

#include <fcntl.h>
#include <linux/spi/spidev.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

SPI::SPI() {
	
//	this->device = "/dev/spidev0.0";
	this->device = "";
	this->bits = 8;
//	this->speed = 24000000; // 24Mhz - proly doesnt work
//	this->speed = 16000000; // 16Mhz 
//	this->speed = 8000000; // 8Mhz 
	this->speed = 4000000; // 4Mhz 
	this->mode = 0;

//	this->init();
}

void SPI::setdevice( string devicefile ) 
{
    //printf("setdevice:devicefile==%s\n", devicefile.c_str());
	this->device = devicefile;
}

void SPI::setmode( uint8_t mode )
{
 this->mode = mode;
}

void SPI::setbits( uint8_t bits )
{
 this->bits = bits;
}

void SPI::setspeed( uint32_t speed )
{
 this->speed = speed;
}

void SPI::init()
{
	int ret;
    //printf("init:this->device.c_str()=%s\n", this->device.c_str());
	this->fd = open(this->device.c_str(), O_RDWR);
	if (this->fd < 0)
	{
		perror("can't open device");
		abort();
	}

	/*
	 * spi mode
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_MODE, &this->mode);
	if (ret == -1)
	{
		perror("can't set spi mode");
		abort();		
	}

	ret = ioctl(this->fd, SPI_IOC_RD_MODE, &this->mode);
	if (ret == -1)
	{
		perror("can't set spi mode");
		abort();				
	}
	
	/*
	 * bits per word
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_BITS_PER_WORD, &this->bits);
	if (ret == -1)
	{
		perror("can't set bits per word");
		abort();				
	}

	ret = ioctl(this->fd, SPI_IOC_RD_BITS_PER_WORD, &this->bits);
	if (ret == -1)
	{
		perror("can't set bits per word");
		abort();						
	}
	/*
	 * max speed hz
	 */
	ret = ioctl(this->fd, SPI_IOC_WR_MAX_SPEED_HZ, &this->speed);
	if (ret == -1)
	{
		perror("can't set max speed hz");
		abort();						
	}

	ret = ioctl(this->fd, SPI_IOC_RD_MAX_SPEED_HZ, &this->speed);
	if (ret == -1)
	{
		perror("can't set max speed hz");
		abort();						
	}
}

#if 0
uint8_t SPI::transfer(uint8_t tx_)
{
	int ret;
	// One byte is transfered at once
	uint8_t tx[] = {0};
	tx[0] = tx_;

	uint8_t rx[ARRAY_SIZE(tx)] = {0};
	struct spi_ioc_transfer tr;
	tr.tx_buf = (unsigned long)tx;
	tr.rx_buf = (unsigned long)rx;
	tr.len = ARRAY_SIZE(tx);
	tr.delay_usecs = 0;
//	tr.cs_change = 1;
	tr.speed_hz = this->speed;
	tr.bits_per_word = this->bits;

	ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		perror("can't send spi message");
		abort();		
	}

	return rx[0];
}
#endif

uint8_t SPI::transfer(uint8_t tx)
{
    struct spi_ioc_transfer tr;
    memset(&tr, 0, sizeof(tr));
    tr.tx_buf = (unsigned long) &tx;
    uint8_t rx;
    tr.rx_buf = (unsigned long) &rx;
    tr.len = sizeof(tx);
	tr.speed_hz = this->speed;
    tr.delay_usecs = 0;
	tr.bits_per_word = this->bits;
    tr.cs_change = 0;

    int ret;
    ret = ioctl(this->fd, SPI_IOC_MESSAGE(1), &tr);
	if (ret < 1)
	{
		perror("can't send spi message");
		abort();		
	}

    return rx;
}

SPI::~SPI() {
	close(this->fd);
}

