#pragma once
#include <winsock2.h>
#include <ws2def.h>

#define NAME_MAX 100


struct MiscServer {
    char s_name[NAME_MAX];
    char ipv4[NAME_MAX];
    char ipv6[NAME_MAX]; // target address family
    int  port;

    char buf[NAME_MAX];  // for testing raw text

    SOCKET skt; // = socket(AF_INET6, SOCK_STREAM, IPPROTO_UDP);
} MiscServer;