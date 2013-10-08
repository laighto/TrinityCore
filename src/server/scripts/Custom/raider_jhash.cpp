#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "World.h"

enum questdata 
{
    SUMMON_DUROTAR_RIDIBG_WOLF = 73678,    
    RAIDER_KERR = 10682,
    QUEST_RIDING_ON = 25171,
};

class npc_raider_jhash : public CreatureScript
{
    public:
        npc_raider_jhash() : CreatureScript("npc_raider_jhash") { }

        bool OnGossipHello(Player* player, Creature* creature) OVERRIDE
        {
            if (player->IsActiveQuest(QUEST_RIDING_ON))
            {
                //Load gossip menu option + locale from DB
                player->PrepareGossipMenu(creature, 11189);
                player->SendPreparedGossip(creature);
            }
            else 
                player->PlayerTalkClass->SendGossipMenu(11189, creature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) OVERRIDE
        {
            player->PlayerTalkClass->SendCloseGossip();
            
            if (player->IsActiveQuest(QUEST_RIDING_ON))
            {
                player->CastSpell(player, SUMMON_DUROTAR_RIDIBG_WOLF, true);
                creature->SummonCreature(RAIDER_KERR, -825.47f, -4900.59f, 19.63f, 1.086f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
            }
            return true;
        }
};

void AddSC_raider_jhash()
{
    new npc_raider_jhash();
}
