/* Copyright (c) 2011-2019, Stanford University
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include "MacAddress.h"

#include "../RawAddressType.h"

#include <gtest/gtest.h>

namespace Homa {
namespace Drivers {
namespace DPDK {
namespace {

TEST(MacAddressTest, constructorRaw)
{
    uint8_t raw[] = {0xde, 0xad, 0xbe, 0xef, 0x98, 0x76};
    EXPECT_EQ("de:ad:be:ef:98:76", MacAddress(raw).toString());
}

TEST(MacAddressTest, constructorString)
{
    EXPECT_EQ("de:ad:be:ef:98:76", MacAddress("de:ad:be:ef:98:76").toString());
}

TEST(MacAddressTest, constructorWireFormatAddress)
{
    uint8_t bytes[] = {0xde, 0xad, 0xbe, 0xef, 0x98, 0x76};
    Driver::WireFormatAddress wireformatAddress;
    wireformatAddress.type = RawAddressType::MAC;
    memcpy(wireformatAddress.bytes, bytes, 6);
    EXPECT_EQ("de:ad:be:ef:98:76", MacAddress(&wireformatAddress).toString());

    wireformatAddress.type = RawAddressType::FAKE;
    EXPECT_THROW(MacAddress address(&wireformatAddress), BadAddress);
}

TEST(MacAddressTest, constructorAddress)
{
    uint8_t raw[] = {0xde, 0xad, 0xbe, 0xef, 0x98, 0x76};
    MacAddress(raw).toString();
    Driver::Address addr = MacAddress("de:ad:be:ef:98:76").toAddress();
    EXPECT_EQ("de:ad:be:ef:98:76", MacAddress(addr).toString());
}

TEST(MacAddressTest, construct_DefaultCopy)
{
    MacAddress source("de:ad:be:ef:98:76");
    MacAddress dest(source);
    EXPECT_EQ("de:ad:be:ef:98:76", dest.toString());
}

TEST(MacAddressTest, toString)
{
    // tested sufficiently in constructor tests
}

TEST(MacAddressTest, toWireFormat)
{
    Driver::WireFormatAddress wireformatAddress;
    MacAddress("de:ad:be:ef:98:76").toWireFormat(&wireformatAddress);
    EXPECT_EQ(RawAddressType::MAC, wireformatAddress.type);
    EXPECT_EQ(0xde, wireformatAddress.bytes[0]);
    EXPECT_EQ(0xad, wireformatAddress.bytes[1]);
    EXPECT_EQ(0xbe, wireformatAddress.bytes[2]);
    EXPECT_EQ(0xef, wireformatAddress.bytes[3]);
    EXPECT_EQ(0x98, wireformatAddress.bytes[4]);
    EXPECT_EQ(0x76, wireformatAddress.bytes[5]);
}

TEST(MacAddressTest, toAddress)
{
    // Tested in constructorAddress
}

TEST(MacAddressTest, isNull)
{
    uint8_t rawNull[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
    uint8_t rawNonNull[] = {0xde, 0xad, 0xbe, 0xef, 0x98, 0x76};
    EXPECT_TRUE(MacAddress(rawNull).isNull());
    EXPECT_FALSE(MacAddress(rawNonNull).isNull());
}

}  // namespace
}  // namespace DPDK
}  // namespace Drivers
}  // namespace Homa
