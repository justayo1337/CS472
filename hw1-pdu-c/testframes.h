/*
 *  testframes.h
 *
 *  PUT SAMPLE FRAMES CAPTURED FROM WIRESHARK HERE.  Note below the arrays that we
 *  will be processing i have included a few samples and also capture the wireshark
 *  decoded values and the wireshark binary capture.  Right-Click on the wireshark
 *  decoded frame and hit Copy-> then all visible items
 */

#include <stdint.h>

typedef struct test_packet{
    uint8_t     *raw_packet;
    uint32_t    packet_len;
}test_packet_t;

#define MAKE_PACKET(p) {p, sizeof(p)}

uint8_t raw_packet_arp_frame78[] = {
  0xc8, 0x89, 0xf3, 0xea, 0x93, 0x14, 0xa0, 0x36,
  0xbc, 0x62, 0xed, 0x50, 0x08, 0x06, 0x00, 0x01,
  0x08, 0x00, 0x06, 0x04, 0x00, 0x01, 0xa0, 0x36,
  0xbc, 0x62, 0xed, 0x50, 0xc0, 0xa8, 0x32, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa8,
  0x32, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
/*
Frame 78: 60 bytes on wire (480 bits), 60 bytes captured (480 bits) on interface en0, id 0
    Section number: 1
    Interface id: 0 (en0)
    Encapsulation type: Ethernet (1)
    Arrival Time: Sep 24, 2023 09:57:27.654257000 EDT
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1695563847.654257000 seconds
    [Time delta from previous captured frame: 0.474723000 seconds]
    [Time delta from previous displayed frame: 0.000000000 seconds]
    [Time since reference or first frame: 3.263589000 seconds]
    Frame Number: 78
    Frame Length: 60 bytes (480 bits)
    Capture Length: 60 bytes (480 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ethertype:arp]
    [Coloring Rule Name: ARP]
    [Coloring Rule String: arp]
Ethernet II, Src: ASUSTekC_62:ed:50 (a0:36:bc:62:ed:50), Dst: Apple_ea:93:14 (c8:89:f3:ea:93:14)
    Destination: Apple_ea:93:14 (c8:89:f3:ea:93:14)
    Source: ASUSTekC_62:ed:50 (a0:36:bc:62:ed:50)
    Type: ARP (0x0806)
    Padding: 000000000000000000000000000000000000
Address Resolution Protocol (request)
    Hardware type: Ethernet (1)
    Protocol type: IPv4 (0x0800)
    Hardware size: 6
    Protocol size: 4
    Opcode: request (1)
    Sender MAC address: ASUSTekC_62:ed:50 (a0:36:bc:62:ed:50)
    Sender IP address: 192.168.50.1
    Target MAC address: 00:00:00_00:00:00 (00:00:00:00:00:00)
    Target IP address: 192.168.50.99

0000   c8 89 f3 ea 93 14 a0 36 bc 62 ed 50 08 06 00 01
0010   08 00 06 04 00 01 a0 36 bc 62 ed 50 c0 a8 32 01
0020   00 00 00 00 00 00 c0 a8 32 63 00 00 00 00 00 00
0030   00 00 00 00 00 00 00 00 00 00 00 00


*/


//This is an ICMP ping request message
uint8_t raw_packet_icmp_frame362[] = {
  0xa0, 0x36, 0xbc, 0x62, 0xed, 0x50, 0xc8, 0x89,
  0xf3, 0xea, 0x93, 0x14, 0x08, 0x00, 0x45, 0x00,
  0x00, 0x54, 0x2a, 0xec, 0x00, 0x00, 0x40, 0x01,
  0x89, 0x31, 0xc0, 0xa8, 0x32, 0x63, 0x90, 0x76,
  0x43, 0x0a, 0x08, 0x00, 0x7b, 0xda, 0x48, 0x59,
  0x00, 0x00, 0x65, 0x0e, 0x01, 0xee, 0x00, 0x00,
  0xe1, 0xcc, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d,
  0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
  0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
  0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
  0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
  0x36, 0x37
};

/*
WIRESHARK DECODED:

Frame 362: 98 bytes on wire (784 bits), 98 bytes captured (784 bits) on interface en0, id 0
Ethernet II, Src: Apple_ea:93:14 (c8:89:f3:ea:93:14), Dst: ASUSTekC_62:ed:50 (a0:36:bc:62:ed:50)
Internet Protocol Version 4, Src: 192.168.50.99, Dst: 144.118.67.10
    0100 .... = Version: 4
    .... 0101 = Header Length: 20 bytes (5)
    Differentiated Services Field: 0x00 (DSCP: CS0, ECN: Not-ECT)
    Total Length: 84
    Identification: 0x2aec (10988)
    000. .... = Flags: 0x0
    ...0 0000 0000 0000 = Fragment Offset: 0
    Time to Live: 64
    Protocol: ICMP (1)
    Header Checksum: 0x8931 [validation disabled]
    [Header checksum status: Unverified]
    Source Address: 192.168.50.99
    Destination Address: 144.118.67.10
Internet Control Message Protocol
    Type: 8 (Echo (ping) request)
    Code: 0
    Checksum: 0x7bda [correct]
    [Checksum Status: Good]
    Identifier (BE): 18521 (0x4859)
    Identifier (LE): 22856 (0x5948)
    Sequence Number (BE): 0 (0x0000)
    Sequence Number (LE): 0 (0x0000)
    [Response frame: 363]
    Timestamp from icmp data: Sep 22, 2023 17:06:54.057804000 EDT
    [Timestamp from icmp data (relative): 0.034783000 seconds]
    Data (48 bytes)

    BINARY WINDOW:

    0000   a0 36 bc 62 ed 50 c8 89 f3 ea 93 14 08 00 45 00
    0010   00 54 2a ec 00 00 40 01 89 31 c0 a8 32 63 90 76
    0020   43 0a 08 00 7b da 48 59 00 00 65 0e 01 ee 00 00
    0030   e1 cc 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15
    0040   16 17 18 19 1a 1b 1c 1d 1e 1f 20 21 22 23 24 25
    0050   26 27 28 29 2a 2b 2c 2d 2e 2f 30 31 32 33 34 35
    0060   36 37
*/

uint8_t raw_packet_icmp_frame198[] = {
  0xc8, 0x89, 0xf3, 0xea, 0x93, 0x14, 0xa0, 0x36,
  0xbc, 0x62, 0xed, 0x50, 0x08, 0x00, 0x45, 0xc0,
  0x00, 0x50, 0xa8, 0xfa, 0x00, 0x00, 0x40, 0x01,
  0xeb, 0x3d, 0xc0, 0xa8, 0x32, 0x01, 0xc0, 0xa8,
  0x32, 0x63, 0x0b, 0x00, 0xbb, 0xbd, 0x00, 0x00,
  0x00, 0x00, 0x45, 0x00, 0x00, 0x34, 0xea, 0x3b,
  0x00, 0x00, 0x01, 0x11, 0x08, 0xf2, 0xc0, 0xa8,
  0x32, 0x63, 0x90, 0x76, 0x43, 0x0a, 0xea, 0x3a,
  0x82, 0x9b, 0x00, 0x20, 0xcc, 0x4b, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/*
Frame 198: 94 bytes on wire (752 bits), 94 bytes captured (752 bits) on interface en0, id 0
Ethernet II, Src: ASUSTekC_62:ed:50 (a0:36:bc:62:ed:50), Dst: Apple_ea:93:14 (c8:89:f3:ea:93:14)
Internet Protocol Version 4, Src: 192.168.50.1, Dst: 192.168.50.99
    0100 .... = Version: 4
    .... 0101 = Header Length: 20 bytes (5)
    Differentiated Services Field: 0xc0 (DSCP: CS6, ECN: Not-ECT)
    Total Length: 80
    Identification: 0xa8fa (43258)
    000. .... = Flags: 0x0
    ...0 0000 0000 0000 = Fragment Offset: 0
    Time to Live: 64
    Protocol: ICMP (1)
    Header Checksum: 0xeb3d [validation disabled]
    [Header checksum status: Unverified]
    Source Address: 192.168.50.1
    Destination Address: 192.168.50.99
Internet Control Message Protocol
    Type: 11 (Time-to-live exceeded)
    Code: 0 (Time to live exceeded in transit)
    Checksum: 0xbbbd [correct]
    [Checksum Status: Good]
    Unused: 00000000
    Internet Protocol Version 4, Src: 192.168.50.99, Dst: 144.118.67.10
        0100 .... = Version: 4
        .... 0101 = Header Length: 20 bytes (5)
        Differentiated Services Field: 0x00 (DSCP: CS0, ECN: Not-ECT)
        Total Length: 52
        Identification: 0xea3b (59963)
        000. .... = Flags: 0x0
        ...0 0000 0000 0000 = Fragment Offset: 0
        Time to Live: 1
        Protocol: UDP (17)
        Header Checksum: 0x08f2 [validation disabled]
        [Header checksum status: Unverified]
        Source Address: 192.168.50.99
        Destination Address: 144.118.67.10
    User Datagram Protocol, Src Port: 59962, Dst Port: 33435
Data (24 bytes)


0000   c8 89 f3 ea 93 14 a0 36 bc 62 ed 50 08 00 45 c0
0010   00 50 a8 fa 00 00 40 01 eb 3d c0 a8 32 01 c0 a8
0020   32 63 0b 00 bb bd 00 00 00 00 45 00 00 34 ea 3b
0030   00 00 01 11 08 f2 c0 a8 32 63 90 76 43 0a ea 3a
0040   82 9b 00 20 cc 4b 00 00 00 00 00 00 00 00 00 00
0050   00 00 00 00 00 00 00 00 00 00 00 00 00 00

*/


//another arp packet
uint8_t arp_test_15328[] = {
0xb2, 0xa0, 0x24, 0x17, 0x8e, 0xbb, 0x9c, 0x6b, 
0x00, 0x23, 0xbd, 0xb5, 0x08, 0x06, 0x00, 0x01, 
0x08, 0x00, 0x06, 0x04, 0x00, 0x02, 0x9c, 0x6b, 
0x00, 0x23, 0xbd, 0xb5, 0x0a, 0x00, 0x00, 0xf4, 
0xb2, 0xa0, 0x24, 0x17, 0x8e, 0xbb, 0x0a, 0x00, 
0x00, 0x3d                                      
};

/*Frame 15328: 42 bytes on wire (336 bits), 42 bytes captured (336 bits) on interface \Device\NPF_{EC6562A1-E9BD-4845-BFB6-53A7A886957C}, id 0
    Section number: 1
    Interface id: 0 (\Device\NPF_{EC6562A1-E9BD-4845-BFB6-53A7A886957C})
    Encapsulation type: Ethernet (1)
    Arrival Time: Apr 13, 2024 09:39:46.434745000 Eastern Daylight Time
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1713015586.434745000 seconds
    [Time delta from previous captured frame: 0.000014000 seconds]
    [Time delta from previous displayed frame: 0.000014000 seconds]
    [Time since reference or first frame: 59.992766000 seconds]
    Frame Number: 15328
    Frame Length: 42 bytes (336 bits)
    Capture Length: 42 bytes (336 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ethertype:arp]
    [Coloring Rule Name: ARP]
    [Coloring Rule String: arp]
Ethernet II, Src: 9c:6b:00:23:bd:b5 (9c:6b:00:23:bd:b5), Dst: b2:a0:24:17:8e:bb (b2:a0:24:17:8e:bb)
    Destination: b2:a0:24:17:8e:bb (b2:a0:24:17:8e:bb)
    Source: 9c:6b:00:23:bd:b5 (9c:6b:00:23:bd:b5)
    Type: ARP (0x0806)
Address Resolution Protocol (reply)
    Hardware type: Ethernet (1)
    Protocol type: IPv4 (0x0800)
    Hardware size: 6
    Protocol size: 4
    Opcode: reply (2)
    Sender MAC address: 9c:6b:00:23:bd:b5 (9c:6b:00:23:bd:b5)
    Sender IP address: 10.0.0.244
    Target MAC address: b2:a0:24:17:8e:bb (b2:a0:24:17:8e:bb)
    Target IP address: 10.0.0.61*/


//icmp test packets
uint8_t  icmp_test_55[] ={
  0xb4, 0x8c, 0x9d, 0xa0, 0xee, 0xf7, 0x00, 0x1d,
  0x71, 0x72, 0x64, 0xc0, 0x08, 0x00, 0x45, 0x00,
  0x00, 0x54, 0x67, 0xfd, 0x40, 0x00, 0xec, 0x01,
  0xb9, 0xbc, 0x34, 0x5e, 0xec, 0xf8, 0x0a, 0xfa,
  0x40, 0x9e, 0x00, 0x00, 0x93, 0x0d, 0x32, 0x09,
  0x00, 0x5a, 0xa2, 0x1e, 0x20, 0x66, 0x00, 0x00,
  0x00, 0x00, 0xb3, 0x37, 0x06, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
  0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
  0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
  0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
  0x36, 0x37                               
};

/*
Frame 55: 98 bytes on wire (784 bits), 98 bytes captured (784 bits) on interface wlp5s0, id 0
    Section number: 1
    Interface id: 0 (wlp5s0)
        Interface name: wlp5s0
    Encapsulation type: Ethernet (1)
    Arrival Time: Apr 17, 2024 15:10:26.415633711 EDT
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1713381026.415633711 seconds
    [Time delta from previous captured frame: 0.008092896 seconds]
    [Time delta from previous displayed frame: 0.008092896 seconds]
    [Time since reference or first frame: 3.591004211 seconds]
    Frame Number: 55
    Frame Length: 98 bytes (784 bits)
    Capture Length: 98 bytes (784 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ethertype:ip:icmp:data]
    [Coloring Rule Name: ICMP]
    [Coloring Rule String: icmp || icmpv6]
Ethernet II, Src: Cisco_72:64:c0 (00:1d:71:72:64:c0), Dst: AzureWav_a0:ee:f7 (b4:8c:9d:a0:ee:f7)
    Destination: AzureWav_a0:ee:f7 (b4:8c:9d:a0:ee:f7)
    Source: Cisco_72:64:c0 (00:1d:71:72:64:c0)
    Type: IPv4 (0x0800)
Internet Protocol Version 4, Src: 52.94.236.248, Dst: 10.250.64.158
Internet Control Message Protocol
    Type: 0 (Echo (ping) reply)
    Code: 0
    Checksum: 0x930d [correct]
    [Checksum Status: Good]
    Identifier (BE): 12809 (0x3209)
    Identifier (LE): 2354 (0x0932)
    Sequence Number (BE): 90 (0x005a)
    Sequence Number (LE): 23040 (0x5a00)
    [Request frame: 54]
    [Response time: 8.093 ms]
    Timestamp from icmp data: Apr 17, 2024 15:10:26.000000000 EDT
    [Timestamp from icmp data (relative): 0.415633711 seconds]
    Data (48 bytes)

*/

/* Frame (74 bytes) */
uint8_t  icmp_test_54[] = {
  0x00, 0x1d, 0x71, 0x72, 0x64, 0xc0, 0xb4, 0x8c,
  0x9d, 0xa0, 0xee, 0xf7, 0x08, 0x00, 0x45, 0x00,
  0x00, 0x54, 0x67, 0xfd, 0x40, 0x00, 0x40, 0x01,
  0x65, 0xbd, 0x0a, 0xfa, 0x40, 0x9e, 0x34, 0x5e,
  0xec, 0xf8, 0x08, 0x00, 0x8b, 0x0d, 0x32, 0x09,
  0x00, 0x5a, 0xa2, 0x1e, 0x20, 0x66, 0x00, 0x00,
  0x00, 0x00, 0xb3, 0x37, 0x06, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
  0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
  0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
  0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
  0x36, 0x37
};


/*
    Frame 54: 98 bytes on wire (784 bits), 98 bytes captured (784 bits) on interface wlp5s0, id 0
    Section number: 1
    Interface id: 0 (wlp5s0)
        Interface name: wlp5s0
    Encapsulation type: Ethernet (1)
    Arrival Time: Apr 17, 2024 15:10:26.407540815 EDT
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1713381026.407540815 seconds
    [Time delta from previous captured frame: 0.074632038 seconds]
    [Time delta from previous displayed frame: 0.979708699 seconds]
    [Time since reference or first frame: 3.582911315 seconds]
    Frame Number: 54
    Frame Length: 98 bytes (784 bits)
    Capture Length: 98 bytes (784 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ethertype:ip:icmp:data]
    [Coloring Rule Name: ICMP]
    [Coloring Rule String: icmp || icmpv6]
Ethernet II, Src: AzureWav_a0:ee:f7 (b4:8c:9d:a0:ee:f7), Dst: Cisco_72:64:c0 (00:1d:71:72:64:c0)
    Destination: Cisco_72:64:c0 (00:1d:71:72:64:c0)
    Source: AzureWav_a0:ee:f7 (b4:8c:9d:a0:ee:f7)
    Type: IPv4 (0x0800)
Internet Protocol Version 4, Src: 10.250.64.158, Dst: 52.94.236.248
Internet Control Message Protocol
    Type: 8 (Echo (ping) request)
    Code: 0
    Checksum: 0x8b0d [correct]
    [Checksum Status: Good]
    Identifier (BE): 12809 (0x3209)
    Identifier (LE): 2354 (0x0932)
    Sequence Number (BE): 90 (0x005a)
    Sequence Number (LE): 23040 (0x5a00)
    [Response frame: 55]
    Timestamp from icmp data: Apr 17, 2024 15:10:26.000000000 EDT
    [Timestamp from icmp data (relative): 0.407540815 seconds]
    Data (48 bytes)

*/

/* Frame (74 bytes) */
uint8_t  icmp_test_56[] = {
  0xd4, 0x3f, 0xcb, 0xed, 0xd9, 0xb9, 0xb4, 0x8c,
  0x9d, 0xa0, 0xee, 0xf7, 0x08, 0x00, 0x45, 0x00,
  0x00, 0x54, 0x01, 0xeb, 0x40, 0x00, 0x40, 0x01,
  0x1d, 0xbf, 0x0a, 0x00, 0x00, 0xf0, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x00, 0xce, 0x69, 0x45, 0x60,
  0x00, 0x45, 0xc1, 0x35, 0x20, 0x66, 0x00, 0x00,
  0x00, 0x00, 0x3e, 0x82, 0x05, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
  0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d,
  0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d,
  0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35,
  0x36, 0x37
};


/*
 Frame 56: 98 bytes on wire (784 bits), 98 bytes captured (784 bits) on interface wlp5s0, id 0
    Section number: 1
    Interface id: 0 (wlp5s0)
        Interface name: wlp5s0
    Encapsulation type: Ethernet (1)
    Arrival Time: Apr 17, 2024 16:49:05.361053219 EDT
    [Time shift for this packet: 0.000000000 seconds]
    Epoch Time: 1713386945.361053219 seconds
    [Time delta from previous captured frame: 0.153006466 seconds]
    [Time delta from previous displayed frame: 0.978195944 seconds]
    [Time since reference or first frame: 2.270338561 seconds]
    Frame Number: 56
    Frame Length: 98 bytes (784 bits)
    Capture Length: 98 bytes (784 bits)
    [Frame is marked: False]
    [Frame is ignored: False]
    [Protocols in frame: eth:ethertype:ip:icmp:data]
    [Coloring Rule Name: ICMP]
    [Coloring Rule String: icmp || icmpv6]
Ethernet II, Src: AzureWav_a0:ee:f7 (b4:8c:9d:a0:ee:f7), Dst: ARRISGro_ed:d9:b9 (d4:3f:cb:ed:d9:b9)
    Destination: ARRISGro_ed:d9:b9 (d4:3f:cb:ed:d9:b9)
        Address: ARRISGro_ed:d9:b9 (d4:3f:cb:ed:d9:b9)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Source: AzureWav_a0:ee:f7 (b4:8c:9d:a0:ee:f7)
        Address: AzureWav_a0:ee:f7 (b4:8c:9d:a0:ee:f7)
        .... ..0. .... .... .... .... = LG bit: Globally unique address (factory default)
        .... ...0 .... .... .... .... = IG bit: Individual address (unicast)
    Type: IPv4 (0x0800)
Internet Protocol Version 4, Src: 10.0.0.240, Dst: 8.8.8.8
    0100 .... = Version: 4
    .... 0101 = Header Length: 20 bytes (5)
    Differentiated Services Field: 0x00 (DSCP: CS0, ECN: Not-ECT)
        0000 00.. = Differentiated Services Codepoint: Default (0)
        .... ..00 = Explicit Congestion Notification: Not ECN-Capable Transport (0)
    Total Length: 84
    Identification: 0x01eb (491)
    010. .... = Flags: 0x2, Don't fragment
        0... .... = Reserved bit: Not set
        .1.. .... = Don't fragment: Set
        ..0. .... = More fragments: Not set
    ...0 0000 0000 0000 = Fragment Offset: 0
    Time to Live: 64
    Protocol: ICMP (1)
    Header Checksum: 0x1dbf [validation disabled]
    [Header checksum status: Unverified]
    Source Address: 10.0.0.240
    Destination Address: 8.8.8.8
Internet Control Message Protocol
    Type: 8 (Echo (ping) request)
    Code: 0
    Checksum: 0xce69 [correct]
    [Checksum Status: Good]
    Identifier (BE): 17760 (0x4560)
    Identifier (LE): 24645 (0x6045)
    Sequence Number (BE): 69 (0x0045)
    Sequence Number (LE): 17664 (0x4500)
    [Response frame: 57]
    Timestamp from icmp data: Apr 17, 2024 16:49:05.000000000 EDT
    [Timestamp from icmp data (relative): 0.361053219 seconds]
    Data (48 bytes)
        Data: 3e82050000000000101112131415161718191a1b1c1d1e1f202122232425262728292a2b…
        [Length: 48]

*/
