#pragma once

namespace PLX {

    class GC;
    class Globals;
    class HashTable;
    class List;
    class Triple;
    class Function;
    class Boolean;
    class Nil;
    class Symbol;
    class P_Data;
    class P_Literal;

    extern Globals* GLOBALS;

    class Globals {
    public:
        Globals();
        ~Globals();

        void initializeAll();

        // The function names are capitalized because otherwise some of the
        // names collide with intrinsic C++ names (like true and false).
        HashTable* IdentifierInternTable();
        HashTable* SymbolInternTable();
        void SetArgMap(HashTable* argMap);
        HashTable* ArgMap();
        Triple* EmptyTriple();
        List* EmptyList();
        Boolean* True();
        Boolean* False();
        Nil* NilObject();
        Triple* DynamicEnvironment();
        Symbol* BooleanSymbol();
        Symbol* EoiSymbol();
        Symbol* IdentifierSymbol();
        Symbol* IntegerSymbol();
        Symbol* NilSymbol();
        Symbol* ParseIgnoreSymbol();
        Symbol* ReservedSymbol();
        Symbol* SpecialSymbol();
        Symbol* StringSymbol();
        Symbol* SymbolSymbol();

    private:
        HashTable* _identifierInternTable {nullptr};
        HashTable* _symbolInternTable {nullptr};
        HashTable* _argMap {nullptr};
        List* _emptyList {nullptr};
        Triple* _emptyTriple {nullptr};
        Nil* _nil {nullptr};
        Triple* _dynamicEnvironment {nullptr};
        Boolean* _true {nullptr};
        Boolean* _false {nullptr};
        Symbol* _booleanSymbol {nullptr};
        Symbol* _eoiSymbol {nullptr};
        Symbol* _identifierSymbol {nullptr};
        Symbol* _integerSymbol {nullptr};
        Symbol* _nilSymbol {nullptr};
        Symbol* _parseIgnoreSymbol {nullptr};
        Symbol* _reservedSymbol {nullptr};
        Symbol* _specialSymbol {nullptr};
        Symbol* _stringSymbol {nullptr};
        Symbol* _symbolSymbol {nullptr};
    };

}
