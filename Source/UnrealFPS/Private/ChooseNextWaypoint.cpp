// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "../Public/ChooseNextWaypoint.h"

//IWYU

#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	///Get the patrol points.
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRouteComp = ControlledPawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComp)) { return EBTNodeResult::Failed; } //Protect agains no Patrol Route component.
	auto PatrolPoints = PatrolRouteComp->GetPatrolPoints();
	if(PatrolPoints.Num() == 0 )
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard has no patrol points"));
		return EBTNodeResult::Failed;
	}

	
	

	///Set Next Waypoint.
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]); //TODO protect against empty array.
	
	//UE_LOG(LogTemp, Warning, TEXT("Waypoint Index: %i"), Index);
	

	///Cycle index
	auto NewIndex = (Index+1) % (PatrolPoints.Num());
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);
	
	return EBTNodeResult::Succeeded;
	
}
