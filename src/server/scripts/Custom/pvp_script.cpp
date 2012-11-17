#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "World.h"

const Position allyPositions[3] =
{
    { -13248.2f, 282.385f, 21.8568f, 0.12517f },
    { -13193.7f, 315.692f, 21.8568f, 4.36162f },
    { -13162.7f, 262.096f, 21.8568f, 2.91257f },
};

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
        {
            if (player->getGender() == GENDER_MALE)
            {
                char msg[250];
                snprintf(msg, 250, "|CFF7BBEF7[Boss Announcer]|r:|cffff0000 %s |r and his group killed world boss |CFF18BE00[%s]|r !!!", player->GetName(),boss->GetName());
                sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
            }
            else
            {
                char msg[250];
                snprintf(msg, 250, "|CFF7BBEF7[Boss Announcer]|r:|cffff0000 %s |r and her group killed world boss |CFF18BE00[%s]|r !!!", player->GetName(),boss->GetName());
                sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
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