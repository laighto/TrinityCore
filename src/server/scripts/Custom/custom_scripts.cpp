#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "World.h"
#include "Chat.h"
#include "Language.h"
#include "GossipDef.h"
#include "SmartAI.h"
#include "Player.h"

const Position allyPositions[3] =
{
    { -13248.2f, 282.385f, 21.8568f, 0.12517f },
    { -13193.7f, 315.692f, 21.8568f, 4.36162f },
    { -13162.7f, 262.096f, 21.8568f, 2.91257f },
};

enum CustomSpell
{
    ORANGE_FRIENDS      = 38787,
    POWER_OF_FRIENDSHIP = 26664,
};

enum Customdata
{
    NPC_BOSS_GIFT = 911912,
    FACTION_HOSTILE = 14,
    REWARD_PREPARED_ITEMPACK = 6,
};

uint32 counter = 1;
uint32 leader = 0;
bool checker = false;

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

            killed->ResurrectPlayer(1.0f, false);
            killed->DurabilityRepairAll(false, 0, false);

            if (killer->GetAreaId() != 2177)
            {
                killer->CastSpell(killer, 15007, true);
                if (Aura * aur = killer->GetAura(15007))
                    aur->SetDuration(30*IN_MILLISECONDS); 
            }

            killed->CastSpell(killed, 48325, true);
            if (Aura * aur = killed->GetAura(48325))
                aur->SetDuration(7*IN_MILLISECONDS); 

            if (sWorld->getBoolConfig(PvPEvent))
            {
                killed->CastSpell(killed, 9454, true);
                if (Aura * freeze = killed->GetAura(9454))
                    freeze->SetDuration(300*IN_MILLISECONDS); 
            }

            uint32 rnd = urand(0, 2);
            killed->TeleportTo(0, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());

            //Frost
          //  if (roll_chance_f(1.0f))
          //  {
           //     killer->AddItem(49426, 1);
           //     sWorld->SendWorldText(12015, killer->GetName().c_str());
            //}

        }
       /* else //Marry Xmas
        {
            killer->SummonGameObject(600003, killed->GetPositionX(), killed->GetPositionY(), killed->GetPositionZ(), 0, 0, 0, 0, 0, 0);
        }*/

        //Add ancient shard
        //if (roll_chance_f(1.0f) && killer->InBattleground())
        //    killer->AddItem(23359, 1);

      /*  //WORLD MASS EVENT
        if (sWorld->getBoolConfig(CONFIG_WORLD_EVENT) && !checker)
        {
            if (killed->GetGUIDLow() == leader)
            {
                QueryResult result = CharacterDatabase.PQuery("SELECT guid FROM world_event_player WHERE guid = %u ;", killer->GetGUIDLow());

                if (result)
                {         
                    CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed + 10 WHERE guid = %u ;", killer->GetGUIDLow());
                    CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed - 100 WHERE guid = %u ;", killed->GetGUIDLow());
                }
                else
                {         
                    CharacterDatabase.PExecute("INSERT INTO world_event_player VALUES (%u, 10, 0);", killer->GetGUIDLow());
                    CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed - 100 WHERE guid = %u ;", killed->GetGUIDLow());
                }

                QueryResult leadercheck = CharacterDatabase.PQuery("SELECT guid FROM world_event_player ORDER BY creature_killed DESC LIMIT 1;");

                if (leadercheck)
                {
                    Field *fieldsDB = leadercheck->Fetch();
                    leader = fieldsDB[0].GetUInt32();

                    if (killer->GetGUIDLow() == leader)
                    {
                        killer->AddAura(47044, killer);
                        char msg[250];
                        snprintf(msg, 250, "|CFF7BBEF7[World Event Announcer]|r:|cffff0000 %s |r has become Renegade over %s, HIGH priority to kill HIM!", killer->GetName().c_str(), killed->GetName().c_str());
                        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
                    }
                }
            }
        }*/
    }
};

