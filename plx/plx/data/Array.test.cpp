#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/data/Triple.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Array_Test : public PlxTestFixture {};


    TEST_F(Array_Test, CreateInstance) {
        Array* a3 = new Array(3);
        EXPECT_TRUE(a3->isA(TypeId::D_ARRAY));
        EXPECT_EQ("Array", a3->typeName());
        EXPECT_EQ(3, a3->length());
        for (int n=0; n<3; n++) {
            Object* elem;
            EXPECT_TRUE(a3->get(n, elem));
            EXPECT_EQ(GLOBALS->NilObject(), elem);
        }
    }



    TEST_F(Array_Test, CreateFromList) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Array* a3 = new Array({i100, i200, i300});
        EXPECT_EQ(3, a3->length());
        Object* elem;
        EXPECT_TRUE(a3->get(0, elem));
        EXPECT_EQ(i100, elem);
        EXPECT_TRUE(a3->get(1, elem));
        EXPECT_EQ(i200, elem);
        EXPECT_TRUE(a3->get(2, elem));
        EXPECT_EQ(i300, elem);
    }



    TEST_F(Array_Test, BoolValue) {
        Array* a0 = new Array(0);
        Array* a1 = new Array(1);
        EXPECT_FALSE(a0->boolValue());
        EXPECT_TRUE(a1->boolValue());
    }



    TEST_F(Array_Test, Equals) {
        Array* a3a = new Array(3);
        Array* a3b = new Array(3);
        Array* a3c = new Array(3);
        Array* a4 = new Array(4);
        a3c->set(2, new Integer(123));
        EXPECT_TRUE(a3a->equals(a3b));
        EXPECT_EQ(*a3a, *a3b);
        EXPECT_TRUE(a3b->equals(a3a));
        EXPECT_EQ(*a3b, *a3a);
        EXPECT_FALSE(a3a->equals(a3c));
        EXPECT_NE(*a3a, *a3c);
        EXPECT_FALSE(a3c->equals(a4));
        EXPECT_NE(*a3c, *a4);
    }



    TEST_F(Array_Test, HashCode) {
        Integer* i100_1 = new Integer(100);
        Integer* i100_2 = new Integer(100);
        Array* a3_1 = new Array(3);
        a3_1->set(1, i100_1);
        Array* a3_2 = new Array(3);
        a3_2->set(1, i100_2);
        HashCode hashCode1;
        EXPECT_TRUE(a3_1->hashCode(hashCode1));
        HashCode hashCode2;
        EXPECT_TRUE(a3_2->hashCode(hashCode2));
        EXPECT_EQ(hashCode1, hashCode2);
        Array* a0 = new Array(0);
        HashCode hashCode3;
        EXPECT_TRUE(a0->hashCode(hashCode3));
        EXPECT_NE(hashCode1, hashCode3);
        EXPECT_NE(hashCode2, hashCode3);
    }



    TEST_F(Array_Test, Index) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Array* a3 = new Array({i100, i200, i300});
        Object* value;
        ASSERT_TRUE(a3->index(new Integer(0), value));
        EXPECT_EQ(i100, value);
        ASSERT_TRUE(a3->index(new Integer(1), value));
        EXPECT_EQ(i200, value);
        ASSERT_TRUE(a3->index(new Integer(2), value));
        EXPECT_EQ(i300, value);
        EXPECT_THROW(a3->index(new Integer(-1), value), Array*);
        EXPECT_THROW(a3->index(new Integer(3), value), Array*);
    }



    TEST_F(Array_Test, Length) {
        Array* a0 = new Array(0);
        Array* a1 = new Array(1);
        Array* a2 = new Array(2);
        EXPECT_EQ(0, a0->length());
        EXPECT_EQ(1, a1->length());
        EXPECT_EQ(2, a2->length());
    }



    TEST_F(Array_Test, SetGet) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Array* a3 = new Array({i100, i200, i300});
        Object* elem;
        EXPECT_THROW(a3->get(-1, elem), Array*);
        EXPECT_TRUE(a3->get(0, elem));
        EXPECT_EQ(i100, elem);
        EXPECT_TRUE(a3->get(1, elem));
        EXPECT_EQ(i200, elem);
        EXPECT_TRUE(a3->get(2, elem));
        EXPECT_EQ(i300, elem);
        EXPECT_THROW(a3->get(3, elem), Array*);
    }


    TEST_F(Array_Test, GetOutOfBounds) {
        Array* array = new Array(0);
        Object* value = nullptr;
        EXPECT_THROW(array->get(0, value), Array*);
    }



    TEST_F(Array_Test, ShowOn) {
        {
            std::stringstream ss;
            ss << GLOBALS->NilObject();
            EXPECT_EQ("nil", ss.str());
        }
        {
            Array* a0 = new Array(0);
            std::stringstream ss;
            ss << a0;
            EXPECT_EQ("{}", ss.str());
        }
        {
            Array* a1 = new Array(1);
            std::stringstream ss;
            ss << a1;
            EXPECT_EQ("{nil}", ss.str());
        }
        {
            Array* a2 = new Array(2);
            std::stringstream ss;
            ss << a2;
            EXPECT_EQ("{nil, nil}", ss.str());
        }
    }



    TEST_F(Array_Test, ToList) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Array* array = new Array({i100, i200, i300});
        List* list1;
        EXPECT_TRUE(array->toList(list1));
        List* expectedList = List::create({i100, i200, i300});
        EXPECT_EQ(*expectedList, *list1);
    }



    TEST_F(Array_Test, ToQueue) {
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        Array* array = new Array({i100, i200, i300});
        Queue* queue1;
        EXPECT_TRUE(array->toQueue(queue1));
        Queue* expectedQueue = new Queue({i100, i200, i300});
        EXPECT_EQ(*expectedQueue, *queue1);
    }


}
