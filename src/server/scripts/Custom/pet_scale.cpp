#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "World.h"

enum PetCalculate
{
     SPELL_HUNTER_PET_CRIT              = 19591,
     SPELL_WARLOCK_PET_CRIT             = 35695,
     SPELL_WARLOCK_PET_HIT_EXPERTISE    = 61013,
     SPELL_HUNTER_PET_HIT_EXPERTISE     = 61017,
     SPELL_DK_PET_HIT                   = 61697,
     SPELL_SHAMAN_PET_HIT               = 61783,
};

class spell_gen_pet_calculate : public SpellScriptLoader
{
    public:
        spell_gen_pet_calculate() : SpellScriptLoader("spell_gen_pet_calculate") { }

        class spell_gen_pet_calculate_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_gen_pet_calculate_AuraScript);

            bool Load()
            {
                if (!GetCaster() || !GetCaster()->GetOwner() || GetCaster()->GetOwner()->GetTypeId() != TYPEID_PLAYER)
                    return false;
                return true;
            }

            void CalculateAmountCritSpell(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
                {
                    // For others recalculate it from:
                    float CritSpell = 0.0f;
                   // Crit from Intellect
                    CritSpell += owner->GetSpellCritFromIntellect();
                    // Increase crit from SPELL_AURA_MOD_SPELL_CRIT_CHANCE
                    CritSpell += owner->GetTotalAuraModifier(SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
                    // Increase crit from SPELL_AURA_MOD_CRIT_PCT
                    CritSpell += owner->GetTotalAuraModifier(SPELL_AURA_MOD_CRIT_PCT);
                    // Increase crit spell from spell crit ratings
                    CritSpell += owner->GetRatingBonusValue(CR_CRIT_SPELL);

                    amount += int32(CritSpell);
                }
            }

            void CalculateAmountCritMelee(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
                {
                    // For others recalculate it from:
                    float CritMelee = 0.0f;
                    // Crit from Agility
                    CritMelee += owner->GetMeleeCritFromAgility();
                    // Increase crit from SPELL_AURA_MOD_WEAPON_CRIT_PERCENT
                    CritMelee += owner->GetTotalAuraModifier(SPELL_AURA_MOD_WEAPON_CRIT_PERCENT);
                    // Increase crit from SPELL_AURA_MOD_CRIT_PCT
                    CritMelee += owner->GetTotalAuraModifier(SPELL_AURA_MOD_CRIT_PCT);
                    // Increase crit melee from melee crit ratings
                    CritMelee += owner->GetRatingBonusValue(CR_CRIT_MELEE);

                    amount += int32(CritMelee);
                }
            }

            void CalculateAmountMeleeHit(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
             {
                if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
                {
                    // For others recalculate it from:
                    float HitMelee = 0.0f;
                   // Increase hit from SPELL_AURA_MOD_HIT_CHANCE
                    HitMelee += owner->GetTotalAuraModifier(SPELL_AURA_MOD_HIT_CHANCE);
                    // Increase hit melee from meele hit ratings
                    HitMelee += owner->GetRatingBonusValue(CR_HIT_MELEE);

                    amount += int32(HitMelee);
                }
            }

            void CalculateAmountSpellHit(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
                {
                    // For others recalculate it from:
                    float HitSpell = 0.0f;
                    // Increase hit from SPELL_AURA_MOD_SPELL_HIT_CHANCE
                    HitSpell += owner->GetTotalAuraModifier(SPELL_AURA_MOD_SPELL_HIT_CHANCE);
                    // Increase hit spell from spell hit ratings
                    HitSpell += owner->GetRatingBonusValue(CR_HIT_SPELL);

                    amount += int32(HitSpell);
                }
            }
            
            void CalculateAmountExpertise(AuraEffect const* /*aurEff*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
                {
                    // For others recalculate it from:
                    float Expertise = 0.0f;
                    // Increase hit from SPELL_AURA_MOD_EXPERTISE
                    Expertise += owner->GetTotalAuraModifier(SPELL_AURA_MOD_EXPERTISE);
                    // Increase Expertise from Expertise ratings
                    Expertise += owner->GetRatingBonusValue(CR_EXPERTISE);

                    amount += int32(Expertise);
                }
            }

            void Register()
            {
                switch (m_scriptSpellId)
                {
                    case SPELL_HUNTER_PET_CRIT:
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountCritMelee, EFFECT_0, SPELL_AURA_MOD_WEAPON_CRIT_PERCENT);
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountCritSpell, EFFECT_1, SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
                        break;
                    case SPELL_WARLOCK_PET_CRIT:
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountCritSpell, EFFECT_0, SPELL_AURA_MOD_SPELL_CRIT_CHANCE);
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountCritMelee, EFFECT_1, SPELL_AURA_MOD_WEAPON_CRIT_PERCENT);
                        break;
                    case SPELL_WARLOCK_PET_HIT_EXPERTISE:
                    case SPELL_HUNTER_PET_HIT_EXPERTISE:
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountMeleeHit, EFFECT_0, SPELL_AURA_MOD_HIT_CHANCE);
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountSpellHit, EFFECT_1, SPELL_AURA_MOD_SPELL_HIT_CHANCE);
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountExpertise, EFFECT_2, SPELL_AURA_MOD_EXPERTISE);
                        break;
                    case SPELL_DK_PET_HIT:
                    case SPELL_SHAMAN_PET_HIT:
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountMeleeHit, EFFECT_0, SPELL_AURA_MOD_HIT_CHANCE);
                        DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_gen_pet_calculate_AuraScript::CalculateAmountSpellHit, EFFECT_1, SPELL_AURA_MOD_SPELL_HIT_CHANCE);
                        break;
                    default:
                        break;
                }
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_gen_pet_calculate_AuraScript();
        }
};

void AddSC_pet_scale()
{
    new spell_gen_pet_calculate();
}