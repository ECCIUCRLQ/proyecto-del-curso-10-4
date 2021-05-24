#include <iostream>
#include <bitset>
using namespace std;

string conversorTextoBinario(string palabra){
	string stringBinario = "";
	for(char& _char : palabra){
		stringBinario +=bitset<8>(_char).to_string();
	}
	return stringBinario;	
	
}

int main(){
	string prueba = "A5D45";
	cout << "normal" << prueba<< "\n";
	cout << "binario" <<  conversorTextoBinario(prueba);
	
	
}
