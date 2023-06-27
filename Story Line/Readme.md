## Summary 

Showcasing a development framework wherein platform Independent and Open source applicatiions like MQTT, Arduino IDE for WiFi Module, Segger Embedded Studio for NRF52832 BLE and tools on Linux are connected though network in publishing and subscribing to messages.

A messsaging protocol like MQTT which allows multiple end to end devices, talk to each other through publishing and subscribing to topics. The MQTT username and password from the broker should match the publisher and subscribe in order to get the connection to MQTT broker. ESP8266, a low power WiFi Module connects with the network under use reads, transmit, recieve and controls the operations as requested from broker and between the devices.

* Broker: broker.hivemq.com
* TCP Port: 1883

 On the other hand NRF52832 BLE based Module, is  being connected over the network through MQTT in the same way in controlling, transmitting and receiving datas to and fro between the broker.

  Meantime Linux Machine being set in sending datas in packets with timestamp. At the end all platforms ESP8266 run on Arduino IDE, NRF52832, linux and MQTT being connected together in transmitting and receiving data i.e., For example, Linux machine can send data or request for controlling the operations of ESP/NRF with the same being reflecting in Segger Embedded Studio, serial monitor and MQTT server. And data published from MQTT server can be monitored over the Serial monitor and Segger Studio and vice cersa. 

## Mobile App
![Screenshot_2023-06-28-01-01-13-265_at tripwire mqtt client](https://github.com/cpganiger/360_Coders/assets/60978907/d3300876-ae1d-40c6-bb3d-ee6193d76799)

## Arduino Serial Monitor

![Capture](https://github.com/cpganiger/360_Coders/assets/60978907/786ba669-1c79-4815-b465-2f24581cd326)  

In an overall, different platforms are brought up together irrespective of the platforms they run on, to interconnect all at the same time in responding to any controllable request from any one of the end device and vice versa. 
