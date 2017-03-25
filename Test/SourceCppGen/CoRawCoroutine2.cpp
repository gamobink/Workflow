/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

Source: ../Resources/Codegen/CoRawCoroutine2.txt

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#include "CoRawCoroutine2.h"

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

#define GLOBAL_SYMBOL ::vl_workflow_global::CoRawCoroutine2::
#define GLOBAL_NAME ::vl_workflow_global::CoRawCoroutine2::Instance().
#define GLOBAL_OBJ &::vl_workflow_global::CoRawCoroutine2::Instance()
#define USERIMPL(...)

/***********************************************************************
Global Variables
***********************************************************************/

BEGIN_GLOBAL_STORAGE_CLASS(vl_workflow_global_CoRawCoroutine2)
	vl_workflow_global::CoRawCoroutine2 instance;
	INITIALIZE_GLOBAL_STORAGE_CLASS

		instance.s = ::vl::WString(L"", false);
	FINALIZE_GLOBAL_STORAGE_CLASS

		instance.s = ::vl::WString::Empty;
END_GLOBAL_STORAGE_CLASS(vl_workflow_global_CoRawCoroutine2)

namespace vl_workflow_global
{
/***********************************************************************
Global Functions
***********************************************************************/

	::vl::WString CoRawCoroutine2::main()
	{
		auto coroutine = ::vl::Ptr<::vl::reflection::description::ICoroutine>(new ::vl_workflow_global::__vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine());
		{
			auto i = 0;
			while ((::vl::__vwsn::This(coroutine.Obj())->GetStatus() != ::vl::reflection::description::CoroutineStatus::Stopped))
			{
				::vl::__vwsn::This(coroutine.Obj())->Resume(true);
				(GLOBAL_NAME s = ((((::vl::WString(L"", false) + GLOBAL_NAME s) + ::vl::WString(L"[-", false)) + ::vl::__vwsn::ToString(i)) + ::vl::WString(L"]", false)));
				(i = (i + 1));
			}
		}
		return GLOBAL_NAME s;
	}

	CoRawCoroutine2& CoRawCoroutine2::Instance()
	{
		return Getvl_workflow_global_CoRawCoroutine2().instance;
	}

/***********************************************************************
Closures
***********************************************************************/

	//-------------------------------------------------------------------

	__vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine::__vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine()
	{
		this->__vwsn_co0_switch_0 = 0;
		this->__vwsn_co1_for_begin_i = 0;
		this->__vwsn_co2_for_end_i = 0;
		this->__vwsn_co3_i = 0;
		this->__vwsn_co4_ex = ::vl::Ptr<::vl::reflection::description::IValueException>();
		this->__vwsn_co_state_ = 0;
		this->__vwsn_prop_Failure = ::vl::Ptr<::vl::reflection::description::IValueException>();
		this->__vwsn_prop_Status = ::vl::reflection::description::CoroutineStatus::Waiting;
	}

	::vl::Ptr<::vl::reflection::description::IValueException> __vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine::GetFailure()
	{
		return __vwsn_prop_Failure;
	}
	void __vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine::SetFailure(::vl::Ptr<::vl::reflection::description::IValueException> __vwsn_value_)
	{
		(__vwsn_prop_Failure = __vwsn_value_);
	}

	::vl::reflection::description::CoroutineStatus __vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine::GetStatus()
	{
		return __vwsn_prop_Status;
	}
	void __vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine::SetStatus(::vl::reflection::description::CoroutineStatus __vwsn_value_)
	{
		(__vwsn_prop_Status = __vwsn_value_);
	}

