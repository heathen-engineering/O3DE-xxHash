
#pragma once

namespace xxHash
{
    // System Component TypeIds
    inline constexpr const char* xxHashSystemComponentTypeId = "{F04CB34E-CAE4-4DBF-9040-B057136C8790}";
    inline constexpr const char* xxHashEditorSystemComponentTypeId = "{7E9C4210-C404-4AED-8C6B-A2CB918E0DA8}";

    // Module derived classes TypeIds
    inline constexpr const char* xxHashModuleInterfaceTypeId = "{6FB37186-1B5B-4454-AC0C-38E53A0D5337}";
    inline constexpr const char* xxHashModuleTypeId = "{6A476E61-F545-4410-81E5-8676F656C44F}";
    // The Editor Module by default is mutually exclusive with the Client Module
    // so they use the Same TypeId
    inline constexpr const char* xxHashEditorModuleTypeId = xxHashModuleTypeId;

    // Interface TypeIds
    inline constexpr const char* xxHashRequestsTypeId = "{8EA611A8-1EC4-49A9-A13C-59B013C63451}";

    // Utility class TypeIds
    inline constexpr const char* xxHashFunctionsTypeId = "{3F8A2B1C-D4E5-6F70-98AB-CDEF01234567}";
} // namespace xxHash
