#include "packetiser.h"

status_t packetiser(packet_t* result_packet, uint8_t* input_data, uint8_t input_data_length)
{

    // printf("Packetiser,Headers %x,  %x, %x, %ld\n", result_packet->headers.id,
    //                                                 result_packet->headers.type, 
    //                                                 result_packet->headers.data_length, 
    //                                                 result_packet->timestamp);
    memcpy((uint8_t*)&result_packet->data[0], input_data, input_data_length);
    result_packet->crc = crc_16((uint8_t*)&result_packet->data[0], MAX_DATA_LENGTH);

}

void display_packet(packet_t* input_packet)
{
    printf("Headers: %X, %ld\n", input_packet->headers.type, input_packet->timestamp);
#if 1
    printf("Data = \n");
    for(int index= 0; index<= MAX_DATA_LENGTH; index++)
    {
        printf("%02X \t, ", input_packet->data[index]);
    }
#endif
    printf("CRC = %0X \n", input_packet->crc);

}

status_t verify_crc(packet_t* input_packet)
{
    uint16_t calculated_crc = crc_16((uint8_t*)&input_packet->data[0], MAX_DATA_LENGTH);

    printf("Calculated CRC = %X, Sent CRC= %X\n", input_packet->crc, calculated_crc);
    if(input_packet->crc == calculated_crc)
    {
        return SUCCESS;
    }
    return ERROR;
}