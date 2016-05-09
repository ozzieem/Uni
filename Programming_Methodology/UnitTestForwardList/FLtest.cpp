#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForwardList
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(FLSort)
		{
			forwardList<int> list;
			list.push_back(6);
			list.push_back(5);
			list.push_back(4);
			list.push_back(1);
			list.push_back(3);
			list.push_back(9);

			Assert::AreEqual(6, list.front());
			Assert::AreEqual(9, list.last());

			list.sortInt();

			Assert::AreEqual(1, list.front());
			Assert::AreEqual(9, list.last());
		}

		TEST_METHOD(FLIterator)
		{
			forwardList<int> list;
			list.push_front(1);
			list.push_front(2);
			list.push_front(3);
			list.push_front(4);

			Assert::AreEqual(true, list.begin()->data == 4);
			Assert::AreEqual(false, list.begin()->next == nullptr);
			Assert::AreEqual(true, list.end() == nullptr);
		}

		TEST_METHOD(FLContainsValue)
		{
			forwardList<int> list;

			list.push_front(2);
			list.push_front(1);

			Assert::AreEqual(false, list.contains(3));
			Assert::AreEqual(true, list.contains(2));
			Assert::AreEqual(true, list.contains(1));
		}

		TEST_METHOD(FLIsEmpty)
		{
			forwardList<int> list;

			list.push_front(2);

			Assert::AreEqual(false, list.empty());
		}

		TEST_METHOD(FLPopFront)
		{
			forwardList<int> list;

			list.push_front(2);
			list.push_front(1);

			list.pop_front();

			Assert::AreEqual(2, list.front());
		}

		TEST_METHOD(FLPop)
		{
			forwardList<int> list;

			list.push_back(3);
			list.push_back(2);
			list.push_back(1);

			Assert::AreEqual(3, list.front());

			list.pop(0);

			Assert::AreEqual(2, list.front());
		}

		TEST_METHOD(FLPushFront)
		{
			forwardList<int> list;

			list.push_front(2);
			Assert::AreEqual(2, list.front());

			list.push_front(1);

			list.push_front(3);
			Assert::AreEqual(3, list.front());
		}

		TEST_METHOD(FLPushBack)
		{
			forwardList<int> list;

			list.push_back(2);
			list.push_back(1);
			list.push_back(3);

			Assert::AreEqual(2, list.front());
			Assert::AreEqual(2, list.begin()->data);
			Assert::AreEqual(1, list.begin()->next->data);
			Assert::AreEqual(3, list.begin()->next->next->data);
		}

		TEST_METHOD(FLCopyList)
		{
			forwardList<int> list1;

			list1.push_front(1);
			list1.push_front(2);
			list1.push_front(3);

			forwardList<int> list2(list1);

			Assert::AreEqual(list1.front(), list2.front());
		}

		TEST_METHOD(FLClearList)
		{
			forwardList<int> list;

			list.push_front(1);
			list.push_front(2);
			list.push_front(3);

			Assert::AreEqual(false, list.empty());

			list.clear();

			Assert::AreEqual(true, list.empty());
		}

		TEST_METHOD(FLListSize)
		{
			forwardList<int> list;

			list.push_front(1);
			list.push_front(2);
			list.push_front(3);

			Assert::AreEqual(3, list.max_size());

			list.pop_front();

			Assert::AreEqual(2, list.max_size());
		}

		TEST_METHOD(FLInsertAfter)
		{
			forwardList<int> list;

			list.push_front(4);
			list.insert_after(list.begin(), 7);
			list.insert_after(list.begin()->next, 10);

			Assert::AreEqual(4, list.begin()->data);
			Assert::AreEqual(7, list.begin()->next->data);
			Assert::AreEqual(10, list.begin()->next->next->data);
		}

		TEST_METHOD(FLEraseAfter)
		{
			forwardList<int> list;
			list.push_front(4);
			list.push_front(7);
			list.push_front(10);

			Assert::AreEqual(10, list.begin()->data);
			Assert::AreEqual(7, list.begin()->next->data);
			Assert::AreEqual(4, list.begin()->next->next->data);
			list.erase_after(list.begin());
			Assert::AreEqual(4, list.begin()->next->data);
		}
	};
}

