/*
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

/*

    NPC_BRIATHA = 25949,
    NPC_HERETIC_EMISSAR = 25951,
    NPC_HERETIC_GUARD = 25980,
    ITEM_TO_USE = 35237
*/

#include "ScriptPCH.h"
#include "World.h"
#include "Player.h"
#include "ScriptedCreature.h"

Player* user;
bool trigger;

enum questdata
{
    AN_INNOCENT_DISGUISE_QUEST_COMPLETE = 46375,
    QUEST = 11891
};

enum eventlist
{
    EVENT_1 = 1,
    EVENT_2 = 2,
    EVENT_3 = 3,
    EVENT_4 = 4,
    EVENT_5 = 5,
    EVENT_COMPLETE = 6,
    EVENT_RESET = 7,
    EVENT_GLOBAL_RESET = 8
};

enum txtlist
{
    SAY_TXT_1 = 0,
    SAY_TXT_2 = 0,
    SAY_TXT_3 = 1,
    SAY_TXT_4 = 1,
    SAY_TXT_5 = 2
};

class orb_of_the_crawler : public ItemScript
{
    public:
        orb_of_the_crawler() : ItemScript("orb_of_the_crawler") { }

        bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
        {
            // sScriptMgr->LoadDatabase();
            if (player->GetQuestRewardStatus(QUEST) != QUEST_STATUS_COMPLETE)
            {
                user = player;
                return false;
            }
            else 
                return true;
        }
};

class npc_heretic_emisar : public CreatureScript
{
public:
    npc_heretic_emisar() : CreatureScript("npc_heretic_emisar") { }

    struct npc_heretic_emisarAI : public ScriptedAI
    {
        npc_heretic_emisarAI(Creature* creature) : ScriptedAI(creature) {}

        void Scedule()
        {
            events.ScheduleEvent(EVENT_2, 7000, 0, 0);
            events.ScheduleEvent(EVENT_4, 17000, 0, 0);
        }

        void Reset() override
        {
            events.Reset();
        }

        void UpdateAI(uint32 uiDiff) override
        {
            if (user != NULL && trigger)
            {
                trigger = false;
                Scedule();
            }

            events.Update(uiDiff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_2:
                    Talk(SAY_TXT_2);
                    break;
                case EVENT_4:
                    Talk(SAY_TXT_4);
                    Reset();
                    break;
                default:
                    break;
                }
            }
        }
        private:
            EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_heretic_emisarAI(creature);
    }
};

class npc_briatha : public CreatureScript
{
    public:
        npc_briatha() : CreatureScript("npc_briatha") { }

        struct npc_briathaAI : public ScriptedAI
        {
            npc_briathaAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset() override
        {
            user = NULL;
            scedule_sequence = true;
            globalreset = false;
            trigger = false;
            events.Reset();
        }

        void Scedule()
        {
            events.ScheduleEvent(EVENT_1, 2000, 0, 0); 
            events.ScheduleEvent(EVENT_3, 13000, 0, 0); 
            events.ScheduleEvent(EVENT_5, 23000, 0, 0); 
            events.ScheduleEvent(EVENT_COMPLETE, 25000, 0, 0);
            events.ScheduleEvent(EVENT_RESET, 26000, 0, 0); 
        }

        void UpdateAI(uint32 uiDiff) override
        {
            events.Update(uiDiff);

            if (scedule_sequence && user != NULL)
            {
                if (!globalreset)
                {
                    globalreset = true;
                    events.ScheduleEvent(EVENT_GLOBAL_RESET, 40000, 0, 0);
                }

                Player* target = me->SelectNearestPlayer(25.0f);
                if (target && GUID_LOPART(target->GetGUID()) == GUID_LOPART(user->GetGUID()))
                {
                    scedule_sequence = false;
                    trigger = true;
                    Scedule();
                }
            }

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_1:
                    Talk(SAY_TXT_1);
                    break;
                case EVENT_3:
                    Talk(SAY_TXT_3);
                    break;
                case EVENT_5:
                    Talk(SAY_TXT_5);
                    break;
                case EVENT_COMPLETE:
                    if (user)
                        user->CastSpell(user, AN_INNOCENT_DISGUISE_QUEST_COMPLETE, false);
                    break;
                case EVENT_RESET:
                case EVENT_GLOBAL_RESET:
                    Reset();
                    break;
                default:
                    break;
                }
            }
        }
        private:
            bool scedule_sequence;
            bool globalreset;
            EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_briathaAI(creature);
    }
};

void AddSC_an_innocent_disguise()
{
    new orb_of_the_crawler();
    new npc_briatha();
    new npc_heretic_emisar();
}