
#pragma once

#include "GameplayTagContainer.h"

#define LOSTARKTAG_DATA_DAMAGE FGameplayTag::RequestGameplayTag(FName("Data.Damage"))
#define LOSTARKTAG_CHARACTER_ISDEAD FGameplayTag::RequestGameplayTag(FName("Character.State.IsDead"))
#define LOSTARKTAG_CHARACTER_ATTACK FGameplayTag::RequestGameplayTag(FName("Character.State.Attack"))
#define LOSTARKTAG_CHARACTER_ISSKILLING FGameplayTag::RequestGameplayTag(FName("Character.State.IsSkilling"))
#define LOSTARKTAG_CHARACTER_SKILLCOOLDOWN FGameplayTag::RequestGameplayTag(FName("Character.State.SkillCooldown"))

#define LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_EXP FGameplayTag::RequestGameplayTag(FName("Attributes.Player.Primary.EXP"))
#define LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_EXPEDITIONEXP FGameplayTag::RequestGameplayTag(FName("Attributes.Player.Primary.ExpeditionEXP"))
#define LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_REQUIREDEXP FGameplayTag::RequestGameplayTag(FName("Attributes.Player.Primary.RequiredEXP"))
#define LOSTARKTAG_ATTRIBUTES_PLAYER_PRIMARY_EXPEDITIONREQUIREDEXP FGameplayTag::RequestGameplayTag(FName("Attributes.Player.Primary.ExpeditionRequiredEXP"))

#define LOSTARKTAG_ATTRIBUTES_PLAYER_VITAL_CURRENTLIFEPOINT FGameplayTag::RequestGameplayTag(FName("Attributes.Player.Vital.CurrentLifePoint"))
#define LOSTARKTAG_ATTRIBUTES_PLAYER_VITAL_CURRENTMANAPOINT FGameplayTag::RequestGameplayTag(FName("Attributes.Player.Vital.CurrentManaPoint"))

#define GAMEPLAYCUE_BOSS_FIRE FGameplayTag::RequestGameplayTag(FName("GameplayCue.Boss.Fire"))