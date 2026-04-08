
#include <xxHash/xxHashTypeIds.h>
#include <xxHashModuleInterface.h>
#include "xxHashSystemComponent.h"

namespace xxHash
{
    class xxHashModule
        : public xxHashModuleInterface
    {
    public:
        AZ_RTTI(xxHashModule, xxHashModuleTypeId, xxHashModuleInterface);
        AZ_CLASS_ALLOCATOR(xxHashModule, AZ::SystemAllocator);
    };
}// namespace xxHash

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), xxHash::xxHashModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_xxHash, xxHash::xxHashModule)
#endif
