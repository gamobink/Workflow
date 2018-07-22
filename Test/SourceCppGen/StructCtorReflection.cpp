/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

Source: ../Resources/Codegen/StructCtor.txt

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#include "StructCtorReflection.h"

#if defined( _MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses-equality"
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#endif

/***********************************************************************
Reflection
***********************************************************************/

namespace vl
{
	namespace reflection
	{
		namespace description
		{
#ifndef VCZH_DEBUG_NO_REFLECTION
			IMPL_CPP_TYPE_INFO(depended_structs::A)
			IMPL_CPP_TYPE_INFO(depended_structs::B)
			IMPL_CPP_TYPE_INFO(depended_structs::C)
			IMPL_CPP_TYPE_INFO(depended_structs::D)

#define _ ,
			BEGIN_STRUCT_MEMBER(::depended_structs::A)
				STRUCT_MEMBER(data)
			END_STRUCT_MEMBER(::depended_structs::A)

			BEGIN_STRUCT_MEMBER(::depended_structs::B)
				STRUCT_MEMBER(data)
			END_STRUCT_MEMBER(::depended_structs::B)

			BEGIN_STRUCT_MEMBER(::depended_structs::C)
				STRUCT_MEMBER(data)
			END_STRUCT_MEMBER(::depended_structs::C)

			BEGIN_STRUCT_MEMBER(::depended_structs::D)
				STRUCT_MEMBER(data)
			END_STRUCT_MEMBER(::depended_structs::D)

#undef _
			class StructCtorTypeLoader : public Object, public ITypeLoader
			{
			public:
				void Load(ITypeManager* manager)
				{
					ADD_TYPE_INFO(::depended_structs::A)
					ADD_TYPE_INFO(::depended_structs::B)
					ADD_TYPE_INFO(::depended_structs::C)
					ADD_TYPE_INFO(::depended_structs::D)
				}

				void Unload(ITypeManager* manager)
				{
				}
			};
#endif

			bool LoadStructCtorTypes()
			{
#ifndef VCZH_DEBUG_NO_REFLECTION
				if (auto manager = GetGlobalTypeManager())
				{
					return manager->AddTypeLoader(MakePtr<StructCtorTypeLoader>());
				}
#endif
				return false;
			}
		}
	}
}

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
