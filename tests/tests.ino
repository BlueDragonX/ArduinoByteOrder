#include <AUnit.h>
#include <Arduino.h>
#include <Endian.h>


namespace Endian {
size_t printBytes(uint8_t* bytes, size_t len) {
    size_t n = 0;
    for(size_t i = 0; i < len; ++i) {
        if (bytes[i] <= 0x0F) {
            n += SERIAL_PORT_MONITOR.print("0");
        }
        n += SERIAL_PORT_MONITOR.print(bytes[i], HEX);
    }
    return n;
}

#define assertHexEqual(left, right) do { \
    if (left != right) { \
        SERIAL_PORT_MONITOR.print(left, HEX); \
        SERIAL_PORT_MONITOR.print(" != "); \
        SERIAL_PORT_MONITOR.println(right, HEX); \
        assertTrue(false); \
    } \
} while (false)

#define assertBytesEqual(left, right, len) do { \
    if (memcmp(left, right, len) != 0) { \
        printBytes(left, len); \
        SERIAL_PORT_MONITOR.print(" != "); \
        printBytes(right, len); \
        Serial.println(); \
        assertTrue(false); \
    } \
} while (false)

using namespace aunit;

test(RMemcpyTest, Empty) {
    uint8_t src[] = {};
    uint8_t actual[] = {};
    uint8_t expect[] = {};
    rmemcpy(actual, src, 0);
    assertBytesEqual(actual, expect, 0);
}

test(RMemcpyTest, One) {
    uint8_t src[] = {0x11};
    uint8_t actual[1];
    uint8_t expect[] = {0x11};
    rmemcpy(actual, src, 1);
    assertBytesEqual(actual, expect, 1);
}

test(RMemcpyTest, Multiple) {
    uint8_t src[] = {0x11, 0x22, 0x33, 0x44, 0x55};
    uint8_t actual[5];
    uint8_t expect[] = {0x55, 0x44, 0x33, 0x22, 0x11};
    rmemcpy(actual, src, 5);
    assertBytesEqual(actual, expect, 5);
}

test(ReverseTest, BytesEmpty) {
    uint8_t actual[] = {};
    uint8_t expect[] = {};
    reverse(actual, 0);
    assertBytesEqual(actual, expect, 0);
}

test(ReverseTest, BytesOne) {
    uint8_t actual[] = {0x11};
    uint8_t expect[] = {0x11};
    reverse(actual, 1);
    assertBytesEqual(actual, expect, 1);
}

