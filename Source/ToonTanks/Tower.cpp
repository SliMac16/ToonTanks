// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"




void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Find the distance to the Tank
    if(Tank)
    {
        //Check to see if th Tank is in range
        if(InFireRange())
        {
            //If in range, rotate turret toward Tank
            RotateTurret(Tank->GetActorLocation());
        }

        
    
    }
    

    
}

void ATower::HandleDestruction()
{
    Super::HandleDestruction();
    Destroy();
}

void ATower::BeginPlay()
{
    Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this ,0));

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{   
    if(Tank == nullptr)
    {
        return;
    }

    if(InFireRange() && Tank->IsTankAlive)
    {
        Fire();
    }
    
}

bool ATower::InFireRange()
{
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    if(Distance <= FireRange){
        return true;
    }

    return false;
}
