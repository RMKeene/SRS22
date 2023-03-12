#include "pch.h"
#include "CppUnitTest.h"

#include "tinyfloat.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SRS22
{
	TEST_CLASS(SRS22Test)
	{
	public:

		TEST_METHOD(TinyFloatTest)
		{
			tinyfloat tf(0.12345f);
			Assert::AreEqual(0.12345f, tinyfloat::tf2f(tf), tinyfloat::TINYFLOATTOLLERANCE);

			tf = tinyfloat((tinyfloatprim)5);
			Assert::AreEqual(-1.92188f, tinyfloat::tf2f(tf), tinyfloat::TINYFLOATTOLLERANCE);
			
			tf = 1.1234f;
			Assert::AreEqual(1.1234f, tinyfloat::tf2f(tf), tinyfloat::TINYFLOATTOLLERANCE);
			
			tf = 0.0f;
			Assert::AreEqual(0.0f, tinyfloat::tf2f(tf), tinyfloat::TINYFLOATTOLLERANCE);
			Assert::AreEqual((tinyfloatprim)128, tf.v);
		}
	};
}
