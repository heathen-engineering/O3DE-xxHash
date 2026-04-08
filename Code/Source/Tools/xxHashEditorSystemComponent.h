
#pragma once

#include <Clients/xxHashSystemComponent.h>

namespace xxHash
{
    class xxHashEditorSystemComponent
        : public xxHashSystemComponent
    {
        using BaseSystemComponent = xxHashSystemComponent;
    public:
        AZ_COMPONENT_DECL(xxHashEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        xxHashEditorSystemComponent();
        ~xxHashEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        void Activate() override;
        void Deactivate() override;
    };
} // namespace xxHash
