#include "interpreter.h"

void Interpreter::evaluate() {
    while(!tree.isEmpty()) {
        tree.takeFirst()->evaluate(symboltable);
    }
}
