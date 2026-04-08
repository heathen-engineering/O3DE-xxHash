
#pragma once

#include <AzCore/Component/Component.h>
#include <xxHash/xxHashBus.h>

namespace xxHash
{
    class xxHashSystemComponent
        : public AZ::Component
        , protected xxHashRequestBus::Handler
    {
    public:
        AZ_COMPONENT_DECL(xxHashSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        xxHashSystemComponent();
        ~xxHashSystemComponent();

    protected:
        ////////////////////////////////////////////////////////////////////////
        // xxHashRequestBus interface implementation
        AZ::u32  Hash32(const AZStd::string& input, AZ::u32 seed) override;
        AZ::u64  Hash64(const AZStd::string& input, AZ::u64 seed) override;
        AZ::Uuid Hash128(const AZStd::string& input) override;
        ////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////
        // AZ::Component interface implementation
        void Init() override;
        void Activate() override;
        void Deactivate() override;
        ////////////////////////////////////////////////////////////////////////
    };

} // namespace xxHash
