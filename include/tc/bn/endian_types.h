	/**
	 * @file endian_types.h
	 * @brief Declaration of macros and classes to unwrap primatives in an endian agnostic way.
	 * @author Jack (jakcron)
	 * @version 0.1
	 * @date 2020/12/05
	 **/
#pragma once
#include <cinttypes>
#include <type_traits>

namespace tc { namespace bn { namespace detail {

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

}}} // namespace tc::bn::detail

namespace tc { namespace bn {

	/**
	 * @struct le16
	 * @brief Wrapper that allows accessing a little-endian 16-bit POD regardless of processor endianness 
	 **/
template <typename T>
struct le16 {
public:
	static_assert(sizeof(T) == sizeof(uint16_t), "le16 requires T to be 16 bit.");
	static_assert(std::is_pod<T>::value, "le16 requires T to be a POD.");

		/// Unwrap value (Implicit)
	operator T() const { return unwrap(); }
		/// Wrap value (Implicit)
	le16& operator=(const T& var) { wrap(var); return *this; }

		/// Unwrap value
	inline T unwrap() const { return (T)detail::__le_uint16((uint16_t)mVar); }
		/// Wrap value
	inline void wrap(const T& var) { mVar = (T)detail::__le_uint16((uint16_t)var); }
private:
	T mVar;
};

	/**
	 * @struct be16
	 * @brief Wrapper that allows accessing a big-endian 16-bit POD regardless of processor endianness 
	 **/
template <typename T>
struct be16 {
public:
	static_assert(sizeof(T) == sizeof(uint16_t), "be16 requires T to be 16 bit.");
	static_assert(std::is_pod<T>::value, "be16 requires T to be a POD.");

		/// Unwrap value (Implicit)
	operator T() const { return unwrap(); }
		/// Wrap value (Implicit)
	be16& operator=(const T& var) { wrap(var); return *this; }

		/// Unwrap value
	inline T unwrap() const { return (T)detail::__be_uint16((uint16_t)mVar); }
		/// Wrap value
	inline void wrap(const T& var) { mVar = (T)detail::__be_uint16((uint16_t)var); }
private:
	T mVar;
};

	/**
	 * @struct le32
	 * @brief Wrapper that allows accessing a little-endian 32-bit POD regardless of processor endianness 
	 **/
template <typename T>
struct le32 {
public:
	static_assert(sizeof(T) == sizeof(uint32_t), "le32 requires T to be 32 bit.");
	static_assert(std::is_pod<T>::value, "le32 requires T to be a POD.");

		/// Unwrap value (Implicit)
	operator T() const { return unwrap(); }
		/// Wrap value (Implicit)
	le32& operator=(const T& var) { wrap(var); return *this; }

		/// Unwrap value
	inline T unwrap() const { return (T)detail::__le_uint32((uint32_t)mVar); }
		/// Wrap value
	inline void wrap(const T& var) { mVar = (T)detail::__le_uint32((uint32_t)var); }
private:
	T mVar;
};

	/**
	 * @struct be32
	 * @brief Wrapper that allows accessing a big-endian 32-bit POD regardless of processor endianness 
	 **/
template <typename T>
struct be32 {
public:
	static_assert(sizeof(T) == sizeof(uint32_t), "be32 requires T to be 32 bit.");
	static_assert(std::is_pod<T>::value, "be32 requires T to be a POD.");

		/// Unwrap value (Implicit)
	operator T() const { return unwrap(); }
		/// Wrap value (Implicit)
	be32& operator=(const T& var) { wrap(var); return *this; }

		/// Unwrap value
	inline T unwrap() const { return (T)detail::__be_uint32((uint32_t)mVar); }
		/// Wrap value
	inline void wrap(const T& var) { mVar = (T)detail::__be_uint32((uint32_t)var); }
private:
	T mVar;
};

	/**
	 * @struct le64
	 * @brief Wrapper that allows accessing a little-endian 64-bit POD regardless of processor endianness 
	 **/
template <typename T>
struct le64 {
public:
	static_assert(sizeof(T) == sizeof(uint64_t), "le64 requires T to be 64 bit.");
	static_assert(std::is_pod<T>::value, "le64 requires T to be a POD.");

		/// Unwrap value (Implicit)
	operator T() const { return unwrap(); }
		/// Wrap value (Implicit)
	le64& operator=(const T& var) { wrap(var); return *this; }

		/// Unwrap value
	inline T unwrap() const { return (T)detail::__le_uint64((uint64_t)mVar); }
		/// Wrap value
	inline void wrap(const T& var) { mVar = (T)detail::__le_uint64((uint64_t)var); }
private:
	T mVar;
};

	/**
	 * @struct be64
	 * @brief Wrapper that allows accessing a big-endian 64-bit POD regardless of processor endianness 
	 **/
template <typename T>
struct be64 {
public:
	static_assert(sizeof(T) == sizeof(uint64_t), "be64 requires T to be 64 bit.");
	static_assert(std::is_pod<T>::value, "be64 requires T to be a POD.");

		/// Unwrap value (Implicit)
	operator T() const { return unwrap(); }
		/// Wrap value (Implicit)
	be64& operator=(const T& var) { wrap(var); return *this; }

		/// Unwrap value
	inline T unwrap() const { return (T)detail::__be_uint64((uint64_t)mVar); }
		/// Wrap value
	inline void wrap(const T& var) { mVar = (T)detail::__be_uint64((uint64_t)var); }
private:
	T mVar;
};

}} // namespace tc::bn

namespace tc { namespace bn {


}} // namespace tc::bn