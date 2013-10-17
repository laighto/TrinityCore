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

#include "GridDefines.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Cell.h"
#include "CellImpl.h"

class npc_krennan_aranas : public CreatureScript
{
    public:
        npc_krennan_aranas() : CreatureScript("npc_krennan_aranas") { }

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

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/) OVERRIDE
        {
            player->PlayerTalkClass->SendCloseGossip();
            //creature->AI()->Talk(0);
            intro = true;
            return true;
        }
};

class npc_prince_liam : public CreatureScript
{
    public:
        npc_prince_liam() : CreatureScript("npc_prince_liam") { }

        struct npc_prince_liamAI : public ScriptedAI
        {
            npc_prince_liamAI(Creature* creature) : ScriptedAI(creature) {}

            EventMap events;
            bool ignoredamage;
            bool prepared;
 
            void Reset() OVERRIDE
            {
                me->SetVisible(true);
                me->Relocate(eventPositionsTeamA[0].GetPositionX(), eventPositionsTeamA[0].GetPositionY(), eventPositionsTeamA[0].GetPositionZ(), eventPositionsTeamA[0].GetOrientation());
                event_active = false;
                intro = false;
                event_intro = false;
                stage2 = false;
                stage2b = false;
                me->CastSpell(me, SPELL_SOLDIER_OF_BFGC, false);
                me->Mount(2409, 512);
                crossbowman = 0;
                abom = 0;
                military_quoter = false;
                gurerrot = false;
                s2center = false;
                boss_gurerrot_dead = false;
                resetall = false;

                pos1 = false;
                pos2 = false;
                pos3 = false;
                pos4 = false;
                mpos1 = false; //Military quoter enter
                mpos2 = false; //Military quoter center
                mpos3 = false; //boss gurerroth
                events.Reset();
                SpawnMilitia();
                s3pos = false;
                endpoint = false;
                ignoredamage = true;
                stage4 = false;
                boss2 = false;
                bfgcdone = false;
                prepared = false;
            }

            void SpawnMilitia()
            {
                for (int i=0; i < 20; i++) 
                    if(Creature* creature = me->SummonCreature(GILNEAN_MILLITIA, eventPositionsMilitia[i].GetPositionX(), eventPositionsMilitia[i].GetPositionY(), eventPositionsMilitia[i].GetPositionZ(), eventPositionsMilitia[i].GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 300000))
                        militia[i] = creature;
            }

            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                me->Relocate(eventPositionsTeamA[0].GetPositionX(), eventPositionsTeamA[0].GetPositionY(), eventPositionsTeamA[0].GetPositionZ(), eventPositionsTeamA[0].GetOrientation());
                resetall = true;
            }

            void JustRespawned() OVERRIDE
            {
                Reset();
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
                events.ScheduleEvent(EVENT_BEGIN_BATTLE, 48000, 0, 0);
                events.ScheduleEvent(RESET_ALL, 900000, 0, 0);
            }

