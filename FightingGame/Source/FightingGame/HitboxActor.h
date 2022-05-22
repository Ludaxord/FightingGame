// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitboxActor.generated.h"

UENUM(BlueprintType)
enum class EHitBoxEnum: uint8 {
	HBE_Proximity UMETA(DisplayName = "Proximity"),
	HBE_Strike UMETA(DisplayName = "Strike"),
	HBE_Hurtbox UMETA(DisplayName = "Hurtbox"),
	HBE_None UMETA(DisplayName = "None"),
	HBE_MAX UMETA(DisplayName = "MAX"),
};

UCLASS()
class FIGHTINGGAME_API AHitboxActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHitboxActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void TriggerVisualizeBox();

	UFUNCTION(BlueprintCallable)
	void TriggerSpawnHitBox();

	UFUNCTION(BlueprintCallable)
	void TriggerCheckCollision();

	UFUNCTION(BlueprintImplementableEvent)
	void VisualizeHitBox();

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                     UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                       UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	                       bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	EHitBoxEnum HitBoxType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* HitBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	FVector HitBoxLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	float HitBoxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* ProximityMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* StrikeMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	UMaterialInstance* HurtMaterial;
};
