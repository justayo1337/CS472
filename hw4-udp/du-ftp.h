#pragma once

#define PROG_MD_CLI     0
#define PROG_MD_SVR     1
#define DEF_PORT_NO     2080
#define FNAME_SZ        150
#define PROG_DEF_FNAME  "test.c"
#define PROG_DEF_SVR_ADDR   "127.0.0.1"

typedef struct prog_config{
    int     prog_mode;
    int     port_number;
    char    svr_ip_addr[16];
    char    file_name[128];
} prog_config;




typedef struct ftp_pdu{
    int     proto_ver; //  
    int     mtype; // DU_FTP_SND || DU_FTP_ACK ||  DU_FTP_CONNECT | DU_FTP_NACK | DU_FTP_RESEND
    int     filesize; 
    char    filename[128];
    int     file_status; // FILE_FOUND || FILE_NOT_FOUND || CANNOT_READ_FILE || CLOSE_FILE || CANNOT_WRITE_FILE 
    char    err_msg[256];
    int     send_status; // DONE_SENDING || STILL_SENDING || SEND_FAILURE || RESEND_FILE 
    int     seqNum; 
} ftp_pdu;