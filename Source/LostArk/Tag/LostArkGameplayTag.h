
#pragma once

#include "GameplayTagContainer.h"

#define LOSTARKTAG_DATA_DAMAGE FGameplayTag::RequestGameplayTag(FName("Data.Damage"))
#define LOSTARKTAG_CHARACTER_ISDEAD FGameplayTag::RequestGameplayTag(FName("Character.State.IsDead"))
#define LOSTARKTAG_CHARACTER_ATTACK FGameplayTag::RequestGameplayTag(FName("Character.State.Attack"))
#define LOSTARKTAG_CHARACTER_ISSKILLING FGameplayTag::RequestGameplayTag(FName("Character.State.IsSkilling"))
#define LOSTARKTAG_CHARACTER_SKILLCOOLDOWN FGameplayTag::RequestGameplayTag(FName("Character.State.SkillCooldown"))

#define GAMEPLAYCUE_BOSS_FIRE FGameplayTag::RequestGameplayTag(FName("GameplayCue.Boss.Fire"))