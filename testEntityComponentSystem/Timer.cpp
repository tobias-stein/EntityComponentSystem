#include "stdafx.h"  
#include "CppUnitTest.h"  

#include "util/Timer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {

	template<> inline std::wstring ToString<ECS::TimeStamp>(const ECS::TimeStamp& t) { RETURN_WIDE_STRING(t); }
}}}


namespace ECS
{
	using namespace util;

	TEST_CLASS(TimerTest)
	{
	public:

		TEST_METHOD(TestTimeStampConversion)
		{
			TimeStamp ts1;
			Assert::AreEqual((u32)ts1, 0U);

			TimeStamp ts2(123.456f), ts3(123.456f);
			Assert::IsTrue(ts2 == ts3);

			TimeStamp ts4(123.456f), ts5(123.457f);
			Assert::IsTrue(ts4 != ts5);

			TimeStamp ts6(1234.5678f);
			TimeStamp ts7;
			ts7.asUInt = ts6;
			Assert::AreEqual(1234.5678f, ts7.asFloat);
		}

		TEST_METHOD(TestTimer)
		{
			Timer t1;
			Assert::AreEqual((u32)t1.GetTimeStamp(), 0U);

			t1.Tick(100.0f);
			t1.Tick(150.0f);
			t1.Tick(10.0f);
			t1.Tick(0.5f);

			TimeStamp ts1 = t1.GetTimeStamp();
			Assert::AreEqual(ts1, TimeStamp(260.5f));

			t1.Reset();
			Assert::AreEqual((u32)t1.GetTimeStamp(), 0U);

			t1.Tick(0.5f);
			t1.Tick(10.0f);
			t1.Tick(250.0f);
			TimeStamp ts2 = t1.GetTimeStamp();

			Assert::AreEqual(ts1, ts2);
		}
	};
}