            void SearchTarget() OVERRIDE
            {
                if((!military_quoter || s3pos) && !ignoredamage)
                {
                    if (Unit* target = me->FindNearestCreature(FORSAKEN_CROSSBOWMAN, 70.0f))
                    {                  
                        if (target->GetDistance2d(me) < 6)
                        {
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);
                            if (urand(0, 6) > 5)
                                Talk(SAY_RANDOM_TXT);
                        }
                        else if (target->GetDistance2d(me) < 30)
                        {
                            me->GetMotionMaster()->MoveChase(target, 7.0f);
                            me->CastSpell(target, SPELL_SHOOT, false);
                            if (urand(0, 6) > 5)
                                Talk(SAY_RANDOM_TXT);
                        }
                        else 
                        {
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);
                        }
                    }
                }
                else if (!ignoredamage)
                {
                    if (Unit* target = me->FindNearestCreature(VILE_ABOMINATION, 70.0f))
                    {                  
                        if (target->GetDistance2d(me) < 6)
                        {
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);
                            if (urand(0, 6) > 5)
                                Talk(SAY_RANDOM_TXT);
                        }
                        else if (target->GetDistance2d(me) < 30)
                        {
                            me->GetMotionMaster()->MoveChase(target, 8.0f);
                            me->CastSpell(target, SPELL_SHOOT, false);
                            if (urand(0, 6) > 5)
                                Talk(SAY_RANDOM_TXT);
                        }
                        else 
                        {
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);
                        }
                    }
                    else if (Unit* target = me->FindNearestCreature(FORSAKEN_CROSSBOWMAN, 60.0f))
                    {                  
                        if (target->GetDistance2d(me) < 6)
                        {
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);
                            if (urand(0, 6) > 5)
                                Talk(SAY_RANDOM_TXT);
                        }
                        else if (target->GetDistance2d(me) < 30)
                        {
                            me->GetMotionMaster()->MoveChase(target, 10.0f);
                            me->CastSpell(target, SPELL_SHOOT, false);
                            if (urand(0, 6) > 5)
                                Talk(SAY_RANDOM_TXT);
                        }
                        else 
                        {
                            me->GetMotionMaster()->MoveChase(target);
                            me->Attack(target, true);
                        }
                    }
                }
            }

            void DamageTaken(Unit* attacker, uint32& damage) OVERRIDE
            {
                if (damage >= me->GetHealth())
                    damage = 1;

                if(!ignoredamage)
                    me->Attack(attacker, true);
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
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[1].GetPositionX(), eventPositionsTeamA[1].GetPositionY(), eventPositionsTeamA[1].GetPositionZ(), true);
                            events.ScheduleEvent(STAGE_1_CENTER, 15000, 0, 0);
                            events.ScheduleEvent(STAGE_1_FIGHT, 20000, 0, 0);                 
                            break;
                        case STAGE_1_FIGHT:
                            SearchTarget();
                            if (!stage2)
                                events.ScheduleEvent(STAGE_1_FIGHT, 3000, 0, 0);
                            ignoredamage = false;
                            break;
                        case STAGE_1_CENTER:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[2].GetPositionX(), eventPositionsTeamA[2].GetPositionY(), eventPositionsTeamA[2].GetPositionZ(), true);
                            ignoredamage = true;
                            events.RescheduleEvent(STAGE_1_FIGHT, 5000, 0, 0);
                            break;
                        case STAGE2_PREPARE:
                            ignoredamage = true;
                            me->CombatStop(true);
                            me->GetMotionMaster()->Clear();
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[3].GetPositionX(), eventPositionsTeamA[3].GetPositionY(), eventPositionsTeamA[3].GetPositionZ(), true);
                            //me->Relocate(eventPositionsTeamA[3].GetPositionX(), eventPositionsTeamA[3].GetPositionY(), eventPositionsTeamA[3].GetPositionZ(), eventPositionsTeamA[3].GetOrientation());
                            if (!prepared)
                            {
                                events.RescheduleEvent(STAGE2_PREPARE, 2000, 0, 0);
                                prepared = true;
                            }
                            break;
                        case STAGE2: // Military quoter
                            me->GetMotionMaster()->Clear();
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            //me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[4].GetPositionX(), eventPositionsTeamA[4].GetPositionY(), eventPositionsTeamA[4].GetPositionZ(), true);
                            //me->GetMotionMaster()->MovePath(99999, false); 
                            me->SetVisible(false);
                            me->Relocate(eventPositionsTeamA[4].GetPositionX(), eventPositionsTeamA[4].GetPositionY(), eventPositionsTeamA[4].GetPositionZ(), eventPositionsTeamA[4].GetOrientation());
                            military_quoter = true;
                            ignoredamage = true;
                            me->SetVisible(true);
                            break;
                        case STAGE2_A_FIGHT:
                            ignoredamage = false;
                            SearchTarget();
                            if (!gurerrot)
                                events.ScheduleEvent(STAGE2_A_FIGHT, 3500, 0, 0);
                            break;
                        case STAGE2_A_CENTER:
                            me->GetMotionMaster()->Clear();
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->StopMoving(); 
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[5].GetPositionX(), eventPositionsTeamA[5].GetPositionY(), eventPositionsTeamA[5].GetPositionZ(), true);
                            ignoredamage = true;
                            events.RescheduleEvent(STAGE2_A_FIGHT, 5000, 0, 0);
                            break;
                        case STAGE_BOSS_G:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            ignoredamage = true;
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[6].GetPositionX(), eventPositionsTeamA[6].GetPositionY(), eventPositionsTeamA[6].GetPositionZ(), true);
                            ignoredamage = true;
                            break;
                        case STAGE_BOSS_FIGHT_G:
                            ignoredamage = false;
                            if (Unit* target = me->FindNearestCreature(GORERROT, 10.0f))
                            {
                                me->GetMotionMaster()->MoveChase(target, 6.0f);
                                me->CastSpell(target, SPELL_SHOOT, false);
                            }
                            else events.ScheduleEvent(STAGE_BOSS_G, 100, 0, 0);

                            if (!boss_gurerrot_dead)
                                events.ScheduleEvent(STAGE_BOSS_FIGHT_G, 3500, 0, 0);
                            break;
                        case STAGE_3_POINT_1:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[7].GetPositionX(), eventPositionsTeamA[7].GetPositionY(), eventPositionsTeamA[7].GetPositionZ(), true);
                            ignoredamage = true;
                            break;
                        case STAGE_3_POINT_2:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[8].GetPositionX(), eventPositionsTeamA[8].GetPositionY(), eventPositionsTeamA[8].GetPositionZ(), true);
                            ignoredamage = true;
                            events.RescheduleEvent(STAGE_3_FIGHT_A, 7000, 0, 0);
                            break;
                        case STAGE_3_POINT_3:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[9].GetPositionX(), eventPositionsTeamA[9].GetPositionY(), eventPositionsTeamA[9].GetPositionZ(), true);
                            ignoredamage = true;
                            events.RescheduleEvent(STAGE_3_FIGHT_A, 7000, 0, 0);
                            break;
                        case STAGE_3_POINT_4:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->Clear();
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[10].GetPositionX(), eventPositionsTeamA[10].GetPositionY(), eventPositionsTeamA[10].GetPositionZ(), true);
                            ignoredamage = true;
                            events.RescheduleEvent(STAGE_3_FIGHT_A, 7000, 0, 0);
                            break;
                        case STAGE_3_POINT_5:
                            endpoint = true;
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[11].GetPositionX(), eventPositionsTeamA[11].GetPositionY(), eventPositionsTeamA[11].GetPositionZ(), false);
                            ignoredamage = true;
                            break;
                        case STAGE_3_FIGHT_A:
                            SearchTarget();
                            if (!endpoint)
                                events.ScheduleEvent(STAGE_3_FIGHT_A, 3500, 0, 0);
                            ignoredamage = false;
                            break;
                        case STAGE_3_POINT_DESPAWN:
                            me->SetVisible(false);
                            stage4 = true;
                            break;
                        default:
                            break;
                    }
                }

                if(crossbowman > 33 && !stage2)
                {
                    ignoredamage = true;
                    stage2 = true;
                    events.ScheduleEvent(STAGE2_PREPARE, 100, 0, 0);
                    events.ScheduleEvent(STAGE2, 15000, 0, 0);
                    events.ScheduleEvent(STAGE2_A_FIGHT, 20000, 0, 0);
                }

                if(abom > 15 && !s2center)
                {
                    events.ScheduleEvent(STAGE2_A_CENTER, 1000, 0, 0);
                    s2center = true;
                }

                if(abom > 18 && !gurerrot)
                {
                    gurerrot = true;
                    events.ScheduleEvent(STAGE_BOSS_G, 1000, 0, 0);
                    events.ScheduleEvent(STAGE_BOSS_FIGHT_G, 10000, 0, 0);
                    abom = 0;
                }

                if (boss_gurerrot_dead && !s3pos)
                {
                    events.ScheduleEvent(STAGE_3_POINT_1, 8000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_2, 25000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_3, 45000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_4, 70000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_4, 90000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_5, 100000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_DESPAWN, 110000, 0, 0);
                    events.ScheduleEvent(STAGE_3_FIGHT_A, 16000, 0, 0);
                    s3pos = true;
                }

                if(resetall || bfgcdone)
                {
                    me->Relocate(eventPositionsTeamA[0].GetPositionX(), eventPositionsTeamA[0].GetPositionY(), eventPositionsTeamA[0].GetPositionZ(), eventPositionsTeamA[0].GetOrientation());
                    me->SetRespawnTime(120);
                    me->DespawnOrUnsummon(100);
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_prince_liamAI(creature);
        }
};

