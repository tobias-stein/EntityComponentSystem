#include "stdafx.h"  
#include "CppUnitTest.h"  

#include "util/Handle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<> inline std::wstring ToString<ECS::util::Handle32>(const ECS::util::Handle32& t) { RETURN_WIDE_STRING(t); }
#ifndef WIN32
	template<> inline std::wstring ToString<ECS::util::Handle64>(const ECS::util::Handle64& t) { RETURN_WIDE_STRING(t); }
#endif
}}}


namespace ECS
{
	using namespace util;

	TEST_CLASS(HandleTest)
	{
	public:

		TEST_METHOD(TestHandle32)
		{
			Handle32 h0;
			Handle32 h1;
			
			Assert::AreEqual(h0, (Handle32)Handle32::INVALID_HANDLE);
			Assert::AreEqual(h0, h1);


			Assert::AreNotEqual(Handle32(Handle32::MAX_INDICES, Handle32::MAX_VERSION), (Handle32)Handle32::INVALID_HANDLE);

			Assert::AreNotEqual(Handle32(123, 1), Handle32(123, 2));
			Assert::AreNotEqual(Handle32(124, 1), Handle32(123, 1));

			Assert::AreEqual(Handle32(123, 456), Handle32(123, 456));
		}

		TEST_METHOD(TestHandle64)
		{
			Handle64 h0;
			Handle64 h1;

			Assert::AreEqual(h0, (Handle64)Handle64::INVALID_HANDLE);
			Assert::AreEqual(h0, h1);


			Assert::AreNotEqual(Handle64(Handle64::MAX_INDICES, Handle64::MAX_VERSION), (Handle64)Handle64::INVALID_HANDLE);

			Assert::AreNotEqual(Handle64(123, 1), Handle64(123, 2));
			Assert::AreNotEqual(Handle64(124, 1), Handle64(123, 1));

			Assert::AreEqual(Handle64(123, 456), Handle64(123, 456));
		}
	};
}