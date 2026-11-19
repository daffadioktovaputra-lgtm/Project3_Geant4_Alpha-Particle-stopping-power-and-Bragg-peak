#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    G4int n_particle = 1;

    fParticleGun = new G4ParticleGun(n_particle);

    auto* particleTable = G4ParticleTable::GetParticleTable();

    auto* alpha =
        particleTable->FindParticle("alpha");

    fParticleGun->SetParticleDefinition(alpha);

    // Energi alfa = 5 MeV
    fParticleGun->SetParticleEnergy(5.0 * MeV);

    // Posisi awal partikel
    fParticleGun->SetParticlePosition(
	G4ThreeVector(-5.01 * cm, 0.0, 0.0)
    );

    // Arah gerak sepanjang +X
    fParticleGun->SetParticleMomentumDirection(
        G4ThreeVector(1.0, 0.0, 0.0)
    );
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}
