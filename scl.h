#ifndef SCL_INCLUDED
#define SCL_INCLUDED
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>

namespace scl{
    struct Chunk{
        int size = 0;
        int allocated = 0;
        uint8_t* data = nullptr;
        void m_realloc() {
            allocated *= 18;
            allocated /= 10;
            allocated += 1;
            data = (uint8_t*)realloc(data, allocated);
            //std::cout << "Reallocation, allocated " << allocated << std::endl;
        }
        inline void add(uint8_t val) {
            if (size == allocated) m_realloc();
            data[size++] = val;
        }
        void clear() {free(data);}

    };
    enum class ValueType{
        VAL_INT,
        VAL_BOOL,
        VAL_OBJ,
    };
    enum class ObjType{
        OBJ_FUNCTION, 
        OBJ_STRING
    };
    struct Obj{
        ObjType type;
    };
    struct Value {
        ValueType type;
        union {
            bool as_bool;
            int as_int;
            Obj* as_obj;
        };
    };
    struct _VM{
        int sp = 0;
        int pp = 0;
        Chunk* program_data;
        void reset() {}
    };
    inline _VM vm;

    enum OPCODE{
        OP_NOP,
        OP_PUSH_CONSTANT,
        OP_POP,
        
        OP_ADD,
        OP_SUB,
        OP_MULT,
        OP_DIV,
        
        
    };
    void run(Chunk* data);
}
#endif
#ifdef SCL_IMPLEMENTATION

void run_instr() {
    switch(vm->program_data) {
        case OP_NOP: return;
        case OP_PUSH: return;
    }
}
void scl::run(Chunk* data) {
    vm.reset();
    vm->program_data = data;
    while (vm->pp < vm->program_data.size) {
        run_instr();
    } 
}
#endif
