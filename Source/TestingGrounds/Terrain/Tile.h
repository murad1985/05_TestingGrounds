// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;

};

class UActorPool;

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawns(TSubclassOf<APawn> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500);
	
	TArray<FSpawnPosition> RandomSpawnPositions(int32 MinSpawn, int32 MaxSpawn, float MinScale, float MaxScale, float Radius);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MinExtent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetPool(UActorPool* InPool);

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(FVector& OutLocation, float Radius);

	template<class T>
	void RandomlyPlacedActors(TSubclassOf<T> ToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 500, float MinScale = 1, float MaxScale = 1);

	void PlaceActor(TSubclassOf<AActor> ToSpawn, FSpawnPosition SpawnPosition);

	void PlaceActor(TSubclassOf<APawn> ToSpawn, FSpawnPosition SpawnPosition);

	UActorPool* Pool;

	void PositionNavMeshBoundsVolume();

	AActor* NavMeshBoundsVolume;
};


