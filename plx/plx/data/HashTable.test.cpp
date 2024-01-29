#include <gtest/gtest.h>

#include <test/PlxTestFixture.hpp>

#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    class HashTable_Test : public PlxTestFixture {};

    TEST_F(HashTable_Test, TestUnorderedMap1) {
        std::unordered_map<Object*, Object*> map1;
        String* abc = new String("Abc");
        String* def = new String("Def");
        String* ghi = new String("Ghi");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        map1[abc] = i100;
        map1[def] = i200;
        auto iter = map1.find(abc);
        ASSERT_NE(iter, map1.end());
        EXPECT_EQ(i100, iter->second);
        iter = map1.find(def);
        ASSERT_NE(iter, map1.end());
        EXPECT_EQ(i200, iter->second);
        iter = map1.find(ghi);
        ASSERT_EQ(iter, map1.end());
    }

    TEST_F(HashTable_Test, CreateInstance) {
        HashTable* hash1 = new HashTable();
        EXPECT_TRUE(hash1->isA(TypeId::D_HASHTABLE));
        EXPECT_EQ("HashTable", hash1->typeName());
        EXPECT_EQ(0, hash1->count());
    }

    TEST_F(HashTable_Test, BoolValue_Count_IsEmpty_Put_Get) {
        HashTable* hash1 = new HashTable();
        EXPECT_FALSE(hash1->boolValue());
        EXPECT_EQ(0, hash1->count());
        EXPECT_TRUE(hash1->isEmpty());
        String* abc = new String("abc");
        Integer* i100 = new Integer(100);
        hash1->put(abc, i100);
        EXPECT_TRUE(hash1->boolValue());
        EXPECT_EQ(1, hash1->count());
        EXPECT_FALSE(hash1->isEmpty());
        Object* value;
        EXPECT_TRUE(hash1->get(abc, value));
        EXPECT_EQ(i100, value);
        String* def = new String("def");
        Integer* i200 = new Integer(200);
        hash1->put(def, i200);
        EXPECT_TRUE(hash1->get(def, value));
        EXPECT_EQ(i200, value);
        String* ghi = new String("ghi");
        EXPECT_FALSE(hash1->get(ghi, value));
    }

    TEST_F(HashTable_Test, Equals) {
        HashTable* hash1 = new HashTable();
        HashTable* hash2 = new HashTable();
        EXPECT_TRUE(hash1->equals(hash2));
        EXPECT_TRUE(hash2->equals(hash1));
        String* abc = new String("abc");
        Integer* i100 = new Integer(100);
        hash1->put(abc, i100);
        EXPECT_FALSE(hash1->equals(hash2));
        EXPECT_FALSE(hash2->equals(hash1));
        hash2->put(abc, i100);
        EXPECT_TRUE(hash1->equals(hash2));
        EXPECT_TRUE(hash2->equals(hash1));
    }

    TEST_F(HashTable_Test, HashCodes) {
        HashTable* hash1 = new HashTable();
        String* abc_1 = new String("abc");
        String* abc_2 = new String("abc");
        {
            size_t h1 = std::hash<Object*>{}(abc_1);
            size_t h2 = std::hash<Object*>{}(abc_2);
            ASSERT_EQ(h1, h2);
        }
        Integer* i100 = new Integer(100);
        Integer* i100b = new Integer(100);
        Integer* i200 = new Integer(200);
        {
            size_t h1 = std::hash<Object*>{}(i100);
            size_t h2 = std::hash<Object*>{}(i100b);
            ASSERT_EQ(h1, h2);
            size_t h3 = std::hash<Object*>{}(i200);
            ASSERT_NE(h2, h3);
        }
        hash1->put(abc_1, i100);
        Object* elem;
        EXPECT_TRUE(hash1->get(abc_1, elem));
        EXPECT_EQ(i100, elem);
        hash1->put(abc_2, i200);
        EXPECT_TRUE(hash1->get(abc_2, elem));
        EXPECT_EQ(i200, elem);
        EXPECT_TRUE(hash1->get(abc_1, elem));
        EXPECT_EQ(i200, elem);
    }

    TEST_F(HashTable_Test, Index) {
        String* a = new String("A");
        String* b = new String("B");
        String* c = new String("C");
        Integer* i100 = new Integer(100);
        Integer* i200 = new Integer(200);
        Integer* i300 = new Integer(300);
        HashTable* hash1 = new HashTable();
        hash1->put(a, i100);
        hash1->put(b, i200);
        hash1->put(c, i300);
        Object* value;
        ASSERT_TRUE(hash1->index(a, value));
        EXPECT_EQ(i100, value);
        ASSERT_TRUE(hash1->index(b, value));
        EXPECT_EQ(i200, value);
        ASSERT_TRUE(hash1->index(c, value));
        EXPECT_EQ(i300, value);
        EXPECT_FALSE(hash1->index(new Integer(-1), value));
        EXPECT_FALSE(hash1->index(new Integer(3), value));
    }

#if 0
    TEST_F(HashTable_Test, Keys) {
        HashTable* hash1 = new HashTable();
        String* abc = new String("abc");
        Integer* i100 = new Integer(100);
        hash1->put(abc, i100);
        String* def = new String("def");
        Integer* i200 = new Integer(200);
        hash1->put(def, i200);
        Array* keyArray = hash1->keys();
        EXPECT_EQ(2, keyArray->length());
        Object* key1;
        Object* key2;
        EXPECT_TRUE(keyArray->get(0, key1));
        EXPECT_TRUE(keyArray->get(1, key2));
        EXPECT_TRUE(key1->equals(abc) || key1->equals(def));
        EXPECT_TRUE(key2->equals(abc) || key2->equals(def));
    }
#endif

    TEST_F(HashTable_Test, ShowOn) {
        {
            HashTable* hash1 = new HashTable();
            std::stringstream ss;
            ss << hash1;
            EXPECT_EQ("#{}", ss.str());
        }
        {
            HashTable* hash1 = new HashTable();
            String* a = new String("A");
            Integer* i100 = new Integer(100);
            hash1->put(a, i100);
            std::stringstream ss;
            ss << hash1;
            EXPECT_EQ("#{\"A\"=100}", ss.str());
        }
        {
            HashTable* hash1 = new HashTable();
            String* a = new String("A");
            Integer* i100 = new Integer(100);
            hash1->put(a, i100);
            String* b = new String("B");
            Integer* i200 = new Integer(200);
            hash1->put(b, i200);
            std::stringstream ss;
            ss << hash1;
            std::string expectedString1 = "#{\"A\"=100, \"B\"=200}";
            std::string expectedString2 = "#{\"B\"=200, \"A\"=100}";
            std::string actualString = ss.str();
            EXPECT_TRUE(expectedString1 == actualString || expectedString2 == actualString)
                << "Expected either '" << expectedString1 << "' or '" << expectedString2 << "'\n"
                << "Actual string = '" << actualString << "'";
        }
    }

}
