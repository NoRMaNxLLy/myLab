#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* turn a /n prefix to binary netmask*/
int prefix2mask(int n)
{
        return 0xFFFFFFFF << (32 - n);
}

/* turn a netmask to /n prefix */
int mask2prefix(unsigned int mask)
{
                     /* 10000000 00000000 00000000 00000000*/
        unsigned int i = 0x80000000;
        int count = 0;

        while (i) {
                if (mask & i) {
                        count++;
                }
                i >>= 1;
        }

        return count;
}


/* return 1 if the mask is valid, 0 otherwise */
int validmask(unsigned int mask) {
        unsigned int i = 0x80000000;
        int found_zero = 0;

        // this does not look right...
        mask = ntohl(mask);

        while (i) {
                if ((mask & i) == 0) {
                        found_zero = 1;
                }

                /* if the bit is set and we already found one off, then
                 * not valid mask */
                if (mask & i && found_zero)
                        return 0;

                i >>= 1;
        }

        return 1;
}

int main(int argc, char *argv[])
{
        int prefix, ret;
        struct in_addr ip, netmask, network, broadcast;

        if (argc < 2) {
                fprintf(stderr, "%s ipaddr[/24] [dotted_netmask]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        char *_;
        if ((_ = strchr(argv[1], '/'))) {
                *_++ = '\0';
                prefix = strtol(_, NULL, 10);
                if (0 > prefix || prefix > 32) {
                        fprintf(stderr, "invalid prefix: /%d\n", prefix);
                        exit(EXIT_FAILURE);
                }

                netmask.s_addr = htonl(prefix2mask(prefix));
        }

        ret = inet_pton(AF_INET, argv[1], &(ip));
        if (ret == 0) {
                fprintf(stderr, "invalid ipv4 address: %s\n", argv[1]);
                exit(EXIT_FAILURE);
        }

        if (argv[2]) {
                if (netmask.s_addr) {
                        fprintf(stderr, "%s\n", "use /n or netmask, not both");
                        exit(EXIT_FAILURE);
                }

                ret = inet_pton(AF_INET, argv[2], &(netmask));
                if (ret == 0 || !validmask(netmask.s_addr)) {
                        fprintf(stderr, "invalid netmask: %s\n", argv[2]);
                        exit(EXIT_FAILURE);
                }

                /* convert the netmask to /n prefix */
                prefix = mask2prefix(netmask.s_addr);
        }

        network.s_addr   = ip.s_addr & netmask.s_addr;
        broadcast.s_addr = ip.s_addr | (netmask.s_addr ^ 0xFFFFFFFF);

        /* print out everything... */
        char buf[INET_ADDRSTRLEN];

        printf("prefix: /%d\n", prefix);
        printf("netmask: %s\n", inet_ntop(AF_INET, &netmask, buf, INET_ADDRSTRLEN));
        printf("network: %s\n", inet_ntop(AF_INET, &network, buf, INET_ADDRSTRLEN));
        printf("broadcast: %s\n", inet_ntop(AF_INET, &broadcast, buf, INET_ADDRSTRLEN));
}
