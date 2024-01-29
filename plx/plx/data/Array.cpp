#include <cassert>
#include <vector>

#include <plx/data/Array.hpp>
#include <plx/data/Queue.hpp>
#include <plx/literal/Integer.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Array::Array(int nElems)
        : Array {nElems, GLOBALS->NilObject()}
    {}

    Array::Array(int nElems, Object* initialValue)
        : _elems {static_cast<std::vector<Object*>::size_type>(nElems), initialValue}
    {}

    Array::Array(std::initializer_list<Object*> elems)
        : Array(elems.size())
    {
    int index = 0;
    for (Object* elem : elems) {
        _elems[index++] = elem;
    } 
    }

    bool Array::boolValue() const {
        if (_elems.size() == 0) {
        return false;
        } else {
        return true;
        }
    }

    bool Array::equals(const Object* other) const {
        if (this == other) {
            return true;
        }
        if (!other->isA(TypeId::D_ARRAY)) {
            return false;
        }
        const Array* otherArray = static_cast<const Array*>(other);
        if (this->_elems.size() != otherArray->_elems.size()) {
        return false;
        }

        for (size_t i = 0; i < otherArray->_elems.size(); i++) {
            if (this[i] != otherArray[i]) {
            return false;
            }
         }
        return true;
    }

    bool Array::get(int index, Object*& value) {
        if (index < 0 || index >= static_cast<int>(_elems.size())) {
            throwException("Array",
                "Index out of range",
                new Array({new Integer(index), this})
            );
        }
        value = _elems[index]; 
        return true;
    }

    bool Array::hashCode(HashCode& hashCode) {
        static const int typeHashCode = std::hash<int>{}(static_cast<int>(typeId()));
        HashCode hashCode1 = typeHashCode;
        for (Object* elem : _elems) {
            HashCode hashCode2;
            if (!elem->hashCode(hashCode2)) {
                return false;
            }
            hashCode1 = hashRotateLeft(hashCode1) ^ hashCode2;
        }
        hashCode = hashCode1;
        return true;
    }

    bool Array::index(Object* indexer, Object*& retrievedValue) {
        if (!indexer->isA(TypeId::L_INTEGER)) {
            throwException("Array", "Indexer must be an integer", 
                new Array({indexer, indexer->typeSymbol()}));
        }
        Integer* indexerInt = static_cast<Integer*>(indexer);
        int n = indexerInt->value();
        if (!get(n, retrievedValue)) {
            throw retrievedValue;
        }
        return true;
    }

    int Array::length() {
        int len;
        length(len);
        return len;
    }

    bool Array::length(int& len) {
        len = _elems.size();
        return true;
    }

    bool Array::set(int index, Object* newElem) {
        if (index < 0 || index >= static_cast<int>(_elems.size())) {
            return false;
        }
        _elems[index] = newElem;
        return true;
    }

    void Array::showOn(std::ostream& ostream) const {
        ostream << '{';
        for (std::vector<Object*>::size_type n=0; n<_elems.size(); n++) {
            if (n > 0) {
                ostream << ", ";
            }
            ostream << _elems[n];
        }
        ostream << '}';
    }

    bool Array::toArray(Array*& array) {
        array = this;
        return true;
    }

    bool Array::toList(List*& list) {
        Queue* queue;
        toQueue(queue);
        list = queue->asList();
        return true;
    }

    bool Array::toQueue(Queue*& queue) {
        queue = new Queue();
        for (Object* elem : _elems) {
            queue->enq(elem);
        }
        return true;
    }

    TypeId Array::typeId() const {
        return TypeId::D_ARRAY;
    }

}
