#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Queue_Test : public PlxTestFixture {};

    TEST_F(Queue_Test, CreateInstance) {
        Queue* q1 = new Queue();
        EXPECT_TRUE(q1->isA(TypeId::D_QUEUE));
        EXPECT_EQ("Queue", q1->typeName());
        EXPECT_EQ(0, q1->length());
        EXPECT_THROW(q1->deq(), Array*);
    }

    TEST_F(Queue_Test, CreateWithMultipleObjects) {
        Queue* q1 = new Queue({
            GLOBALS->NilObject(),
            GLOBALS->NilObject(),
            GLOBALS->NilObject()
        });
        EXPECT_EQ(3, q1->length());
    }

    TEST_F(Queue_Test, BoolValue) {
        Queue* q1 = new Queue();
        EXPECT_FALSE(q1->boolValue());
        q1->enq(new Integer(100));
        EXPECT_TRUE(q1->boolValue());
    }

    TEST_F(Queue_Test, EnqDeq) {
        Queue* q1 = new Queue();
        Integer* i100 = new Integer(100);
        EXPECT_TRUE(q1->isEmpty());
        EXPECT_EQ(0, q1->length());
        q1->enq(i100);
        EXPECT_FALSE(q1->isEmpty());
        EXPECT_EQ(1, q1->length());
        Integer* i200 = new Integer(200);
        q1->enq(i200);
        EXPECT_EQ(2, q1->length());
        Integer* i300 = new Integer(300);
        q1->enq(i300);
        EXPECT_EQ(3, q1->length());
        Object* elem = q1->deq();
        EXPECT_EQ(2, q1->length());
        EXPECT_EQ(i100, elem);
        elem = q1->deq();
        EXPECT_EQ(1, q1->length());
        EXPECT_EQ(i200, elem);
        elem = q1->deq();
        EXPECT_EQ(0, q1->length());
        EXPECT_EQ(i300, elem);
        EXPECT_TRUE(q1->isEmpty());
        EXPECT_EQ(0, q1->length());
        EXPECT_THROW(q1->deq(), Array*);
    }

    TEST_F(Queue_Test, EnqList) {
        Queue* q1 = new Queue();
        q1->enq({GLOBALS->NilObject(), GLOBALS->NilObject(), GLOBALS->NilObject()});
        EXPECT_EQ(3, q1->length());
    }

    TEST_F(Queue_Test, Equals) {
        Queue* q1 = new Queue();
        Queue* q2 = new Queue();
        EXPECT_TRUE(q1->equals(q2));
        EXPECT_TRUE(q2->equals(q1));
        Integer* i100 = new Integer(100);
        q1->enq(i100);
        EXPECT_FALSE(q1->equals(q2));
        EXPECT_FALSE(q2->equals(q1));
        q2->enq(i100);
        EXPECT_TRUE(q1->equals(q2));
        EXPECT_TRUE(q2->equals(q1));
        Integer* i200 = new Integer(200);
        q1->enq(i200);
        EXPECT_FALSE(q1->equals(q2));
        EXPECT_FALSE(q2->equals(q1));
        q2->enq(i200);
        EXPECT_TRUE(q1->equals(q2));
        EXPECT_TRUE(q2->equals(q1));
    }

    TEST_F(Queue_Test, IsEmpty) {
        Queue *q1 = new Queue();
        EXPECT_TRUE(q1->isEmpty());
        Integer *i100 = new Integer(100);
        q1->enq(i100);
        EXPECT_FALSE(q1->isEmpty());
    }

    TEST_F(Queue_Test, Length) {
        Queue* q1 = new Queue();
        EXPECT_EQ(0, q1->length());
        Integer* i100 = new Integer(100);
        q1->enq(i100);
        EXPECT_EQ(1, q1->length());
        Integer* i200 = new Integer(200);
        q1->enq(i200);
        EXPECT_EQ(2, q1->length());
    }

    TEST_F(Queue_Test, ShowOn) {
        Queue* q1 = new Queue();
        {
            std::stringstream ss;
            ss << q1;
            EXPECT_EQ("~[]", ss.str());
        }
        q1->enq(new Integer(100));
        {
            std::stringstream ss;
            ss << q1;
            EXPECT_EQ("~[100]", ss.str());
        }
        q1->enq(new Integer(200));
        {
            std::stringstream ss;
            ss << q1;
            EXPECT_EQ("~[100, 200]", ss.str());
        }
        q1->enq(new Integer(300));
        {
            std::stringstream ss;
            ss << q1;
            EXPECT_EQ("~[100, 200, 300]", ss.str());
        }
        q1->deq();
        {
            std::stringstream ss;
            ss << q1;
            EXPECT_EQ("~[200, 300]", ss.str());
        }
        q1->deq();
        {
            std::stringstream ss;
            ss << q1;
            EXPECT_EQ("~[300]", ss.str());
        }
        q1->deq();
        {
            std::stringstream ss;
            ss << q1;
            EXPECT_EQ("~[]", ss.str());
        }
    }

    TEST_F(Queue_Test, ToArray) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Queue* queue1 = new Queue({i100, i200, i300});
        Array* array1;
        EXPECT_TRUE(queue1->toArray(array1));
        Array* expectedArray = new Array({i100, i200, i300});
        EXPECT_EQ(*expectedArray, *array1);
    }

    TEST_F(Queue_Test, ToList) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Queue* queue1 = new Queue({i100, i200, i300});
        List* list1;
        EXPECT_TRUE(queue1->toList(list1));
        List* expectedList = List::create({i100, i200, i300});
        EXPECT_EQ(*expectedList, *list1);
    }

}
