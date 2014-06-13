#pragma once

namespace Lux
{
	namespace MT
	{
		LUX_CORE_API int32_t atomicIncrement(int32_t volatile *value);
		LUX_CORE_API int32_t atomicDecrement(int32_t volatile *value);
		LUX_CORE_API int32_t atomicAdd(int32_t volatile *addend, int32_t value);
		LUX_CORE_API int32_t atomicSubtract(int32_t volatile *addend, int32_t value);
		LUX_CORE_API bool compareAndExchange(int32_t volatile* dest, int32_t exchange, int32_t comperand);
		LUX_CORE_API bool compareAndExchange64(int64_t volatile* dest, int64_t exchange, int64_t comperand);
	} // ~namespace MT
} // ~namespace Lux