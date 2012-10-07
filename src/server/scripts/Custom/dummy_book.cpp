#include "ScriptPCH.h"
#include "World.h"
#include "ObjectMgr.h"

#define GOSSIP_HELLO_DEMO1  "Unlearn Goblin Engineer"
#define GOSSIP_HELLO_DEMO2  "Unlearn Gnomish Engineer"
#define GOSSIP_HELLO_DEMO3  "Revert to One Talent Specialization"
#define GOSSIP_HELLO_DEMO4  "Learn Dual Talent Specialization."

enum Spells
{
    SPELL_UNLEARN_GOBLIN_ENGINEER     = 68334,
    SPELL_UNLEARN_GNOMISH_ENGINEER    = 68333,
    SPELL_REVERT_TO_ONE_TALENT_SPEC   = 63651,
    SPELL_LEARN_DUAL_TALENT_SPEC      = 63624,
};

class dummy_book : public GameObjectScript
{
    public:
        dummy_book() : GameObjectScript("dummy_book") { }

        bool OnGossipHello(Player* player, GameObject* object)
        {
           player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetTrinityStringForDBCLocale(999950/*GOSSIP_HELLO_DEMO1*/), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
           player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetTrinityStringForDBCLocale(999951/*GOSSIP_HELLO_DEMO2*/), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
           player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetTrinityStringForDBCLocale(999952/*GOSSIP_HELLO_DEMO3*/), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
           player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, sObjectMgr->GetTrinityStringForDBCLocale(999953/*GOSSIP_HELLO_DEMO4*/), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);

           player->SEND_GOSSIP_MENU(player->GetGossipTextId(object), object->GetGUID());
           return true;
        }

        bool OnGossipSelect(Player* player, GameObject* object, uint32 /*sender*/, uint32 action)
        {
            player->CLOSE_GOSSIP_MENU();

            switch (action - GOSSIP_ACTION_INFO_DEF)
            {
                case 0:
                    player->CastSpell(player, SPELL_UNLEARN_GOBLIN_ENGINEER, true);
                    player->ModifyMoney(-1 * 1500000);
                    break;
                case 1:
                    player->CastSpell(player, SPELL_UNLEARN_GNOMISH_ENGINEER, true);
                    player->ModifyMoney(-1 * 1500000);
                    break;
                case 2:
                    player->CastSpell(player, SPELL_REVERT_TO_ONE_TALENT_SPEC, true);
                    break;
                case 3:
                    player->CastSpell(player, SPELL_LEARN_DUAL_TALENT_SPEC, true);
                    player->ModifyMoney(-1 * 10000000);
                    break;
            }
            return true;
        }
};

void AddSC_dummy_book()
{
    new dummy_book();
}