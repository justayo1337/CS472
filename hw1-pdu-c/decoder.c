#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "packet.h"
#include "nethelper.h"
#include "decoder.h"

//This is where you will be putting your captured network frames for testing.
//Before you do your own, please test with the ones that I provided as samples:
#include "testframes.h"

//You can update this array as you add and remove test cases, you can
//also comment out all but one of them to isolate your testing. This
//allows us to loop over all of the test cases.  Note MAKE_PACKET creates
//a test_packet_t element for each sample, this allows us to get and use
//the packet length, which will be helpful later.
test_packet_t TEST_CASES[] = {
    MAKE_PACKET(raw_packet_icmp_frame198),
    MAKE_PACKET(raw_packet_icmp_frame362),
    MAKE_PACKET(raw_packet_arp_frame78), 
    //extra tests from my side
  //  MAKE_PACKET(arp_test_15328),
 //  MAKE_PACKET(icmp_test_55),
//   MAKE_PACKET(icmp_test_54),
   MAKE_PACKET(icmp_test_56)

};

int main(int argc, char **argv) {
    //This code is here as a refresher on how to figure out how
    //many elements are in a statically defined C array. Note
    //that sizeof(TEST_CASES) is not 3, its the total number of 
    //bytes.  On my machine it comes back with 48, because each
    //element is of type test_packet_t which on my machine is 16 bytes.
    //Thus, with the scaffold I am providing 48/16 = 3, which is
    //the correct size.  
    int num_test_cases = sizeof(TEST_CASES) / sizeof(test_packet_t);
    //printf("sizeof array = %ld\n\n",sizeof(raw_packet_arp_frame78));

    printf("STARTING...");
    for (int i = 0; i < num_test_cases; i++) {
        printf("\n--------------------------------------------------\n");
        printf("TESTING A NEW PACKET\n");
        printf("--------------------------------------------------\n");
        test_packet_t test_case = TEST_CASES[i];

        decode_raw_packet(test_case.raw_packet, test_case.packet_len);
    }

    printf("\nDONE\n");
}

void decode_raw_packet(uint8_t *packet, uint64_t packet_len){
    printf("Packet length = %ld bytes\n", packet_len);

    //Everything we are doing starts with the ethernet PDU at the
    //front.  The below code projects an ethernet_pdu structure 
    //POINTER onto the front of the buffer so we can decode it.
    struct ether_pdu *p = (struct ether_pdu *)packet;
    uint16_t ft = ntohs(p->frame_type);

    printf("Detected raw frame type from ethernet header: 0x%x\n", ft);

    switch(ft) {
        case ARP_PTYPE:
            printf("Packet type = ARP\n");

            //Lets process the ARP packet, convert all of the network byte order
            //fields to host machine byte order
            arp_packet_t *arp = process_arp(packet);

            //Print the arp packet
            print_arp(arp);
            break;
        case IP4_PTYPE:
            printf("Frame type = IPv4, now lets check for ICMP...\n");

            //We know its IP, so lets type the raw packet as an IP packet
            ip_packet_t *ip = (ip_packet_t *)packet;

            //Now check the IP packet to see if its payload is an ICMP packet
            bool isICMP = check_ip_for_icmp(ip);
            if (!isICMP) {
                printf("ERROR: IP Packet is not ICMP\n");
                break;
            }

            //Now lets process the basic icmp packet, convert the network byte order 
            //fields to host byte order
            icmp_packet_t *icmp = process_icmp(ip);

            //Now lets look deeper and see if the icmp packet is actually an
            //ICMP ECHO packet?
            bool is_echo = is_icmp_echo(icmp);
            if (!is_echo) {
                printf("ERROR: We have an ICMP packet, but it is not of type echo\n");
                break;
            }

            //Now lets process the icmp_packet as an icmp_echo_packet, again processing
            //the network byte order fields
            icmp_echo_packet_t *icmp_echo_packet = process_icmp_echo(icmp);

            //The ICMP packet now has its network byte order fields
            //adjusted, lets print it
            print_icmp_echo(icmp_echo_packet);

            break;
    default:
        printf("UNKNOWN Frame type?\n");
    }
}

/********************************************************************************/
/*                       ARP PROTOCOL HANDLERS                                  */
/********************************************************************************/

/*
 *  This function takes a raw_packet that has already been verified to be an ARP
 *  packet.  It typecasts the raw_packet into an arp_packet_t *, and then 
 *  converts all of the network byte order fields into host byte order.
 */
arp_packet_t *process_arp(raw_packet_t raw_packet) {
    
    //Converts raw_packet via
    //type conversion to arp_packet_t and then convert the
    //network byte order fields to host byte order fields using
    //ntohs() and/or ntohl().  Returns a pointer to an arp_packet_t
    
    arp_packet_t  *ep = (arp_packet_t *) raw_packet;
    ep->eth_hdr.frame_type = ntohs(ep->eth_hdr.frame_type );
    ep->arp_hdr.htype = ntohs(ep->arp_hdr.htype );
    ep->arp_hdr.ptype = ntohs(ep->arp_hdr.ptype );
    ep->arp_hdr.op = ntohs(ep->arp_hdr.op );    
    return ep;
}

