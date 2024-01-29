#pragma once

#include <cassert>
#include <iostream>
#include <list>

#include <plx/object/HashCode.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    enum class TypeId;

    class Array;
    class Evaluator;
    class GC;
    class List;
    class Queue;
    class Symbol;
    class Triple;

    class Object {
    public:
        Object();
        virtual ~Object() = default;

        virtual bool boolValue() const;
        virtual void displayOn(std::ostream& ostream) const;
        virtual bool equals(const Object* other) const;
        virtual bool hashCode(HashCode& hashCode);
        virtual bool index(Object* indexer, Object*& retrievedValue);
        virtual bool length(int& len);
        virtual TypeId typeId() const;

        // type conversions
        virtual void showOn(std::ostream& ostream) const;
        virtual bool toArray(Array*& array);
        virtual bool toList(List*& list);
        virtual bool toQueue(Queue*& queue);

        bool isA(TypeId typeId) const;
        std::string toString();
        std::string typeName() const;
        Symbol* typeSymbol() const;

        bool operator==(const Object& rhs) const;
        bool operator==(const Object* other) const;
        bool operator!=(const Object& rhs) const;

    private:

    };

    // This operator can't be a member function because the first
    // parameter is an ostream and not an Object.
    std::ostream& operator<<(std::ostream& ostream, const PLX::Object* object);

}

namespace std {
    // The std::unordered_map class needs these two struct functions.
    template <>
    struct hash<PLX::Object*> {
        size_t operator()(PLX::Object* obj) const {
            PLX::HashCode hashCode;
            assert(obj->hashCode(hashCode));
            return hashCode;
        }
    };

    template <>
    struct equal_to<PLX::Object*> {
        bool operator()(const PLX::Object* obj1, const PLX::Object* obj2) const {
            const void* vobj1 = static_cast<const void*>(obj1);
            const void* vobj2 = static_cast<const void*>(obj2);
            if (vobj1 == vobj2) {
                return true;
            }
            return obj1->equals(obj2);
        }
    };
}
