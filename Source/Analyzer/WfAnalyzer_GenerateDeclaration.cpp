#include "WfAnalyzer.h"

namespace vl
{
	namespace workflow
	{
		namespace analyzer
		{
			using namespace collections;
			using namespace parsing;
			using namespace reflection;
			using namespace reflection::description;
			using namespace runtime;
			using namespace typeimpl;

			typedef WfInstruction Ins;

#define INSTRUCTION(X) context.AddInstruction(node, X)

/***********************************************************************
GenerateInstructions(Initialize)
***********************************************************************/

			class GenerateInitializeInstructionsVisitor : public Object, public WfDeclaration::IVisitor
			{
			public:
				WfCodegenContext&						context;

				GenerateInitializeInstructionsVisitor(WfCodegenContext& _context)
					:context(_context)
				{
				}

				void Visit(WfNamespaceDeclaration* node)override
				{
					FOREACH(Ptr<WfDeclaration>, decl, node->declarations)
					{
						GenerateInitializeInstructions(context, decl);
					}
				}

				void Visit(WfFunctionDeclaration* node)override
				{
				}

				void Visit(WfVariableDeclaration* node)override
				{
					auto scope = context.manager->declarationScopes[node].Obj();
					auto symbol = scope->symbols[node->name.value][0];
					vint variableIndex = context.globalVariables[symbol.Obj()];
					GenerateExpressionInstructions(context, node->expression);
					INSTRUCTION(Ins::StoreGlobalVar(variableIndex));
				}

				void Visit(WfEventDeclaration* node)override
				{
				}

				void Visit(WfPropertyDeclaration* node)override
				{
				}

				void Visit(WfClassDeclaration* node)override
				{
				}
			};

			void GenerateInitializeInstructions(WfCodegenContext& context, Ptr<WfDeclaration> declaration)
			{
				GenerateInitializeInstructionsVisitor visitor(context);
				declaration->Accept(&visitor);
			}

/***********************************************************************
GenerateInstructions(Declaration)
***********************************************************************/

			Ptr<WfCodegenFunctionContext> GenerateFunctionInstructions_Prolog(WfCodegenContext& context, WfLexicalScope* scope, Ptr<WfAssemblyFunction> meta, Ptr<ITypeInfo> returnType, Ptr<WfLexicalSymbol> recursiveLambdaSymbol, const List<Ptr<WfLexicalSymbol>>& argumentSymbols, const List<Ptr<WfLexicalSymbol>>& capturedSymbols, ParsingTreeCustomBase* node)
			{
				auto functionContext = MakePtr<WfCodegenFunctionContext>();
				functionContext->function = meta;
				context.functionContext = functionContext;
				{
					FOREACH_INDEXER(Ptr<WfLexicalSymbol>, argumentSymbol, index, argumentSymbols)
					{
						functionContext->arguments.Add(argumentSymbol.Obj(), index);
					}
					FOREACH_INDEXER(Ptr<WfLexicalSymbol>, capturedSymbol, index, capturedSymbols)
					{
						functionContext->capturedVariables.Add(capturedSymbol.Obj(), index);
					}
				}
				if (recursiveLambdaSymbol)
				{
					vint variableIndex = meta->argumentNames.Count() + meta->localVariableNames.Add(L"<recursive-lambda>" + recursiveLambdaSymbol->name);
					functionContext->localVariables.Add(recursiveLambdaSymbol.Obj(), variableIndex);
				}
					
				meta->firstInstruction = context.assembly->instructions.Count();
				if (recursiveLambdaSymbol)
				{
					for (vint i = 0; i < functionContext->capturedVariables.Count(); i++)
					{
						INSTRUCTION(Ins::LoadCapturedVar(i));
					}
					INSTRUCTION(Ins::LoadClosure(context.assembly->functions.IndexOf(meta.Obj()), functionContext->capturedVariables.Count()));
					INSTRUCTION(Ins::StoreLocalVar(functionContext->localVariables[recursiveLambdaSymbol.Obj()]));
				}
				return functionContext;
			}

			void GenerateFunctionInstructions_Epilog(WfCodegenContext& context, WfLexicalScope* scope, Ptr<WfAssemblyFunction> meta, Ptr<ITypeInfo> returnType, Ptr<WfLexicalSymbol> recursiveLambdaSymbol, const List<Ptr<WfLexicalSymbol>>& argumentSymbols, const List<Ptr<WfLexicalSymbol>>& capturedSymbols, Ptr<WfCodegenFunctionContext> functionContext, ParsingTreeCustomBase* node)
			{
				if (returnType->GetDecorator() == ITypeInfo::TypeDescriptor && returnType->GetTypeDescriptor()->GetValueSerializer())
				{
					auto serializer = returnType->GetTypeDescriptor()->GetValueSerializer();
					auto defaultText = serializer->GetDefaultText();
					Value result;
					serializer->Parse(defaultText, result);
					INSTRUCTION(Ins::LoadValue(result));
				}
				else
				{
					INSTRUCTION(Ins::LoadValue(Value()));
				}
				INSTRUCTION(Ins::Return());
				meta->lastInstruction = context.assembly->instructions.Count() - 1;
				context.functionContext = 0;

				GenerateClosureInstructions(context, functionContext);
			}

