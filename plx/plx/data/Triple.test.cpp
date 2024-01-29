#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/Triple.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Triple_Test : public PlxTestFixture {};

    TEST_F(Triple_Test, CreateInstance) {
        Triple* triple1 = new Triple();
        EXPECT_TRUE(triple1->isA(TypeId::D_TRIPLE));
        EXPECT_EQ("Triple", triple1->typeName());
        EXPECT_EQ(GLOBALS->NilObject(), triple1->key());
        EXPECT_EQ(GLOBALS->NilObject(), triple1->value());
        EXPECT_EQ(triple1, triple1->next());
        String* abc = new String("abc");
        Integer* i100 = new Integer(100);
        Triple* triple2 = new Triple(abc, i100);
        EXPECT_EQ(abc, triple2->key());
        EXPECT_EQ(i100, triple2->value());
        EXPECT_TRUE(triple2->next()->isEmpty());
    }

    TEST_F(Triple_Test, BoolValue) {
        EXPECT_FALSE(GLOBALS->EmptyTriple()->boolValue());
        Triple* triple1 = new Triple();
        EXPECT_TRUE(triple1->boolValue());
    }

    TEST_F(Triple_Test, Equals) {
        Triple* triple1 = new Triple();
        String* abc = new String("abc");
        Integer* i100 = new Integer(100);
        Triple* triple2 = new Triple(abc, i100, triple1);
        EXPECT_FALSE(GLOBALS->EmptyTriple()->equals(triple1));
        EXPECT_FALSE(triple1->equals(triple2));
        Triple* triple3 = new Triple(abc, i100, triple1);
        EXPECT_TRUE(triple3->equals(triple2));
    }

    TEST_F(Triple_Test, IsEmpty) {
        EXPECT_TRUE(GLOBALS->EmptyTriple()->isEmpty());
        Triple* triple1 = new Triple();
        EXPECT_FALSE(triple1->isEmpty());
    }

    TEST_F(Triple_Test, SetGet) {
        Triple* triple1 = new Triple();
        String* abc = new String("abc");
        Integer* i100 = new Integer(100);
        Triple* triple2 = new Triple(abc, i100, triple1);
        EXPECT_EQ(abc, triple2->key());
        EXPECT_EQ(i100, triple2->value());
        EXPECT_EQ(triple1, triple2->next());
        Integer* i200 = new Integer(200);
        triple2->setValue(i200);
        EXPECT_EQ(i200, triple2->value());
    }

    TEST_F(Triple_Test, SetGet_EmptyTriple) {
        Triple* triple1 = GLOBALS->EmptyTriple();
        EXPECT_THROW(triple1->setValue(GLOBALS->NilObject()), Array*);
        EXPECT_THROW(triple1->setNext(GLOBALS->EmptyTriple()), Array*);
    }

    TEST_F(Triple_Test, ShowOn) {
        String* x = new String("x");
        Integer* i100 = new Integer(100);
        Triple* triple1 = new Triple(x, i100);
        {
            std::stringstream ss;
            ss << triple1;
            EXPECT_EQ("\"x\"=100", ss.str());
        }
        String* y = new String("y");
        Integer* i200 = new Integer(200);
        Triple* triple2 = new Triple(y, i200, triple1);
        {
            std::stringstream ss;
            ss << triple2;
            EXPECT_EQ("\"y\"=200, \"x\"=100", ss.str());
        }
        String* z = new String("z");
        Integer* i300 = new Integer(300);
        Triple* triple3 = new Triple(z, i300);
        triple3->setNext(triple2);
        {
            std::stringstream ss;
            ss << triple3;
            EXPECT_EQ("\"z\"=300, \"y\"=200, \"x\"=100", ss.str());
        }
    }

}
