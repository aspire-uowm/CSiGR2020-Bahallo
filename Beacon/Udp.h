#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#ifdef __cplusplus
  extern "C"{
#endif

    char* Udpssid = "Node"; // wifi ssid
    char* Udppassword = '\0'; //wifi password

    char* udpAddress = "192.168.43.155"; //destination IP
    unsigned int udpPort=1234; //Server port

    byte mac[] = { 0xFE, 0xBB, 0x34, 0xE5, 0x29, 0xFC };

    WiFiUDP udp;

    char pktbuf[10];//buffer to store udp data
    char rx_val;

    void UdpInit();
    void UdpRun();
#ifdef __cplusplus
  }
#endif