const Position afkPositions[3] =
{
    { 5806.56f, 865.759f, 1063.911f, 4.739f },
    { 5644.94f, 861.313f, 569.724f, 2.4673f },
    { 5652.90f, 454.909f, 789.917f, 0.8486f },
};

class mod_afk : public PlayerScript
{
public:
    mod_afk() : PlayerScript("mod_afk") { }

    void OnPlayerAfk(Player* player)
    {
        if (sWorld->getBoolConfig(DalaranAntiAfk))
        {
            if (player->GetZoneId() == 4395/*Dalaran zone*/)
            {
                uint32 rand = urand(0, 2);

                if (rand == 0)
                	player->SetDisplayId(21304);//pig
                else if (rand == 1)
                    player->SetDisplayId(25146); //elemental
                else player->SetDisplayId(30414); //panda monk

                if (sWorld->getBoolConfig(DalaranAntiAfkTP))
                    player->TeleportTo(0, -13225.71f, 232.982f, 33.436f, 1.055f);
                else
                {
                     uint32 rnd = urand(0, 2);
                     player->TeleportTo(571, afkPositions[rnd].GetPositionX(), afkPositions[rnd].GetPositionY(), afkPositions[rnd].GetPositionZ(), afkPositions[rnd].GetOrientation());
                }
            }
            else if (player->GetZoneId() == 4415/*Violet Hold*/)
                player->TeleportTo(571, 5695.1f, 505.2f, 652.7f, 4.0f);
        }
    }
};

class Boss_Announcer : public PlayerScript
{
public:
    Boss_Announcer() : PlayerScript ("Boss_Announcer") {}
 
