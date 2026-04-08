
#include "xxHashModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <xxHash/xxHashTypeIds.h>

#include <Clients/xxHashSystemComponent.h>

namespace xxHash
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(xxHashModuleInterface,
        "xxHashModuleInterface", xxHashModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(xxHashModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(xxHashModuleInterface, AZ::SystemAllocator);

    xxHashModuleInterface::xxHashModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            xxHashSystemComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList xxHashModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<xxHashSystemComponent>(),
        };
    }
} // namespace xxHash
