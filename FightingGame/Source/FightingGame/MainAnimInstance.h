// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HitboxActor.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"


UENUM(BlueprintType)
enum class EPunchAttack : uint8 {
	EPA_1Input,
	EPA_2Input,
	EPA_None,
	EPA_MAX,
};

UENUM(BlueprintType)
enum class EKickAttack : uint8 {
	EKA_3Input,
	EKA_4Input,
	EKA_None,
	EKA_MAX,
};

UCLASS()
class FIGHTINGGAME_API UMainAnimInstance : public UAnimInstance {
	GENERATED_BODY()
public:
	UMainAnimInstance();

	UFUNCTION(BlueprintCallable)
	void UpdateAnimProperties(float DeltaTime);

	void NativeInitializeAnimation() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
	class ACharacter* CurrentCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	bool bInAir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	FTransform PlayerTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	TArray<AHitboxActor*> ProximityHitboxes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	TArray<AHitboxActor*> ActiveHitboxes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox", meta = (AllowPrivateAccess = "true"))
	AHitboxActor* HitboxActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput1Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput2Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput3Attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput4Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	EKickAttack KickAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	EPunchAttack PunchAttack;

public:
	FORCEINLINE EPunchAttack GetPunchAttack() const {
		return PunchAttack;
	}

	FORCEINLINE EKickAttack GetKickAttack() const {
		return KickAttack;
	}
};
