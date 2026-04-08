
#include <xxHash/xxHashFunctions.h>
#include <xxHash/xxhash.h>

#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Script/ScriptContextAttributes.h>

#include <cstdio>

namespace xxHash
{
    void xxHashFunctions::Reflect(AZ::ReflectContext* context)
    {
        if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<xxHashFunctions>("xxHash")
                ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                ->Attribute(AZ::Script::Attributes::Category, "Hash")
                ->Method("Hash 32", &xxHashFunctions::Hash32,
                    {{{ "Input", "The string to hash" }, { "Seed", "32-bit seed value" }}})
                ->Method("Hash 64", &xxHashFunctions::Hash64,
                    {{{ "Input", "The string to hash" }, { "Seed", "64-bit seed value" }}})
                ->Method("Hash 128", &xxHashFunctions::Hash128,
                    {{{ "Input", "The string to hash" }}});
        }
    }

    AZ::u32 xxHashFunctions::Hash32(const AZStd::string& input, AZ::u32 seed)
    {
        return static_cast<AZ::u32>(XXH32(input.data(), input.size(), seed));
    }

    AZ::u64 xxHashFunctions::Hash64(const AZStd::string& input, AZ::u64 seed)
    {
        return static_cast<AZ::u64>(XXH3_64bits_withSeed(input.data(), input.size(), static_cast<XXH64_hash_t>(seed)));
    }

    AZ::Uuid xxHashFunctions::Hash128(const AZStd::string& input)
    {
        const XXH128_hash_t h = XXH3_128bits(input.data(), input.size());

        // AZ::Uuid has no raw-bytes constructor; format as a UUID hex string and parse it.
        // Layout: high64 fills the first three groups (4+2+2 bytes),
        //         low64  fills the last two groups  (2+6 bytes).
        char buf[39]; // {xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx}\0
        snprintf(buf, sizeof(buf),
            "{%08X-%04X-%04X-%04X-%012llX}",
            static_cast<unsigned int>(h.high64 >> 32),
            static_cast<unsigned int>((h.high64 >> 16) & 0xFFFF),
            static_cast<unsigned int>(h.high64 & 0xFFFF),
            static_cast<unsigned int>(h.low64 >> 48),
            static_cast<unsigned long long>(h.low64 & 0x0000FFFFFFFFFFFFull));

        return AZ::Uuid::CreateString(buf, 38);
    }

} // namespace xxHash
