// Fill out your copyright notice in the Description page of Project Settings.


#include "MainAnimInstance.h"

#include "FightingGameCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

UMainAnimInstance::UMainAnimInstance(): PunchAttack(EPunchAttack::EPA_None),
                                        KickAttack(EKickAttack::EKA_None) {
}

void UMainAnimInstance::UpdateAnimProperties(float DeltaTime) {
	if (!CurrentCharacter)
		CurrentCharacter = Cast<ACharacter>(TryGetPawnOwner());

	if (CurrentCharacter) {
		bInAir = CurrentCharacter->GetMovementComponent()->IsFalling();
		FVector Velocity = CurrentCharacter->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();

		PlayerTransform = CurrentCharacter->GetTransform();

		if (AFightingGameCharacter* FightingCharacter = Cast<AFightingGameCharacter>(CurrentCharacter)) {
			bAttack = FightingCharacter->IsAttacking();

			if (FightingCharacter->Input1Clicked() || FightingCharacter->Input2Clicked()) {
				KickAttack = EKickAttack::EKA_None;
				if (FightingCharacter->Input1Clicked()) {
					PunchAttack = EPunchAttack::EPA_1Input;
				}
				else if (FightingCharacter->Input2Clicked()) {
					PunchAttack = EPunchAttack::EPA_2Input;
				}
			}
			else if (FightingCharacter->Input3Clicked() || FightingCharacter->Input4Clicked()) {
				PunchAttack = EPunchAttack::EPA_None;
				if (FightingCharacter->Input3Clicked()) {
					KickAttack = EKickAttack::EKA_3Input;
				}
				else if (FightingCharacter->Input4Clicked()) {
					KickAttack = EKickAttack::EKA_4Input;
				}
			}
			else {
				KickAttack = EKickAttack::EKA_None;
				PunchAttack = EPunchAttack::EPA_None;
			}

			bInput1Attack = PunchAttack == EPunchAttack::EPA_1Input;
			bInput2Attack = PunchAttack == EPunchAttack::EPA_2Input;
			bInput3Attack = KickAttack == EKickAttack::EKA_3Input;
			bInput4Attack = KickAttack == EKickAttack::EKA_4Input;

			// bInput1Attack = FightingCharacter->Input1Clicked();
			// bInput2Attack = FightingCharacter->Input2Clicked();
			// bInput3Attack = FightingCharacter->Input3Clicked();
			// bInput4Attack = FightingCharacter->Input4Clicked();
		}
	}
}

void UMainAnimInstance::NativeInitializeAnimation() {
	CurrentCharacter = Cast<ACharacter>(TryGetPawnOwner());
}