class npc_gilnean_millitia : public CreatureScript
{
    public:
        npc_gilnean_millitia() : CreatureScript("npc_gilnean_millitia") { }

        struct npc_gilnean_millitiaAI : public ScriptedAI
        {
            npc_gilnean_millitiaAI(Creature* creature) : ScriptedAI(creature) {}

            EventMap events;
            float dist;
            bool ignoredamage;
            bool boss2b;

            void Reset() OVERRIDE
            {
                events.Reset();
                s3posb = false;
                ignoredamage = false;
                boss2b = false;
            }

            void DamageTaken(Unit* attacker, uint32& damage) OVERRIDE
            {
                if (damage >= me->GetHealth())
                    damage = 1;

                if(!ignoredamage)
                {
                    me->GetMotionMaster()->MoveChase(attacker);
                    me->Attack(attacker, true);
                }
            }

            void SearchTargets(Unit* attacker) OVERRIDE
            {
                if((!military_quoter || s3posb) && !ignoredamage)
                {
                    if (Unit* target = attacker->FindNearestCreature(FORSAKEN_CROSSBOWMAN, 80.0f))
                    {                  
                        if (target->GetDistance2d(attacker) < 6)
                        {
                            attacker->GetMotionMaster()->MoveChase(target);
                            attacker->Attack(target, true);
                        }
                        else if (target->GetDistance2d(attacker) < 30)
                        {
                            attacker->CastSpell(target, SPELL_SHOOT, false);
                        }
                        else 
                        {
                            attacker->GetMotionMaster()->MoveChase(target, 10.0f);
                            attacker->Attack(target, true);
                        }
                    }
                }
                else if (!ignoredamage)
                {
                    if (Unit* target = attacker->FindNearestCreature(VILE_ABOMINATION, 70.0f))
                    {                  
                        if (target->GetDistance2d(attacker) < 6)
                        {
                            attacker->GetMotionMaster()->MoveChase(target);
                            attacker->Attack(target, true);
                        }
                        else if (target->GetDistance2d(attacker) < 30)
                        {
                            attacker->CastSpell(target, SPELL_SHOOT, false);
                        }
                        else 
                        {
                            attacker->GetMotionMaster()->MoveChase(target, 10.0f);
                            attacker->Attack(target, true);
                        }
                    }
                    else if (Unit* target = attacker->FindNearestCreature(FORSAKEN_CROSSBOWMAN, 50.0f))
                    {                  
                        if (target->GetDistance2d(attacker) < 6)
                        {
                            attacker->GetMotionMaster()->MoveChase(target);
                            attacker->Attack(target, true);
                        }
                        else if (target->GetDistance2d(attacker) < 30)
                        {
                            attacker->CastSpell(target, SPELL_SHOOT, false);
                        }
                        else 
                        {
                            attacker->GetMotionMaster()->MoveChase(target, 10.0f);
                            attacker->Attack(target, true);
                        }
                    }
                }
            }

