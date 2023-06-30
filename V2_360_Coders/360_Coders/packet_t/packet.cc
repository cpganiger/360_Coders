#include "packet.h"

packet::packet()
{
    std::cout << "\n";
}


packet::~packet()
{
    std::cout << "\n";
}

status_t packet::packetiser(headers_t* headers, uint8_t *data, uint8_t data_length)
{
    std::cout << "\nSource: " << headers->source
              << "\nDestination: " << headers->destination
              << "\nType: " << headers->type
              << "\nData length: " << headers->data_length
              << "\nData: ";

    m_packet.start = '$';
    memcpy((uint8_t*)&m_packet.headers, (uint8_t*)&headers, HEADER_LENGTH);

    memcpy((uint8_t*)&m_packet.data[0], data, data_length);

    m_packet.crc = crc_16((uint8_t*)&m_packet.data[0], MAX_DATA_LENGTH);

    m_packet.timestamp= time(NULL);
    m_packet.end = ';';

    return SUCCESS;
}

void packet::display_packet()
{
    std::cout << "\nStart: " << m_packet.start
              << "\nSource: " << m_packet.headers.source
              << "\nDestination: " << m_packet.headers.destination
              << "\nType: " << m_packet.headers.type
              << "\nData length: " << m_packet.headers.data_length
              << "\nData: ";

    for(int index= 0; index<= MAX_DATA_LENGTH; index++)
    {
        std::cout  << m_packet.data[index];
    }
    std::cout << "\ncrc = "<<m_packet.crc
              << "\nTimestamp: "<<m_packet.timestamp
              << "\nEnd: "<<m_packet.end
              <<"\n";
}

status_t packet::verify_crc()
{
    uint16_t calculated_crc = crc_16((uint8_t*)&m_packet.data[0], MAX_DATA_LENGTH);

    std::cout << "Calculated CRC:" << m_packet.crc
              << "Recieved   CRC: "<< calculated_crc 
              <<"\n";

    if(m_packet.crc == calculated_crc)
    {
        std::cout << "Packet intact\n";
        return SUCCESS;
    }
    std::cout << "Packet Corrupted\n";
    return ERROR;
}