	void __vwsnc1_CoRawCoroutine2_main__vl_reflection_description_ICoroutine::Resume(bool __vwsn_raise_exception_)
	{
		if ((::vl::__vwsn::This(this)->GetStatus() != ::vl::reflection::description::CoroutineStatus::Waiting))
		{
			throw ::vl::Exception(::vl::WString(L"Resume should be called only when the coroutine is in the waiting status.", false));
		}
		::vl::__vwsn::This(this)->SetStatus(::vl::reflection::description::CoroutineStatus::Executing);
		try
		{
			{
				while (true)
				{
					if ((__vwsn_co_state_ == 0))
					{
						(__vwsn_co1_for_begin_i = 0);
						(__vwsn_co2_for_end_i = (4 - 1));
						(__vwsn_co3_i = __vwsn_co1_for_begin_i);
						if ((__vwsn_co3_i <= __vwsn_co2_for_end_i))
						{
							(__vwsn_co_state_ = 5);
							continue;
						}
						(__vwsn_co_state_ = 1);
						continue;
					}
					else if ((__vwsn_co_state_ == 1))
					{
						::vl::__vwsn::This(this)->SetStatus(::vl::reflection::description::CoroutineStatus::Stopped);
						return;
					}
					else if ((__vwsn_co_state_ == 2))
					{
						(__vwsn_co3_i = (__vwsn_co3_i + 1));
						if ((__vwsn_co3_i <= __vwsn_co2_for_end_i))
						{
							(__vwsn_co_state_ = 5);
							continue;
						}
						(__vwsn_co_state_ = 1);
						continue;
					}
					else if ((__vwsn_co_state_ == 3))
					{
						{
							(GLOBAL_NAME s = ((::vl::WString(L"", false) + GLOBAL_NAME s) + ::vl::WString(L"!", false)));
						}
						throw ::vl::Exception(::vl::__vwsn::This(__vwsn_co4_ex.Obj())->GetMessage());
					}
					else if ((__vwsn_co_state_ == 4))
					{
						try
						{
							{
								{
									(GLOBAL_NAME s = ((((::vl::WString(L"", false) + GLOBAL_NAME s) + ::vl::WString(L"[", false)) + ::vl::__vwsn::This(__vwsn_co4_ex.Obj())->GetMessage()) + ::vl::WString(L"]", false)));
								}
							}
						}
						catch(const ::vl::Exception& __vwsne_1)
						{
							auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_1.Message());
							{
								(__vwsn_co4_ex = __vwsn_co_ex_);
								(__vwsn_co_state_ = 3);
								continue;
							}
						}
						catch(const ::vl::Error& __vwsne_1)
						{
							auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_1.Description());
							{
								(__vwsn_co4_ex = __vwsn_co_ex_);
								(__vwsn_co_state_ = 3);
								continue;
							}
						}
						(__vwsn_co_state_ = 7);
						continue;
					}
					else if ((__vwsn_co_state_ == 5))
					{
						try
						{
							{
								(__vwsn_co0_switch_0 = (__vwsn_co3_i % 2));
								if ((__vwsn_co0_switch_0 == 0))
								{
									(GLOBAL_NAME s = ((((::vl::WString(L"", false) + GLOBAL_NAME s) + ::vl::WString(L"[+", false)) + ::vl::__vwsn::ToString(__vwsn_co3_i)) + ::vl::WString(L"]", false)));
									(__vwsn_co_state_ = 6);
									continue;
								}
								if ((__vwsn_co0_switch_0 == 1))
								{
									{
										throw ::vl::Exception(::vl::WString(L"*", false));
									}
									(__vwsn_co_state_ = 7);
									continue;
								}
							}
						}
						catch(const ::vl::Exception& __vwsne_2)
						{
							auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_2.Message());
							{
								(__vwsn_co4_ex = __vwsn_co_ex_);
								(__vwsn_co_state_ = 4);
								continue;
							}
						}
						catch(const ::vl::Error& __vwsne_2)
						{
							auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_2.Description());
							{
								(__vwsn_co4_ex = __vwsn_co_ex_);
								(__vwsn_co_state_ = 4);
								continue;
							}
						}
						(__vwsn_co_state_ = 7);
						continue;
					}
					else if ((__vwsn_co_state_ == 6))
					{
						::vl::__vwsn::This(this)->SetStatus(::vl::reflection::description::CoroutineStatus::Waiting);
						(__vwsn_co_state_ = 7);
						try
						{
							{
								return;
							}
						}
						catch(const ::vl::Exception& __vwsne_3)
						{
							auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_3.Message());
							{
								(__vwsn_co4_ex = __vwsn_co_ex_);
								(__vwsn_co_state_ = 4);
								continue;
							}
						}
						catch(const ::vl::Error& __vwsne_3)
						{
							auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_3.Description());
							{
								(__vwsn_co4_ex = __vwsn_co_ex_);
								(__vwsn_co_state_ = 4);
								continue;
							}
						}
					}
					else if ((__vwsn_co_state_ == 7))
					{
						{
							(GLOBAL_NAME s = ((::vl::WString(L"", false) + GLOBAL_NAME s) + ::vl::WString(L"!", false)));
						}
						(__vwsn_co_state_ = 2);
						continue;
					}
				}
			}
		}
		catch(const ::vl::Exception& __vwsne_0)
		{
			auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_0.Message());
			{
				::vl::__vwsn::This(this)->SetFailure(__vwsn_co_ex_);
				::vl::__vwsn::This(this)->SetStatus(::vl::reflection::description::CoroutineStatus::Stopped);
				if (__vwsn_raise_exception_)
				{
					throw;
				}
			}
		}
		catch(const ::vl::Error& __vwsne_0)
		{
			auto __vwsn_co_ex_ = ::vl::reflection::description::IValueException::Create(__vwsne_0.Description());
			{
				::vl::__vwsn::This(this)->SetFailure(__vwsn_co_ex_);
				::vl::__vwsn::This(this)->SetStatus(::vl::reflection::description::CoroutineStatus::Stopped);
				if (__vwsn_raise_exception_)
				{
					throw;
				}
			}
		}
	}

}

#undef GLOBAL_SYMBOL
#undef GLOBAL_NAME
#undef GLOBAL_OBJ
#undef USERIMPL

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
