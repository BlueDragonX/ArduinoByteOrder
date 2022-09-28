#include "Endian.h"

#include <Arduino.h>

namespace Endian {

Endianness host() {
    union {
        uint16_t a;
        uint8_t b[2];
    } endian = {0x0001};
    if (endian.b[0]) {
        return LITTLE;
    } else{
        return BIG;
    }
}

void reverse(uint8_t* bytes, size_t len) {
    uint8_t tmp;
    for (size_t i = 0; i < (len / 2); ++i) {
        tmp = bytes[i];
        bytes[i] = bytes[len - i - 1];
        bytes[len - i - 1] = tmp;
    } 
}

void rmemcpy(uint8_t* dest, const uint8_t* src, size_t len) {
    for (size_t i = 0; i < len; i++) {
        dest[i] = src[len - i - 1];
    }
}

void reverse(uint16_t* s) {
    reverse((uint8_t*)s, 2);
}

void reverse(uint32_t* l) {
    reverse((uint8_t*)l, 4);
}

void reverse(uint64_t* ll) {
    reverse((uint8_t*)ll, 8);
}

void htonb(uint8_t* bytes, size_t len) {
    if (host() == LITTLE) {
        reverse(bytes, len);
    }
}

uint16_t htons(uint16_t hs) {
    if (host() == BIG) {
        return hs;
    }
    return (
        ((hs & 0xFF00) >> 8) |
        ((hs & 0x00FF) << 8));
}

uint32_t htonl(uint32_t hl) {
    if (host() == BIG) {
        return hl;
    }
    return (
        ((hl & 0xFF000000) >> 24) |
        ((hl & 0x00FF0000) >> 8) |
        ((hl & 0x0000FF00) << 8) |
        ((hl & 0x000000FF) << 24));
}

uint64_t htonll(uint64_t hll) {
    if (host() == BIG) {
        return hll;
    }
    return (
        ((hll & 0xFF00000000000000) >> 56) |
        ((hll & 0x00FF000000000000) >> 40) |
        ((hll & 0x0000FF0000000000) >> 24) |
        ((hll & 0x000000FF00000000) >> 8) |
        ((hll & 0x00000000FF000000) << 8) |
        ((hll & 0x0000000000FF0000) << 24) |
        ((hll & 0x000000000000FF00) << 40) |
        ((hll & 0x00000000000000FF) << 56));
}

void ntohb(uint8_t* bytes, size_t len) {
    htonb(bytes, len);
}

uint16_t ntohs(uint16_t ns) {
    return htons(ns); 
}

uint32_t ntohl(uint32_t nl) {
    return htonl(nl);
}

uint64_t ntohll(uint64_t nll) {
    return htonll(nll);
}

void hstonb(uint8_t* nb, uint16_t hs) {
    hstob(nb, hs, BIG);
}

void hltonb(uint8_t* nb, uint32_t hl) {
    hltob(nb, hl, BIG);
}

void hlltonb(uint8_t* nb, uint64_t hll) {
    hlltob(nb, hll, BIG);
}

uint16_t nbtohs(const uint8_t* nb) {
    return btohs(nb, BIG);
}

uint32_t nbtohl(const uint8_t* nb) {
    return btohl(nb, BIG);
}

uint64_t nbtohll(const uint8_t* nb) {
    return btohll(nb, BIG);
}

uint16_t btohs(const uint8_t* bytes, Endianness order) {
    uint16_t hs;
    if (host() == order) {
        memcpy(&hs, bytes, 2);
    } else {
        rmemcpy((uint8_t*)&hs, bytes, 2);
    }
    return hs;
}

uint32_t btohl(const uint8_t* bytes, Endianness order) {
    uint32_t hl;
    if (host() == order) {
        memcpy(&hl, bytes, 4);
    } else {
        rmemcpy((uint8_t*)&hl, bytes, 4);
    }
    return hl;
}

uint64_t btohll(const uint8_t* bytes, Endianness order) {
    uint64_t hll;
    if (host() == order) {
        memcpy(&hll, bytes, 8);
    } else {
        rmemcpy((uint8_t*)&hll, bytes, 8);
    }
    return hll;
}

void hstob(uint8_t* bytes, uint16_t hs, Endianness order) {
    if (host() == order) {
        memcpy(bytes, (uint8_t*)&hs, 2);
    } else {
        rmemcpy(bytes, (uint8_t*)&hs, 2);
    }
}

void hltob(uint8_t* bytes, uint32_t hl, Endianness order) {
    if (host() == order) {
        memcpy(bytes, (uint8_t*)&hl, 4);
    } else {
        rmemcpy(bytes, (uint8_t*)&hl, 4);
    }
}

void hlltob(uint8_t* bytes, uint64_t hll, Endianness order) {
    if (host() == order) {
        memcpy(bytes, (uint8_t*)&hll, 8);
    } else {
        rmemcpy(bytes, (uint8_t*)&hll, 8);
    }
}

}  // namespace Endian
