## Programming Assignment 1

#### Directions
The purpose of this assignment is to dust off some of your C skills and
get exposure to the types of things you do in network programming working
with raw buffers and manipulating them using PDUs and Packet structures.
You will also get the chance to play with wireshark to create your own 
test cases, but before you do this, you should implement this code with
the samples that I already provided.

I have provided a makefile for you.  `make build` compiles your program and
creates an executable called `decoder`.  Running `make run` will run your
program.

See the homework supplement I provided on blackboard for some more information
and background.

#### What to Hand In
This assignment only requires you to modify code in `decoder.c`.  All of the
network structures are in `packet.h` make sure you understand them.  To make
things easier for you to convert buffered data to formatted strings for things
like IP and MAC addresses, I have provided helpers in `nethelper.c`.  Again, 
please only modify `decoder.c`.

When you are ready to submit, you can create a zip file of your entire
directory and submit on blackboard.  AKA in other words everything required so
that the grader only has to execute `make build && make run`. to compile, link, 
and execute your program.  Alternatively, you can create a git repo on GitHub
with a public repository and provide a link to this repo as your blackboard
submission.  If you dont want this code public, but want to use a git environment
you can also push to a private Drexel CCI GitLab repo and provide that link
as your blackboard submission.

#### Warnings, dont let this be you...
This is a **REALY EASY** assignment if you are comfortable with C.  My solution is 
about 40 lines of code for **ALL** of the things you need to accomplish. If you need
to refresh your C knowledge, PLEASE DONT WAIT UNTIL THE LAST MINUTE. This assignment
is setting the foundation for typical network programming tasks which involve
creating and manipulating structures, working with buffers, pointers, etc.  

If you find yourself struggling, you are not stupid.  You just need a refresher on systems programming in C.  I will be doing some office hours to help refresh your memory on C programming during the first two weeks - no need to attend if you are comfortable with these things, but please make it a priority to attend if you dont
understand what is going on. 

I also put a **TON** of documentation in the code to help you.  To make things
easier on the grader, please thin out the documentation in your submission, removing
mine and putting in documentation relevant to your specific implementation.

---

# Results from my solution with the packets in the `testframes.h` file and the pcaps

```bash
ayo@raspberrypi  ~/classes/cs472/hw1-pdu-c   main ±  make run  
./decoder
STARTING...
--------------------------------------------------
TESTING A NEW PACKET
--------------------------------------------------
Packet length = 94 bytes
Detected raw frame type from ethernet header: 0x800
Frame type = IPv4, now lets check for ICMP...
ICMP Type 11
Error: Expected an ECHO REQUEST or an ECHO response
ERROR: We have an ICMP packet, but it is not of type echo

--------------------------------------------------
TESTING A NEW PACKET
--------------------------------------------------
Packet length = 98 bytes
Detected raw frame type from ethernet header: 0x800
Frame type = IPv4, now lets check for ICMP...
ICMP Type 8
ICMP PACKET DETAILS
    type: 0x0008
    checksum: 0x7bda
    id(BE): 0x4859
    id(LE): 0x5948
    sequence(BE): 0x0000
    sequence(LE): 0x0000
    timestamp: 0x650e01eee1cc
    payload: 48 bytes
    ECHO Timestamp 1(Probable): TS = 2023-09-22 22:06:54.57804
    ECHO Timestamp 2(Probable): TS = 2096-07-13 20:37:09.3437297664

    PAYLOAD
    OFFSET    | CONTENTS
    -------------------------------------------------------------
    0x0000    |  0x08  0x09  0x0a  0x0b  0x0c  0x0d  0x0e  0x0f
    0x0008    |  0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
    0x0010    |  0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f
    0x0018    |  0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27
    0x0020    |  0x28  0x29  0x2a  0x2b  0x2c  0x2d  0x2e  0x2f
    0x0028    |  0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37
--------------------------------------------------
TESTING A NEW PACKET
--------------------------------------------------
Packet length = 60 bytes
Detected raw frame type from ethernet header: 0x806
Packet type = ARP
ARP PACKET DETAILS
     htype: 0x0001
     ptype: 0x0800
     hlen: 6
     plen: 4
     op: 1 (ARP REQUEST)
     spa: 192.168.50.1
     sha: a0:36:bc:62:ed:50
     tpa: 192.168.50.99
     tha: 00:00:00:00:00:00

--------------------------------------------------
TESTING A NEW PACKET
--------------------------------------------------
Packet length = 42 bytes
Detected raw frame type from ethernet header: 0x806
Packet type = ARP
ARP PACKET DETAILS
     htype: 0x0001
     ptype: 0x0800
     hlen: 6
     plen: 4
     op: 2 (ARP RESPONSE)
     spa: 10.0.0.244
     sha: 9c:6b:00:23:bd:b5
     tpa: 10.0.0.61
     tha: b2:a0:24:17:8e:bb

--------------------------------------------------
TESTING A NEW PACKET
--------------------------------------------------
Packet length = 98 bytes
Detected raw frame type from ethernet header: 0x800
Frame type = IPv4, now lets check for ICMP...
ICMP Type 8
ICMP PACKET DETAILS
    type: 0x0008
    checksum: 0x03bb
    id(BE): 0x4c26
    id(LE): 0x264c
    sequence(BE): 0x0010
    sequence(LE): 0x0010
    timestamp: 0x74020660
    payload: 48 bytes
    ECHO Timestamp 1(Probable): TS = 1973-11-08 21:45:10.0
    ECHO Timestamp 2(Probable): TS = 2024-04-17 22:32:55.0

    PAYLOAD
    OFFSET    | CONTENTS
    -------------------------------------------------------------
    0x0000    |  0xbb  0x95  0x06  0x00  0x00  0x00  0x00  0x00
    0x0008    |  0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
    0x0010    |  0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f
    0x0018    |  0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27
    0x0020    |  0x28  0x29  0x2a  0x2b  0x2c  0x2d  0x2e  0x2f
    0x0028    |  0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37
--------------------------------------------------
TESTING A NEW PACKET
--------------------------------------------------
Packet length = 98 bytes
Detected raw frame type from ethernet header: 0x800
Frame type = IPv4, now lets check for ICMP...
ICMP Type 8
ICMP PACKET DETAILS
    type: 0x0008
    checksum: 0xfd4d
    id(BE): 0x4b35
    id(LE): 0x354b
    sequence(BE): 0x0018
    sequence(LE): 0x0018
    timestamp: 0xe43e20660
    payload: 48 bytes
    ECHO Timestamp 1(Probable): TS = 2091-05-06 08:59:34.0
    ECHO Timestamp 2(Probable): TS = 2024-04-17 22:28:04.0

    PAYLOAD
    OFFSET    | CONTENTS
    -------------------------------------------------------------
    0x0000    |  0xe2  0xec  0x09  0x00  0x00  0x00  0x00  0x00
    0x0008    |  0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17
    0x0010    |  0x18  0x19  0x1a  0x1b  0x1c  0x1d  0x1e  0x1f
    0x0018    |  0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27
    0x0020    |  0x28  0x29  0x2a  0x2b  0x2c  0x2d  0x2e  0x2f
    0x0028    |  0x30  0x31  0x32  0x33  0x34  0x35  0x36  0x37
DONE
 ayo@raspberrypi  ~/classes/cs472/hw1-pdu-c   main ±  
 ```