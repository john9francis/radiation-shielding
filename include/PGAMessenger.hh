#ifndef rad_shield_PGA_MESSENGER_HH
#define rad_shield_PGA_MESSENGER_HH 1

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "PrimaryGeneratorAction.hh"

namespace rad_shield {
	class PGAMessenger : public G4UImessenger {
	public:
		PGAMessenger(PrimaryGeneratorAction* PGA);
		~PGAMessenger();

		void SetNewValue(G4UIcommand* command, G4String newValues) override;


	private:
		PrimaryGeneratorAction* fPGA;

		G4UIcmdWithADoubleAndUnit* fSetRightSkewCmd;


	};
}

#endif // !rad_shield_PGA_MESSENGER_HH 1
