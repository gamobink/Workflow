/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

Source: ../Resources/Codegen/WorkflowAttributes.txt

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#ifndef VCZH_WORKFLOW_COMPILER_GENERATED_WORKFLOWATTRIBUTES
#define VCZH_WORKFLOW_COMPILER_GENERATED_WORKFLOWATTRIBUTES

#include "../Source/CppTypes.h"

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

namespace calculator
{
	class Expression;
	class NumberExpression;
	class BinaryExpression;

	class Expression : public ::vl::Object, public ::vl::reflection::Description<Expression>
	{
#ifndef VCZH_DEBUG_NO_REFLECTION
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<Expression>;
#endif
	public:
		Expression();
	};

	class NumberExpression : public ::calculator::Expression, public ::vl::reflection::Description<NumberExpression>
	{
#ifndef VCZH_DEBUG_NO_REFLECTION
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<NumberExpression>;
#endif
	private:
		::vl::vint32_t value = 0;
	public:
		::vl::vint32_t GetValue();
		void SetValue(::vl::vint32_t _value);
		NumberExpression(::vl::vint32_t _value);
	};

	class BinaryExpression : public ::calculator::Expression, public ::vl::reflection::Description<BinaryExpression>
	{
#ifndef VCZH_DEBUG_NO_REFLECTION
		friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<BinaryExpression>;
#endif
	public:
		enum class BinaryOperator : vl::vuint64_t
		{
			Add = 0UL,
			Sub = 1UL,
			Mul = 2UL,
			Div = 3UL,
		};

	private:
		::calculator::BinaryExpression::BinaryOperator op = ::calculator::BinaryExpression::BinaryOperator::Add;
	public:
		::calculator::BinaryExpression::BinaryOperator GetOp();
		void SetOp(::calculator::BinaryExpression::BinaryOperator _value);
	private:
		::vl::Ptr<::calculator::Expression> left = ::vl::Ptr<::calculator::Expression>();
	public:
		::vl::Ptr<::calculator::Expression> GetLeft();
		void SetLeft(::vl::Ptr<::calculator::Expression> _value);
	private:
		::vl::Ptr<::calculator::Expression> right = ::vl::Ptr<::calculator::Expression>();
	public:
		::vl::Ptr<::calculator::Expression> GetRight();
		void SetRight(::vl::Ptr<::calculator::Expression> _value);
		BinaryExpression(::vl::Ptr<::calculator::Expression> _left, ::calculator::BinaryExpression::BinaryOperator _op, ::vl::Ptr<::calculator::Expression> _right);
	};
	inline ::calculator::BinaryExpression::BinaryOperator operator& (::calculator::BinaryExpression::BinaryOperator a, ::calculator::BinaryExpression::BinaryOperator b) { return static_cast<::calculator::BinaryExpression::BinaryOperator>(static_cast<::vl::vuint64_t>(a) & static_cast<::vl::vuint64_t>(b)); }
	inline ::calculator::BinaryExpression::BinaryOperator operator| (::calculator::BinaryExpression::BinaryOperator a, ::calculator::BinaryExpression::BinaryOperator b) { return static_cast<::calculator::BinaryExpression::BinaryOperator>(static_cast<::vl::vuint64_t>(a) | static_cast<::vl::vuint64_t>(b)); }

}
/***********************************************************************
Global Variables and Functions
***********************************************************************/

namespace vl_workflow_global
{
	class WorkflowAttributes
	{
	public:

		::vl::WString Print(::vl::Ptr<::calculator::Expression> expr);
		::vl::vint32_t Evaluate(::vl::Ptr<::calculator::Expression> expr);
		::vl::WString main();

		static WorkflowAttributes& Instance();
	};
}

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
			DECL_TYPE_INFO(::calculator::BinaryExpression)
			DECL_TYPE_INFO(::calculator::BinaryExpression::BinaryOperator)
			DECL_TYPE_INFO(::calculator::Expression)
			DECL_TYPE_INFO(::calculator::NumberExpression)
#endif

			extern bool LoadWorkflowAttributesTypes();
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

#endif
