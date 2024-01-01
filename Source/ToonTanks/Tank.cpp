// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"



ATank::ATank()
{
    
    Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Arm"));
	Arm->SetupAttachment(RootComponent);


    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(Arm);

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("Move"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            (ECollisionChannel::ECC_Visibility), 
            false, 
            HitResult);
        
        
        DrawDebugSphere(
            GetWorld(), 
            HitResult.ImpactPoint,
            25.f,
            12,
            FColor::Red,
            false,
            -1.f);

    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

void ATank::Move(float Value)
{
    UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);

    FVector DeltaLocation = FVector::ZeroVector;

    DeltaLocation.X = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * speed;

    AddActorLocalOffset(DeltaLocation, true);
    
}

void ATank::Turn(float Value){

    FRotator DeltaRotation = FRotator::ZeroRotator;

    DeltaRotation.Yaw = Value * UGameplayStatics::GetWorldDeltaSeconds(this) * TurnRate;

    AddActorLocalRotation(DeltaRotation, true);

}

