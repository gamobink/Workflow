/***********************************************************************
Generated from ../Resources/Codegen/TryFinally.txt
***********************************************************************/

#ifndef VCZH_WORKFLOW_CPP_GENERATED_TRYFINALLY
#define VCZH_WORKFLOW_CPP_GENERATED_TRYFINALLY

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
	class TryFinally
	{
	public:

		::vl::vint32_t sum = 0;

		void test1();
		void test2();
		void test3();
		void test4();
		::vl::WString main();

		static TryFinally& Instance();
	};
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif
