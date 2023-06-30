/**
 * @file packetiser.h
 * @author 360_Coders
 * @brief Packet Format forOver the air communication
 * @version 0.1
 * @date 2023-06-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef PACKET_H_
#define PACKET_H_

#include "stdint.h"
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip> // This might be necessary

#include "checksum.h"

#define HEADER_LENGTH       (sizeof(headers_t))
#define CRC_LENGTH          (2)
#define MAX_DATA_LENGTH     (10)
#define MAX_PACKET_LENGTH   (sizeof(packet_t))
#define PACKET_START        ('$')
#define PACKET_END          (';')

#define GPIO_SET_LOW        (0x00)
#define GPIO_BLINK          (0x55)
#define GPIO_TOGGLE         (0xAA)
#define GPIO_SET_HIGH       (0xFF)

#define PACKET_REQUEST      (0x00)
#define PACKET_INFO         (0x01)
#define PACKET_HEART_BEAT   (0x55)
#define PACKET_ALERT        (0xAA)
#define PACKET_RESPONSE     (0xFF)

typedef enum status_t
{
    SUCCESS,
    ERROR,
    NULL_PTR
} status_t;


typedef struct __attribute__((__packed__)) headers_t
{
    uint8_t source;
    uint8_t destination;
    uint8_t type;
    uint8_t data_length;
    
} headers_t;

typedef struct __attribute__((__packed__)) packet_t
{
    uint8_t start;
    headers_t headers;
    uint8_t data[MAX_DATA_LENGTH];
    uint16_t crc;
    time_t timestamp;
    uint8_t end;
} packet_t;

class packet
{
private:
    packet_t m_packet;
public:
    packet();

    status_t packetiser(headers_t* headers, uint8_t *data, uint8_t data_length);

    status_t crc_calculator();

    void display_packet();

    status_t verify_crc();
    
    ~packet();
};
#endif