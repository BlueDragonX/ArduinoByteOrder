#ifndef _ENDIAN_H_
#define _ENDIAN_H_

// Disable lwIP macros in the event lwIP is installed.
#define LWIP_DONT_PROVIDE_BYTEORDER_FUNCTIONS

#include <Arduino.h>

namespace Endian {

enum Endianness {
    BIG = 0,
    LITTLE = 1,
};

// Return the endianness of the host.
Endianness host();

// Reverse memcpy. Copies src byte array to dest in reverse order.
void rmemcpy(uint8_t* dest, const uint8_t* src, size_t len);

// Reverse the order of a byte array of the given length.
void reverse(uint8_t* bytes, size_t len);

// Reverse the order of an unsigned short.
void reverse(uint16_t* s);

// Reverse the order of an unsigned long.
void reverse(uint32_t* l);

// Reverse the order of an unsigned long long.
void reverse(uint64_t* ll);

// Convert a host order byte array to network order.
void htonb(uint8_t* bytes, size_t len);

// Return a host order short in network order.
uint16_t htons(uint16_t hs);

// Return a host order long in network order.
uint32_t htonl(uint32_t hl);

// Return a host order long long in network order.
uint64_t htonll(uint64_t hll);

// Write a host order short to a byte array in network order.
void hstonb(uint8_t* nb, uint16_t hs);

// Write a host order long to a byte array in network order.
void hltonb(uint8_t* nb, uint32_t hl);

// Write a host order long long to a byte array in network order.
void hlltonb(uint8_t* nb, uint64_t hll);

// Convert a network order byte array to host order.
void ntohb(uint8_t* bytes, size_t len);

// Return a network order short in host order.
uint16_t ntohs(uint16_t ns);

// Return a network order long in host order.
uint32_t ntohl(uint32_t nl);

// Return a network order long long in host order.
uint64_t ntohll(uint64_t nll);

// Read a host order short stored as a network order byte array.
uint16_t nbtohs(const uint8_t* nb);

// Read a host order long stored as a network order byte array.
uint32_t nbtohl(const uint8_t* nb);

// Read a host order long long stored as a network order byte array.
uint64_t nbtohll(const uint8_t* nb);

// Return a host order short stored as a byte array in the given order.
uint16_t btohs(const uint8_t* bytes, Endianness order);

// Return a host order long stored as a byte array in the given order.
uint32_t btohl(const uint8_t* bytes, Endianness order);

// Return a host order long long stored as a byte array in the given order.
uint64_t btohll(const uint8_t* bytes, Endianness order);

// Write a host order short to a byte array in the given order.
void hstob(uint8_t* bytes, uint16_t hs, Endianness order);

// Write a host order long to a byte array in the given order.
void hltob(uint8_t* bytes, uint32_t hl, Endianness order);

// Write a host order long long to a byte array in the given order.
void hlltob(uint8_t* bytes, uint64_t hll, Endianness order);

}  // namespace Endian

#endif // _ENDIAN_H_
