#include <iostream>
#include <vector>

class TwoBitPredictor {
private:
    std::vector<int> counters;

public:
    TwoBitPredictor(int numEntries) {
        // Initialize the counters with "Weakly Taken" (01).
        for (int i = 0; i < numEntries; ++i) {
            counters.push_back(1);
        }
    }

    // Given the index of the entry, predict the next branch outcome.
    bool predict(int index) {
        if (counters[index] >= 2) {
            return true;  // Taken
        } else {
            return false; // Not Taken
        }
    }

    // Update the counter based on the actual outcome.
    void update(int index, bool actualOutcome) {
        if (actualOutcome) {
            if (counters[index] < 3) {
                counters[index]++;  // Increment the counter if the branch was taken.
            }
        } else {
            if (counters[index] > 0) {
                counters[index]--;  // Decrement the counter if the branch was not taken.
            }
        }
    }
};

int main() {
    const int numEntries = 16; // Number of entries in the predictor.
    TwoBitPredictor predictor(numEntries);

    // Simulation of predictions and updates.
    std::vector<int> branchHistory = {1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0}; // Example branch history.

    for (int i = 0; i < branchHistory.size(); ++i) {
        bool prediction = predictor.predict(0); // Always using the first entry for simplicity.
        bool actualOutcome = branchHistory[i];

        std::cout << "Cycle " << i + 1 << ": Prediction = " << prediction
                  << ", Actual Outcome = " << actualOutcome << std::endl;

        predictor.update(0, actualOutcome); // Always updating the first entry for simplicity.
    }

    return 0;
}