/*
 *  This function takes an arp packet and just pretty-prints it to stdout using
 *  printf.  It decodes and indicates in the output if the request was an 
 *  ARP_REQUEST or an ARP_RESPONSE
 */
void print_arp(arp_packet_t *arp){
//Takes the arp parameter, of type arp_packet_t and print it out
//nicely.  
 printf("ARP PACKET DETAILS\n");
 printf("     htype: 0x%04x\n",arp->arp_hdr.htype);
 printf("     ptype: 0x%04x\n",arp->arp_hdr.ptype);
 printf("     hlen: %d\n",arp->arp_hdr.hlen);
 printf("     plen: %d\n",arp->arp_hdr.plen);
 if (arp->arp_hdr.op == 1){ 
    printf("     op: %d (ARP REQUEST)\n",arp->arp_hdr.op);
    }else if(arp->arp_hdr.op == 2) {
        printf("     op: %d (ARP RESPONSE)\n",arp->arp_hdr.op);
    }

 printf("     spa: %d.%d.%d.%d\n",arp->arp_hdr.spa[0],arp->arp_hdr.spa[1],arp->arp_hdr.spa[2],arp->arp_hdr.spa[3]);
 printf("     sha: %02x:%02x:%02x:%02x:%02x:%02x\n",arp->arp_hdr.sha[0],arp->arp_hdr.sha[1],arp->arp_hdr.sha[2],arp->arp_hdr.sha[3],arp->arp_hdr.sha[4],arp->arp_hdr.sha[5]);
 printf("     tpa: %d.%d.%d.%d\n",arp->arp_hdr.tpa[0],arp->arp_hdr.tpa[1],arp->arp_hdr.tpa[2],arp->arp_hdr.tpa[3]);
 printf("     tha: %02x:%02x:%02x:%02x:%02x:%02x\n",arp->arp_hdr.tha[0],arp->arp_hdr.tha[1],arp->arp_hdr.tha[2],arp->arp_hdr.tha[3],arp->arp_hdr.tha[4],arp->arp_hdr.tha[5]); 
}

/********************************************************************************/
/*                       ICMP PROTOCOL HANDLERS                                  */
/********************************************************************************/

/*
 *  This function takes an ip packet and then inspects its internal fields to 
 *  see if the IP packet is managing an underlying ICMP packet.  If so, return
 *  true, if not return false.  You need to see if the "protocol" field in the
 *  IP PDU is set to ICMP_PTYPE to do this.
 */
bool check_ip_for_icmp(ip_packet_t *ip){
    //This function inspects the provided IP packet and extracts
    //the protocol.  If the protocol is ICMP_PTYPE then we return true
    //otherwise we return false.
    
    if (ip->ip_hdr.protocol == ICMP_PTYPE){
        return true;
    }
    return false;
}

/*
 *  This function takes an IP packet and converts it into an icmp packet. Note
 *  that it is assumed that we already checked if the IP packet is encapsulating
 *  an ICMP packet.  So we need to type convert it from (ip_packet_t *) to
 *  (icmp_packet *).  There are some that need to be converted from
 *  network to host byte order. 
 */
icmp_packet_t *process_icmp(ip_packet_t *ip){
    //Converts ip_packet via
    //type conversion to icmp_packet_t and then convert the
    //network byte order fields to host byte order fields using
    //ntohs() and/or ntohl().  Returns a pointer to an icmp_packet_t
    //You do not need to allocate any memory. 
    
    icmp_packet_t *icmpnew = (icmp_packet_t *) ip;
    printf("ICMP Type %d\n",icmpnew->icmp_hdr.type);
    icmpnew->ip.ip_hdr.identification = ntohs(icmpnew->ip.ip_hdr.identification );
    icmpnew->ip.ip_hdr.header_checksum = ntohs(icmpnew->ip.ip_hdr.header_checksum );
    icmpnew->ip.eth_hdr.frame_type  = ntohs(icmpnew->ip.eth_hdr.frame_type );
    icmpnew->icmp_hdr.checksum = ntohs(icmpnew->icmp_hdr.checksum) ;
    return icmpnew;
}

/*
 *  This function takes a known ICMP packet, and checks if its of type ECHO. We do
 *  this by checking the "type" field in the icmp_hdr and evaluating if its equal to
 *  ICMP_ECHO_REQUEST or ICMP_ECHO_RESPONSE.  If true, we return true. If not, its
 *  still ICMP but not of type ICMP_ECHO. 
 */
