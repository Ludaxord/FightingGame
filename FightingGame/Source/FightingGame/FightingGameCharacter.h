// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FightingGameCharacter.generated.h"

UCLASS(config=Game)
class AFightingGameCharacter : public ACharacter {
	GENERATED_BODY()

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EX", meta = (AllowPrivateAccess = "true"))
	float EX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EX", meta = (AllowPrivateAccess = "true"))
	float MaxEX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
	FString CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bIsAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	bool bInput4;

protected:
	/** Called for side to side input */
	void MoveRight(float Val);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	AFightingGameCharacter();

	virtual void Tick(float DeltaSeconds) override;

	void Crouching();

	void StartInput1();
	void StartInput2();
	void StartInput3();
	void StartInput4();
	void StartSuper1();
	void StartSuper2();

	void StopInput1();
	void StopInput2();
	void StopInput3();
	void StopInput4();
	void StopSuper1();
	void StopSuper2();

	void TakeDamage(float DamageAmount);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const {
		return SideViewCameraComponent;
	}

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const {
		return CameraBoom;
	}

	FORCEINLINE bool IsAttacking() const {
		return bIsAttacking;
	}

	FORCEINLINE bool Input1Clicked() const {
		return bInput1;
	}

	FORCEINLINE bool Input2Clicked() const {
		return bInput2;
	}

	FORCEINLINE bool Input3Clicked() const {
		return bInput3;
	}

	FORCEINLINE bool Input4Clicked() const {
		return bInput4;
	}
};
