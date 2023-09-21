#include <iostream>
#include <vector>

class TwoBitPredictor {
private:
    std::vector<int> counters;

public:
    TwoBitPredictor(int numEntries) {
        // Inicialize os contadores com valores iniciais de 2 bits (00).
        for (int i = 0; i < numEntries; ++i) {
            counters.push_back(0);
        }
    }

    // Dado o índice da entrada, preveja o próximo desvio.
    bool predict(int index) {
        if (counters[index] >= 2) {
            return true;  // Fortemente tomado (11)
        } else {
            return false; // Não tomado ou fracamente tomado (00 ou 01)
        }
    }

    // Atualiza o contador com base no desvio real.
    void update(int index, bool actualOutcome) {
        if (actualOutcome) {
            if (counters[index] < 3) {
                counters[index]++;  // Incrementa o contador se o desvio foi tomado.
            }
        } else {
            if (counters[index] > 0) {
                counters[index]--;  // Decrementa o contador se o desvio não foi tomado.
            }
        }
    }
};

int main() {
    const int numEntries = 16; // Número de entradas no preditor.
    TwoBitPredictor predictor(numEntries);

    // Simulação de previsões e atualizações.
    std::vector<int> branchHistory = {1, 0, 1, 1, 0, 0, 1, 0, 1, 0}; // Exemplo de histórico de desvios.

    for (int i = 0; i < branchHistory.size(); ++i) {
        int index = i % numEntries;
        bool prediction = predictor.predict(index);
        bool actualOutcome = branchHistory[i];

        std::cout << "Cycle " << i + 1 << ": Prediction = " << prediction
                  << ", Actual Outcome = " << actualOutcome << std::endl;

        predictor.update(index, actualOutcome);
    }

    return 0;
}
