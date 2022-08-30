// Copyright Coffee Stain Studios. All Rights Reserved.


#include "TestFactoryConnection.h"

void UTestFactoryConnection::OnComponentDestroyed(bool isDestroyingHierarchy)
{
	UE_LOG(LogTemp, Error, TEXT("OnComponentDestroyed"))
	Super::OnComponentDestroyed(isDestroyingHierarchy);
}

void UTestFactoryConnection::OnRegister()
{
	UE_LOG(LogTemp, Error, TEXT("OnRegister"))
	Super::OnRegister();
}

void UTestFactoryConnection::OnUnregister()
{
	UE_LOG(LogTemp, Error, TEXT("OnUnregister"))
	Super::OnUnregister();
}

void UTestFactoryConnection::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion)
{
	UE_LOG(LogTemp, Error, TEXT("PostLoadGame_Implementation"))
	Super::PostLoadGame_Implementation(saveVersion, gameVersion);
}

void UTestFactoryConnection::SetDirection(EFactoryConnectionDirection newDirection)
{
	UE_LOG(LogTemp, Error, TEXT("SetDirection"))
	mDirection = newDirection;
}

void UTestFactoryConnection::SetConnectorClearance(float clearance)
{
	UE_LOG(LogTemp, Error, TEXT("SetConnectorClearance"))
	mConnectorClearance = clearance;
}

void UTestFactoryConnection::SetInventory(UFGInventoryComponent* inventory)
{
	UE_LOG(LogTemp, Error, TEXT("SetInventory"))
	Super::SetInventory(inventory);
}

void UTestFactoryConnection::SetInventoryAccessIndex(int32 index)
{
	UE_LOG(LogTemp, Error, TEXT("SetInventoryAccessIndex"))
	Super::SetInventoryAccessIndex(index);
}

int32 UTestFactoryConnection::GetInventoryAccessIndex() const
{
	UE_LOG(LogTemp, Error, TEXT("GetInventoryAccessIndex"))
	return mInventoryAccessIndex;
}

void UTestFactoryConnection::SetConnection(UFGFactoryConnectionComponent* toComponent)
{
	UE_LOG(LogTemp, Error, TEXT("SetConnection"))
	Super::SetConnection(toComponent);
}

UFGFactoryConnectionComponent* UTestFactoryConnection::GetConnection() const
{
	UE_LOG(LogTemp, Error, TEXT("GetConnection"))
	return mConnectedComponent;
}

void UTestFactoryConnection::ClearConnection()
{
	UE_LOG(LogTemp, Error, TEXT("ClearConnection"))
	Super::ClearConnection();
}

bool UTestFactoryConnection::IsConnected() const
{
	UE_LOG(LogTemp, Error, TEXT("IsConnected"))
	return mHasConnectedComponent;
}

UFGInventoryComponent* UTestFactoryConnection::GetInventory() const
{
	UE_LOG(LogTemp, Error, TEXT("GetInventory"))
	return mConnectionInventory;
}

EFactoryConnectionDirection UTestFactoryConnection::GetDirection() const
{
	UE_LOG(LogTemp, Error, TEXT("GetDirection"))
	return mDirection;
}

EFactoryConnectionDirection UTestFactoryConnection::GetCompatibleSnapDirection() const
{
	UE_LOG(LogTemp, Error, TEXT("GetCompatibleSnapDirection"))
	return Super::GetCompatibleSnapDirection();
}

EFactoryConnectionConnector UTestFactoryConnection::GetConnector() const
{
	UE_LOG(LogTemp, Error, TEXT("GetConnector"))
	return mConnector;
}

bool UTestFactoryConnection::CanSnapTo(UFGFactoryConnectionComponent* otherConnection) const
{
	UE_LOG(LogTemp, Error, TEXT("CanSnapTo"))
	return Super::CanSnapTo(otherConnection);
}

bool UTestFactoryConnection::CanConnectTo(UFGFactoryConnectionComponent* otherConnection) const
{
	UE_LOG(LogTemp, Error, TEXT("CanConnectTo"))
	return Super::CanConnectTo(otherConnection);
}

void UTestFactoryConnection::SetForwardPeekAndGrabToBuildable(bool forwardPeekAndGrab)
{
	UE_LOG(LogTemp, Error, TEXT("SetForwardPeekAndGrabToBuildable"))
	mForwardPeekAndGrabToBuildable = forwardPeekAndGrab;
}

float UTestFactoryConnection::GetConnectorClearance() const
{
	UE_LOG(LogTemp, Error, TEXT("GetConnectorClearance"))
	return mConnectorClearance;
}

FVector UTestFactoryConnection::GetConnectorLocation(bool withClearance) const
{
	UE_LOG(LogTemp, Error, TEXT("GetConnectorLocation"))
	return Super::GetConnectorLocation(withClearance);
}

FVector UTestFactoryConnection::GetConnectorNormal() const
{
	UE_LOG(LogTemp, Error, TEXT("GetConnectorNormal"))
	return GetComponentRotation().Vector();
}

bool UTestFactoryConnection::Factory_PeekOutput(TArray<FInventoryItem>& out_items,
	TSubclassOf<UFGItemDescriptor> type) const
{
	UE_LOG(LogTemp, Error, TEXT("Factory_PeekOutput"))
	return Super::Factory_PeekOutput(out_items, type);
}

bool UTestFactoryConnection::Factory_GrabOutput(FInventoryItem& out_item, float& out_OffsetBeyond,
	TSubclassOf<UFGItemDescriptor> type)
{
	UE_LOG(LogTemp, Error, TEXT("Factory_GrabOutput"))
	return Super::Factory_GrabOutput(out_item, out_OffsetBeyond, type);
}

bool UTestFactoryConnection::Factory_Internal_PeekOutputInventory(TArray<FInventoryItem>& out_items,
	TSubclassOf<UFGItemDescriptor> type) const
{
	UE_LOG(LogTemp, Error, TEXT("Factory_Internal_PeekOutputInventory"))
	return Super::Factory_Internal_PeekOutputInventory(out_items, type);
}

bool UTestFactoryConnection::Factory_Internal_GrabOutputInventory(FInventoryItem& out_item,
	TSubclassOf<UFGItemDescriptor> type)
{
	UE_LOG(LogTemp, Error, TEXT("Factory_Internal_GrabOutputInventory"))
	return Super::Factory_Internal_GrabOutputInventory(out_item, type);
}

AFGBuildable* UTestFactoryConnection::GetOuterBuildable() const
{
	UE_LOG(LogTemp, Error, TEXT("GetOuterBuildable"))
	return mOuterBuildable;
}

void UTestFactoryConnection::SortComponentList(TInlineComponentArray<UFGFactoryConnectionComponent*>& io_components)
{
	UE_LOG(LogTemp, Error, TEXT("SortComponentList"))
	Super::SortComponentList(io_components);
}

uint8 UTestFactoryConnection::MaxNumGrab(float delta) const
{
	UE_LOG(LogTemp, Error, TEXT("MaxNumGrab"))
	return Super::MaxNumGrab(delta);
}