           /* void DoMeleeAttackIfReady() OVERRIDE
            {
                if (me->GetVictim())
                {
                    me->GetMotionMaster()->MoveIdle();
                    me->Attack(me->GetVictim(), false);
                }
            }*/

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case STAGE1_B_1:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[1].GetPositionX()+dist, eventPositionsTeamB[1].GetPositionY()+dist, eventPositionsTeamB[1].GetPositionZ(), true);
                                }
                            }
                            ignoredamage = true;
                            events.ScheduleEvent(STAGE_1_B_FIGHT, 20000, 0, 0);
                            break;
                        case STAGE1_B_2:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[2].GetPositionX()+dist, eventPositionsTeamB[2].GetPositionY()+dist, eventPositionsTeamB[2].GetPositionZ(), true);
                                }
                            }
                            ignoredamage = true;
                            break;
                        case STAGE1_B_3:
                            for (int i = 0; i < 20; i++)
                            {
                                if (militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[3].GetPositionX()+dist, eventPositionsTeamB[3].GetPositionY()+dist, eventPositionsTeamB[3].GetPositionZ(), true);
                                }
                            }      
                            ignoredamage = true;
                            break;
                        case STAGE_1_B_FIGHT:
                            for (int i = 0; i < 20; i++)
                            {
                                if (militia[i] && militia[i]->IsAlive())
                                {
                                    SearchTargets(militia[i]);
                                }
                            }
                            ignoredamage = false;
                            if (!stage2)
                                events.ScheduleEvent(STAGE_1_B_FIGHT, urand(3000, 5000), 0, 0);
                            break;
                        case STAGE2_B:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->CombatStop(true);
                                    militia[i]->GetMotionMaster()->Clear();
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[4].GetPositionX()+dist, eventPositionsTeamB[4].GetPositionY()+dist, eventPositionsTeamB[4].GetPositionZ(), true);
                                   // militia[i]->Relocate(eventPositionsTeamB[4].GetPositionX()+dist, eventPositionsTeamB[4].GetPositionY()+dist, eventPositionsTeamB[4].GetPositionZ(), eventPositionsTeamB[4].GetOrientation());
                                }
                            }
                            ignoredamage = true;
                            break;
                        case STAGE2B:  // Military quoter
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->GetMotionMaster()->Clear();
                                    //militia[i]->GetMotionMaster()->MovePath(99999, false);   
                                    militia[i]->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                                    //militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[5].GetPositionX()+dist, eventPositionsTeamB[5].GetPositionY()+dist, eventPositionsTeamB[5].GetPositionZ(), true);
                                    militia[i]->Relocate(eventPositionsTeamB[5].GetPositionX(), eventPositionsTeamB[5].GetPositionY(), eventPositionsTeamB[5].GetPositionZ(), eventPositionsTeamB[5].GetOrientation());
                                }
                            }
                            ignoredamage = true;
                            break;
                        case STAGE2_B_1:  // Military quoter center
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->GetMotionMaster()->Clear();
                                    militia[i]->StopMoving();
                                    militia[i]->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[6].GetPositionX()+dist, eventPositionsTeamB[6].GetPositionY()+dist, eventPositionsTeamB[6].GetPositionZ(), true);
                                }
                            }
                            ignoredamage = true;
                            break;
                        case STAGE_2_B_FIGHT:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                    SearchTargets(militia[i]);
                            }
                            ignoredamage = false;
                            if (!gurerrot)
                                events.ScheduleEvent(STAGE_2_B_FIGHT, urand(2000, 5000), 0, 0);
                            break;
                        case STAGE_BOSS_Gm:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[7].GetPositionX()+dist, eventPositionsTeamB[7].GetPositionY()+dist, eventPositionsTeamB[7].GetPositionZ(), true);
                                }
                            }
                            ignoredamage = true;
                            break;
                        case STAGE_BOSS_FIGHT_Gm:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    if (Unit* target = militia[i]->FindNearestCreature(GORERROT, 10.0f))
                                    {
                                        if (target->GetDistance2d(militia[i]) < 5)
                                        {
                                             militia[i]->GetMotionMaster()->MoveChase(target, 8.0f);
                                             militia[i]->Attack(target, true);
                                        }
                                        if (urand(0, 1) == 1)
                                        {
                                            militia[i]->GetMotionMaster()->MoveChase(target, 10.0f);
                                            militia[i]->CastSpell(target, SPELL_SHOOT, false);
                                        }
                                    }
                                    else events.ScheduleEvent(STAGE_BOSS_Gm, 1000, 0, 0);
                                }
                            }
                            ignoredamage = false;
                            if (!boss_gurerrot_dead)
                                events.ScheduleEvent(STAGE_BOSS_FIGHT_Gm, 2000, 0, 0);
                            break;
                        case STAGE_3_POINT_1:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, militia[i]->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->Clear();
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[7].GetPositionX()+dist, eventPositionsTeamA[7].GetPositionY()+dist, eventPositionsTeamA[7].GetPositionZ(), true);
                                }
                            }
                            ignoredamage = true;
                            break;
                        case STAGE_3_POINT_2:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, militia[i]->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->Clear();
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[8].GetPositionX()+dist, eventPositionsTeamA[8].GetPositionY()+dist, eventPositionsTeamA[8].GetPositionZ(), true);
                                }
                            }
                            events.RescheduleEvent(STAGE_3_FIGHT_B, 7000, 0, 0);
                            ignoredamage = true;
                            break;
                        case STAGE_3_POINT_3:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, militia[i]->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->Clear();
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[9].GetPositionX()+dist, eventPositionsTeamA[9].GetPositionY()+dist, eventPositionsTeamA[9].GetPositionZ(), true);
                                }
                            }
                            events.RescheduleEvent(STAGE_3_FIGHT_B, 7000, 0, 0);
                            ignoredamage = true;
                            break;
                        case STAGE_3_POINT_4:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, militia[i]->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->Clear();
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[10].GetPositionX()+dist, eventPositionsTeamA[10].GetPositionY()+dist, eventPositionsTeamA[10].GetPositionZ(), true);
                                }
                            }
                            events.RescheduleEvent(STAGE_3_FIGHT_B, 7000, 0, 0);
                            ignoredamage = true;
                            break;
                        case STAGE_3_POINT_5:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-4, 4);
                                    militia[i]->SetSpeed(MOVE_RUN, militia[i]->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->Clear();
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamA[11].GetPositionX()+dist, eventPositionsTeamA[11].GetPositionY()+dist, eventPositionsTeamA[11].GetPositionZ(), false);
                                }
                            }
                            ignoredamage = true;
                            break;
                        case STAGE_3_FIGHT_B:
                            for (int i = 0; i < 20; i++)
                                if(militia[i] && militia[i]->IsAlive())
                                    SearchTargets(militia[i]);
                            ignoredamage = false;
                            if (!endpoint)
                                events.ScheduleEvent(STAGE_3_FIGHT_B, 3500, 0, 0);
                            break;
                        case STAGE_4:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    dist = frand(-5, 5);
                                    militia[i]->SetSpeed(MOVE_RUN, militia[i]->GetSpeedRate(MOVE_RUN), true);
                                    militia[i]->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[8].GetPositionX()+dist, eventPositionsTeamB[8].GetPositionY()+dist, eventPositionsTeamB[8].GetPositionZ(), true);
                                }
                            }
                            break;
                        case STAGE_4_FIGHT:
                            for (int i = 0; i < 20; i++)
                            {
                                if(militia[i] && militia[i]->IsAlive())
                                {
                                    if (Unit* target = militia[i]->FindNearestCreature(LADY_SYLVANAS_WINDRUNNER, 100.0f))
                                    {
                                        militia[i]->GetMotionMaster()->MoveChase(target, 16.0f);
                                        militia[i]->CastSpell(target, SPELL_SHOOT, false);
                                    }
                                    else events.ScheduleEvent(STAGE_4, 1000, 0, 0);
                                }
                            }
                            if (!bfgcdone)
                                events.ScheduleEvent(STAGE_4_FIGHT, 3500, 0, 0);
                            break;
                        default:
                            break;
                    }
                }
                
                if (event_active && !pos1)
                {
                    pos1 = true;
                    events.ScheduleEvent(STAGE1_B_1, 100, 0, 0);
                }
                
                if (event_active && crossbowman > 1 && !pos2)
                {
                    events.ScheduleEvent(STAGE_1_B_FIGHT, 7000, 0, 0);
                    pos2 = true;
                    pos3 = true;
                }

                if(event_active && pos3 && crossbowman > 10)
                {
                    pos3 = false;
                    pos4 = true;
                    events.ScheduleEvent(STAGE1_B_2, urand(2000,5000), 0, 0);
                    events.RescheduleEvent(STAGE_1_B_FIGHT, 15000, 0, 0);
                }
                
                if(event_active && pos4 && crossbowman > 23)
                {
                    pos4 = false;
                    events.ScheduleEvent(STAGE1_B_3, urand(2000,5000), 0, 0);
                    events.RescheduleEvent(STAGE_1_B_FIGHT, 15000, 0, 0);
                }

                if(stage2 && !stage2b)
                {
                    stage2b = true;
                    events.ScheduleEvent(STAGE2_B, 1000, 0, 0);
                }

                if(military_quoter && !mpos1 && stage2b)
                {
                    ignoredamage = true;
                    mpos1 = true;
                    events.ScheduleEvent(STAGE2B, 8000, 0, 0);
                    events.RescheduleEvent(STAGE_2_B_FIGHT, 17000, 0, 0);
                }
                else if (military_quoter && !mpos2 && abom > 12)
                {
                    mpos2 = true;
                    events.ScheduleEvent(STAGE2_B_1, 1000, 0, 0); //move to center of military quoter
                    events.RescheduleEvent(STAGE_2_B_FIGHT, 15000, 0, 0);
                }

                if(gurerrot && !mpos3)
                {
                    mpos3 = true;
                    ignoredamage = true;
                    events.ScheduleEvent(STAGE_BOSS_Gm, 1000, 0, 0);
                    events.RescheduleEvent(STAGE_BOSS_FIGHT_Gm, 10000, 0, 0);
                }

                if (boss_gurerrot_dead && !s3posb)
                {
                    events.ScheduleEvent(STAGE_3_POINT_1, 8000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_2, 30000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_3, 65000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_4, 80000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_4, 95000, 0, 0);
                    events.ScheduleEvent(STAGE_3_POINT_5, 100000, 0, 0);
                    events.ScheduleEvent(STAGE_3_FIGHT_B, 16000, 0, 0);
                    s3posb = true;
                }

                if (me->GetHealthPct() < 50)
                    me->SetFullHealth();

                if(resetall || bfgcdone)
                {
                    me->DespawnOrUnsummon(1000);
                    Reset();
                }

                if (me->GetVictim() && !ignoredamage)
                {
                    if ((me->GetVictim())->GetDistance2d(me) < 6)
                    {
                        me->GetMotionMaster()->MoveChase(me->GetVictim());
                        me->Attack(me->GetVictim(), true);
                    }
                    else if (urand(0, 4) == 4)
                        me->CastSpell(me->GetVictim(), SPELL_SHOOT, false);
                }

                if (stage4 && !boss2b)
                {
                    events.ScheduleEvent(STAGE_4, 10000, 0, 0);
                    events.ScheduleEvent(STAGE_4_FIGHT, 15000, 0, 0);
                    boss2b = true;
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_gilnean_millitiaAI(creature);
        }
};

