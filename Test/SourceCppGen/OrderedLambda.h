/***********************************************************************
Generated from ../Resources/Codegen/OrderedLambda.txt
***********************************************************************/

#ifndef VCZH_WORKFLOW_CPP_GENERATED_ORDEREDLAMBDA
#define VCZH_WORKFLOW_CPP_GENERATED_ORDEREDLAMBDA

#include "../Source/CppTypes.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses-equality"
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#endif


/***********************************************************************
Global Variables and Functions
***********************************************************************/

namespace vl_workflow_global
{
	class OrderedLambda
	{
	public:

		::vl::vint32_t Apply(const ::vl::Func<::vl::vint32_t(::vl::vint32_t)>& f, ::vl::vint32_t arg);
		::vl::Func<::vl::vint32_t(::vl::vint32_t)> Adder(::vl::vint32_t x);
		::vl::WString main();

		static OrderedLambda& Instance();
	};
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif
