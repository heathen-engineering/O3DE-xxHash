
#include "xxHashSystemComponent.h"

#include <xxHash/xxHashTypeIds.h>
#include <xxHash/xxHashFunctions.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace xxHash
{
    AZ_COMPONENT_IMPL(xxHashSystemComponent, "xxHashSystemComponent",
        xxHashSystemComponentTypeId);

    void xxHashSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<xxHashSystemComponent, AZ::Component>()
                ->Version(0);
        }

        xxHashFunctions::Reflect(context);
    }

    void xxHashSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("xxHashService"));
    }

    void xxHashSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("xxHashService"));
    }

    void xxHashSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void xxHashSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    xxHashSystemComponent::xxHashSystemComponent()
    {
        if (xxHashInterface::Get() == nullptr)
        {
            xxHashInterface::Register(this);
        }
    }

    xxHashSystemComponent::~xxHashSystemComponent()
    {
        if (xxHashInterface::Get() == this)
        {
            xxHashInterface::Unregister(this);
        }
    }

    void xxHashSystemComponent::Init()
    {
    }

    void xxHashSystemComponent::Activate()
    {
        xxHashRequestBus::Handler::BusConnect();
    }

    void xxHashSystemComponent::Deactivate()
    {
        xxHashRequestBus::Handler::BusDisconnect();
    }

    AZ::u32 xxHashSystemComponent::Hash32(const AZStd::string& input, AZ::u32 seed)
    {
        return xxHashFunctions::Hash32(input, seed);
    }

    AZ::u64 xxHashSystemComponent::Hash64(const AZStd::string& input, AZ::u64 seed)
    {
        return xxHashFunctions::Hash64(input, seed);
    }

    AZ::Uuid xxHashSystemComponent::Hash128(const AZStd::string& input)
    {
        return xxHashFunctions::Hash128(input);
    }

} // namespace xxHash
