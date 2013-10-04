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
#include "the_warchief_cometh.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "World.h"

class npc_w_mortuus : public CreatureScript
{
    public:
        npc_w_mortuus() : CreatureScript("npc_w_mortuus") { }

        bool OnQuestAccept(Player* player, Creature* creature, const Quest* quest) OVERRIDE
        {
            if (quest->GetQuestId() == QUEST_TWC)
            {
                start_event = true; 
            }
            return true;
        }
};

class npc_w_warchief : public CreatureScript
{
    public:
        npc_w_warchief() : CreatureScript("npc_w_warchief") { }

        struct npc_w_warchiefAI : public ScriptedAI
        {
            npc_w_warchiefAI(Creature* creature) : ScriptedAI(creature) {}

            EventMap events;
            
            void Reset() OVERRIDE
            {
                arrivedw = false;
                events.Reset();
            }

            void Scedule()
            {
                events.ScheduleEvent(EVENT_3, 15000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_4, 18000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_8, 31000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_16, 72000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_17, 76000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_13, 60000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_14, 62000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_19, 83000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_20, 85000-7000, 0, 0); //warchief
                events.ScheduleEvent(EVENT_22, 89000-7000, 0, 0); //warchief
                events.ScheduleEvent(LEFT, 94000-7000, 0, 0);
                events.ScheduleEvent(RESET, 98000-7000, 0, 0);
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                if (scedule_sequence)
                {
                    scedule_sequence = false;
                    Scedule();
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_3:
                            arrivedw = true;
                            Talk(SAY_TXT_3);
                            break;
                        case EVENT_4:
                            Talk(SAY_TXT_4);
                            break;
                        case EVENT_8:
                            Talk(SAY_TXT_8);
                            break;
                        case EVENT_13:
                            Talk(SAY_TXT_13);
                            break;
                        case EVENT_14:
                            Talk(SAY_TXT_14);
                            break;
                        case EVENT_16:
                            Talk(SAY_TXT_16);
                            break;
                        case EVENT_17:
                            Talk(SAY_TXT_17);
                            break;
                        case EVENT_19:
                            Talk(SAY_TXT_19);
                            break;
                        case EVENT_20:
                            Talk(SAY_TXT_20);
                            break;
                        case EVENT_22:
                            Talk(SAY_TXT_22);
                            DoCast(SPELL_QUEST_COMPLETE);
                            break;
                        case LEFT:
                            if(GameObject* portal1 = me->FindNearestGameObject(GO_PORTAL_FROM_ORGRIMMAR, 35.0f))
                                portal1->RemoveFromWorld();
                            if(GameObject* portal2 = me->FindNearestGameObject(GO_PORTAL_FROM_ORGRIMMAR, 35.0f))
                                portal2->RemoveFromWorld();
                             if(GameObject* portal3 = me->FindNearestGameObject(GO_PORTAL_FROM_ORGRIMMAR, 35.0f))                  
                                portal3->RemoveFromWorld();
                            me->DespawnOrUnsummon(5000);
                            me->SetSpeed(MOVE_WALK, me->GetSpeedRate(MOVE_WALK), true);
                            me->GetMotionMaster()->MovePoint(eventPositions[3].GetPositionX(), eventPositions[3].GetPositionY(), eventPositions[3].GetPositionZ(), true);
                            break;
                        case RESET:
                            Reset();
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_w_warchiefAI(creature);
        }
};

class npc_w_sylvanas : public CreatureScript
{
    public:
        npc_w_sylvanas() : CreatureScript("npc_w_sylvanas") { }

        struct npc_w_sylvanasAI : public ScriptedAI
        {
            npc_w_sylvanasAI(Creature* creature) : ScriptedAI(creature) {}

            EventMap events;
            bool sceduleds;
            GameObject* portal1;
            GameObject* portal2;
            GameObject* portal3;

            void Reset() OVERRIDE
            {
                start_event = false;
                sceduleds = false;
                scedule_sequence = false;
                events.Reset();
                allowmorph = false;
            }

