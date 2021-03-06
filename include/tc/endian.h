	/**
	 * @file endian.h
	 * @brief Declaration of macros and classes to unwrap primatives in an endian agnostic way
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2019/01/15
	 **/
#pragma once
#include <cinttypes>

static inline uint16_t __local_bswap16(uint16_t x) {
	return ((x << 8) & 0xff00) | ((x >> 8) & 0x00ff);
}


static inline uint32_t __local_bswap32(uint32_t x) {
	return	((x << 24) & 0xff000000 ) |
			((x <<  8) & 0x00ff0000 ) |
			((x >>  8) & 0x0000ff00 ) |
			((x >> 24) & 0x000000ff );
}

static inline uint64_t __local_bswap64(uint64_t x)
{
	return (uint64_t)__local_bswap32(x>>32) |
	      ((uint64_t)__local_bswap32(x&0xFFFFFFFF) << 32);
}

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
static inline uint64_t __be_uint64(uint64_t a) { return __local_bswap64(a); }
static inline uint32_t __be_uint32(uint32_t a) { return __local_bswap32(a); }
static inline uint16_t __be_uint16(uint16_t a) { return __local_bswap16(a); }
static inline uint64_t __le_uint64(uint64_t a) { return a; }
static inline uint32_t __le_uint32(uint32_t a) { return a; }
static inline uint16_t __le_uint16(uint16_t a) { return a; }
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
static inline uint64_t __be_uint64(uint64_t a) { return a; }
static inline uint32_t __be_uint32(uint32_t a) { return a; }
static inline uint16_t __be_uint16(uint16_t a) { return a; }
static inline uint64_t __le_uint64(uint64_t a) { return __local_bswap64(a); }
static inline uint32_t __le_uint32(uint32_t a) { return __local_bswap32(a); }
static inline uint16_t __le_uint16(uint16_t a) { return __local_bswap16(a); }
#endif

	/**
	 * @struct le_uint16_t
	 * @brief Wrapper that allows accessing a little-endian uint16_t regardless of processor endianness 
	 **/
struct le_uint16_t {
public:
		/// Unwrap value
	inline uint16_t unwrap() const { return __le_uint16(mVar);}
		/// Wrap value
	inline void wrap(uint16_t var) { mVar = __le_uint16(var); }
private:
	uint16_t mVar;
};

	/**
	 * @struct be_uint16_t
	 * @brief Wrapper that allows accessing a big-endian uint16_t regardless of processor endianness 
	 **/
struct be_uint16_t {
public:
		/// Unwrap value
	inline uint16_t unwrap() const { return __be_uint16(mVar);}
		/// Wrap value
	inline void wrap(uint16_t var) { mVar = __be_uint16(var); }
private:
	uint16_t mVar;
};

	/**
	 * @struct le_uint32_t
	 * @brief Wrapper that allows accessing a little-endian uint32_t regardless of processor endianness 
	 **/
struct le_uint32_t {
public:
		/// Unwrap value
	inline uint32_t unwrap() const { return __le_uint32(mVar);}
		/// Wrap value
	inline void wrap(uint32_t var) { mVar = __le_uint32(var); }
private:
	uint32_t mVar;
};

	/**
	 * @struct be_uint32_t
	 * @brief Wrapper that allows accessing a big-endian uint32_t regardless of processor endianness 
	 **/
struct be_uint32_t {
public:
		/// Unwrap value
	inline uint32_t unwrap() const { return __be_uint32(mVar);}
		/// Wrap value
	inline void wrap(uint32_t var) { mVar = __be_uint32(var); }
private:
	uint32_t mVar;
};

	/**
	 * @struct le_uint64_t
	 * @brief Wrapper that allows accessing a little-endian uint64_t regardless of processor endianness 
	 **/
struct le_uint64_t {
public:
		/// Unwrap value
	inline uint64_t unwrap() const { return __le_uint64(mVar);}
		/// Wrap value
	inline void wrap(uint64_t var) { mVar = __le_uint64(var); }
private:
	uint64_t mVar;
};

	/**
	 * @struct be_uint64_t
	 * @brief Wrapper that allows accessing a big-endian uint64_t regardless of processor endianness 
	 **/
struct be_uint64_t {
public:
		/// Unwrap value
	inline uint64_t unwrap() const { return __be_uint64(mVar);}
		/// Wrap value
	inline void wrap(uint64_t var) { mVar = __be_uint64(var); }
private:
	uint64_t mVar;
};