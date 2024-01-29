#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/HashTable.hpp>
#include <plx/data/Triple.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class Identifier_Test : public PlxTestFixture {};

    TEST_F(Identifier_Test, CreateInstance) {
        Identifier* identifier1 = Identifier::create("Abc");
        EXPECT_TRUE(identifier1->isA(TypeId::E_IDENTIFIER));
        EXPECT_EQ("Identifier", identifier1->typeName());
        Identifier* identifier2 = Identifier::create("Abc");
        // This asserts that both identifiers are the same object
        std::cerr << "Identifier_Test " << (void*)identifier1 << ", " << (void*)identifier2 << "\n";
        ASSERT_EQ(identifier1, identifier2);
        HashCode hashCode1;
        EXPECT_TRUE(identifier1->hashCode(hashCode1));
        HashCode hashCode2;
        EXPECT_TRUE(identifier2->hashCode(hashCode2));
        EXPECT_NE(0, hashCode1);
        EXPECT_NE(0, hashCode2);
        EXPECT_EQ(hashCode1, hashCode2);
        Identifier* identifier3 = Identifier::create("Def");
        HashCode hashCode3;
        EXPECT_TRUE(identifier3->hashCode(hashCode3));
        EXPECT_NE(hashCode1, hashCode3);
        EXPECT_NE(hashCode2, hashCode3);
    }

    TEST_F(Identifier_Test, ShowOn) {
        {
            std::stringstream ss;
            Identifier* ident1 = Identifier::create("abc");
            ss << ident1;
            EXPECT_EQ("abc", ss.str());
        }
        {
            std::stringstream ss;
            Identifier* ident1 = Identifier::create("def");
            ss << ident1;
            EXPECT_EQ("def", ss.str());
        }
    }

}