class npc_forsaken_crossbow : public CreatureScript
{
    public:
        npc_forsaken_crossbow() : CreatureScript("npc_forsaken_crossbow") { }

        struct npc_forsaken_crossbowAI : public ScriptedAI
        {
            npc_forsaken_crossbowAI(Creature* creature) : ScriptedAI(creature) {}
 
            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                crossbowman = crossbowman + 1;
                //sWorld->SendGMText(30000, crossbowman);
            }

            void UpdateAI(uint32 /*uiDiff*/) OVERRIDE
            {
                if(resetall)
                {
                    me->DespawnOrUnsummon(100);
                    me->SetRespawnTime(300);
                }
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_forsaken_crossbowAI(creature);
        }
};

class npc_vile_abomination : public CreatureScript
{
    public:
        npc_vile_abomination() : CreatureScript("npc_vile_abomination") { }

        struct npc_vile_abominationAI : public ScriptedAI
        {
            npc_vile_abominationAI(Creature* creature) : ScriptedAI(creature) {}
 
            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                abom = abom + 1;
            }

            void UpdateAI(uint32 /*uiDiff*/) OVERRIDE
            {
                if(resetall)
                {
                    me->DespawnOrUnsummon(100);
                    me->SetRespawnTime(300);
                }
                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_vile_abominationAI(creature);
        }
};

