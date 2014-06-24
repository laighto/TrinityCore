#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "World.h"
#include "Chat.h"
#include "Language.h"
#include "GossipDef.h"
#include "SmartAI.h"
#include "Player.h"

enum actionlist
{
    REWARD_SINGLE_ITEMS = 1,
    REWARD_ITEM_WITH_COUNT = 2,
    REWARD_ITEM_WITH_RANDOM_COUNT = 3,
    REWARD_SPELLS_CAST = 4,

};

enum messages
{
    INVALID_CODE = 0,
    CODE_WAS_USED = 1,
    SUCCESS_USE = 2,
};

class code_manager : public CreatureScript
{
public:
    code_manager() : CreatureScript("code_manager") { }


    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) override
    {
        player->PlayerTalkClass->SendCloseGossip();

        if (player->IsMounted())
            player->Dismount();

        bool active = 0;
        uint32 actiontodo = 0;
        uint32 data0 = 0;
        uint32 data1 = 0;
        uint32 data2 = 0;
        uint32 data3 = 0;

        std::string strcode(code);

        if (code)
        {
           // sWorld->SendServerMessage(SERVER_MSG_STRING, strcode.c_str());
           // QueryResult result = CharacterDatabase.PQuery("SELECT active, actionid, data0, data1, data2, data3 FROM code_manager WHERE code = %s", strcode.c_str());

            PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CODE);
            stmt->setString(0, strcode);
            PreparedQueryResult result = CharacterDatabase.Query(stmt);

            if (result)
            {
                Field* columns = result->Fetch();
                active = columns[0].GetBool();
                actiontodo = columns[1].GetUInt32();
                data0 = columns[2].GetUInt32();
                data1 = columns[3].GetUInt32();
                data2 = columns[4].GetUInt32();
                data3 = columns[5].GetUInt32();
            }
            else
            {
                //sWorld->SendServerMessage(SERVER_MSG_STRING, "ERROR: Invalid code.");
                //creature->MonsterSay("ERROR: Invalid code.", LANG_UNIVERSAL, 0);
                creature->AI()->Talk(INVALID_CODE);
                return true;
            }
        }

        if (!active)
        {
            //sWorld->SendServerMessage(SERVER_MSG_STRING, "ERROR: Code is already activated.");
           // creature->MonsterSay("ERROR: Code is already activated.", LANG_UNIVERSAL, 0);
            creature->AI()->Talk(CODE_WAS_USED);
            return true;
        }
        else
        {
            switch (actiontodo)
            {
                case REWARD_SINGLE_ITEMS:
                {
                    //sWorld->SendServerMessage(SERVER_MSG_STRING, "ACTION: REWARD_SINGLE_ITEMS");
                    if (data0 > 0)
                        player->AddItem(data0, 1);
                    if (data1 > 0)
                        player->AddItem(data1, 1);
                    if (data2 > 0)
                        player->AddItem(data2, 1);
                    if (data3 > 0)
                        player->AddItem(data3, 1);
                    break;
                }
                case REWARD_ITEM_WITH_COUNT:
                {
                    //sWorld->SendServerMessage(SERVER_MSG_STRING, "ACTION: REWARD_ITEM_WITH_COUNT");
                    if (data0 > 0 && data1 > 0)
                        player->AddItem(data0, data1);
                    if (data2 > 0 && data3 > 0)
                        player->AddItem(data2, data3);
                    break;
                }
                case REWARD_ITEM_WITH_RANDOM_COUNT:
                {
                    //sWorld->SendServerMessage(SERVER_MSG_STRING, "ACTION: REWARD_ITEM_WITH_RANDOM_COUNT");
                    if (data0 > 0)
                    {
                        if (data1 == 0)
                            data1 = 1;
                        if (data2 == 0)
                            data2 = 1;
                        if (data1<=data2)
                            player->AddItem(data0, urand(data1, data2));
                        else 
                            player->AddItem(data0, urand(data2, data1));
                    }
                    break;
                }
                case REWARD_SPELLS_CAST:
                {
                    if (data0 > 0)
                        player->CastSpell(player, data0, false);
                    if (data1 > 0)
                        player->CastSpell(player, data1, false);
                    if (data2 > 0)
                        player->CastSpell(player, data2, false);
                    if (data3 > 0)
                        player->CastSpell(player, data3, false);
                    break;
                }
                default: 
                    break;
            }

            PreparedStatement *stmt = CharacterDatabase.GetPreparedStatement(CHAR_UPD_CODE);
            stmt->setUInt32(0, player->GetGUIDLow());
            stmt->setUInt32(1, player->GetSession()->GetAccountId());
            stmt->setString(2, strcode);
            CharacterDatabase.Execute(stmt);
           // CharacterDatabase.PExecute("UPDATE code_manager SET active=0, charguid = %u, characcount = %u WHERE code = %s ;", player->GetGUIDLow(), player->GetSession()->GetAccountId(), code);
           // creature->MonsterSay("Code successfuly activated!", LANG_UNIVERSAL, 0);
            creature->AI()->Talk(SUCCESS_USE);
        }
        
        //sWorld->SendServerMessage(SERVER_MSG_STRING, code);

        return true;
    }
};

void AddSC_server_manager()
{
    new code_manager();
}