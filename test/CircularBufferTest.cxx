#include "circularbuffer.hpp"
#include <cstddef>
#include <cstdint>
#include <gtest/gtest.h>

TEST(circularBufferTest, constructor)
{
	std::size_t size = 10;
	auto buffer = CircularBuffer<std::uint16_t>(size);
	EXPECT_EQ(size, buffer.maxSize());
}

TEST(circularBufferTest, addFirstValue)
{
	std::size_t size = 10;
	auto buffer = CircularBuffer<std::uint16_t>(size);
	EXPECT_EQ(size, buffer.maxSize());
	ASSERT_EQ(0, buffer.size());
	ASSERT_EQ(true, buffer.isEmpty());

	buffer.push(1337);

	EXPECT_EQ(1, buffer.size());
	EXPECT_EQ(false, buffer.isEmpty());
}

TEST(circularBufferTest, popValue)
{
	std::size_t size = 10;
	auto buffer = CircularBuffer<std::uint16_t>(size);
	EXPECT_EQ(size, buffer.maxSize());
	ASSERT_EQ(0, buffer.size());
	ASSERT_EQ(true, buffer.isEmpty());

	std::uint16_t value = 1337;
	buffer.push(value);

	EXPECT_EQ(1, buffer.size());
	EXPECT_EQ(false, buffer.isEmpty());

	auto result = buffer.pop();

	EXPECT_EQ(value, result);
}
