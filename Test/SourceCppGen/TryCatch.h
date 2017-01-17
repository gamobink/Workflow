/***********************************************************************
Generated from ../Resources/Codegen/TryCatch.txt
***********************************************************************/

#ifndef VCZH_WORKFLOW_CPP_GENERATED_TRYCATCH
#define VCZH_WORKFLOW_CPP_GENERATED_TRYCATCH

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
	class TryCatch
	{
	public:

		::vl::WString log;

		void Test1();
		void Test2();
		void Throw(const ::vl::WString& message);
		void Test3();
		void Test4();
		::vl::WString main();

		static TryCatch& Instance();
	};
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif
