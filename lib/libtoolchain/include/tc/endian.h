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


class le_uint16_t {
public:
	inline uint16_t get() const { return __le_uint16(mVar);}
	inline void set(uint16_t var) { mVar = __le_uint16(var); }
	inline uint16_t operator=(uint16_t var) { set(var); return get();}
	inline uint16_t operator*() const { return get(); }
private:
	uint16_t mVar;
};

class be_uint16_t {
public:
	inline uint16_t get() const { return __be_uint16(mVar);}
	inline void set(uint16_t var) { mVar = __be_uint16(var); }
	inline uint16_t operator=(uint16_t var) { set(var); return get();}
	inline uint16_t operator*() const { return get(); }
private:
	uint16_t mVar;
};

class le_uint32_t {
public:
	inline uint32_t get() const { return __le_uint32(mVar);}
	inline void set(uint32_t var) { mVar = __le_uint32(var); }
	inline uint32_t operator=(uint32_t var) { set(var); return get();}
	inline uint32_t operator*() const { return get(); }
private:
	uint32_t mVar;
};

class be_uint32_t {
public:
	inline uint32_t get() const { return __be_uint32(mVar);}
	inline void set(uint32_t var) { mVar = __be_uint32(var); }
	inline uint32_t operator=(uint32_t var) { set(var); return get();}
	inline uint32_t operator*() const { return get(); }
private:
	uint32_t mVar;
};

class le_uint64_t {
public:
	inline uint64_t get() const { return __le_uint64(mVar);}
	inline void set(uint64_t var) { mVar = __le_uint64(var); }
	inline uint64_t operator=(uint64_t var) { set(var); return get();}
	inline uint64_t operator*() const { return get(); }
private:
	uint64_t mVar;
};

class be_uint64_t {
public:
	inline uint64_t get() const { return __be_uint64(mVar);}
	inline void set(uint64_t var) { mVar = __be_uint64(var); }
	inline uint64_t operator=(uint64_t var) { set(var); return get();}
	inline uint64_t operator*() const { return get(); }
private:
	uint64_t mVar;
};