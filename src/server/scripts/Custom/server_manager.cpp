/*
Script written by chaosua in 2014

Code manager provides support rewards for customer codes 

Database columns code_manager:
`code` - unique key that can be ganerated as you wish
`active` - 0 code is used or 1 code can be used

`actionid` - Id of a command to do:
`data0` - `data3 - data fields for action

    REWARD_SINGLE_ITEMS = 1: 
        data0-data3 - entry from item_tenplate
    REWARD_ITEM_WITH_COUNT = : 
        data0, data2 - entry from item_tenplate, data1, data3 - count of items
    REWARD_ITEM_WITH_RANDOM_COUNT = 3: 
        data0: entry from item_tenplate, data1 - minimal couont, data2 - maximum count
    REWARD_SPELL_CAST = 4: 
        data0 - spell Id from Spell.dbc
    REWARD_CURRENCY = 5: 
        data0=0 -> money, data0=1 -> honor points, data0=2 -> arena points, data1 - count of selected currency
    REWARD_PREPARED_ITEMPACK = 6: 
        data0 - Id od pack in code_prepared_itempack table

`comment` - Description of Action, that code activates
`charguid` - character id. from which was code activated
`characcount` - Account id. from which was code activated


code_prepared_itempack:
`packid` - id of package
`item` - entry from item_tenplate
`count` - amount of item

*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "World.h"
#include "Chat.h"
#include "Language.h"
#include "GossipDef.h"
#include "SmartAI.h"
#include "Player.h"
#include "AccountMgr.h"
#include "ObjectMgr.h"


enum actionlist
{
    REWARD_SINGLE_ITEMS = 1,
    REWARD_ITEM_WITH_COUNT = 2,
    REWARD_ITEM_WITH_RANDOM_COUNT = 3,
    REWARD_SPELL_CAST = 4,
    REWARD_CURRENCY = 5,
    REWARD_PREPARED_ITEMPACK = 6,
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


    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 /*sender*/, uint32 /*action*/, const char* code) override
    {
        bool active = 0;
        uint32 actiontodo = 0;
        uint32 data0 = 0;
        uint32 data1 = 0;
        uint32 data2 = 0;
        uint32 data3 = 0;
        std::string strcode(code);
        //bool complete = 0;
        CharacterDatabase.EscapeString(strcode);

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
                player->PlayerTalkClass->SendCloseGossip();
                return true;
            }
        }

        if (!active)
        {
            //sWorld->SendServerMessage(SERVER_MSG_STRING, "ERROR: Code is already activated.");
           // creature->MonsterSay("ERROR: Code is already activated.", LANG_UNIVERSAL, 0);
            creature->AI()->Talk(CODE_WAS_USED);
            player->PlayerTalkClass->SendCloseGossip();
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
                case REWARD_SPELL_CAST:
                {
                    if (data0 > 0)
                        player->CastSpell(player, data0, false);
                    break;
                }
                case REWARD_CURRENCY:
                {
                    if (data0 == 0 && data1 > 0)
                        player->ModifyMoney(data1);
                    if (data0 == 1 && data1 > 0)
                        player->ModifyHonorPoints(data1);
                    if (data0 == 2 && data1 > 0)
                        player->ModifyArenaPoints(data1);
                    break;
                }
                case REWARD_PREPARED_ITEMPACK:
                {
                    if (data0 > 0)
                    {
                        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ITEMPACK);
                        stmt->setUInt32(0, data0);
                        PreparedQueryResult result = CharacterDatabase.Query(stmt);

                        if (result)
                        {
                            do
                            {
                                Field* columns = result->Fetch();
                                uint32 item = columns[0].GetUInt32();
                                uint32 count = columns[1].GetUInt32();
                                if (count != 0)
                                    player->AddItem(item, count);
                            }
                            while (result->NextRow());
                        }
                        else
                        {
                            creature->Say("Code successfuly activated! But there is no Reward Packs!!!", LANG_UNIVERSAL, 0);
                            return true;
                        }
                    }
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
        player->PlayerTalkClass->SendCloseGossip();
        return true;
    }
};

class login_code_controller : public PlayerScript
{
public:
    login_code_controller() : PlayerScript("login_code_controller") { }

