
#pragma once

#include <AzCore/EBus/EBus.h>
#include <AzCore/Interface/Interface.h>
#include <AzCore/Math/Uuid.h>
#include <AzCore/std/string/string.h>

namespace xxHash
{
    class xxHashRequests
    {
    public:
        AZ_RTTI(xxHashRequests, "{1EAEF250-A464-49C6-8657-3E0C88B26CC4}");
        virtual ~xxHashRequests() = default;

        //! Compute a 32-bit xxHash of the given string with an optional seed.
        virtual AZ::u32 Hash32(const AZStd::string& input, AZ::u32 seed) = 0;

        //! Compute a 64-bit xxHash of the given string with an optional seed.
        virtual AZ::u64 Hash64(const AZStd::string& input, AZ::u64 seed) = 0;

        //! Compute a 128-bit xxHash (XXH3) of the given string. Returns as AZ::Uuid.
        virtual AZ::Uuid Hash128(const AZStd::string& input) = 0;
    };

    class xxHashBusTraits
        : public AZ::EBusTraits
    {
    public:
        static constexpr AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Single;
        static constexpr AZ::EBusAddressPolicy AddressPolicy = AZ::EBusAddressPolicy::Single;
    };

    using xxHashRequestBus = AZ::EBus<xxHashRequests, xxHashBusTraits>;
    using xxHashInterface = AZ::Interface<xxHashRequests>;

} // namespace xxHash
