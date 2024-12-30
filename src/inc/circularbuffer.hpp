#pragma once

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>

template <typename T> class CircularBuffer {
public:
	explicit CircularBuffer<T>(std::size_t size)
		: mSize(size)
		, mBuffer(std::unique_ptr<T[]>(new T[mSize]))
	{
	}

	CircularBuffer<T>(const T&) = delete;
	CircularBuffer<T>(const T&&) = delete;

	~CircularBuffer<T>()
	{
		delete[] mBuffer.get();
		mBuffer.release();
	};

	void push(const T& data)
	{
		if (nullptr == mBuffer) {
			return;
		}

		std::lock_guard<std::mutex> lock(mMutex);

		if (mEmpty) {
			mEmpty = false;
		}

		mBuffer[mWriteIndex] = data;

		mWriteIndex = (mWriteIndex + 1) % mSize;

		if (mWriteIndex >= mSize) {
			mFull = true;
		}
	}

	T pop()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		if (mEmpty) {
			return T();
		}

		auto result = mBuffer[mReadIndex];
		mBuffer[mReadIndex] = {};
		mReadIndex = (mReadIndex + 1) % mSize;

		if (mReadIndex == 0 && mWriteIndex == 0) {
			mEmpty = true;
		}

		return result;
	}

	void clear()
	{
		std::lock_guard<std::mutex> lock(mMutex);
		for (std::size_t i = 0; i < mSize; i++) {
			*mBuffer[i] = {};
		}
		mEmpty = true;
		mFull = false;
		mReadIndex = 0;
		mWriteIndex = 0;
	}

	bool isEmpty() const { return mEmpty; }

	bool isFull() const { return mFull; }

	std::size_t maxSize() const { return mSize; }

	std::size_t size() const { return static_cast<std::size_t>(mWriteIndex); }

private:
	std::size_t mSize {};
	std::unique_ptr<T[]> mBuffer {};
	std::atomic_bool mEmpty { true };
	std::atomic_bool mFull {};
	std::uint16_t mReadIndex {};
	std::uint16_t mWriteIndex {};
	std::mutex mMutex {};
};