    void OnCreatureKill(Player* player, Creature* creature)
    {
        if (creature->isWorldBoss() && player->GetSession()->GetSecurity() < 1)
            sWorld->SendWorldText(LANG_BOSS_ANNOUNCER, player->GetName().c_str(), creature->GetNameForLocaleIdx(player->GetSession()->GetSessionDbLocaleIndex()).c_str());

        // New event Pseudo Doppelganger
        if (sWorld->getBoolConfig(CONFIG_WORLD_EVENT) && !creature->isWorldBoss() && roll_chance_i(1) && ((player->getLevel() - creature->getLevel()) <= 5))
        {
            if (Creature* miniboss = creature->SummonCreature(NPC_BOSS_GIFT, creature->GetPositionX() + 0.1f, creature->GetPositionY() + 0.1f, creature->GetPositionZ() + 0.1f, 0, TEMPSUMMON_TIMED_DESPAWN, 180000))
            {
                miniboss->setFaction(FACTION_HOSTILE);
                miniboss->SetLevel(player->getLevel() + 1);
                miniboss->SetMaxHealth(int32(player->GetMaxHealth() * 1.5));
                miniboss->SetArmor(player->GetArmor());
                miniboss->SetStat(STAT_STRENGTH, player->GetStat(STAT_STRENGTH));
                miniboss->SetStat(STAT_AGILITY, int32(player->GetStat(STAT_AGILITY) * 1.1));
                miniboss->SetStat(STAT_STAMINA, int32(player->GetStat(STAT_STAMINA) * 1.1));
                miniboss->SetStat(STAT_INTELLECT, player->GetStat(STAT_INTELLECT));
                miniboss->SetStat(STAT_SPIRIT, player->GetStat(STAT_SPIRIT));
                std::string str = "Dark ";
                str += player->GetName();
                miniboss->SetName(str);
            }
        }

        // Low chance to get Level UP
        if (player->getLevel() < 80 && roll_chance_f(0.05f) && (player->getLevel() - creature->getLevel()) <= 5)
            player->SetLevel(player->getLevel() + 1);

/*        //WORLD MASS EVENT
        if (sWorld->getBoolConfig(CONFIG_WORLD_EVENT) && !checker && ((player->getLevel() - boss->getLevel()) <= 5))
        {
            //counter++;

            QueryResult result = CharacterDatabase.PQuery("SELECT guid FROM world_event_player WHERE guid = %u ;", player->GetGUIDLow());

            if (!result)
            {
                if (boss->isWorldBoss() && (boss->GetRespawnTime() > DAY * 0.5))
                {
                    if (player->GetGUIDLow() == leader)
                        CharacterDatabase.PExecute("INSERT INTO world_event_player VALUES (%u, 1, 1);", player->GetGUIDLow());
                    else CharacterDatabase.PExecute("INSERT INTO world_event_player VALUES (%u, 50, 1);", player->GetGUIDLow());
                    
                    counter = counter + 50;
                }
                else if (boss->isElite())
                {
                    if (player->GetGUIDLow() == leader)
                        CharacterDatabase.PExecute("INSERT INTO world_event_player VALUES (%u, 1, 0);", player->GetGUIDLow());
                    else CharacterDatabase.PExecute("INSERT INTO world_event_player VALUES (%u, 10, 0);", player->GetGUIDLow());
                    
                    counter = counter + 10;
                }
                else
                {
                    CharacterDatabase.PExecute("INSERT INTO world_event_player VALUES (%u, 1, 0);", player->GetGUIDLow());
                    counter++;
                }
            }
            else
            {
                if (boss->isWorldBoss() && (boss->GetRespawnTime() > DAY * 0.5))
                {
                    if (player->GetGUIDLow() == leader)
                        CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed + 1, boss_killed = boss_killed + 1 WHERE guid = %u ;", player->GetGUIDLow());
                    else CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed + 50, boss_killed = boss_killed + 1 WHERE guid = %u ;", player->GetGUIDLow());
                    
                    counter = counter + 10;                
                }
                else if (boss->isElite())
                {
                    if (player->GetGUIDLow() == leader)
                        CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed + 1 WHERE guid = %u ;", player->GetGUIDLow());
                    else CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed + 10 WHERE guid = %u ;", player->GetGUIDLow());
                    
                    counter = counter + 5;
                }
                else
                {
                    CharacterDatabase.PExecute("UPDATE world_event_player SET creature_killed = creature_killed + 1 WHERE guid = %u ;", player->GetGUIDLow());
                    counter++;
                }
            }

            if (counter > 50)
            {
                CharacterDatabase.PExecute("UPDATE world_event SET creatures_killed = creatures_killed +  %u", counter);
                counter = 1;
            }
        }
        // END WORLD MASS EVENT
*/

/*        //Gift
        if (roll_chance_f(10.0f))
            player->SummonGameObject(600004, boss->GetPositionX()+0.1f, boss->GetPositionY()+0.1f, boss->GetPositionZ()+0.1f, 0, 0, 0, 0, 0, 0);
*/
    }

