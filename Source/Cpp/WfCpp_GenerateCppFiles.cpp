#include "WfCpp.h"

namespace vl
{
	namespace workflow
	{
		namespace cppcodegen
		{
			using namespace stream;

/***********************************************************************
GenerateCppFiles
***********************************************************************/

			WfCppInput::WfCppInput(const WString& _assemblyName)
			{
				headerGuardPrefix = L"VCZH_WORKFLOW_COMPILER_GENERATED_";
				assemblyName = _assemblyName;
				assemblyNamespace = L"vl_workflow_global";
				includeFileName = _assemblyName + L"Includes";
				defaultFileName = _assemblyName;
			}

			template<typename TCallback>
			WString GenerateToStream(const TCallback& callback)
			{
				MemoryStream stream;
				{
					StreamWriter writer(stream);
					callback(writer);
				}
				stream.SeekFromBegin(0);
				{
					StreamReader reader(stream);
					return reader.ReadToEnd();
				}
			}

			void GenerateCppComment(StreamWriter& writer, const WString& comment)
			{
				writer.WriteLine(L"/***********************************************************************");
				writer.WriteLine(L"!!!!!! DO NOT MODIFY !!!!!!");
				writer.WriteLine(L"");
				writer.WriteLine(comment);
				writer.WriteLine(L"");
				writer.WriteLine(L"This file is generated by Workflow compiler");
				writer.WriteLine(L"https://github.com/vczh-libraries");
				writer.WriteLine(L"***********************************************************************/");
			}

			Ptr<WfCppOutput> GenerateCppFiles(Ptr<WfCppInput> input, analyzer::WfLexicalScopeManager* manager)
			{
				WfCppConfig config(manager, input->assemblyName, input->assemblyNamespace);
				auto output = MakePtr<WfCppOutput>();

				bool multiFile = false;
				switch (input->multiFile)
				{
				case WfCppMultiFile::Enabled:
					multiFile = true;
					break;
				case WfCppMultiFile::Disabled:
					multiFile = false;
					break;
				default:
					multiFile = config.topLevelClassDeclsForFiles.Count() > 1;
				}

				output->cppFiles.Add(input->defaultFileName + L".h", GenerateToStream([&](StreamWriter& writer)
				{
					GenerateCppComment(writer, input->comment);
					writer.WriteLine(L"");
					writer.WriteLine(L"#ifndef " + input->headerGuardPrefix + wupper(input->defaultFileName));
					writer.WriteLine(L"#define " + input->headerGuardPrefix + wupper(input->defaultFileName));
					writer.WriteLine(L"");
					FOREACH(WString, include, input->extraIncludes)
					{
						writer.WriteLine(L"#include \"" + include + L"\"");
					}
					writer.WriteLine(L"");
					config.WriteHeader(writer, multiFile);
					writer.WriteLine(L"");
					writer.WriteLine(L"#endif");
				}));

				output->cppFiles.Add(input->defaultFileName + L".cpp", GenerateToStream([&](StreamWriter& writer)
				{
					GenerateCppComment(writer, input->comment);
					writer.WriteLine(L"");
					if (multiFile)
					{
						writer.WriteLine(L"#include \"" + input->includeFileName + L".h\"");
					}
					else
					{
						writer.WriteLine(L"#include \"" + input->defaultFileName + L".h\"");
					}
					writer.WriteLine(L"");
					config.WriteCpp(writer, multiFile);
				}));

				if (multiFile)
				{
					output->cppFiles.Add(input->includeFileName + L".h", GenerateToStream([&](StreamWriter& writer)
					{
						GenerateCppComment(writer, input->comment);
						writer.WriteLine(L"");
						writer.WriteLine(L"#ifndef " + input->headerGuardPrefix + wupper(input->includeFileName));
						writer.WriteLine(L"#define " + input->headerGuardPrefix + wupper(input->includeFileName));
						writer.WriteLine(L"");

						writer.WriteLine(L"#include \"" + input->defaultFileName + L".h\"");
						FOREACH(WString, fileName, config.topLevelClassDeclsForFiles.Keys())
						{
							if (fileName != L"")
							{
								writer.WriteLine(L"#include \"" + fileName + L".h\"");
							}
						}

						if (config.manager->declarationTypes.Count() > 0)
						{
							writer.WriteLine(L"");
							config.WriteHeader_Reflection(writer);
						}

						writer.WriteLine(L"");
						writer.WriteLine(L"#endif");
					}));

					FOREACH(WString, fileName, config.topLevelClassDeclsForFiles.Keys())
					{
						if (fileName != L"")
						{
							output->cppFiles.Add(fileName + L".h", GenerateToStream([&](StreamWriter& writer)
							{
								GenerateCppComment(writer, input->comment);
								writer.WriteLine(L"");
								writer.WriteLine(L"#ifndef " + input->headerGuardPrefix + wupper(fileName));
								writer.WriteLine(L"#define " + input->headerGuardPrefix + wupper(fileName));
								writer.WriteLine(L"");
								writer.WriteLine(L"#include \"" + input->defaultFileName + L".h\"");
								writer.WriteLine(L"");
								config.WriteSubHeader(writer, fileName);
								writer.WriteLine(L"");
								writer.WriteLine(L"#endif");
							}));

							output->cppFiles.Add(fileName + L".cpp", GenerateToStream([&](StreamWriter& writer)
							{
								GenerateCppComment(writer, input->comment);
								writer.WriteLine(L"");
								writer.WriteLine(L"#include \"" + input->includeFileName + L".h\"");
								writer.WriteLine(L"");
								config.WriteSubCpp(writer, fileName);
							}));
						}
					}
				}

				return output;
			}
		}
	}
}