    uint32 GetUniquePackId(PreparedQueryResult result, uint32 data)
    {
        uint32 array_data[71] = { 0 };
        uint32 packid = data;
        uint32 data1 = 0;
        uint32 data2 = 0;
        uint32 counter = 0;
        uint32 arraysize = 0;
        bool need_to_generate = false;

        do
        {
            Field* columns = result->Fetch();
            array_data[arraysize] = columns[0].GetInt32();
            arraysize++;
        } while (result->NextRow());

        if (packid <= 10 && arraysize < 10)
        {
            need_to_generate = true;
            data1 = 1,
            data2 = 10;
        }
        else if (packid <= 10 && arraysize == 10)
        {
            packid = urand(11, 20);
        }
        else if (packid <= 20 && arraysize < 20)
        {
            need_to_generate = true;
            data1 = 11,
            data2 = 20;
        }
        else if (packid <= 20 && arraysize == 20)
        {
            packid = urand(21, 30);
        }
        else if (packid <= 30 && arraysize < 30)
        {
            need_to_generate = true;
            data1 = 21,
            data2 = 30;
        }
        else if (packid <= 30 && arraysize == 30)
        {
            packid = urand(31, 40);
        }
        else if (packid <= 40 && arraysize < 40)
        {
            need_to_generate = true;
            data1 = 31,
            data2 = 40;
        }
        else if (packid <= 40 && arraysize == 40)
        {
            packid = urand(41, 50);
        }
        else if (packid <= 50 && arraysize < 50)
        {
            need_to_generate = true;
            data1 = 41,
            data2 = 50;
        }
        else if (packid <= 50 && arraysize == 50)
        {
            packid = urand(51, 60);
        }
        else if (packid <= 60 && arraysize < 60)
        {
            need_to_generate = true;
            data1 = 51,
            data2 = 60;
        }
        else if (packid <= 60 && arraysize == 60)
        {
            packid = urand(61, 70);
        }

        if (need_to_generate)
        {
            do
            {
                counter = 0;
                packid = urand(data1, data2);

                for (uint32 i = 0; i < arraysize; i++)
                {
                    if (packid == array_data[i])
                        counter++;
                }
            } while (counter != 0);
        }

        return (packid);
    }

    void OnLogin(Player* player, bool /*firstLogin*/) override
    {
        /*SELECT count of votes*/
        PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_CODE_ACC_VOTES);
        stmt->setUInt32(0, player->GetSession()->GetAccountId());
        PreparedQueryResult result = LoginDatabase.Query(stmt);
        if (result)
        {
            Field* columns = result->Fetch();
            uint32 votecount = columns[0].GetUInt32();

            if (votecount >= 5) /* account have points to get reward pack*/
            {
                stmt = LoginDatabase.GetPreparedStatement(LOGIN_SEL_CODE_ACC_REW);
                stmt->setUInt32(0, player->GetSession()->GetAccountId());
                PreparedQueryResult result = LoginDatabase.Query(stmt);
                
                uint32 packid = 0;
                PreparedStatement* stmta = LoginDatabase.GetPreparedStatement(LOGIN_UPD_CODE_ACC_REW);
                PreparedStatement* stmtb = LoginDatabase.GetPreparedStatement(LOGIN_INS_CODE_ACC_REW);

                if (result)
                {
                    Field* columns = result->Fetch();
                    packid = columns[0].GetUInt32();

                    /*Only 70 packs are available for now*/
                    if (packid > 70)
                        return;

                    /* RANDOMIZSING */
                    packid = GetUniquePackId(result, packid);

                    if (packid == 0)
                        return;

                    stmta->setUInt32(0, 5);
                    stmta->setUInt32(1, player->GetSession()->GetAccountId());

                    stmtb->setUInt32(0, player->GetSession()->GetAccountId());
                    stmtb->setUInt32(1, packid);
                }
                else
                {
                    /*First reward*/
                    packid = urand(1, 10);

                    stmta->setUInt32(0, 5);
                    stmta->setUInt32(1, player->GetSession()->GetAccountId());

                    stmtb->setUInt32(0, player->GetSession()->GetAccountId());
                    stmtb->setUInt32(1, packid);
                }

                if (stmta && stmtb)
                {
                    LoginDatabase.Execute(stmta);
                    LoginDatabase.Execute(stmtb);

                    //Generating CODE format XXXX-XXXXX-XXXX
                    std::string code = "";
                    for (int i = 0; i< 13; i++)
                    {
                        int Char_Code;
                        Char_Code = urand(48, 57);
                        code += char(Char_Code);
                        if (i == 3 || i == 8)
                            code += "-";
                    }
                    //sWorld->SendServerMessage(SERVER_MSG_STRING, code.c_str());

                    stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CODE);
                    stmt->setString(0, code);
                    stmt->setUInt32(1, REWARD_PREPARED_ITEMPACK);
                    stmt->setUInt32(2, packid);
                    stmt->setUInt32(3, 0);
                    stmt->setUInt32(4, 0);
                    stmt->setUInt32(5, 0);
                    stmt->setString(6, "Vote Reward");
                    CharacterDatabase.Execute(stmt);

                    std::string subject;
                    std::string text;
                    if (player->GetSession()->GetSessionDbLocaleIndex() != 8)
                    {
                        subject = "Dark Portal Reward System";
                        text = "You have obtained Reward for vote activity. Please use this CODE in DP Manager:\n\n";
                        text += code;
                        text += "\n\nPlease REMEMBER this code or you will lose your reward!\nAlso you can share this code to other players";
                    }
                    else
                    {
                        subject = "Dark Portal Система наград";
                        text = "Вы получили код за активность в голосовании. Используйте его у Менеджера ДП для получения подарка.\n\n";
                        text += code;
                        text += "\n\nЗапомните этот код, иначе вы потеряете свою награду!\nТакже вы можете предать этот код другому игроку.";
                    }

                    // Creature id of code manager
                    uint32 codemanager = 100107;
                    SQLTransaction trans = CharacterDatabase.BeginTransaction();
                    MailDraft(subject, text).SendMailTo(trans, MailReceiver(player, GUID_LOPART(player->GetGUID())), MailSender(MAIL_CREATURE, codemanager));
                    CharacterDatabase.CommitTransaction(trans);
                }
            }
        }
    }
};

void AddSC_server_manager()
{
    new code_manager();
    new login_code_controller();
}