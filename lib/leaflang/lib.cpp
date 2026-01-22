#include "lib.h"

using namespace std;
using namespace swan;

size_t FindLibFunction(const Lib& lib, const string& name) {
    for (size_t i = 0; i < lib.size(); ++i) {
        if (lib[i].name == name) {
            return i;
        }
    }
    return -1;
}
