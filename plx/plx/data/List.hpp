#pragma once

#include <list>

#include <plx/object/Object.hpp>

namespace PLX {

    class Array;

    class List : public Object {
    public:
        List();
        List(Object* first);
        List(Object* first, Object* rest);

        // Unique functions ------------------------------------------------

        static List* create(std::initializer_list<Object*> elems);

        Object* first();
        Object* second();
        Object* third();
        Object* rest();
        List* restAsList() const;
        bool isEmpty() const;
        int length() const;
        List* locate(Object* obj);
        List* reverse();
        void setFirst(Object* first);
        void setRest(Object* rest);
        void showOnWith(std::ostream& ostream, const std::string& open, const std::string& sep, const std::string& close) const;

        // Overloaded functions --------------------------------------------

        bool boolValue() const override;
        bool equals(const Object* other) const override;
        bool hashCode(HashCode& hashCode) override;
        bool length(int& len) override;
        void showOn(std::ostream& ostream) const override;
        bool toArray(Array*& array) override;
        bool toList(List*& list) override;
        bool toQueue(Queue*& queue) override;
        TypeId typeId() const override;

    private:
        Object* _first;
        Object* _rest;
    };

}
