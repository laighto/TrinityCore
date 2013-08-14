/*
 * Copyright (C) 2013  chaosua2008@gmail.com
 *
 * EVENT written by chaosua in 2013 
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

#include "battle_for_gilneas.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "World.h"

class npc_prince_liam : public CreatureScript
{
    public:
        npc_prince_liam() : CreatureScript("npc_prince_liam") { }

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_prince_liamAI(creature);
        }

        struct npc_prince_liamAI : public ScriptedAI
        {
            npc_prince_liamAI(Creature* creature) : ScriptedAI(creature) {}
 
            void Reset() OVERRIDE
            {
                me->Relocate(eventPositionsTeamA[0].GetPositionX(), eventPositionsTeamA[0].GetPositionY(), eventPositionsTeamA[0].GetPositionZ(), eventPositionsTeamA[0].GetOrientation());
                event_active = false;
                intro = false;
                event_intro = false;
                stage2 = false;
                stage2b = false;
                me->CastSpell(me, SPELL_SOLDIER_OF_BFGC, false);
                me->Mount(2409, 512);
                liamGUID = me->GetGUID();
                crossbowman = 0;
                militiacounter = 0;
                resetall = false;
            }

            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                me->Relocate(eventPositionsTeamA[0].GetPositionX(), eventPositionsTeamA[0].GetPositionY(), eventPositionsTeamA[0].GetPositionZ(), eventPositionsTeamA[0].GetOrientation());
                resetall = true;
            }

            void Speech()
            {
                Talk(SAY_INTRO_1);
                events.ScheduleEvent(EVENT_INTRO_2, 7000, 0, 0);
                events.ScheduleEvent(EVENT_INTRO_3, 15000, 0, 0);
                events.ScheduleEvent(EVENT_INTRO_4, 25000, 0, 0);
                events.ScheduleEvent(EVENT_INTRO_5, 33000, 0, 0);
                events.ScheduleEvent(EVENT_INTRO_6, 41000, 0, 0);
                events.ScheduleEvent(EVENT_INTRO_7, 45000, 0, 0);
                events.ScheduleEvent(EVENT_BEGIN_BATTLE, 49000, 0, 0);
                events.ScheduleEvent(RESET_ALL, 900000, 0, 0);
            }

            void DamageTaken(Unit* attacker, uint32& damage) OVERRIDE
            {
                me->Attack(attacker, true);
            }

            void EnterCombat(Unit* who) OVERRIDE
            {

            }

            void EnterEvadeMode() OVERRIDE
            {
                //Talk(SAY_EVADE);
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                if (me->GetHealthPct() < 5)
                    me->SetFullHealth();

                if (intro && !event_intro)
                {
                    Speech();
                    event_intro = true;
                }

                //me->CastSpell(me, SPELL_SOLDIER_OF_BFGC, false);
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case RESET_ALL:
                            resetall=true;
                            break;
                        case EVENT_INTRO_2:
                            Talk(SAY_INTRO_2);
                            break;
                        case EVENT_INTRO_3:
                            Talk(SAY_INTRO_3);
                            break;
                        case EVENT_INTRO_4:
                            Talk(SAY_INTRO_4);
                            break;
                        case EVENT_INTRO_5:
                            Talk(SAY_INTRO_5);
                            break;
                        case EVENT_INTRO_6:
                            Talk(SAY_INTRO_6);
                            break;
                        case EVENT_INTRO_7:
                            Talk(SAY_INTRO_7);
                            break;
                        case EVENT_BEGIN_BATTLE:
                            event_active = true;
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[1].GetPositionX(), eventPositionsTeamA[1].GetPositionY(), eventPositionsTeamA[1].GetPositionZ());
                            //sWorld->SendGMText(30000, crossbowman);
                            events.ScheduleEvent(STAGE1_A, 10000, 0, 0);
                            events.ScheduleEvent(STAGE1, 12000, 0, 0);                 
                            break;
                        case STAGE1:
                            if (Unit* target = me->FindNearestCreature(FORSAKEN_CROSSBOWMAN, 50.0f))
                            {
                                me->GetMotionMaster()->MoveChase(target);
                                me->Attack(target, false);
                                if (urand(0,10) > 7)
                                    Talk(SYA_RANDOM_TXT);
                                //sWorld->SendGMText(30001, target->GetGUID());
                            }
                            if (!stage2)
                                events.ScheduleEvent(STAGE1, urand(2000, 6000), 0, 0);
                            break;
                        case STAGE1_A:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[2].GetPositionX(), eventPositionsTeamA[2].GetPositionY(), eventPositionsTeamA[2].GetPositionZ());
                            break;
                        case STAGE2:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[3].GetPositionX(), eventPositionsTeamA[3].GetPositionY(), eventPositionsTeamA[3].GetPositionZ());
                            //sWorld->SendGMText(30000, crossbowman);
                            break;
                    }
                }

                if(crossbowman > 32 && !stage2)
                {
                    events.Reset();
                    events.ScheduleEvent(STAGE2, 1000, 0, 0);
                    stage2 = true;
                }

                if(resetall)
                    me->DespawnOrUnsummon(100);

                DoMeleeAttackIfReady();
            }

            private:
                EventMap events;
        };

};

npc_prince_liam linker;

class npc_krennan_aranas : public CreatureScript
{
    public:
        npc_krennan_aranas () : CreatureScript("npc_krennan_aranas") { }

        bool OnGossipHello(Player* player, Creature* creature) OVERRIDE
        {
            if (player->IsActiveQuest(QUEST_BFGC) && !intro)
            {
                //Load gossip menu option from DB
                player->PrepareGossipMenu(creature, 11061);
                player->SendPreparedGossip(creature);
            }
            else 
                player->PlayerTalkClass->SendGossipMenu(11189, creature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) OVERRIDE
        {
            player->PlayerTalkClass->SendCloseGossip();
            creature->AI()->Talk(0);
            intro = true;

           //if (Creature* liam = creature->FindNearestCreature(PRINCE_LIAM_GREYMANE, 50.0f))
           //    liam->AI()->Reset();
           //player->CastSpell(player, SUMMON_DUROTAR_RIDIBG_WOLF, true);
           // if (Creature* summon1 = creature->SummonCreature(RAIDER_KERR, -825.47f, -4900.59f, 19.63f, 1.086f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);

            return true;
        }
};

class npc_gilnean_millitia : public CreatureScript
{
    public:
        npc_gilnean_millitia() : CreatureScript("npc_gilnean_millitia") { }

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_gilnean_millitiaAI(creature);
        }

        struct npc_gilnean_millitiaAI : public ScriptedAI
        {
            npc_gilnean_millitiaAI(Creature* creature) : ScriptedAI(creature) {}

            void Reset() OVERRIDE
            {
                 pos1 = false;
                 pos2 = false;
                 pos3 = false;
                 pos4 = false;
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                if(event_active && !pos1)
                {
                    if (militiacounter > 20)
                    {
                        militiacounter = 0;
                        pos1 = true;
                        pos2 = true;
                    }
                    events.ScheduleEvent(STAGE1_B, 100, 0, 0);
                }
                
                if(event_active && pos2 && crossbowman > 5)
                {
                    if (militiacounter > 20)
                    {
                        militiacounter = 0;
                        pos2 = false;
                        pos3 = true;
                    }
                    events.ScheduleEvent(STAGE1_B_1, urand(30000,40000), 0, 0);
                }
                
                if(event_active && pos3 && crossbowman>10)
                {
                    if (militiacounter>20)
                    {
                        militiacounter = 0;
                        pos3 = false;
                        pos4 = true;
                    }
                    events.ScheduleEvent(STAGE1_B_2, urand(30000,40000), 0, 0);
                }
                
                if(event_active && pos4 && crossbowman > 20)
                {
                    if (militiacounter>20)
                    {
                        militiacounter = 0;
                        pos4 = false;
                    }
                    events.ScheduleEvent(STAGE1_B_3, urand(30000,40000), 0, 0);
                }

                if(stage2 && !stage2b)
                {
                    if (militiacounter > 20)
                        stage2b = true;
                    events.ScheduleEvent(STAGE2_B, 1000, 0, 0);
                }

                if (me->GetHealthPct() < 5)
                    me->SetFullHealth();

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case STAGE1_B:
                            dist = frand(-4, 4);
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[0].GetPositionX()+dist, eventPositionsTeamB[0].GetPositionY()+dist, eventPositionsTeamB[0].GetPositionZ());
                            events.ScheduleEvent(STAGE1_B_FIGHT, 10000, 0, 0);
                            militiacounter++;
                            break;
                        case STAGE1_B_1:
                            dist = frand(-4, 4);
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[1].GetPositionX()+dist, eventPositionsTeamB[1].GetPositionY()+dist, eventPositionsTeamB[1].GetPositionZ());
                            events.RescheduleEvent(STAGE1_B_FIGHT, 10000, 0, 0);
                            militiacounter++;
                            break;
                        case STAGE1_B_2:
                            dist = frand(-4, 4);
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[2].GetPositionX()+dist, eventPositionsTeamB[2].GetPositionY()+dist, eventPositionsTeamB[2].GetPositionZ());
                            events.RescheduleEvent(STAGE1_B_FIGHT, 10000, 0, 0);
                            militiacounter++;
                            break;
                        case STAGE1_B_3:
                            dist = frand(-4, 4);
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[3].GetPositionX()+dist, eventPositionsTeamB[3].GetPositionY()+dist, eventPositionsTeamB[3].GetPositionZ());
                            events.RescheduleEvent(STAGE1_B_FIGHT, 10000, 0, 0);
                            militiacounter++;
                            break;
                        case STAGE1_B_FIGHT:
                            if (Unit* target = me->FindNearestCreature(FORSAKEN_CROSSBOWMAN, 50.0f))
                            {
                                me->GetMotionMaster()->MoveChase(target);
                                me->Attack(target, false);
                                //sWorld->SendGMText(30001, target->GetGUID());
                            }
                            if (!stage2)
                                events.ScheduleEvent(STAGE1_B_FIGHT, urand(6000, 15000), 0, 0);
                            break;
                        case STAGE2_B:
                            dist = frand(-4, 4);
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[4].GetPositionX()+dist, eventPositionsTeamB[4].GetPositionY()+dist, eventPositionsTeamB[4].GetPositionZ());
                            militiacounter++;
                            break;
                    }
                }
                
                if(resetall)
                    me->DespawnOrUnsummon(100);

                DoMeleeAttackIfReady();
            }
            private:
                EventMap events;
                int dist;
                bool pos1;
                bool pos2;
                bool pos3;
                bool pos4;
        };
};

class npc_forsaken_crossbow : public CreatureScript
{
    public:
        npc_forsaken_crossbow() : CreatureScript("npc_forsaken_crossbow") { }

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_forsaken_crossbowAI(creature);
        }

        struct npc_forsaken_crossbowAI : public ScriptedAI
        {
            npc_forsaken_crossbowAI(Creature* creature) : ScriptedAI(creature) {}
 
            void Reset() OVERRIDE
            {
                 
            }

            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                crossbowman = crossbowman + 1;
                //sWorld->SendGMText(30000, crossbowman);
            }

            void Update(uint32 uiDiff) OVERRIDE
            {
                if(resetall)
                    me->DespawnOrUnsummon(100);

            }
        };
};

class npc_gorrerot : public CreatureScript
{
    public:
        npc_gorrerot () : CreatureScript("npc_gorrerot") { }

    void Update (uint32 diff) OVERRIDE
    {

    }
};

class npc_lady_sylvanas : public CreatureScript
{
    public:
        npc_lady_sylvanas () : CreatureScript("npc_lady_sylvanas") { }

    void Update (uint32 diff) OVERRIDE
    {

    }
};


void AddSC_bfgc_script()
{
    new npc_krennan_aranas;
    new npc_prince_liam;
    new npc_gilnean_millitia;
    new npc_forsaken_crossbow;
    new npc_gorrerot;
    new npc_lady_sylvanas;
}