class npc_gorrerot : public CreatureScript
{
    public:
        npc_gorrerot() : CreatureScript("npc_gorrerot") { }

        struct npc_gorrerotAI : public ScriptedAI
        {
            npc_gorrerotAI(Creature* creature) : ScriptedAI(creature) {}
 
            EventMap events;

            void Reset() OVERRIDE
            {
                me->SetVisible(false);
                me->SetReactState(REACT_PASSIVE);
                me->AI()->EnterEvadeMode();
            }

            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                boss_gurerrot_dead = true;
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                if(gurerrot)
                {
                    me->SetVisible(true);
                    me->SetReactState(REACT_AGGRESSIVE);
                }

                if(resetall)
                    Reset();

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_gorrerotAI(creature);
        }
};

class npc_king_genn_greymane : public CreatureScript
{
    public:
        npc_king_genn_greymane() : CreatureScript("npc_king_genn_greymane") { }

        struct npc_king_genn_greymaneAI : public ScriptedAI
        {
            npc_king_genn_greymaneAI(Creature* creature) : ScriptedAI(creature) {}
 
            EventMap events;

            void Reset() OVERRIDE
            {
                me->AI()->EnterEvadeMode();
                events.Reset();
            }

            void DamageTaken(Unit* attacker, uint32& damage) OVERRIDE
            {
                if (damage >= me->GetHealth())
                    damage = 1;

                me->GetMotionMaster()->MoveChase(attacker);
                me->Attack(attacker, true);
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case STAGE_4:
                            me->SetSpeed(MOVE_RUN, me->GetSpeedRate(MOVE_RUN), true);
                            me->GetMotionMaster()->MovePoint(0, eventPositionsTeamB[8].GetPositionX(), eventPositionsTeamB[8].GetPositionY(), eventPositionsTeamB[8].GetPositionZ(), true);
                            break;
                        case STAGE_4_FIGHT:
                            if (Unit* target = me->FindNearestCreature(LADY_SYLVANAS_WINDRUNNER, 100.0f))
                            {
                                me->GetMotionMaster()->MoveChase(target, 1.0f);
                                me->Attack(target, true);
                            }
                            else 
                                events.ScheduleEvent(STAGE_4, 1000, 0, 0);

                            if (!bfgcdone)
                                events.ScheduleEvent(STAGE_4_FIGHT, 3000, 0, 0);
                            break;
                        default:
                            break;
                    }
                }

