#ifndef MSGPACK_PACK_HPP__
#define MSGPACK_PACK_HPP__

#include "msgpack/object.hpp"
#include "msgpack/zone.hpp"
#include <arpa/inet.h>  // __BYTE_ORDER
#include <stdexcept>

namespace msgpack {


template <typename Stream>
class packer {
public:
	packer(Stream& s);

public:
	void pack_int(int d)					{ pack_int_impl(m_stream, d); }
	void pack_unsigned_int(unsigned int d)	{ pack_unsigned_int_impl(m_stream, d); }
	void pack_unsigned_int_8(uint8_t d)		{ pack_unsigned_int_8_impl(m_stream, d); }
	void pack_unsigned_int_16(uint16_t d)	{ pack_unsigned_int_16_impl(m_stream, d); }
	void pack_unsigned_int_32(uint32_t d)	{ pack_unsigned_int_32_impl(m_stream, d); }
	void pack_unsigned_int_64(uint64_t d)	{ pack_unsigned_int_64_impl(m_stream, d); }
	void pack_signed_int_8(uint8_t d)		{ pack_signed_int_8_impl(m_stream, d); }
	void pack_signed_int_16(uint16_t d)		{ pack_signed_int_16_impl(m_stream, d); }
	void pack_signed_int_32(uint32_t d)		{ pack_signed_int_32_impl(m_stream, d); }
	void pack_signed_int_64(uint64_t d)		{ pack_signed_int_64_impl(m_stream, d); }
	void pack_float(float d)				{ pack_float_impl(m_stream, d); }
	void pack_double(double d)				{ pack_double_impl(m_stream, d); }
	void pack_nil()							{ pack_nil(m_stream); }
	void pack_true()						{ pack_true(m_stream); }
	void pack_false()						{ pack_false(m_stream); }
	void pack_array(unsigned int n)			{ pack_array_impl(m_stream, n); }
	void pack_map(unsigned int n)			{ pack_map_impl(m_stream, n); }
	void pack_string(const char* b)			{ pack_string_impl(m_stream, b); }
	void pack_raw(const void* b, size_t l)	{ pack_raw_impl(m_stream, b, l); }

private:
	static void pack_int_impl(Stream& x, int d);
	static void pack_unsigned_int_impl(Stream& x, unsigned int d);
	static void pack_unsigned_int_8_impl(Stream& x, uint8_t d);
	static void pack_unsigned_int_16_impl(Stream& x, uint16_t d);
	static void pack_unsigned_int_32_impl(Stream& x, uint32_t d);
	static void pack_unsigned_int_64_impl(Stream& x, uint64_t d);
	static void pack_signed_int_8_impl(Stream& x, int8_t d);
	static void pack_signed_int_16_impl(Stream& x, int16_t d);
	static void pack_signed_int_32_impl(Stream& x, int32_t d);
	static void pack_signed_int_64_impl(Stream& x, int64_t d);
	static void pack_float_impl(Stream& x, float d);
	static void pack_double_impl(Stream& x, double d);
	static void pack_nil_impl(Stream& x);
	static void pack_true_impl(Stream& x);
	static void pack_false_impl(Stream& x);
	static void pack_array_impl(Stream& x, unsigned int n);
	static void pack_map_impl(Stream& x, unsigned int n);
	static void pack_string_impl(Stream& x, const char* b);
	static void pack_raw_impl(Stream& x, const void* b, size_t l);
	static void append_buffer(Stream& x, const unsigned char* buf, unsigned int len)
		{ x.append((const char*)buf, len); }

private:
	Stream& m_stream;

private:
	packer();
};

#define msgpack_pack_inline_func(name) \
	template <typename Stream> \
	inline void packer<Stream>::pack_ ## name ## _impl
#define msgpack_pack_context Stream&
#define msgpack_pack_append_buffer append_buffer
#include "msgpack/pack/inline_impl.h"
#undef msgpack_pack_context
#undef msgpack_pack_append_buffer

template <typename Stream>
packer<Stream>::packer(Stream& s) : m_stream(s) { }


class dynamic_stream {
public:
	template <typename Stream>
	dynamic_stream(Stream& s);
public:
	dynamic_stream& append(const char* buf, size_t len)
		{ (*m_function)(m_object, buf, len); return *this; }
private:
	void* m_object;
	void (*m_function)(void* object, const char* buf, size_t len);
private:
	template <typename Stream, Stream& (Stream::*MemFun)(const char*, size_t)>
	static void append_trampoline(void* object, const char* buf, size_t len);
};


class dynamic_packer {
public:
	template <typename Stream>
	dynamic_packer(Stream& s);

public:
	void pack_int(int d)					{ pack_int_impl(m_stream, d); }
	void pack_unsigned_int(unsigned int d)	{ pack_unsigned_int_impl(m_stream, d); }
	void pack_unsigned_int_8(uint8_t d)		{ pack_unsigned_int_8_impl(m_stream, d); }
	void pack_unsigned_int_16(uint16_t d)	{ pack_unsigned_int_16_impl(m_stream, d); }
	void pack_unsigned_int_32(uint32_t d)	{ pack_unsigned_int_32_impl(m_stream, d); }
	void pack_unsigned_int_64(uint64_t d)	{ pack_unsigned_int_64_impl(m_stream, d); }
	void pack_signed_int_8(uint8_t d)		{ pack_signed_int_8_impl(m_stream, d); }
	void pack_signed_int_16(uint16_t d)		{ pack_signed_int_16_impl(m_stream, d); }
	void pack_signed_int_32(uint32_t d)		{ pack_signed_int_32_impl(m_stream, d); }
	void pack_signed_int_64(uint64_t d)		{ pack_signed_int_64_impl(m_stream, d); }
	void pack_float(float d)				{ pack_float_impl(m_stream, d); }
	void pack_double(double d)				{ pack_double_impl(m_stream, d); }
	void pack_nil()							{ pack_nil_impl(m_stream); }
	void pack_true()						{ pack_true_impl(m_stream); }
	void pack_false()						{ pack_false_impl(m_stream); }
	void pack_array(unsigned int n)			{ pack_array_impl(m_stream, n); }
	void pack_map(unsigned int n)			{ pack_map_impl(m_stream, n); }
	void pack_string(const char* b)			{ pack_string_impl(m_stream, b); }
	void pack_raw(const void* b, size_t l)	{ pack_raw_impl(m_stream, b, l); }

public:

private:
	static void pack_int_impl(dynamic_stream& x, int d);
	static void pack_unsigned_int_impl(dynamic_stream& x, unsigned int d);
	static void pack_unsigned_int_8_impl(dynamic_stream& x, uint8_t d);
	static void pack_unsigned_int_16_impl(dynamic_stream& x, uint16_t d);
	static void pack_unsigned_int_32_impl(dynamic_stream& x, uint32_t d);
	static void pack_unsigned_int_64_impl(dynamic_stream& x, uint64_t d);
	static void pack_signed_int_8_impl(dynamic_stream& x, int8_t d);
	static void pack_signed_int_16_impl(dynamic_stream& x, int16_t d);
	static void pack_signed_int_32_impl(dynamic_stream& x, int32_t d);
	static void pack_signed_int_64_impl(dynamic_stream& x, int64_t d);
	static void pack_float_impl(dynamic_stream& x, float d);
	static void pack_double_impl(dynamic_stream& x, double d);
	static void pack_nil_impl(dynamic_stream& x);
	static void pack_true_impl(dynamic_stream& x);
	static void pack_false_impl(dynamic_stream& x);
	static void pack_array_impl(dynamic_stream& x, unsigned int n);
	static void pack_map_impl(dynamic_stream& x, unsigned int n);
	static void pack_string_impl(dynamic_stream& x, const char* b);
	static void pack_raw_impl(dynamic_stream& x, const void* b, size_t l);
	static void append_buffer(dynamic_stream& x, const unsigned char* buf, unsigned int len)
		{ x.append((const char*)buf, len); }

private:
	dynamic_stream m_stream;

private:
	dynamic_packer();
};

#undef MSGPACK_PACK_INLINE_IMPL_H__
#define msgpack_pack_inline_func(name) \
	inline void dynamic_packer::pack_ ## name ## _impl
#define msgpack_pack_context dynamic_stream&
#define msgpack_pack_append_buffer append_buffer
#include "msgpack/pack/inline_impl.h"
#undef msgpack_pack_context
#undef msgpack_pack_append_buffer

template <typename Stream>
dynamic_packer::dynamic_packer(Stream& s) : m_stream(s) { }

template <typename Stream>
dynamic_stream::dynamic_stream(Stream& s)
{
	m_object = reinterpret_cast<void*>(&s);
	m_function = &dynamic_stream::append_trampoline<Stream, &Stream::append>;
}

template <typename Stream, Stream& (Stream::*MemFun)(const char*, size_t)>
void dynamic_stream::append_trampoline(void* object, const char* buf, size_t len)
{
	(reinterpret_cast<Stream*>(object)->*MemFun)(buf, len);
}


template <typename Stream>
inline void pack(Stream& s, object o)
{
	dynamic_packer pk(s);
	o.pack(pk);
}


}  // namespace msgpack

#endif /* msgpack/pack.hpp */
