#ifndef rad_shield_ENERGY_ACCUMULATOR_HH
#ifndef rad_shield_ENERGY_ACCUMULATOR_HH 1



#include "G4Accumulable.hh"
#include "G4AccumulableManager.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"

class EnergyAccumulator {
public:
    EnergyAccumulator() : fAccumulatedEnergy(0.0) {
        fAccumulable = new G4Accumulable<G4double>(0.0);
        G4AccumulableManager::Instance()->RegisterAccumulable(fAccumulable);
    }

    ~EnergyAccumulator() {
        delete accumulable;
    }

    // Function to accumulate energy from stepping action
    void AccumulateEnergy(const G4Step* step) {
        G4double stepEnergy = step->GetTotalEnergyDeposit();
        fAccumulatedEnergy += stepEnergy;
        *fAccumulable += stepEnergy;
    }

    // Function to retrieve accumulated energy
    G4double GetAccumulatedEnergy() const {
        return fAccumulatedEnergy;
    }

private:
    G4double fAccumulatedEnergy;
    G4Accumulable<G4double>* fAccumulable;
};


#endif // !rad_shield_ENERGY_ACCUMULATOR_HH 1
