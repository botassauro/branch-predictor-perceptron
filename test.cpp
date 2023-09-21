#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Defina uma estrutura para representar uma entrada na BTB
struct BTBEntry {
    unsigned long tag;
    unsigned long target_address;
    bool valid;

    BTBEntry() : valid(false) {}
};

// Implemente a BTB como um vetor de vetores (matriz 2D)
class BTB {
public:
    BTB(int sets, int ways) : sets_(sets), ways_(ways) {
        btb_.resize(sets_, vector<BTBEntry>(ways_));
    }

    // Função para pesquisar na BTB
    bool search(unsigned long index, unsigned long tag, unsigned long &target) {
        for (int i = 0; i < ways_; i++) {
            if (btb_[index][i].valid && btb_[index][i].tag == tag) {
                target = btb_[index][i].target_address;
                return true; // Encontrou um hit na BTB
            }
        }
        return false; // Não encontrou um hit na BTB
    }

    // Função para inserir na BTB
    void insert(unsigned long index, unsigned long tag, unsigned long target) {
        for (int i = 0; i < ways_; i++) {
            if (!btb_[index][i].valid) {
                btb_[index][i].valid = true;
                btb_[index][i].tag = tag;
                btb_[index][i].target_address = target;
                return;
            }
        }
        // Se todas as vias estiverem ocupadas, substitua a entrada mais antiga (política FIFO)
        for (int i = 0; i < ways_ - 1; i++) {
            btb_[index][i] = btb_[index][i + 1];
        }
        btb_[index][ways_ - 1].tag = tag;
        btb_[index][ways_ - 1].target_address = target;
    }

private:
    int sets_;
    int ways_;
    vector<vector<BTBEntry>> btb_;
};

int main() {
    // Crie uma BTB com 1024 conjuntos e 12 vias
    BTB btb(1024, 12);

    // Exemplo de pesquisa e inserção na BTB
    unsigned long pc = 0x12345678;
    unsigned long target = 0xabcdef00;
    unsigned long index = (pc >> 2) % 1024; // Use 1024 conjuntos
    unsigned long tag = pc >> 14; // Ajuste o número de bits de tag conforme necessário

    vector<unsigned long> v;
    unsigned long aux = 0x12345678;

    for (int i = 0; i < 2000; i++) {
        v.push_back(aux);
        index = (aux >> 2) % 1024;
        tag = aux >> 6;
        //cout << hex << aux << endl;
        cout << hex << index << "/" << tag << endl;

        aux = aux + 4;

        
    }

    // Pesquisar na BTB
    if (btb.search(index, tag, target)) {
        cout << "Hit na BTB! O endereço de destino é 0x" << hex << target << endl;
    } else {
        cout << "Miss na BTB! O endereço de destino deve ser calculado." << endl;
        // Calcule o endereço de destino e, em seguida, insira na BTB
        // (substitua o cálculo do endereço de destino e os valores de exemplo)
        //target = pc + 4; // Exemplo simples
        btb.insert(index, tag, target);
        cout << "O endereço de destino foi calculado como 0x" << hex << target << " e inserido na BTB." << endl;
    }

    if (btb.search(index, tag, target)) {
        cout << "Hit na BTB! O endereço de destino é 0x" << hex << target << endl;
    } else {
        cout << "Miss na BTB! O endereço de destino deve ser calculado." << endl;
        // Calcule o endereço de destino e, em seguida, insira na BTB
        // (substitua o cálculo do endereço de destino e os valores de exemplo)
        //target = pc + 4; // Exemplo simples
        btb.insert(index, tag, target);
        cout << "O endereço de destino foi calculado como 0x" << hex << target << " e inserido na BTB." << endl;
    }

    return 0;
}
