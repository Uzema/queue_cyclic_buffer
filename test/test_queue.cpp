#include "queue.h"
#include <gtest.h>

TEST(queue, CanCreateQueue) {
	ASSERT_NO_THROW(Queue<int> q);
}

TEST(queue, DefaultQueueIsEmpty) {
	Queue<int> q;
	ASSERT_EQ(0, q.size());
}

TEST(queue, CanCreateQueueWithSize) {
	ASSERT_NO_THROW(Queue<int> q(3));
}

TEST(queue, ThrowWhenCreateQueueWithNegativeSize) {
	ASSERT_ANY_THROW(Queue<int> q(-3));
}

TEST(queue, EmptyQueueIfEmpty) {
	Queue<int> q;
	ASSERT_EQ(true, q.empty());
}

TEST(queue, FullQueueIfFull) {
	Queue<int> q(3);
	q.push(1);
	q.push(2);
	q.push(3);
	ASSERT_EQ(true, q.full());
}

TEST(queue, CanTop) {
	Queue<int> q;
	q.push(4);
	q.push(5);
	ASSERT_EQ(4, q.top());
}

TEST(queue, CanBottom) {
	Queue<int> q;
	q.push(4);
	q.push(5);
	ASSERT_EQ(5, q.bottom());
}

TEST(queue, CanPush) {
	Queue<int> q;
	q.push(3);
	ASSERT_EQ(3, q.top());
}

TEST(queue, ThrowWhenPopInEmptyQ) {
	Queue<int> q;
	ASSERT_ANY_THROW(q.pop());
}

TEST(queue, CanPop) {
	Queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.pop();
	ASSERT_EQ(2, q.top());
}

TEST(queue, ThrowWhenTopInEmptyQ) {
	Queue<int> q;
	ASSERT_ANY_THROW(q.top());
}

TEST(queue, ThrowWhenBottomInEmptyQ) {
	Queue<int> q;
	ASSERT_ANY_THROW(q.bottom());
}

TEST(queue, PopInFullQueueAndPush) {
	Queue<int> q(3);
	q.push(1);
	q.push(2);
	q.push(3); //123
	q.pop(); //*23
	q.push(4); //423
	EXPECT_EQ(2, q.top());
	EXPECT_EQ(4, q.bottom());
}

TEST(queue, Repacking) {
	Queue<int> q(3);
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);
	EXPECT_EQ(4, q.size());
	EXPECT_EQ(1, q.top());
	EXPECT_EQ(4, q.bottom());
}


TEST(queue, PopInFullQueueAndPushWithRepacking) {
	Queue<int> q(3);
	q.push(1); //1**
	q.push(2); //12*
	q.push(3); //123
	q.pop(); //*23
	q.push(4); //423 currentSize == capacity
	q.push(5); //repacking => 2345**
	EXPECT_EQ(4, q.size());
	EXPECT_EQ(2, q.top());
	EXPECT_EQ(5, q.bottom());
}