    void OnLogin(Player* player, bool /*firstLogin*/)
    {
        //Recruit  A Friend System/ Player 'A' logs in. System should try to find online Player 'B' with account(B)==recruiter(A);
        std::string recruiterNameB;
        //uint32 online = 0;
        uint64 recruiterGuidB = 0;
        uint64 recruiteridB = player->GetSession()->GetRecruiterId(); //Get recruiter AccID(B) For Loged in Player(A)
        uint64 recruitAccIdA = player->GetSession()->GetAccountId(); //Get Player(A) AccID(A)

        //If Loged In Player(A) has recruiter(B) != 0 Try To find if there is player online with that account ID
        if (recruiteridB != 0) 
        {
            // Try Find if there is online character with account==RecruiterID(B)
            QueryResult resultAB =  CharacterDatabase.PQuery("SELECT guid, name FROM characters WHERE online=1 AND account=%u;", recruiteridB);
            if (resultAB)
            {
                Field *row = resultAB->Fetch();
                recruiterGuidB = row[0].GetUInt64();
                recruiterNameB = row[1].GetString();
            }
            // Check if there is player online
            if (recruiterGuidB != 0)
            {
                if (Player* recruiterB = sObjectAccessor->FindPlayerByName(recruiterNameB))
                {
                    recruiterB->CastSpell(recruiterB, POWER_OF_FRIENDSHIP, true);
                    ChatHandler(recruiterB->GetSession()).PSendSysMessage(RECRUIT_ONLINE, player->GetSession()->GetPlayerName().c_str());
                    player->CastSpell(player, POWER_OF_FRIENDSHIP, true);
                    ChatHandler(player->GetSession()).PSendSysMessage(RECRUITER_ONLINE, recruiterB->GetSession()->GetPlayerName().c_str());
                }
            }
            else 
            {
                if (Aura * friendship = player->GetAura(POWER_OF_FRIENDSHIP))
                    friendship->Remove(); 
            }
        }
        else if (recruiteridB == 0) // Player A doesn't have recruiter. Try to Find if someone account B from online list has Players A accountID in recruiter field
        {
            uint64 recruitAccIdB =0;
            QueryResult resultACC =  LoginDatabase.PQuery("SELECT id FROM account WHERE online=1 AND recruiter=%u;", recruitAccIdA);
            if (resultACC)
            {
                Field *row = resultACC->Fetch();
                recruitAccIdB = row[0].GetUInt64();
            }

            //We found account with Players A account in recruiter field
            if (recruitAccIdB != 0)
            {
                uint64 recruitGuidB = 0;
                std::string recruitNameB;

                // If we found online account B with recruiter == recruitAccIdA Try find online character from it
                QueryResult resultBA =  CharacterDatabase.PQuery("SELECT guid, name FROM characters WHERE online=1 AND account=%u;", recruitAccIdB);
                if (resultBA)
                {
                    Field *row = resultBA->Fetch();
                    recruitGuidB = row[0].GetUInt64();
                    recruitNameB = row[1].GetString();
                }

                // Check if there is player online
                if (recruitGuidB != 0)
                {
                    if (Player* recruitB = sObjectAccessor->FindPlayerByName(recruitNameB))
                    {
                        recruitB->CastSpell(recruitB, POWER_OF_FRIENDSHIP, true);
                        ChatHandler(recruitB->GetSession()).PSendSysMessage(RECRUITER_ONLINE, player->GetSession()->GetPlayerName().c_str());
                        player->CastSpell(player, POWER_OF_FRIENDSHIP, true);
                        ChatHandler(player->GetSession()).PSendSysMessage(RECRUIT_ONLINE, recruitB->GetSession()->GetPlayerName().c_str());
                    }
                }
                else 
                {
                    if (Aura * friendship = player->GetAura(POWER_OF_FRIENDSHIP))
                        friendship->Remove(); 
                }
            }
        }

    //WORLD MASS EVENT
        /*if(checker)
        {
            player->SendNewItem(item, 1, false, true);
        }

        if (sWorld->getBoolConfig(CONFIG_WORLD_EVENT) && !checker)
        {
           
            QueryResult resultb = CharacterDatabase.PQuery("SELECT creatures_killed FROM world_event;");

            if (resultb)
            {
                Field *row = resultb->Fetch();
                uint32 creatures = row[0].GetUInt32();
                if (creatures > 500000)
                    checker=true;
            } 

            if (!checker)
            {
                QueryResult result = CharacterDatabase.PQuery("SELECT guid FROM world_event_player ORDER BY creature_killed DESC LIMIT 1;");

                if (result)
                {
                    Field *fieldsDB = result->Fetch();
                    leader = fieldsDB[0].GetUInt32();

                    if (player->GetGUIDLow() == leader)
                    {
                        //player->AddAura(47044, player);
                        char msg[250];
                        snprintf(msg, 250, "|CFF7BBEF7[World Event Announcer]|r:|cffff0000 %s |r is a Renegade, HIGH priority to kill HIM!", player->GetName().c_str());
                        sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
                    }
                    else if (urand (0, 5) == 3)
                    {
                        QueryResult result = CharacterDatabase.PQuery("SELECT name FROM characters WHERE guid = %u;", leader);

                        if (result)
                        {
                            Field *fieldsDB = result->Fetch();
                            const char *name = fieldsDB[0].GetCString();
                            char msg[250];
                            snprintf(msg, 250, "|CFF7BBEF7[World Event Announcer]|r:|cffff0000 %s |r is a Renegade, HIGH priority to kill HIM!", name);
                            sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
                        }
                    }
                }
            }
        }*/
    }
};

