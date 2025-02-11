#define DEBUG_CONVERSION_STACK_PRINT(result, opStack) {Teto::TetoStack copy = result;\
while (!copy.isEmpty()) {\
    if (copy.getTop().isOp) {\
        std::cout << copy.pop().data.op << " ";\
    }\
    else {\
        std::cout << copy.pop().data.value << " ";\
    }\
}\
std::cout << "||||| ";\
Teto::TetoStack copy2 = opStack;\
while (!copy2.isEmpty()) {\
    if (copy2.getTop().isOp) {\
        std::cout << copy2.pop().data.op << " ";\
    }\
    else {\
        std::cout << copy2.pop().data.value << " ";\
    }\
}\
std::cout << std::endl;}
