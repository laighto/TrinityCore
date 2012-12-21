#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "World.h"

const Position allyPositions[3] =
{
    { -13248.2f, 282.385f, 21.8568f, 0.12517f },
    { -13193.7f, 315.692f, 21.8568f, 4.36162f },
    { -13162.7f, 262.096f, 21.8568f, 2.91257f },
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
                    aur->SetDuration(30*IN_MILLISECONDS); // Слабость негодникам
            }

            killed->CastSpell(killed, 48325, true);
            if (Aura * aur = killed->GetAura(48325))
                aur->SetDuration(7*IN_MILLISECONDS); //  Божественный щит

            if (sWorld->getBoolConfig(PvPEvent))
            {
                killed->CastSpell(killed, 9454, true);
                if (Aura * freeze = killed->GetAura(9454))
                    freeze->SetDuration(300*IN_MILLISECONDS); //  Заморозка
            }

            uint32 rnd = urand(0, 2);
            killed->TeleportTo(0, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());
        }
        else //Marry Xmas
        {
            killer->SummonGameObject(600003, killed->GetPositionX(), killed->GetPositionY(), killed->GetPositionZ(), 0, 0, 0, 0, 0, 0);
        }

        //WORLD MASS EVENT
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
        }
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
 
    void OnCreatureKill(Player* player, Creature* boss)
    {
        //WORLD MASS EVENT
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

        if (boss->isWorldBoss())
        {
            if (player->getGender() == GENDER_MALE)
            {
                char msg[250];
                snprintf(msg, 250, "|CFF7BBEF7[Boss Announcer]|r:|cffff0000 %s |r and his group killed world boss |CFF18BE00[%s]|r !!!", player->GetName().c_str(),boss->GetName().c_str());
                sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
            }
            else
            {
                char msg[250];
                snprintf(msg, 250, "|CFF7BBEF7[Boss Announcer]|r:|cffff0000 %s |r and her group killed world boss |CFF18BE00[%s]|r !!!", player->GetName().c_str(),boss->GetName().c_str());
                sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
            }
        }

        //Marry Xmas
        if (urand(0, 5) == 3)
            player->SummonGameObject(600004, boss->GetPositionX()+1.0f, boss->GetPositionY()+1.0f, boss->GetPositionZ()+1.0f, 0, 0, 0, 0, 0, 0);
    }

    //WORLD MASS EVENT
    void OnLogin(Player* player)
    {
        /*if(checker)
        {
            player->SendNewItem(item, 1, false, true);
        }*/

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
        }
    }
};

void AddSC_pvp_script()
{
    new mob_ressurect();
    new mod_afk();
    new Boss_Announcer();
}