// Fill out your copyright notice in the Description page of Project Settings.


#include "HitboxActor.h"

#include "FightingGameCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHitboxActor::AHitboxActor(): HitBoxType(EHitBoxEnum::HBE_None), HitBoxDamage(0.05f) {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HitBox = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hitbox"));
	SetRootComponent(HitBox);
}

// Called when the game starts or when spawned
void AHitboxActor::BeginPlay() {
	Super::BeginPlay();

	// HitBox->OnComponentBeginOverlap.AddDynamic(this, &AHitboxActor::OnBeginOverlap);
	// HitBox->OnComponentEndOverlap.AddDynamic(this, &AHitboxActor::OnEndOverlap);
}


void AHitboxActor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                  const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Actor Overlap -> %s "), *OtherActor->GetName());
	if (AFightingGameCharacter* FightingCharacter = Cast<AFightingGameCharacter>(OtherActor)) {
		UE_LOG(LogTemp, Warning, TEXT("Player -> %s Damage -> %f"), *OtherActor->GetName(), HitBoxDamage);
		FightingCharacter->TakeDamage(HitBoxDamage);
	}
}

void AHitboxActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex) {

}

// Called every frame
void AHitboxActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

}

void AHitboxActor::TriggerVisualizeBox() {
	VisualizeHitBox();
}

void AHitboxActor::TriggerSpawnHitBox() {
	switch (HitBoxType) {

	case EHitBoxEnum::HBE_Proximity:
		HitBox->SetMaterial(0, ProximityMaterial);
		break;
	case EHitBoxEnum::HBE_Strike:
		HitBox->SetMaterial(0, StrikeMaterial);
		break;
	case EHitBoxEnum::HBE_Hurtbox:
		HitBox->SetMaterial(0, HurtMaterial);
		break;
	case EHitBoxEnum::HBE_None: break;
	case EHitBoxEnum::HBE_MAX: break;
	default: ;
	}

	HitBox->SetWorldLocation(HitBoxLocation);
	HitBox->SetVisibility(true);

	TriggerCheckCollision();
}

//TODO: Maybe change to OnComponent(Begin/End)Overlap
void AHitboxActor::TriggerCheckCollision() {
	UE_LOG(LogTemp, Warning, TEXT("AHitboxActor::TriggerCheckCollision"));

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors) {
		UE_LOG(LogTemp, Warning, TEXT("Actor Name -> %s"), *OverlappingActor->GetName());
		if (AFightingGameCharacter* FightingCharacter = Cast<AFightingGameCharacter>(OverlappingActor)) {
			auto Player = UGameplayStatics::GetPlayerCharacter(this, 0);
			if (Player != FightingCharacter) {
				UE_LOG(LogTemp, Warning, TEXT("Player -> %s Damage -> %f"), *FightingCharacter->GetName(), HitBoxDamage);
				FightingCharacter->TakeDamage(HitBoxDamage);
			}
		}
	}

	// auto Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	// if (IsOverlappingActor(Player)) {
	// 	if (AFightingGameCharacter* FightingCharacter = Cast<AFightingGameCharacter>(Player)) {
	// 		UE_LOG(LogTemp, Warning, TEXT("Player -> %s Damage -> %f"), *Player->GetName(), HitBoxDamage);
	// 		FightingCharacter->TakeDamage(HitBoxDamage);
	// 	}
	// }
}
