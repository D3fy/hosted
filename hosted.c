#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/ioctl.h>

#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/netdevice.h>

int    num_resolved = 0;
char **resolved;

int    num_addresses = 0;
char **addresses;

int resolv_addr(const char *str_addr) /* {{{ */
{
	struct addrinfo  hints, *servinfo;
	int              rv;

	memset(&hints, 0, sizeof hints);
	hints.ai_family   = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(str_addr, NULL, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	}
	while (servinfo != NULL) {
		char str[INET_ADDRSTRLEN];
		struct sockaddr_in sock = *(struct sockaddr_in *)(servinfo->ai_addr);
		if (inet_ntop(AF_INET, &(sock.sin_addr), str, INET_ADDRSTRLEN) == NULL) {
			printf("failed: %s\n", strerror(errno));
		}
		resolved[num_resolved] = malloc(sizeof(str));
		resolved[num_resolved] = strdup(str);
		num_resolved++;
		servinfo = servinfo->ai_next;
	}

	return 0;
}
/* }}} */

int device_addr(void) /* {{{ */
{
	addresses = malloc(sizeof(char *));
	int s;
	struct ifconf ifconf;
	struct ifreq ifr[50];

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		fprintf(stderr, "failed to create socket, %s\n", strerror(errno));
		return 1;
	}

	ifconf.ifc_buf = (char *) ifr;
	ifconf.ifc_len = sizeof ifr;

	if (ioctl(s, SIOCGIFCONF, &ifconf) != 0) {
		fprintf(stderr, "failed to get configuration, %s\n", strerror(errno));
		return 1;
	}

	int ifs = ifconf.ifc_len / sizeof(ifr[0]);
	for (int i = 0; i < ifs; i++) {
		char   ip[INET_ADDRSTRLEN];
		struct sockaddr_in *s_in = (struct sockaddr_in *) &ifr[i].ifr_addr;
		if (inet_ntop(AF_INET, &s_in->sin_addr, ip, sizeof(ip)) == NULL) {
			fprintf(stderr, "failed to get address, %s\n", strerror(errno));
			return 1;
		}
		addresses[num_addresses] = malloc(sizeof(ip));
		addresses[num_addresses] = strdup(ip);
		num_addresses++;
	}
	close(s);
	return 0;
}
/* }}} */

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("please provide 1 address\n");
		return 1;
	}
	resolved  = malloc(sizeof(char *));
	addresses = malloc(sizeof(char *));
	if (resolv_addr(argv[1]))
		return 1;
	if (device_addr())
		return 1;
	for (int i = 0; i < num_resolved; i++)
		for (int j = 0; j < num_addresses; j++)
			if (strcmp(addresses[j], resolved[i]) == 0)
				printf("%s is hosted here\n", argv[1]);
	return 0;
}
