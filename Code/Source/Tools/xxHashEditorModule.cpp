
#include <xxHash/xxHashTypeIds.h>
#include <xxHashModuleInterface.h>
#include "xxHashEditorSystemComponent.h"

namespace xxHash
{
    class xxHashEditorModule
        : public xxHashModuleInterface
    {
    public:
        AZ_RTTI(xxHashEditorModule, xxHashEditorModuleTypeId, xxHashModuleInterface);
        AZ_CLASS_ALLOCATOR(xxHashEditorModule, AZ::SystemAllocator);

        xxHashEditorModule()
        {
            m_descriptors.insert(m_descriptors.end(), {
                xxHashEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<xxHashEditorSystemComponent>(),
            };
        }
    };
}// namespace xxHash

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), xxHash::xxHashEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_xxHash_Editor, xxHash::xxHashEditorModule)
#endif
