
#include <AzCore/Serialization/SerializeContext.h>

#include "xxHashEditorSystemComponent.h"

#include <xxHash/xxHashTypeIds.h>

namespace xxHash
{
    AZ_COMPONENT_IMPL(xxHashEditorSystemComponent, "xxHashEditorSystemComponent",
        xxHashEditorSystemComponentTypeId, BaseSystemComponent);

    void xxHashEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<xxHashEditorSystemComponent, xxHashSystemComponent>()
                ->Version(0);
        }
    }

    xxHashEditorSystemComponent::xxHashEditorSystemComponent() = default;

    xxHashEditorSystemComponent::~xxHashEditorSystemComponent() = default;

    void xxHashEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("xxHashEditorService"));
    }

    void xxHashEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("xxHashEditorService"));
    }

    void xxHashEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void xxHashEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void xxHashEditorSystemComponent::Activate()
    {
        xxHashSystemComponent::Activate();
    }

    void xxHashEditorSystemComponent::Deactivate()
    {
        xxHashSystemComponent::Deactivate();
    }

} // namespace xxHash