			void GenerateFunctionInstructions(WfCodegenContext& context, WfLexicalScope* scope, Ptr<WfAssemblyFunction> meta, Ptr<ITypeInfo> returnType, Ptr<WfLexicalSymbol> recursiveLambdaSymbol, const List<Ptr<WfLexicalSymbol>>& argumentSymbols, const List<Ptr<WfLexicalSymbol>>& capturedSymbols, Ptr<WfStatement> statementBody, ParsingTreeCustomBase* node)
			{
				auto functionContext = GenerateFunctionInstructions_Prolog(context, scope, meta, returnType, recursiveLambdaSymbol, argumentSymbols, capturedSymbols, node);
				GenerateStatementInstructions(context, statementBody);
				GenerateFunctionInstructions_Epilog(context, scope, meta, returnType, recursiveLambdaSymbol, argumentSymbols, capturedSymbols, functionContext, node);
			}

			void GenerateFunctionInstructions(WfCodegenContext& context, WfLexicalScope* scope, Ptr<WfAssemblyFunction> meta, Ptr<ITypeInfo> returnType, Ptr<WfLexicalSymbol> recursiveLambdaSymbol, const List<Ptr<WfLexicalSymbol>>& argumentSymbols, const List<Ptr<WfLexicalSymbol>>& capturedSymbols, Ptr<WfExpression> expressionBody, ParsingTreeCustomBase* node)
			{
				auto functionContext = GenerateFunctionInstructions_Prolog(context, scope, meta, returnType, recursiveLambdaSymbol, argumentSymbols, capturedSymbols, node);
				GenerateExpressionInstructions(context, expressionBody);
				INSTRUCTION(Ins::Return());
				GenerateFunctionInstructions_Epilog(context, scope, meta, returnType, recursiveLambdaSymbol, argumentSymbols, capturedSymbols, functionContext, node);
			}

			void GenerateFunctionDeclarationInstructions(WfCodegenContext& context, WfFunctionDeclaration* node, WfLexicalScope* scope, Ptr<WfAssemblyFunction> meta, Ptr<WfLexicalSymbol> recursiveLambdaSymbol)
			{
				List<Ptr<WfLexicalSymbol>> argumentSymbols, capturedSymbols;
				{
					FOREACH(Ptr<WfFunctionArgument>, argument, node->arguments)
					{
						auto symbol = scope->symbols[argument->name.value][0];
						argumentSymbols.Add(symbol);
					}

					vint index = context.manager->functionLambdaCaptures.Keys().IndexOf(node);
					if (index != -1)
					{
						FOREACH(Ptr<WfLexicalSymbol>, symbol, context.manager->functionLambdaCaptures.GetByIndex(index))
						{
							capturedSymbols.Add(symbol);
						}
					}
				}

				auto returnType = CreateTypeInfoFromType(scope, node->returnType);
				GenerateFunctionInstructions(context, scope, meta, returnType, recursiveLambdaSymbol, argumentSymbols, capturedSymbols, node->statement, node);
			}

			class GenerateClassMemberInstructionsVisitor : public Object, public WfDeclaration::IVisitor
			{
			public:
				WfCodegenContext&						context;
				Ptr<WfClassDeclaration>					classDecl;
				Ptr<WfClassMember>						member;

				GenerateClassMemberInstructionsVisitor(WfCodegenContext& _context, Ptr<WfClassDeclaration> _classDecl, Ptr<WfClassMember> _member)
					:context(_context)
					, classDecl(_classDecl)
					, member(_member)
				{
				}

				void Visit(WfNamespaceDeclaration* node)override
				{
				}

				void Visit(WfFunctionDeclaration* node)override
				{
					if (member->kind == WfClassMemberKind::Static)
					{
						GenerateDeclarationInstructions(context, node);
					}
					else if (classDecl->kind == WfClassKind::Class)
					{
						throw 0;
					}
				}

				void Visit(WfVariableDeclaration* node)override
				{
					throw 0;
				}

				void Visit(WfEventDeclaration* node)override
				{
				}

				void Visit(WfPropertyDeclaration* node)override
				{
				}

				void Visit(WfClassDeclaration* node)override
				{
					GenerateDeclarationInstructions(context, node);
				}
			};

			class GenerateDeclarationInstructionsVisitor : public Object, public WfDeclaration::IVisitor
			{
			public:
				WfCodegenContext&						context;

