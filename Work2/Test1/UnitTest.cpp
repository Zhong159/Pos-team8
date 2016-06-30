#include "stdafx.h"
#include "C:\Users\hanyu\Desktop\SoftwareEngineering\Work2\Work2\Item.h"
#include<iostream>
#include <sstream>

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace Test1
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///获取或设置测试上下文，该上下文提供
		///有关当前测试运行及其功能的信息。
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		// 编写测试时，可以使用以下附加特性: 
		//
		// 在运行类中的第一个测试之前使用 ClassInitialize 运行代码
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		// 在类中的所有测试都已运行之后使用 ClassCleanup 运行代码
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//在运行每个测试之前，使用 TestInitialize 来运行代码
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//在每个测试运行完之后，使用 TestCleanup 来运行代码
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void TestMethod1()
		{
			//
			// TODO:  在此处添加测试逻辑
			//
			Item L;
			string barcode = "ITEM000000";
			int number = 5;
			stringstream buffer;
			streambuf *old = cout.rdbuf(buffer.rdbuf());
			L.Print(barcode, number);

			string test1 = buffer.str();
			string test2 = "name:可口可乐, 数量(含赠送的一瓶) : 6, unit : 瓶, 单价 : 3.00元, 小计 : 15.00元.\n";
			bool IsEqual = (test1 == test2) ? true : false ;
            /*
			ofstream log("test1_0.txt");
			streambuf *oldbuf = cout.rdbuf(log.rdbuf());
			

			bool IsEqual;
		string s1;
			string s2;
			ifstream in1,in2;
			in1.open("test1_0.txt");
			in2.open("test1_1.txt");
			while (getline(in1, s1) && getline(in2,s2))
			{
					if (s1 != s2)
					{
						IsEqual = false;
						break;
					}
					IsEqual = true;
			};
			in1.close();
			in2.close();*/

			Assert::AreEqual(IsEqual, true);


				
		};
	};
}