bool is_icmp_echo(icmp_packet_t *icmp) {
    //This function inspects the provided ICMP and checks
    //its type.  If the type is ICMP_ECHO_REQUEST or ICMP_ECHO_RESPONSE 
    //then return true otherwise we return false. The constants are defined in packet.h so take
    //a look there as well.    

    if (icmp->icmp_hdr.type == ICMP_ECHO_REQUEST  || icmp->icmp_hdr.type  ==  ICMP_ECHO_RESPONSE) {
        return true;
    }
    printf("Error: Expected an ECHO REQUEST or an ECHO response\n");
    return false;
}

icmp_echo_packet_t *process_icmp_echo(icmp_packet_t *icmp){
    //Converts icmp_packet_t via
    //type conversion to icmp_echo_packet_t and then converts the
    //network byte order fields to host byte order fields using
    //ntohs() and/or ntohl().  Returns a pointer to an icmp_echo_packet_t

    icmp_echo_packet_t  *ipt = (icmp_echo_packet_t  * ) icmp  ;
    ipt->icmp_echo_hdr.id = ntohs(ipt->icmp_echo_hdr.id);
    ipt->icmp_echo_hdr.sequence = ntohs(ipt->icmp_echo_hdr.sequence);
    ipt->icmp_echo_hdr.timestamp = ntohl(ipt->icmp_echo_hdr.timestamp);
    ipt->icmp_echo_hdr.timestamp_ms = ntohl(ipt->icmp_echo_hdr.timestamp_ms);


    return ipt;
}


void print_icmp_echo(icmp_echo_packet_t *icmp_packet){
//Takes the icmp_packet parameter, of type icmp_echo_packet_t 
//and prints it out nicely.      
    printf("ICMP PACKET DETAILS\n"); 
    uint16_t payload_size = ICMP_Payload_Size(icmp_packet);
    icmp_packet->ip.ip_hdr.total_length = ntohs(icmp_packet->ip.ip_hdr.total_length );
    printf("    type: 0x%04x\n",icmp_packet->icmp_echo_hdr.icmp_hdr.type); 
    printf("    checksum: 0x%04x\n",icmp_packet->icmp_echo_hdr.icmp_hdr.checksum); 

    /* following the similar method wireshark utilizes here
    and showing both values for the ID and Sequence
    e.g
    Identifier (BE): 18521 (0x4859)
    Identifier (LE): 22856 (0x5948)
    Sequence Number (BE): 0 (0x0000)
    Sequence Number (LE): 0 (0x0000)
    */


    printf("    id(BE): %d (0x%04x)\n",icmp_packet->icmp_echo_hdr.id,icmp_packet->icmp_echo_hdr.id);
    printf("    id(LE): %d (0x%04x)\n",htons(icmp_packet->icmp_echo_hdr.id),htons(icmp_packet->icmp_echo_hdr.id));
    printf("    sequence(BE): %d (0x%04x)\n",icmp_packet->icmp_echo_hdr.sequence,icmp_packet->icmp_echo_hdr.sequence);
    printf("    sequence(LE): %d (0x%04x)\n",htons(icmp_packet->icmp_echo_hdr.sequence),htons(icmp_packet->icmp_echo_hdr.sequence));
    printf("    payload: %d bytes\n", payload_size);
    printf("    timestamp: 0x%x%x\n",icmp_packet->icmp_echo_hdr.timestamp,icmp_packet->icmp_echo_hdr.timestamp_ms);
    printf("    timestamp: 0x%x%x\n",htonl(icmp_packet->icmp_echo_hdr.timestamp),htonl(icmp_packet->icmp_echo_hdr.timestamp_ms));

    /* doing this because timestamp isn't native to ICMP Echo see:
     https://stackoverflow.com/questions/70175164/icmp-timestamps-added-to-ping-echo-requests-in-linux-how-are-they-represented-t/71461124#71461124
     https://gitlab.com/wireshark/wireshark/-/issues/19283
     the order in which the bytes are sent over the network is 
     dependent on the implementation of ping/ the utility in use to send the icmp packets, so the bytes are not always sent in network byte order/big endian
     The value differs based on which OS is in use
*/
    printf("    ECHO Timestamp 1(Probable): %s",  get_ts_formatted(icmp_packet->icmp_echo_hdr.timestamp,icmp_packet->icmp_echo_hdr.timestamp_ms));
    printf("    ECHO Timestamp 2(Probable): %s\n",  get_ts_formatted(htonl(icmp_packet->icmp_echo_hdr.timestamp),htonl(icmp_packet->icmp_echo_hdr.timestamp_ms)));

    //Now print the payload data
    print_icmp_payload(icmp_packet->icmp_payload, payload_size);
}

void print_icmp_payload(uint8_t *payload, uint16_t payload_size) {
//this function takes the payload which is just basically an 
//array of bytes and prints it out nicely.
    printf("    PAYLOAD\n    OFFSET    | CONTENTS\n");
    printf("    -------------------------------------------------------------\n");
    printf("    0x%04x    |",0);
     for (int i = 0; i < payload_size; ++i ){
        printf("  0x%02x",payload[i]);
        if ((i+1) % 8 == 0 && i!= payload_size - 1){
            printf("\n    0x%04x    |",i+1);
        }
     }
}