                if (me->GetHealthPct() < 50)
                    me->SetFullHealth();

                if (stage4 && !boss2)
                {
                    events.ScheduleEvent(STAGE_4, 1000, 0, 0);
                    events.ScheduleEvent(STAGE_4_FIGHT, 10000, 0, 0);
                    boss2 = true;
                }

                if(resetall || bfgcdone)
                    Reset();

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_king_genn_greymaneAI(creature);
        }
};

class npc_emberstone_canon_villager : public CreatureScript
{
    public:
        npc_emberstone_canon_villager() : CreatureScript("npc_emberstone_canon_villager") { }

        struct npc_emberstone_canon_villagerAI : public ScriptedAI
        {
            npc_emberstone_canon_villagerAI(Creature* creature) : ScriptedAI(creature) {}
 
            EventMap events;

            void Reset() OVERRIDE
            {
                me->SetVisible(false);
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                if (military_quoter)
                {
                    me->SetVisible(true);
                    me->SetPhaseMask(262144, true);
                }

                if(resetall || bfgcdone)
                    Reset();

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_emberstone_canon_villagerAI(creature);
        }
};

class npc_lady_sylvanas : public CreatureScript
{
    public:
        npc_lady_sylvanas() : CreatureScript("npc_lady_sylvanas") { }

        struct npc_lady_sylvanasAI : public ScriptedAI
        {
            npc_lady_sylvanasAI(Creature* creature) : ScriptedAI(creature) {}
 
            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                me->CastSpell(me, SPELL_BFGC_CONPLETE, false);
                bfgcdone = true;
            }

            void UpdateAI(uint32 /*uiDiff*/) OVERRIDE
            {
                if (me->GetHealthPct() < 21)
                {
                    Talk(0);
                    me->CastSpell(me, SPELL_BFGC_CONPLETE, false);
                    bfgcdone = true;
                    me->DespawnOrUnsummon(3000);
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_lady_sylvanasAI(creature);
        }
};

void AddSC_bfgc_script()
{
    new npc_krennan_aranas();
    new npc_prince_liam();
    new npc_gilnean_millitia();
    new npc_king_genn_greymane();
    new npc_forsaken_crossbow();
    new npc_vile_abomination();
    new npc_gorrerot();
    new npc_emberstone_canon_villager();
    new npc_lady_sylvanas();
}
