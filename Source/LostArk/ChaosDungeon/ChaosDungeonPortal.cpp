// Fill out your copyright notice in the Description page of Project Settings.


#include "../ChaosDungeon/ChaosDungeonPortal.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Widget/MoveWidget.h"
#include "Components/WidgetComponent.h"

int32 AChaosDungeonPortal::MoveWidgetCount = 0;
// Sets default values
AChaosDungeonPortal::AChaosDungeonPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	Portal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal"));
	Portal->SetupAttachment(Sphere);

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AChaosDungeonPortal::OnOverlapBegin);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AChaosDungeonPortal::OnOverlapEnd);

	MoveWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("MoveWidget"));
	MoveWidget->SetupAttachment(RootComponent);
	MoveWidget->SetDrawAtDesiredSize(true);
	MoveWidget->SetRelativeLocation(GetActorLocation() + FVector(0.f, 0.f, 100.f));
	MoveWidget->SetCastShadow(false);
}

void AChaosDungeonPortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MoveWidget->SetHiddenInGame(false);
}

void AChaosDungeonPortal::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	MoveWidget->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AChaosDungeonPortal::BeginPlay()
{
	Super::BeginPlay();
	MoveWidget->SetHiddenInGame(true);
}

// Called every frame
void AChaosDungeonPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

