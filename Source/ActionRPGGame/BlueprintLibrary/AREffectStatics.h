// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "../Types/ARStructTypes.h"
#include "../Types/AREnumTypes.h"
#include "TimerManager.h"
#include "AREffectStatics.generated.h"

UCLASS()
class UAREffectStatics : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Static")
		static class UAREffect* CreateEffect(TSubclassOf<class UAREffect> EffectIn, AActor* EffectCauser, AActor* EffectTarget);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Static")
		static void ApplyEffect(UAREffect* EffectIn);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Static")
		static void ApplyInstantEffect(TSubclassOf<class UAREffectType> EffectIn);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Static")
		static FEffectSpec CreatePeriodicEffect(AActor* EffectTarget, AActor* EffectCauser, float Duration, TSubclassOf<class AAREffectPeriodic> EffectType, const FEffectCue& EffectCue, TSubclassOf<class AARActorCue> ActorCue);
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Static")
		static void ActivatePeriodicEffect(FPeriodicEffect PeriodicEffect);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Static")
		static void ApplyPeriodicEffect(AActor* EffectTarget, AActor* EffectCauser, float Duration, TSubclassOf<class UAREffectPeriodicO> EffectType);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Damage Static")
		static void ChangeAttribute(AActor* Target, AActor* CausedBy, float ModVal, FName AttributeName, TEnumAsByte<EAttrOp> OpType);


	/*
		Ahem. I want to add seprate Heal Damage functionality. which means:
		1. I have to copy paste everything. Bad.
		2. Extract the target aggregation part to seprate functions, and just create simple function for healing
		and damage.
		3. Add switch to indicate whether it is healing or dmage to existing functions.

		Also probably will need to add few more Damage Trace Types:
		1. Positioned Box - Box is spawned in position aligned to player view in hit point.
		2. Cylinder ?

		Retrun array of damaged actors ?
	*/
	/*
	
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Damage Static")
		static void ApplyDamage(AActor* DamageTarget, float BaseDamage, FName AttributeName, AActor* EventInstigator, AActor* DamageCauser, FGameplayTagContainer DamageTag, bool bIsComboFinisher, TSubclassOf<class UDamageType> DamageType);
	/*
		EventInstigator - who Instigated Damage. In General should be controller. But can be any Actor with Attribute component.
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Damage Static")
		static void ApplyPointDamage(AActor* DamageTarget, float AttributeMod, FName AttributeName, const FVector& HitFromLocation, const FHitResult& HitInfo, AActor* EventInstigator, AActor* Causer, bool bIsComboFinisher, TSubclassOf<class UDamageType> DamageType);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Damage Static", meta = (AutoCreateRefTerm = "IgnoreActors"))
		static void ApplyRadialDamage(FName AttributeName, float BaseDamage, const FVector& Origin, TEnumAsByte<ECollisionChannel> Collision, float DamageRadius, TSubclassOf<class UDamageType> DamageTypeClass, const TArray<AActor*>& IgnoreActors, AActor* DamageCauser, AActor* Instigator, bool bDoFullDamage, FGameplayTagContainer DamageTag, bool bIsComboFinisher);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Game Effects|Damage Static", meta = (AutoCreateRefTerm = "IgnoreActors"))
		static void ApplyRadialDamageWithFalloff(FName AttributeName, float BaseDamage, float MinimumDamage, const FVector& Origin, TEnumAsByte<ECollisionChannel> Collision, float DamageInnerRadius, float DamageOuterRadius, float DamageFalloff, TSubclassOf<class UDamageType> DamageTypeClass, const TArray<AActor*>& IgnoreActors, FGameplayTagContainer DamageTag, bool bIsComboFinisher, AActor* DamageCauser = NULL, AActor* Instigator = NULL);
	
	/*
		Apply Damage in box shape from Origin point to end of trace.
	*/
	UFUNCTION(BlueprintCallable, Category = "ActionRPG|Game Effects|Damage Static")
		static void ApplyMultiBoxDamage(FVector StartLocation, float Range, FVector BoxExtends, TEnumAsByte<ECollisionChannel> Collision, AActor* DamageCauser, APawn* DamageInstigator);
	//probably need better category
	/*
	
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Spawn Helpers")
		static void ShootProjectile(TSubclassOf<class AARProjectile> Projectile, FVector Origin, AActor* Causer, FName StartSocket, const FARProjectileInfo& Data, const FHitResult& HitResult, TArray<AActor*> ActorToIgnore);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Spawn Helpers")
		static void SpawnProjectileInArea(TSubclassOf<class AARProjectile> Projectile, AActor* Causer, APawn* Instigator, const FHitResult& HitResult, const FARProjectileInfo& ProjectileInfo, int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "ActionRPG|Spawn Helpers")
		static void SpawnField(TSubclassOf<class AARFieldBase> Field, AActor* Instigator, FHitResult Location, float Duration, float TickInterval);

	static void DrawDebugSweptBox(const UWorld* InWorld, FVector const& Start, FVector const& End, FRotator const & Orientation, FVector const & HalfSize, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
	//TSubclassOf<class AARProjectile> Projectile, AActor* Causer, const FHitResult& HitResult, const FARProjectileInfo& ProjectileInfo
	UFUNCTION()
		static void SpawnProjectile(TSubclassOf<class AARProjectile> Projectile, AActor* Causer, FHitResult HitResult, FARProjectileInfo ProjectileInfo);
	
	UFUNCTION()
		static void SpawnProjectileOne(TSubclassOf<class AARProjectile> Projectile, AActor* Causer, FHitResult HitResult, FARProjectileInfo ProjectileInfo);

	UFUNCTION()
		static void StopTimer(AActor* Causer, int32 HandleIn);

	/*
		Attribute modification helpers.
	*/

	/*
		Drains Attribute. Decrease Target Attribute and increase attribute on Causer.
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Action RPG|Attributes|Damage")
		static void DrainAttribute(FName TargetAttribute, float TargetMod, FName CauserAttribute, float CauserMod, AActor* Target, AActor* Causer);
};