				GenerateDeclarationInstructionsVisitor(WfCodegenContext& _context)
					:context(_context)
				{
				}

				void Visit(WfNamespaceDeclaration* node)override
				{
					FOREACH(Ptr<WfDeclaration>, decl, node->declarations)
					{
						GenerateDeclarationInstructions(context, decl);
					}
				}

				void Visit(WfFunctionDeclaration* node)override
				{
					auto scope = context.manager->declarationScopes[node].Obj();
					auto symbol = context.manager->GetDeclarationSymbol(scope, node);
					auto meta = context.assembly->functions[context.globalFunctions[symbol.Obj()]];
					GenerateFunctionDeclarationInstructions(context, node, scope, meta, 0);
				}

				void Visit(WfVariableDeclaration* node)override
				{
				}

				void Visit(WfEventDeclaration* node)override
				{
				}

				void Visit(WfPropertyDeclaration* node)override
				{
				}

				void Visit(WfClassDeclaration* node)override
				{
					FOREACH(Ptr<WfClassMember>, member, node->members)
					{
						GenerateClassMemberInstructionsVisitor visitor(context, node, member);
						member->declaration->Accept(&visitor);
					}
				}
			};

			void GenerateDeclarationInstructions(WfCodegenContext& context, Ptr<WfDeclaration> declaration)
			{
				GenerateDeclarationInstructionsVisitor visitor(context);
				declaration->Accept(&visitor);
			}

/***********************************************************************
GenerateInstructions(Closure)
***********************************************************************/

			void GenerateClosureInstructions_Function(WfCodegenContext& context, vint functionIndex, WfFunctionDeclaration* node, bool createInterface)
			{
				auto scope = context.manager->declarationScopes[node].Obj();
				auto meta = context.assembly->functions[functionIndex];
				GenerateFunctionDeclarationMetadata(context, node, meta);
				Ptr<WfLexicalSymbol> recursiveLambdaSymbol;
				if (!createInterface && node->name.value != L"")
				{
					recursiveLambdaSymbol = scope->symbols[node->name.value][0];
				}
				GenerateFunctionDeclarationInstructions(context, node, scope, meta, recursiveLambdaSymbol);
			}

			void GenerateClosureInstructions_Ordered(WfCodegenContext& context, vint functionIndex, WfOrderedLambdaExpression* node)
			{
				auto scope = context.manager->expressionScopes[node].Obj();
				List<Ptr<WfLexicalSymbol>> argumentSymbols, capturedSymbols;
				CopyFrom(
					argumentSymbols,
					Range<vint>(0, scope->symbols.Count())
						.Select([scope](vint index)->Ptr<WfLexicalSymbol>{return scope->symbols.GetByIndex(index)[0];})
						.OrderBy([](Ptr<WfLexicalSymbol> a, Ptr<WfLexicalSymbol> b)
						{
							vint aId = wtoi(a->name.Sub(1, a->name.Length() - 1));
							vint bId = wtoi(b->name.Sub(1, a->name.Length() - 1));
							return aId - bId;
						})
					);

				auto meta = context.assembly->functions[functionIndex];
				FOREACH(Ptr<WfLexicalSymbol>, symbol, argumentSymbols)
				{
					meta->argumentNames.Add(symbol->name);
				}
				{
					vint index = context.manager->orderedLambdaCaptures.Keys().IndexOf(node);
					if (index != -1)
					{
						FOREACH(Ptr<WfLexicalSymbol>, symbol, context.manager->orderedLambdaCaptures.GetByIndex(index))
						{
							meta->capturedVariableNames.Add(L"<captured>" + symbol->name);
							capturedSymbols.Add(symbol);
						}
					}
				}

				auto result = context.manager->expressionResolvings[node];
				auto returnType = CopyTypeInfo(result.type->GetElementType()->GetGenericArgument(0));
				GenerateFunctionInstructions(context, scope, meta, returnType, 0, argumentSymbols, capturedSymbols, node->body, node);
			}

			void GenerateClosureInstructions(WfCodegenContext& context, Ptr<WfCodegenFunctionContext> functionContext)
			{
				for (vint i = 0; i < functionContext->closuresToCodegen.Count(); i++)
				{
					vint functionIndex = functionContext->closuresToCodegen.Keys()[i];
					auto closure = functionContext->closuresToCodegen.Values()[i];
					
					if (closure.functionExpression)
					{
						GenerateClosureInstructions_Function(context, functionIndex, closure.functionExpression->function.Obj(), false);
					}
					else if (closure.orderedLambdaExpression)
					{
						GenerateClosureInstructions_Ordered(context, functionIndex, closure.orderedLambdaExpression);
					}
					else if (closure.functionDeclaration)
					{
						GenerateClosureInstructions_Function(context, functionIndex, closure.functionDeclaration, true);
					}
				}
			}

#undef INSTRUCTION
		}
	}
}