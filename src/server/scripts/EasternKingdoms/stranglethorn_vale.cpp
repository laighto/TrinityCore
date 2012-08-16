/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Stranglethorn_Vale
SD%Complete: 100
SDComment: Quest support: 592
SDCategory: Stranglethorn Vale
EndScriptData */

/* ContentData
mob_yenniku
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "World.h"

/*######
## mob_yenniku
######*/

class mob_yenniku : public CreatureScript
{
public:
    mob_yenniku() : CreatureScript("mob_yenniku") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_yennikuAI (creature);
    }

    struct mob_yennikuAI : public ScriptedAI
    {
        mob_yennikuAI(Creature* creature) : ScriptedAI(creature)
        {
            bReset = false;
        }

        uint32 Reset_Timer;
        bool bReset;

        void Reset()
        {
            Reset_Timer = 0;
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_NONE);
        }

        void SpellHit(Unit* caster, const SpellInfo* spell)
        {
            if (caster->GetTypeId() == TYPEID_PLAYER)
            {
                                                                //Yenniku's Release
                if (!bReset && CAST_PLR(caster)->GetQuestStatus(592) == QUEST_STATUS_INCOMPLETE && spell->Id == 3607)
                {
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_STUN);
                    me->CombatStop();                   //stop combat
                    me->DeleteThreatList();             //unsure of this
                    me->setFaction(83);                 //horde generic

                    bReset = true;
                    Reset_Timer = 60000;
                }
            }
            return;
        }

        void EnterCombat(Unit* /*who*/) {}

        void UpdateAI(const uint32 diff)
        {
            if (bReset)
            {
                if (Reset_Timer <= diff)
                {
                    EnterEvadeMode();
                    bReset = false;
                    me->setFaction(28);                     //troll, bloodscalp
                    return;
                }
                else Reset_Timer -= diff;

                if (me->isInCombat() && me->getVictim())
                {
                    if (me->getVictim()->GetTypeId() == TYPEID_PLAYER)
                    {
                        Unit* victim = me->getVictim();
                        if (CAST_PLR(victim)->GetTeam() == HORDE)
                        {
                            me->CombatStop();
                            me->DeleteThreatList();
                        }
                    }
                }
             }

            //Return since we have no target
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

const Position allyPositions[3] =
{
    { -13248.2f, 282.385f, 21.8568f, 0.12517f },
    { -13193.7f, 315.692f, 21.8568f, 4.36162f },
    { -13162.7f, 262.096f, 21.8568f, 2.91257f },
};

class mob_ressurect : public PlayerScript
{
public:
    mob_ressurect() : PlayerScript("mob_ressurect") { }

    void OnPVPKill(Player* killer, Player* killed)
    {
        if (killed->GetAreaId() == 2177) /*&& killed->GetMapId() == 33*/
        {
            if (killed->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
                killed->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

            killed->KillPlayer();
            killed->ResurrectPlayer(1.0f, false);

            if (killer->GetAreaId() != 2177)
            {
                killer->CastSpell(killer, 15007, true);
                if (Aura * aur = killer->GetAura(15007))
                    aur->SetDuration(30*IN_MILLISECONDS); // Слабость негодникам
            }

            killed->CastSpell(killed, 48325, true);
            if (Aura * aur = killed->GetAura(48325))
                aur->SetDuration(7*IN_MILLISECONDS); //  Божественный щит

            if (sWorld->getBoolConfig(PvPEvent))
            {
                killed->CastSpell(killed, 9454, true);
                if (Aura * freeze = killed->GetAura(9454))
                freeze->SetDuration(300*IN_MILLISECONDS); //  Заморозка
            }

            uint32 rnd = urand(0,2);
            killed->TeleportTo(0, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());
        }
    }
};

class mod_afk : public PlayerScript
{
public:
    mod_afk() : PlayerScript("mod_afk") { }

    void OnPlayerAfk(Player* player)
    {
        if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_AFK) && player->GetZoneId() == 4395/*Dalaran zone*/)
        {
            uint32 rnd = urand(0,2);
            player->TeleportTo(0, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());
        }
    }
};

void AddSC_stranglethorn_vale()
{
    new mob_yenniku();
    new mob_ressurect();
    new mod_afk();
}
