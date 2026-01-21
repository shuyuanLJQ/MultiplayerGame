// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"


UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Inital UMETA(DisplayName = "初始状态"),
	EWS_Equipped UMETA(DisplayName = "装备状态"),
	EWS_Dropped UMETA(DisplayName = "掉落状态"),
	EWS_Max UMETA(DisplayName = "最大值")
};



UCLASS()
class MULTIPLAYERGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	void ShowPickupWidget(bool ShowWidget);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		// 作用：这是触发这个事件的组件本身。
		// 解释：如果你在函数里需要引用这个球体（比如想改变它的颜色或禁用它），你就使用这个指针。它指向调用这个重叠事件的那个组件
		AActor* OtherActor,
		//作用：这是碰撞发生的另一方（进入球体的物体）。
		//解释：球体是收集金币的区域，OtherActor 就是“玩家角色”。通常会在这里判断 OtherActor 是不是你想要的类型（比如是否是玩家），然后执行逻辑（比如加分）。
		UPrimitiveComponent* OtherComp,
		//作用：这是另一个物体身上发生碰撞的具体组件。
		//解释：一个角色（Actor）身上可能有多个碰撞组件（比如盒子、胶囊体、球体等）。该参数具体说明是哪个组件碰撞了球体。通常和 OtherActor 配合使用。
		int32 OtherBodyIndex,
		//作用：这是另一个物体身上碰撞体的索引编号。
		//解释：如果OtherActor 有多个物理体（例如一个由多个部分组成的复杂骨骼网格体），这个索引用来标识具体是哪一个部分发生了碰撞。用于复杂物理模拟。
		bool bFromSweep,
		//作用：指示这次重叠是由于“移动检测”（Sweep）产生的，还是由于“瞬移”或“生成”产生的。
		//解释：true：说明 OtherActor 是在移动过程触发的重叠。 false：说明 OtherActor 可能是直接被生成在这个区域里，或者被瞬移到这里的。
		const FHitResult& SweepResult
		//作用：如果 bFromSweep 为 true，这个参数包含了详细的碰撞检测结果。
		//解释：这是一个引用传递的结构体，包含了诸如：碰撞发生的具体位置、法线方向、阻挡发生的距离等信息。如果你需要知道“球体具体是在哪里被碰到的”，可以需要检查这个参数。
	);

private:
	UPROPERTY(VisibleAnywhere, Category = "武器资源")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "武器资源")
	class USphereComponent* AreaSphere;
	
	UPROPERTY(VisibleAnywhere, Category = "武器资源")
	EWeaponState WeaponState;

	UPROPERTY(VisibleAnywhere, Category = "武器资源")
	class UWidgetComponent* PickupWidget;

public:	
	
};
