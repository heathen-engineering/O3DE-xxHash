
#pragma once

#include <AzCore/Math/Uuid.h>
#include <AzCore/RTTI/ReflectContext.h>
#include <AzCore/RTTI/TypeInfoSimple.h>
#include <AzCore/std/string/string.h>

#include <xxHash/xxHashTypeIds.h>

namespace xxHash
{
    //! Pure static helper class that exposes xxHash algorithms to C++ and O3DE scripting.
    //! Reflected to BehaviorContext as "xxHash" — produces Hash 32, Hash 64, and Hash 128
    //! nodes directly in the Script Canvas palette.
    //!
    //! For raw byte-buffer access or advanced APIs (streaming, secret seeds) include
    //! <xxHash/xxhash.h> and call the xxHash C API directly.
    class xxHashFunctions
    {
    public:
        AZ_TYPE_INFO(xxHashFunctions, xxHashFunctionsTypeId);
        static void Reflect(AZ::ReflectContext* context);

        //! Compute a 32-bit hash (XXH32) of the given string.
        static AZ::u32  Hash32(const AZStd::string& input, AZ::u32 seed);

        //! Compute a 64-bit hash (XXH3_64bits) of the given string.
        static AZ::u64  Hash64(const AZStd::string& input, AZ::u64 seed);

        //! Compute a 128-bit xxHash (XXH3_128bits) of the given string.
        //! Returns an AZ::Uuid — a first-class O3DE type usable in serialization,
        //! Script Canvas, Lua, and AZStd containers without any additional setup.
        static AZ::Uuid Hash128(const AZStd::string& input);
    };

} // namespace xxHash
