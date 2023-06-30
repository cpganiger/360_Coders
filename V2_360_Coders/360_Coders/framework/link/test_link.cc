#include <gtest/gtest.h>
#include "packet.h"

TEST(link, send_data)
{
    create_link();
    send_data(TEST_TOPIC_NAME, tx_data, data_length);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

