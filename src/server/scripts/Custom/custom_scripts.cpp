/*
 * patch by chaosua 2012-2013 (chaosua2008@gmail.com)
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

#include "custom_scripts.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "World.h"
#include "Chat.h"
#include "Language.h"

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

class mob_ressurect : public PlayerScript
{
public:
    mob_ressurect() : PlayerScript("mob_ressurect") { }

    void OnPVPKill(Player* killer, Player* killed)
    {
        if (killed->GetAreaId() == 2177) // Gurubashi Arena
        {
            if (killed->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
                killed->RemoveAurasByType(SPELL_AURA_MOD_SHAPESHIFT);

            killed->ResurrectPlayer(1.0f, false);
            killed->DurabilityRepairAll(false, 0, false);

            if (killer->GetAreaId() != 2177)
            {
                killer->CastSpell(killer, 15007, true);
                if (Aura * aur = killer->GetAura(15007))
                    aur->SetDuration(30 * IN_MILLISECONDS); // Слабость негодникам
            }

            killed->CastSpell(killed, 48325, true);
            if (Aura * aur = killed->GetAura(48325))
                aur->SetDuration(7*IN_MILLISECONDS); //  Божественный щит

            if (sWorld->getBoolConfig(PVP_G_ARENA_EVENT))
            {
                killed->CastSpell(killed, 9454, true);
                if (Aura * freeze = killed->GetAura(9454))
                    freeze->SetDuration(300 * IN_MILLISECONDS); //  Заморозка

                if (Aura * aur = killed->GetAura(48325))
                    aur->SetDuration(300 * IN_MILLISECONDS); //  Божественный щит
            }

            uint32 rnd = urand(0, 2);
            killed->TeleportTo(0, allyPositions[rnd].GetPositionX(), allyPositions[rnd].GetPositionY(), allyPositions[rnd].GetPositionZ(), allyPositions[rnd].GetOrientation());

            //Frost
            /*if (roll_chance_f(1.0f))
            {
                killer->AddItem(49426, 1);
                sWorld->SendWorldText(12015, killer->GetName().c_str());
            }*/

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
        if (sWorld->getBoolConfig(ANTI_AFK))
        {
            if (player->GetZoneId() == 4395/*Dalaran zone*/)
            {
                uint32 rand = urand(0, 2);

                if (rand == 0)
                	player->SetDisplayId(21304);//pig
                else if (rand == 1)
                    player->SetDisplayId(25146); //elemental
                else player->SetDisplayId(30414); //panda monk

                if (sWorld->getBoolConfig(ANTI_AFK_DALARAN))
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
        if (boss->isWorldBoss())
            sWorld->SendWorldText(LANG_BOSS_ANNOUNCER, player->GetName().c_str(), boss->GetNameForLocaleIdx(player->GetSession()->GetSessionDbLocaleIndex()).c_str());

        //Berserk
      /*  if (roll_chance_f(1.0f))
        {
            if ( (player->getLevel() - boss->getLevel()) <= 10 )
            {
                player->CastSpell(player, 26662, true);
                if (Aura * bers = player->GetAura(26662))
                    bers->SetDuration(8*IN_MILLISECONDS);
            }
        }*/

        //Gift
        //if (roll_chance_f(10.0f))
         //   player->SummonGameObject(600004, boss->GetPositionX()+0.1f, boss->GetPositionY()+0.1f, boss->GetPositionZ()+0.1f, 0, 0, 0, 0, 0, 0);
    }

    void OnLogin(Player* player)
    {
        //Recruit  A Friend System/ Player 'A' logs in. System should try to find online Player 'B' with account(B)==recruiter(A);
        std::string recruiterNameB;
        uint32 online = 0;
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
    }
};

//Quest Waiting to Exsanguinate 27045
class go_abandoned_outhouse : public GameObjectScript
{
    public:
        go_abandoned_outhouse() : GameObjectScript("go_abandoned_outhouse") { }

        bool OnQuestAccept(Player* player, GameObject* /*go*/, Quest const* quest) OVERRIDE
        {
            if (quest->GetQuestId() == QUEST_WAITING_TO_EXSANGUINATE)
            {
                player->CastSpell(player, SPELL_SUMMON_DEATHSTALKER_YORICK, false); 
            }
            return true;
        }
};

void AddSC_custom_script()
{
    new mob_ressurect();
    new mod_afk();
    new Boss_Announcer();
    new go_abandoned_outhouse();
}