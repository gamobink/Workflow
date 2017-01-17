/***********************************************************************
Generated from ../Resources/Codegen/Property.txt
***********************************************************************/

#include "Property.h"

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses-equality"
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#endif
#define GLOBAL_SYMBOL ::vl_workflow_global::Property::
#define GLOBAL_NAME ::vl_workflow_global::Property::Instance().
#define GLOBAL_OBJ &::vl_workflow_global::Property::Instance()

/***********************************************************************
Global Variables and Functions
***********************************************************************/

BEGIN_GLOBAL_STORAGE_CLASS(vl_workflow_global_Property)
	vl_workflow_global::Property instance;
	INITIALIZE_GLOBAL_STORAGE_CLASS
	FINALIZE_GLOBAL_STORAGE_CLASS
END_GLOBAL_STORAGE_CLASS(vl_workflow_global_Property)

namespace vl_workflow_global
{
	::vl::WString Property::main()
	{
		auto x = [&](){ ::test::Point __vwsn_temp__; __vwsn_temp__.x = 10; __vwsn_temp__.y = 20; return __vwsn_temp__; }();
		auto y = ::vl::Ptr<::test::ObservableValue>(new ::test::ObservableValue(10));
		auto s1 = ((((((((::vl::__vwsn::ToString(x.x) + ::vl::WString(L", ", false)) + ::vl::__vwsn::ToString(x.y)) + ::vl::WString(L", ", false)) + ::vl::__vwsn::ToString(::vl::__vwsn::This(y.Obj())->GetValue())) + ::vl::WString(L", ", false)) + ::vl::__vwsn::This(y.Obj())->GetName()) + ::vl::WString(L", ", false)) + ::vl::__vwsn::This(y.Obj())->GetDisplayName());
		::vl::__vwsn::This(y.Obj())->SetValue(20);
		::vl::__vwsn::This(y.Obj())->SetName(::vl::WString(L"Workflow", false));
		auto s2 = ((((::vl::__vwsn::ToString(::vl::__vwsn::This(y.Obj())->GetValue()) + ::vl::WString(L", ", false)) + ::vl::__vwsn::This(y.Obj())->GetName()) + ::vl::WString(L", ", false)) + ::vl::__vwsn::This(y.Obj())->GetDisplayName());
		return ((s1 + ::vl::WString(L", ", false)) + s2);
	}

	Property& Property::Instance()
	{
		return Getvl_workflow_global_Property().instance;
	}
}

#undef GLOBAL_SYMBOL
#undef GLOBAL_NAME
#undef GLOBAL_OBJ

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
