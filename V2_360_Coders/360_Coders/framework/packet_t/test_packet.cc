#include <gtest/gtest.h>
#include "packet.h"

TEST(packet, HEART_BEAT)
{
    packet tx_packet;
    headers_t tx_headers = {
        .source = 0x00,
        .destination = 0x01,
        .type = PACKET_HEART_BEAT,
        .data_length = 4
    };
    uint8_t tx_data[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    // std::cout << "\nSource: " << tx_headers.source
    //           << "\nDestination: " << tx_headers.destination
    //           << "\nType: " << tx_headers.type
    //           << "\nData length: " << tx_headers.data_length;

    tx_packet.packetiser(&tx_headers,tx_data, 4);
    tx_packet.display_packet();
}

TEST(packet, LED_TURN_ON)
{
    packet tx_packet;
    uint8_t data_len = 1;
    headers_t tx_header = { 0x00,0x01,PACKET_REQUEST, data_len};
    uint8_t tx_data[data_len] = {GPIO_SET_HIGH};

    // std::cout << "Source: " << tx_header.source
    //           << "\nDestination: " << tx_header.destination
    //           << "\nType: " << tx_header.type
    //           << "\nData length: " << tx_header.data_length;

    tx_packet.packetiser(&tx_header, tx_data, 1);
    tx_packet.display_packet();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

