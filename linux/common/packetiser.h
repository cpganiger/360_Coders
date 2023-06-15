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

#define HEADER_LENGTH       (sizeof(headers_t))
#define CRC_LENGTH          (2)
//#define MAX_DATA_LENGTH     (10 - HEADER_LENGTH - CRC_LENGTH)
#define MAX_DATA_LENGTH     (10)
#define MAX_PACKET_LENGTH   (sizeof(packet_t))

#include "stdint.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checksum.h"

typedef enum  __attribute__((__packed__)) status_t
{
    SUCCESS,
    ERROR,
    NULL_PTR
}status_t;

typedef struct __attribute__((__packed__)) headers_t
{
    uint8_t     source;
    uint8_t     destination;
    uint8_t     type;
    uint8_t     data_length;
}headers_t;

typedef struct __attribute__((__packed__)) packet_t
{
    headers_t   headers;
    uint8_t     data[MAX_DATA_LENGTH];
    uint16_t    crc;
    time_t      timestamp;
}packet_t;


status_t packetiser(packet_t* result_packet, uint8_t* data, uint8_t data_length);

status_t crc_calculator(uint8_t* data, uint8_t data_length);

void display_packet(packet_t* input_packet);

status_t verify_crc(packet_t* input_packet);

#endif