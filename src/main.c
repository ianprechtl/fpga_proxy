#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "protocol.h"

int main() {

    // connect and synchronize
    pHandle proxy_inst = protocol_connect();
    if(protocol_synchronize(proxy_inst, 15, 0)){    // require 15 passes, do not print output
        return 1;
    }
    // read 0x3C and 0x40 - read values are DDR3 initialized cell values
    char rx_buffer[8];
    if(protocol_read(proxy_inst, rx_buffer, 8, 0x0000003C)){
        return 1;
    }
    printf("%08x\n",*(uint32_t *)rx_buffer);
    printf("%08x\n",*(uint32_t *)(rx_buffer+4));

    // write to same read addresses
    char tx_buffer[8];
    *(uint32_t *)(tx_buffer+0) = 0x1;
    *(uint32_t *)(tx_buffer+4) = 0xDEADBEAF;
    if(protocol_write(proxy_inst, tx_buffer, 8, 0x0000003C)){
        return 1;
    }

    // verify the write
    if(protocol_read(proxy_inst, rx_buffer, 8, 0x0000003C)){
        return 1;
    }
    printf("%08x\n",*(uint32_t *)rx_buffer);
    printf("%08x\n",*(uint32_t *)(rx_buffer+4));

    // exit
    printf("Closing\n");
    return 0;
}