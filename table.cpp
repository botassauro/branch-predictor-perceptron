#include <iostream>
#include <vector>

#define TABLE_SIZE 100

class BTBEntry {
public:
    bool valid;        // Is the entry valid?
    unsigned int tag;  // Tag to identify the branch instruction
    unsigned int target; // Predicted target address

    BTBEntry() : valid(false), tag(0), target(0) {}
};

class BranchTargetBuffer {
private:
    std::vector<BTBEntry> btb; // Branch target prediction table

public:
    BranchTargetBuffer(size_t size) : btb(size) {}

    // Predict the target address for a branch instruction
    bool predictTarget(unsigned int instructionAddress, unsigned int &predictedTarget) {
        for (BTBEntry &entry : btb) {
            if (entry.valid && entry.tag == instructionAddress) {
                predictedTarget = entry.target;
                return true; // Prediction found
            }
        }
        return false; // No prediction found
    }

    // Update the branch target prediction table with the actual target address
    void updateBTB(unsigned int instructionAddress, unsigned int actualTarget) {
        for (BTBEntry &entry : btb) {
            if (!entry.valid || entry.tag == instructionAddress) {
                entry.valid = true;
                entry.tag = instructionAddress;
                entry.target = actualTarget;
                return;
            }
        }
        // If the table is full, you may need to implement replacement policies.
    }
};

int main() {
    BranchTargetBuffer btb(TABLE_SIZE);

    unsigned int instructionAddress = 0x12345678;
    unsigned int predictedTarget;

    // Simulate a prediction
    if (btb.predictTarget(instructionAddress, predictedTarget)) {
        std::cout << "Predicted target address: 0x" << std::hex << predictedTarget << std::endl;
    } else {
        std::cout << "No prediction found." << std::endl;
    }

    // Simulate an update
    unsigned int actualTarget = 0xAABBCCDD;
    btb.updateBTB(instructionAddress, actualTarget);

    // Predict again after the update
    if (btb.predictTarget(instructionAddress, predictedTarget)) {
        std::cout << "Predicted target address after update: 0x" << std::hex << predictedTarget << std::endl;
    } else {
        std::cout << "No prediction found after update." << std::endl;
    }

    return 0;
}
