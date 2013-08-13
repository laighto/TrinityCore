#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "World.h"

enum questdata 
{
    SUMMON_DUROTAR_RIDIBG_WOLF = 73678,    
    RAIDER_KERR = 10682,
};

class npc_raider_jhash : public CreatureScript
{
    public:
        npc_raider_jhash() : CreatureScript("npc_raider_jhash") { }

        bool OnGossipHello(Player* player, Creature* creature)
        {
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Transform the item!", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_ADD_DISPLAY);
            //pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Make item clean.", GOSSIP_SENDER_MAIN, ACTION_TRANSMOGRIFY_REMOVE_DISPLAY);
            player->PlayerTalkClass->SendGossipMenu(11189, creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
        {
            player->PlayerTalkClass->SendCloseGossip();
            
            if (player->hasQuest(27091))
            {
                player->CastSpell(player, SUMMON_DUROTAR_RIDIBG_WOLF, false);
                if (Creature* summoned = creature->SummonCreature(RAIDER_KERR, -825.47f, -4900.59f, 19.63f, 1.086f,TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000))
                    summoned->SetSpeed(MOVE_WALK, sObjectMgr->GetCreatureTemplate(RAIDER_KERR)->speed_walk);
            }
            return true;
        }
};

void AddSC_custom_script()
{
    new npc_raider_jhash;
}