class code_generator : public ItemScript
{
public:
    code_generator() : ItemScript("code_generator") { }

    void SendCode(Player* player)
    {
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_CODE);

        std::string code = "";
        for (int i = 0; i< 13; i++)
        {
            int Char_Code;
            Char_Code = urand(48, 57);
            code += char(Char_Code);
            if (i == 3 || i == 8)
                code += "-";
        }

        /* RANDOMIZSING pack id from reserved for evenet 100-110*/
        uint32 packid = urand(100, 110);

        stmt->setString(0, code);
        stmt->setUInt32(1, REWARD_PREPARED_ITEMPACK);
        stmt->setUInt32(2, packid);
        stmt->setUInt32(3, 0);
        stmt->setUInt32(4, 0);
        stmt->setUInt32(5, 0);
        stmt->setString(6, "Doppelganger Event");
        CharacterDatabase.Execute(stmt);

        std::string subject;
        std::string text;
        if (player->GetSession()->GetSessionDbLocaleIndex() != 8)
        {
            subject = "Ancient paper";
            text = "Ancient paper burned out, and in the ash you found a numbers. You can use it in DP Manager:\n\n";
            text += code;
            text += "\n\nREMEMBER this code or you will lose your reward!\nAlso you can share this code to other players";
        }
        else
        {
            subject = "Древняя бумага";
            text = "Древняя бумага сгорела, и в пепле вы увидели цифры. Вы може использовать их у Менеджера ДП\n\n";
            text += code;
            text += "\n\nЗапомните этот код, иначе не сможете получить награду!\nВы можете предать этот код другому игроку.";
        }

        // Creature id of code manager
        uint32 codemanager = 100107;

        SQLTransaction trans = CharacterDatabase.BeginTransaction();
        MailDraft(subject, text).SendMailTo(trans, MailReceiver(player, GUID_LOPART(player->GetGUID())), MailSender(MAIL_CREATURE, codemanager));
        CharacterDatabase.CommitTransaction(trans);
        player->Whisper(text, LANG_UNIVERSAL, player);
    }

    bool OnUse(Player* player, Item* /*item*/, SpellCastTargets const& /*targets*/) override
    {
        if (roll_chance_i(50))
            SendCode(player);

        return false;
    }
};

class npc_editor : public CreatureScript
{
public:
    npc_editor() : CreatureScript("npc_editor") { }

    struct npc_editorAI : public ScriptedAI
    {
        npc_editorAI(Creature* creature) : ScriptedAI(creature) { }

        void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
        {
            player->PlayerTalkClass->SendCloseGossip();

            switch (gossipListId)
            {
            case 0:
                player->SetAtLoginFlag(AT_LOGIN_RENAME);
                me->Say("Change NAME SET. PLEASE RELOGIN NOW", LANG_UNIVERSAL, 0);
                break;
            case 1:
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
                me->Say("CHANGE FACTION SET. PLEASE RELOGIN NOW", LANG_UNIVERSAL, 0);
                break;
            case 2:
                player->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
                me->Say("CHANGE RACE SET. PLEASE RELOGIN NOW", LANG_UNIVERSAL, 0);
                break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_editorAI(creature);
    }
};

void AddSC_pvp_script()
{
    new mob_ressurect();
    new mod_afk();
    new Boss_Announcer();
    new npc_editor();
    new code_generator();
}