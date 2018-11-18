#include "stdafx.h"  
#include "CppUnitTest.h"  


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestDynVsCRTPCallSpeed)
{
	static constexpr unsigned N { 40000 };

	class DynamicInterface {
	public:
		virtual void tick(uint64_t n) = 0;
		virtual uint64_t getvalue() = 0;
	};

	class DynamicImplementation : public DynamicInterface {
		uint64_t counter;

	public:
		DynamicImplementation()
			: counter(0) {
		}

		virtual void tick(uint64_t n) {
			counter += n;
		}

		virtual uint64_t getvalue() {
			return counter;
		}
	};

	template <typename Implementation>
	class CRTPInterface {
	public:
		void tick(uint64_t n) {
			impl().tick(n);
		}

		uint64_t getvalue() {
			return impl().getvalue();
		}
	private:
		Implementation & impl() {
			return *static_cast<Implementation*>(this);
		}
	};

	class CRTPImplementation : public CRTPInterface<CRTPImplementation> {
		uint64_t counter;
	public:
		CRTPImplementation()
			: counter(0) {
		}

		void tick(uint64_t n) {
			counter += n;
		}

		uint64_t getvalue() {
			return counter;
		}
	};

public:

	TEST_METHOD(TestDynCallSpeed)
	{
		DynamicInterface* obj = new DynamicImplementation();

		for (unsigned i = 0; i < N; ++i) {
			for (unsigned j = 0; j < i; ++j) {
				obj->tick(j);
			}
		}

		delete obj;
		obj = nullptr;
	}

	TEST_METHOD(TestCRTPCallSpeed)
	{
		CRTPInterface<CRTPImplementation>* obj = new CRTPImplementation();
		for (unsigned i = 0; i < N; ++i) {
			for (unsigned j = 0; j < i; ++j) {
				obj->tick(j);
			}
		}

		delete obj;
		obj = nullptr;
	}
};