            void BeginTalk()
            {
                Talk(SAY_TXT_1); //sylvanas

                events.ScheduleEvent(EVENT_2, 5000, 0, 0); //sylvanas

                events.ScheduleEvent(ARRIVE, 7000, 0, 0);

                events.ScheduleEvent(EVENT_5, 21000, 0, 0); //sylvanas
                events.ScheduleEvent(EVENT_6, 25000, 0, 0); //sylvanas
                events.ScheduleEvent(EVENT_7, 29000, 0, 0); //sylvanas

                events.ScheduleEvent(EVENT_9, 35000, 0, 0); //sylvanas
                events.ScheduleEvent(EVENT_10, 38000, 0, 0); //sylvanas
                events.ScheduleEvent(EVENT_11, 42000, 0, 0); //sylvanas
                events.ScheduleEvent(EVENT_12, 43000, 0, 0); //sylvanas
                /* Valkir casts spell */

                events.ScheduleEvent(EVENT_15, 68000, 0, 0); //sylvanas

                events.ScheduleEvent(EVENT_18, 80000, 0, 0); //sylvanas

                events.ScheduleEvent(RESET, 100000, 0, 0);
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                if (start_event && !sceduleds)
                {
                    sceduleds = true;
                    BeginTalk();
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case ARRIVE:
                            if(Creature* creature = me->SummonCreature(NPC_WARCHIEF, eventPositions[1].GetPositionX(), eventPositions[1].GetPositionY(), eventPositions[1].GetPositionZ(), eventPositions[1].GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 100000))
                            {
                                creature->GetMotionMaster()->MoveJump(eventPositions[0].GetPositionX(), eventPositions[0].GetPositionY(), eventPositions[0].GetPositionZ(), 15.0f, 15.0f);
                                scedule_sequence = true;
                               // npc_w_warchief::npc_w_warchiefAI::Scedule;
                            }
                            if (GameObject* portal1 = me->SummonGameObject(GO_PORTAL_FROM_ORGRIMMAR, eventPositions[1].GetPositionX(), eventPositions[1].GetPositionY(), eventPositions[1].GetPositionZ(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100000))
                                portal1->SetObjectScale(1.0f);
                            if (GameObject* portal2 = me->SummonGameObject(GO_PORTAL_FROM_ORGRIMMAR, eventPositions[2].GetPositionX(), eventPositions[2].GetPositionY(), eventPositions[2].GetPositionZ(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100000))
                                portal2->SetObjectScale(1.0f);
                            if (GameObject* portal3 = me->SummonGameObject(GO_PORTAL_FROM_ORGRIMMAR, eventPositions[3].GetPositionX(), eventPositions[3].GetPositionY(), eventPositions[3].GetPositionZ(), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100000))
                                portal3->SetObjectScale(1.0f);
                            break;
                        case EVENT_2:
                            Talk(SAY_TXT_2);
                            break;
                        case EVENT_5:
                            Talk(SAY_TXT_5);
                            break;
                        case EVENT_6:
                            Talk(SAY_TXT_6);
                            break;
                        case EVENT_7:
                            Talk(SAY_TXT_7);
                            break;
                        case EVENT_9:
                            Talk(SAY_TXT_9);
                            break;
                        case EVENT_10:
                            Talk(SAY_TXT_10);
                            break;
                        case EVENT_11:
                            Talk(SAY_TXT_11);
                            break;
                        case EVENT_12:
                            Talk(SAY_TXT_12);
                            events.ScheduleEvent(AGATHA, 6000, 0, 0);
                            break;
                        case AGATHA:
                            allowcast = true;
                            break;
                        case EVENT_15:
                            Talk(SAY_TXT_15);
                            break;
                        case EVENT_18:
                            Talk(SAY_TXT_18);
                            break;
                        case RESET:
                            Reset();
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_w_sylvanasAI(creature);
        }
};

class npc_w_cromush : public CreatureScript
{
    public:
        npc_w_cromush() : CreatureScript("npc_w_cromush") { }

        struct npc_w_cromushAI : public ScriptedAI
        {
            npc_w_cromushAI(Creature* creature) : ScriptedAI(creature) {}

            EventMap events;
            bool sceduled;

            void Reset() OVERRIDE
            {
                sceduled = false;
                events.Reset();
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                events.Update(uiDiff);

                if (start_event && !sceduled)
                {
                    sceduled = true;
                    events.ScheduleEvent(EVENT_21, 87000, 0, 0); //cromush
                    events.ScheduleEvent(RESET, 100000, 0, 0);
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_21:
                            Talk(SAY_TXT_21);
                            break;
                        case RESET:
                            Reset();
                            break;
                        default:
                            break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_w_cromushAI(creature);
        }
};

class npc_w_elite : public CreatureScript
{
    public:
        npc_w_elite() : CreatureScript("npc_w_elite") { }

        struct npc_w_eliteAI : public ScriptedAI
        {
            npc_w_eliteAI(Creature* creature) : ScriptedAI(creature) {}
 
            void Reset() OVERRIDE
            {
                me->SetVisible(false);
            }

            void UpdateAI(uint32 /*uiDiff*/) OVERRIDE
            {
                if (arrivedw)
                    me->SetVisible(true);
                else 
                    me->SetVisible(false);
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_w_eliteAI(creature);
        }
};

class npc_w_agatha : public CreatureScript
{
    public:
        npc_w_agatha() : CreatureScript("npc_w_agatha") { }

        struct npc_w_agathaAI : public ScriptedAI
        {
            npc_w_agathaAI(Creature* creature) : ScriptedAI(creature) {}
 
            void Reset() OVERRIDE
            {
                allowcast = false;
            }

            void UpdateAI(uint32 /*uiDiff*/) OVERRIDE
            {
                if(allowcast)
                {
                    allowcast = false;
                    DoCast(SPELL_REVIVE_UNDEAD);
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_w_agathaAI(creature);
        }
};

class npc_w_fallen_human : public CreatureScript
{
    public:
        npc_w_fallen_human() : CreatureScript("npc_w_fallen_human") { }

        struct npc_w_fallen_humanAI : public ScriptedAI
        {
            npc_w_fallen_humanAI(Creature* creature) : ScriptedAI(creature) {}

            EventMap events;
            bool allowmorph;

            void SpellHit(Unit* /*caster*/, const SpellInfo* spell) OVERRIDE
            {
                if (spell == sSpellMgr->GetSpellInfo(SPELL_REVIVE_UNDEAD) && start_event)
                    events.ScheduleEvent(MORPH, 8000, 0, 0);
            }

            void Morphing()
            {
                me->RemoveAllAuras();
                if (me->getGender() == GENDER_MALE)
                    me->SetDisplayId(31262);
                else me->SetDisplayId(31261);
            }

            void UpdateAI(uint32 uiDiff) OVERRIDE
            {
                if(!start_event)
                {
                    me->DeMorph();
                    allowmorph = false;
                }
                else if(start_event && allowmorph)
                    Morphing();

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case MORPH:
                            allowmorph = true;
                            break;
                        default:
                            break;
                    }
                }
   
                events.Update(uiDiff);
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_w_fallen_humanAI(creature);
        }
};


void AddSC_warchief_cometh()
{
    new npc_w_sylvanas;
    new npc_w_warchief;
    new npc_w_elite;
    new npc_w_cromush;
    new npc_w_mortuus;
    new npc_w_agatha;
    new npc_w_fallen_human;
}