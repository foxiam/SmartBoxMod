#include "CopyBoxModule.h"

#include "FGConstructDisqualifier.h"
#include "FGHoloTest.h"
#include "Hologram/FGHologram.h"
#include "Patching/NativeHookManager.h"

#define SC StaticClass()

TSet<TSubclassOf<UFGConstructDisqualifier>> FilterDisqualifier = {
	UFGCDBeltMustSnap::SC, UFGCDInvalidFloor::SC,UFGCDMustSnap::SC,UFGCDMustSnapWall::SC, UFGCDMustSnapToCeiling::SC,UFGCDWireSnap::SC,
	UFGCDConveyorTooShort::SC,UFGCDMustHaveRailRoadTrack::SC, UFGCDTrackTooShort::SC, UFGCDPipeTooShort::SC, UFGCDPipeMustSnap::SC};

void FCopyBoxModule::StartupModule() {
#if !WITH_EDITOR
	SUBSCRIBE_METHOD(AFGHologram::AddConstructDisqualifier, [](auto& scope, AFGHologram* self, TSubclassOf< class UFGConstructDisqualifier > disqualifier) {
		if(AActor *owner = self->mParent)
			if(owner->GetClass()->IsChildOf(AFGHoloTest::StaticClass()) && FilterDisqualifier.Contains(disqualifier))
				scope.Cancel();
	});
#endif
}

IMPLEMENT_GAME_MODULE(FCopyBoxModule, CopyBox);