// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryConnectionComponent.h"
#include "UObject/Object.h"
#include "TestFactoryConnection.generated.h"

/**
 * 
 */
UCLASS( ClassGroup = ( Custom ), meta = (BlueprintSpawnableComponent) )
class COPYBOX_API UTestFactoryConnection : public UFGFactoryConnectionComponent
{
	GENERATED_BODY()
	
public:
	virtual void OnComponentDestroyed( bool isDestroyingHierarchy ) override;
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	// End ActorComponent interface

	// Begin save interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End save interface

	/** Set our direction after creation time */
	FORCEINLINE void SetDirection( EFactoryConnectionDirection newDirection );

	/** Set the conveyor clearance for this connection. */
	FORCEINLINE void SetConnectorClearance( float clearance );

	/**
	 * Set the inventory associated with this connection
	 */
	void SetInventory( class UFGInventoryComponent* inventory );

	/**
	* Sets a specified index for the component to access on its assigned inventory
	*/
	void SetInventoryAccessIndex( int32 index );

	/**
	* Gets the inventory access index specified for this factory connection
	*/
	int32 GetInventoryAccessIndex() const;

	/**
	 * Set which connection this is connected to.
	 * @note Sets both ends of the connection.
	 * If there already a connection made we assert.
	 */
	void SetConnection( class UFGFactoryConnectionComponent* toComponent );

	/**
	 * Get which connection this is connected to.
	 */
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection() const;

	/**
	 * Clear the connection on this component
	 * @note Clears both ends of the connection.
	 * If nothing is connected this does nothing.
	 */
	void ClearConnection();

	/**
	 * Is this connection connected to anything.
	 * @return - true if connected; otherwise false. Always false if attached to hologram, snap only or bad index configuration.
	 */
	FORCEINLINE bool IsConnected() const;

	/** Return the inventory associated with this connection. */
	FORCEINLINE class UFGInventoryComponent* GetInventory() const;

	/** Return the direction for this connection. */
	FORCEINLINE EFactoryConnectionDirection GetDirection() const;

	/** Get the direction needed to be able to connect to this connection, ANY if anything is valid. */
	EFactoryConnectionDirection GetCompatibleSnapDirection() const;

	/** Return the connector used for this connection. */
	FORCEINLINE EFactoryConnectionConnector GetConnector() const;

	/** Check if the given connection can snap to this. */
	bool CanSnapTo( UFGFactoryConnectionComponent* otherConnection ) const;
	
	/** Check if the given connection can connect to this. */
	bool CanConnectTo( UFGFactoryConnectionComponent* otherConnection ) const;

	/** Accessor for c++ constructors */
	FORCEINLINE void SetForwardPeekAndGrabToBuildable( bool forwardPeekAndGrab );

	/** Return the clearance needed when routing a conveyor belt from this connection. */
	FORCEINLINE float GetConnectorClearance() const;

	/** Return the connectors world location with or without considering the clearance. */
	FVector GetConnectorLocation( bool withClearance = false ) const;
	/** Return the connectors world normal. */
	FVector GetConnectorNormal() const;

	/**
	 * Check this connection has a output
	 * @param type - Optionally check the type of the output, nullptr for any.
	 * @return true if it has output; false if no output or
	 */
	bool Factory_PeekOutput( TArray< FInventoryItem >& out_items, TSubclassOf< class UFGItemDescriptor > type = nullptr ) const;

	/**
	 * Grab the output on a connection (Grabs 1 resource).
	 * @param type - Type to grab if output has multiple types, nullptr for any.
	 * @param offset - if we are grabbing from a belt the item might have an offset beyond the belt's length
	 * @return valid resource descriptor on success; nullptr if no output of given type exists.
	 */
	bool Factory_GrabOutput( FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type = nullptr );

	/**
	 * Internal function, for when overloading how to handle a peek, peeks our output from a inventory
	 */
	bool Factory_Internal_PeekOutputInventory( TArray< FInventoryItem >& out_items, TSubclassOf< class UFGItemDescriptor > type ) const;

	/**
	 * Internal function, for when overloading how to handle a grab, grabs our output from a inventory
	 */
	bool Factory_Internal_GrabOutputInventory( FInventoryItem& out_item, TSubclassOf< UFGItemDescriptor > type );

	class AFGBuildable* GetOuterBuildable() const;

	/**
	 * Sort the components by name
	 * 
	 * @param io_components - List to be sorted
	 */
	static void SortComponentList( TInlineComponentArray< UFGFactoryConnectionComponent* >& io_components );

	/**
	 * This function tells us the maximum amounts of grabs this building can make this frame
	 */
	virtual uint8 MaxNumGrab( float delta ) const override;
};
