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
 *
 * Txh unknown user from trinitycore.org
 */
#include "ScriptPCH.h"
#include "World.h"

class reset_OnDuel : public PlayerScript
{
    public:
        reset_OnDuel() : PlayerScript("reset_OnDuel") {}

        void ResetData(Player* player)
        {
            player->SetHealth(player->GetMaxHealth());

            switch (player->getPowerType())
            {
            case POWER_MANA:
                player->SetPower(POWER_MANA, player->GetMaxPower(POWER_MANA));
                break;
            case POWER_RAGE:
                player->SetPower(POWER_RAGE, 0);
                break;
            case POWER_RUNIC_POWER:
                player->SetPower(POWER_RUNIC_POWER, 0);
                break;
            default:
                break;
            }
        }

        void OnDuelStart(Player* player1, Player* player2) override
        {
            if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN))
            {
                ResetData(player1);
                ResetData(player2);
            }
        }

        void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType type) override
        {
            if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN) && type == DUEL_WON)
            {
                winner->RemoveArenaSpellCooldowns();
                looser->RemoveArenaSpellCooldowns();

                ResetData(winner);
                ResetData(looser);
            }
        }

//    void OnDuelEnd(Player *winner, Player *looser, DuelCompleteType /*type*/) override
/*    {
        // reset cooldowns in elewynn forest and durotar
        if (sWorld->getBoolConfig(CONFIG_DUEL_RESET_COOLDOWN) && 
            (winner->GetMapId() == 0 || winner->GetMapId() == 1 || winner->GetMapId() == 571 || winner->GetMapId() == 690)
            /* (winner->GetZoneId() == 14 || winner->GetZoneId() == 12)*/
//        )
/*        {
            winner->RemoveArenaSpellCooldowns();
            looser->RemoveArenaSpellCooldowns();
            winner->SetHealth(winner->GetMaxHealth());
            looser->SetHealth(looser->GetMaxHealth());
            if (winner->getPowerType() == POWER_MANA) 
                winner->SetPower(POWER_MANA, winner->GetMaxPower(POWER_MANA));
            if (looser->getPowerType() == POWER_MANA) 
                looser->SetPower(POWER_MANA, looser->GetMaxPower(POWER_MANA));
        }
    }
*/
};

void AddSC_DuelReset()
{
    new reset_OnDuel();
}
