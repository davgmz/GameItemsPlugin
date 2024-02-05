﻿// Copyright Bohdon Sayre, All Rights Reserved.


#include "ViewModels/GameItemContainerSlotViewModel.h"

#include "GameItemContainer.h"
#include "GameItemContainerDef.h"


UGameItemContainerSlotViewModel::UGameItemContainerSlotViewModel()
	: Container(nullptr),
	  Slot(INDEX_NONE),
	  Item(nullptr)
{
}

void UGameItemContainerSlotViewModel::SetContainerAndSlot(UGameItemContainer* NewContainer, int32 NewSlot)
{
	if (Container != NewContainer || Slot != NewSlot)
	{
		Container = NewContainer;
		Slot = NewSlot;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Container);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Slot);

		// TODO: bind to slot-item change event

		UpdateItem();
	}
}

bool UGameItemContainerSlotViewModel::HasItem() const
{
	return Item != nullptr;
}

void UGameItemContainerSlotViewModel::UpdateItem()
{
	UGameItem* NewItem = nullptr;
	if (Container && Slot != INDEX_NONE)
	{
		NewItem = Container->GetItemAt(Slot);
	}

	if (Item != NewItem)
	{
		Item = NewItem;

		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(Item);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(HasItem);
	}
}

TArray<UGameItemContainerSlotViewModel*> UGameItemContainerSlotViewModel::CreateSlotViewModelsForContainer(UObject* Outer, UGameItemContainer* InContainer)
{
	TArray<UGameItemContainerSlotViewModel*> Result;
	if (!Outer || !InContainer)
	{
		return TArray<UGameItemContainerSlotViewModel*>();
	}

	const int32 NumSlots = InContainer->GetNumSlots();
	for (int32 Idx = 0; Idx < NumSlots; ++Idx)
	{
		UGameItemContainerSlotViewModel* NewViewModel = NewObject<UGameItemContainerSlotViewModel>(Outer, NAME_None, RF_Transient);
		NewViewModel->SetContainerAndSlot(InContainer, Idx);
		Result.Add(NewViewModel);
	}

	return Result;
}
