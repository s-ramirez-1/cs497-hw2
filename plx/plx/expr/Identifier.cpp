#include <plx/data/Array.hpp>
#include <plx/data/HashTable.hpp>
#include <plx/data/List.hpp>
#include <plx/data/Triple.hpp>
#include <plx/expr/Identifier.hpp>
#include <plx/literal/Nil.hpp>
#include <plx/literal/String.hpp>
#include <plx/object/Globals.hpp>
#include <plx/object/Object.hpp>
#include <plx/object/TypeIds.hpp>

namespace PLX {

    Identifier* Identifier::create(const std::string& name) {
        String* stringName = new String(name);
        HashCode hashCode;
        stringName->hashCode(hashCode);
        Object* identifierObj;
        Identifier* identifier;
        HashTable* internTable = GLOBALS->IdentifierInternTable();
        if (internTable->get(stringName, identifierObj)) {
            identifier = static_cast<Identifier*>(identifierObj);
        }
        else {
            identifier = new Identifier(name);
            internTable->put(stringName, identifier);
        }
        return identifier;
    }

    Identifier::Identifier(const std::string& name)
        : Symbolic(name)
    {}

    TypeId Identifier::typeId() const {
        return TypeId::E_IDENTIFIER;
    }

}