test(ReverseTest, BytesEvent) {
    uint8_t actual[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t expect[] = {0x44, 0x33, 0x22, 0x11};
    reverse(actual, 4);
    assertBytesEqual(actual, expect, 4);
}

test(ReverseTest, BytesOdd) {
    uint8_t actual[] = {0x11, 0x22, 0x33, 0x44, 0x55};
    uint8_t expect[] = {0x55, 0x44, 0x33, 0x22, 0x11};
    reverse(actual, 5);
    assertBytesEqual(actual, expect, 5);
}

test(ReverseTest, Short) {
    uint16_t actual = 0x1122;
    uint16_t expect = 0x2211;
    reverse(&actual);
    assertEqual(actual, expect);
}

test(ReverseTest, Long) {
    uint32_t actual = 0x11223344;
    uint32_t expect = 0x44332211;
    reverse(&actual);
    assertEqual(actual, expect);
}

test(ReverseTest, LongLong) {
    uint64_t actual = 0x1122334455667788;
    uint64_t expect = 0x8877665544332211;
    reverse(&actual);
    assertEqual(actual, expect);
}

test(HtoNTest, Bytes) {
    uint8_t actual[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t expect[] = {0x11, 0x22, 0x33, 0x44};
    if (host() == LITTLE) {
        reverse(expect, 4);
    }
    htonb(actual, 4);
    assertBytesEqual(actual, expect, 4);
}

test(HtoNTest, Short) {
    uint16_t value = host() == LITTLE ? 0x1122 : 0x2211;
    uint16_t expect = 0x2211;
    assertHexEqual(htons(value), expect);
}

test(HtoNTest, Long) {
    uint32_t value = host() == LITTLE ? 0x11223344 : 0x44332211;
    uint32_t expect = 0x44332211;
    assertHexEqual(htonl(value), expect);
}

test(HtoNTest, LongLong) {
    uint64_t value = host() == LITTLE ? 0x1122334455667788 : 0x8877665544332211;
    uint64_t expect = 0x8877665544332211;
    assertHexEqual(htonll(value), expect);
}

test(NtoHTest, Bytes) {
    uint8_t actual[] = {0x11, 0x22, 0x33, 0x44};
    uint8_t expect[] = {0x11, 0x22, 0x33, 0x44};
    if (host() == LITTLE) {
        reverse(expect, 4);
    }
    ntohb(actual, 4);
    assertBytesEqual(actual, expect, 4);
}

test(NtoHTest, Short) {
    uint16_t value = 0x1122;
    uint16_t expect = host() == BIG ? 0x1122 : 0x2211;
    assertHexEqual(ntohs(value), expect);
}

test(NtoHTest, Long) {
    uint32_t value = 0x11223344;
    uint32_t expect = host() == BIG ? 0x11223344: 0x44332211;
    assertHexEqual(ntohl(value), expect);
}

test(NtoHTest, LongLong) {
    uint64_t value = 0x1122334455667788;
    uint64_t expect = host() == BIG ? 0x1122334455667788: 0x8877665544332211;
    assertHexEqual(ntohll(value), expect);
}

test(NBtoH, Short) {
    uint8_t bytes[] = {0x11, 0x22};
    uint16_t expect = host() == BIG ? 0x1122 : 0x2211;
    assertHexEqual(nbtohs(bytes), expect);
}

test(NBtoH, Long) {
    uint8_t bytes[] = {0x11, 0x22, 0x33, 0x44};
    uint32_t expect = host() == BIG ? 0x11223344 : 0x44332211;
    assertHexEqual(nbtohl(bytes), expect);
}

test(NBtoH, LongLong) {
    uint8_t bytes[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    uint64_t expect = host() == BIG ? 0x1122334455667788 : 0x8877665544332211;
    assertHexEqual(nbtohll(bytes), expect);
}

test(BtoHTest, ShortBig) {
    uint8_t bytes[] = {0x11, 0x22};
    uint16_t expect = 0x1122;
    assertHexEqual(btohs(bytes, BIG), expect);
}

test(BtoHTest, ShortLittle) {
    uint8_t bytes[] = {0x22, 0x11};
    uint16_t expect = 0x1122;
    assertHexEqual(btohs(bytes, LITTLE), expect);
}

test(BtoHTest, LongBig) {
    uint8_t bytes[] = {0x11, 0x22, 0x33, 0x44};
    uint32_t expect = 0x11223344;
    assertHexEqual(btohl(bytes, BIG), expect);
}

test(BtoHTest, LongLittle) {
    uint8_t bytes[] = {0x44, 0x33, 0x22, 0x11};
    uint32_t expect = 0x11223344;
    assertHexEqual(btohl(bytes, LITTLE), expect);
}

test(BtoHTest, LongLongBig) {
    uint8_t bytes[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88};
    uint64_t expect = 0x1122334455667788;
    assertHexEqual(btohll(bytes, BIG), expect);
}

test(BtoHTest, LongLongLittle) {
    uint8_t bytes[] = {0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11};
    uint64_t expect = 0x1122334455667788;
    assertHexEqual(btohll(bytes, LITTLE), expect);
}

}  // namespace Endian

// Test boilerplate.
void setup() {
#ifdef ARDUINO
    delay(1000);
#endif
    SERIAL_PORT_MONITOR.begin(115200);
    while(!SERIAL_PORT_MONITOR);
}

void loop() {
    aunit::TestRunner::run();
    delay(1);
}
