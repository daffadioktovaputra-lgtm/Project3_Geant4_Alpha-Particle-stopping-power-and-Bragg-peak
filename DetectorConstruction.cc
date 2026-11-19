#include "DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

DetectorConstruction::DetectorConstruction()
{}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    auto* nist = G4NistManager::Instance();

    // Material
    G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

    // =========================
    // WORLD
    // =========================

    G4double worldSize = 30.0 * cm;

    auto* solidWorld =
        new G4Box(
            "World",
            worldSize / 2,
            worldSize / 2,
            worldSize / 2
        );

    auto* logicWorld =
        new G4LogicalVolume(
            solidWorld,
            air,
            "World"
        );

    auto* physWorld =
        new G4PVPlacement(
            nullptr,
            G4ThreeVector(),
            logicWorld,
            "World",
            nullptr,
            false,
            0,
            true
        );

    // =========================
    // AIR SCORING BOX
    // Panjang arah X = 10 cm
    // Lebar Y = 10 cm
    // Tinggi Z = 10 cm
    // =========================

    G4double boxLength = 10.0 * cm;
    G4double boxWidth  = 10.0 * cm;
    G4double boxHeight = 10.0 * cm;

    // 100 slice
    G4int numberOfSlices = 100;
    G4double sliceLength = boxLength / numberOfSlices;

    // =========================
    // SCORING SLICE
    // Setiap slice = 1 mm
    // =========================

    auto* solidSlice =
        new G4Box(
            "Slice",
            sliceLength / 2,
            boxWidth / 2,
            boxHeight / 2
        );

    auto* logicSlice =
        new G4LogicalVolume(
            solidSlice,
            air,
            "Slice"
        );

    // =========================
    // PENEMPATAN SLICE
    // Box berada dari x = -5 cm
    // sampai x = +5 cm
    // =========================

    for (G4int i = 0; i < numberOfSlices; i++)
    {
        G4double x =
            -boxLength / 2
            + (i + 0.5) * sliceLength;

        new G4PVPlacement(
            nullptr,
            G4ThreeVector(x, 0.0, 0.0),
            logicSlice,
            "Slice",
            logicWorld,
            false,
            i,
            true
        );
    }

    // =========================
    // VISUALISASI
    // =========================

    auto* sliceVis =
        new G4VisAttributes(
            G4Colour(0.7, 0.7, 0.7)
        );

    sliceVis->SetForceWireframe(true);

    logicSlice->SetVisAttributes(sliceVis);

    logicWorld->SetVisAttributes(
        G4VisAttributes::GetInvisible()
    );

    return physWorld;
}
