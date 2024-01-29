#include <cassert>
#include <list>
#include <sstream>

#include <plx/data/Array.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Queue.hpp>
#include <plx/data/Triple.hpp>
#include <plx/literal/String.hpp>
#include <plx/literal/Symbol.hpp>
#include <plx/object/HashCode.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/ThrowException.hpp>
#include <plx/object/TypeIds.hpp>

#include <unordered_map>

namespace PLX {

    std::ostream& operator<<(std::ostream& ostream, const PLX::Object* object) {
        object->showOn(ostream);
        return ostream;
    }

    bool Object::operator==(const Object& rhs) const {
        return this->equals(&rhs);
    }

    bool Object::operator==(const Object* rhs) const {
        return this->equals(rhs);
    }

    bool Object::operator!=(const Object& rhs) const {
        return !this->equals(&rhs);
    }

    Object::Object() {
    }

    bool Object::boolValue() const {
        return true;
    }

    void Object::displayOn(std::ostream& ostream) const {
        showOn(ostream);
    }

    bool Object::equals(const Object* other) const {
        // The pointers must be cast to void* in case the == operator is
        // ever in the future overloaded to handle Object*.
        const void* thisPtr = static_cast<const void*>(this);
        const void* otherPtr = static_cast<const void*>(other);
        return thisPtr == otherPtr;
    }

    bool Object::hashCode(HashCode& hashCode) {
        (void)hashCode;
        Array* payload = new Array({this, this->typeSymbol()});
        throwException("Object", "Object is not hashable", payload);
        return false;
    }

    bool Object::index(Object* indexer, Object*& retrievedValue) {
        (void)indexer;
        (void)retrievedValue;
        return false;
    }

    bool Object::isA(TypeId typeId) const {
        return (this->typeId()) == typeId;
    }

    bool Object::length(int& len) {
        (void)len;
        return false;
    }

    void Object::showOn(std::ostream& ostream) const {
        ostream << "Object@" << static_cast<const void*>(this);
    }

    bool Object::toArray(Array*& array) {
        (void)array;
        return false;
    }

    bool Object::toList(List*& list) {
        (void)list;
        return false;
    }

    bool Object::toQueue(Queue*& queue) {
        (void)queue;
        return false;
    }

    std::string Object::toString() {
        std::ostringstream ss;
        ss << this;
        return ss.str();
    }

    TypeId Object::typeId() const {
        return TypeId::T_OBJECT;
    }

    std::string Object::typeName() const {
        return TYPE_NAMES[typeId()];
    }

    Symbol* Object::typeSymbol() const {
        return Symbol::create(typeName());
    }

}
