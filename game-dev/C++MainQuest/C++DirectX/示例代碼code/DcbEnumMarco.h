#include <cassert>
#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <optional>
#include <string>

// master list of leaf types that generates enum elements and various switches etc.
#define LEAF_ELEMENT_TYPES \
	X( Float ) \
	X( Float2 ) \
	X( Float3 ) \
	X( Float4 ) \
	X( Matrix ) \
	X( Bool )

namespace Dcb
{
	namespace dx = DirectX;

	enum Type
	{
#define X(el) el,
		LEAF_ELEMENT_TYPES
#undef X
		Struct,
		Array,
		Empty,
	};

	// static map of attributes of each leaf type
	template<Type type>
	struct Map
	{
		static constexpr bool valid = false;
	};
	template<> struct Map<Float>
	{
		using SysType = float; // type used in the CPU side
		static constexpr size_t hlslSize = sizeof(SysType); // size of type on GPU side
		static constexpr const char* code = "F1"; // code used for generating signature of layout
		static constexpr bool valid = true; // metaprogramming flag to check validity of Map <param>
	};
	template<> struct Map<Float2>
	{
		using SysType = dx::XMFLOAT2;
		static constexpr size_t hlslSize = sizeof(SysType);
		static constexpr const char* code = "F2";
		static constexpr bool valid = true;
	};
	template<> struct Map<Float3>
	{
		using SysType = dx::XMFLOAT3;
		static constexpr size_t hlslSize = sizeof(SysType);
		static constexpr const char* code = "F3";
		static constexpr bool valid = true;
	};
	template<> struct Map<Float4>
	{
		using SysType = dx::XMFLOAT4;
		static constexpr size_t hlslSize = sizeof(SysType);
		static constexpr const char* code = "F4";
		static constexpr bool valid = true;
	};
	template<> struct Map<Matrix>
	{
		using SysType = dx::XMFLOAT4X4;
		static constexpr size_t hlslSize = sizeof(SysType);
		static constexpr const char* code = "M4";
		static constexpr bool valid = true;
	};
	template<> struct Map<Bool>
	{
		using SysType = bool;
		static constexpr size_t hlslSize = 4u;
		static constexpr const char* code = "BL";
		static constexpr bool valid = true;
	};

	// ensures that every leaf type in master list has an entry in the static attribute map
#define X(el) static_assert(Map<el>::valid,"Missing map implementation for " #el);
	LEAF_ELEMENT_TYPES
#undef X

	// enables reverse lookup from SysType to leaf type
	template<typename T>
	struct ReverseMap
	{
		static constexpr bool valid = false;
	};
#define X(el) \
	template<> struct ReverseMap<typename Map<el>::SysType> \
	{ \
		static constexpr Type type = el; \
		static constexpr bool valid = true; \
	};
	LEAF_ELEMENT_TYPES
#undef X
}

#ifndef DCB_IMPL_SOURCE
#undef LEAF_ELEMENT_TYPES
#endif