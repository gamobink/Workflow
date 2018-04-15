/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

Source: ../Resources/Codegen/CoAsync2.txt

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#include "CoAsync2Reflection.h"

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
			IMPL_CPP_TYPE_INFO(CoAsync2_types::IStringAsync)

#define _ ,
			BEGIN_INTERFACE_MEMBER(::CoAsync2_types::IStringAsync)
				CLASS_MEMBER_BASE(::vl::reflection::description::IAsync)
				CLASS_MEMBER_STATIC_METHOD(CastResult, { L"value" })
				CLASS_MEMBER_STATIC_METHOD(StoreResult, { L"value" })
			END_INTERFACE_MEMBER(::CoAsync2_types::IStringAsync)

#undef _
			class CoAsync2TypeLoader : public Object, public ITypeLoader
			{
			public:
				void Load(ITypeManager* manager)
				{
					ADD_TYPE_INFO(::CoAsync2_types::IStringAsync)
				}

				void Unload(ITypeManager* manager)
				{
				}
			};
#endif

			bool LoadCoAsync2Types()
			{
#ifndef VCZH_DEBUG_NO_REFLECTION
				if (auto manager = GetGlobalTypeManager())
				{
					return manager->AddTypeLoader(MakePtr<CoAsync2TypeLoader>());
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
