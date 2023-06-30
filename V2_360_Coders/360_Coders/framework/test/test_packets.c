#include "app_main.h"


packet_t test_packet = {};

void test_packet1()
{
    memset((uint8_t *)&test_packet, '\0', MAX_PACKET_LENGTH);

        test_packet.headers.type = 0xAA;
        
        test_packet.headers.source = 0x55;
        test_packet.headers.destination = 0x55;

        test_packet.timestamp = time(NULL);
        uint8_t input_data[4] = {0xDE, 0xAD, 0XBE, 0XEF};
        test_packet.headers.data_length = 4;
        packetiser(&test_packet, input_data, 4);
        
        display_packet(&test_packet);

}

void send_test_packets()
{
    test_packet1();
}