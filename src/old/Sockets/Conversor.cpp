#include <iostream>
#include <bitset>
using namespace std;
char conversorBinarioTexto(const char* str) {
    char parsed = 0;
    for (int i = 0; i < 8; i++) {
        if (str[i] == '1') {
            parsed |= 1 << (7 - i);
            cout << parsed;
        }
    }
    return parsed;
}

int main(){
	const char* prueba = "0100000100110101010001000011010000110101";
	cout << "binario" << prueba<< "\n";
	cout << "normal" <<  conversorBinarioTexto(prueba);
	
	
}
