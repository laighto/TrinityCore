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

#include "AccountMgr.h"
#include "Player.h"
#include "Chat.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"


class custom_recruitafriend : public CommandScript
{
public:
    custom_recruitafriend() : CommandScript("custom_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand customCommandTable[] =
        {
            { "friend",   rbac::RBAC_PERM_COMMAND_RECRUIT_A_FRIEND,     true,  &HandleSetPlayerRecruitCommand,     "", NULL },
            { "delete",   rbac::RBAC_PERM_COMMAND_RECRUIT_A_FRIEND,     true,  &HandleDeletePlayerRecruitCommand,  "", NULL },
            { NULL,               0,                     false, NULL,                               "", NULL }
        };

        static ChatCommand commandTable[] =
        {
            { "recruit",  rbac::RBAC_PERM_COMMAND_RECRUIT_A_FRIEND,     true,  NULL,                 "",  customCommandTable},
            { NULL,                        0,                     false, NULL,                               "", NULL }
        };

        return commandTable;
    }

    static bool HandleSetPlayerRecruitCommand(ChatHandler* handler, const char* args)
    {

        Player* target;
        uint64 targetGuid;
        //uint64 recruiter = 0;
        std::string targetName;
        
        if (!handler->extractPlayerTarget((char*)args, &target, &targetGuid, &targetName))
            return false;

        if (Player* initiator = handler->GetSession()->GetPlayer())
        {
            uint64 InitiatorAccount = sObjectMgr->GetPlayerAccountIdByGUID(initiator->GetGUID());
            uint64 FriendAccount = sObjectMgr->GetPlayerAccountIdByGUID(targetGuid);
            
            if (InitiatorAccount != FriendAccount)
            {
                if (handler->GetSession()->GetRecruiterId() == 0)
                {
                    PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_SET_RECRUITER);
                    stmt->setUInt64(0, FriendAccount);
                    stmt->setUInt64(1, InitiatorAccount);
                    LoginDatabase.Execute(stmt);

                    handler->PSendSysMessage(LANG_PLAYER_SET_RECRUITER_SUCCESS, targetName.c_str());
                }
                else
                {
                    handler->PSendSysMessage(LANG_PLAYER_CAN_NOT_SET_RECRUITER);
                    //handler->PSendSysMessage("%u", recruiter);
                }
            }
            else 
            {
                handler->PSendSysMessage(LANG_PLAYER_NOT_FOUND);
                return false;
            }
        }
        return true;
    }

    static bool HandleDeletePlayerRecruitCommand(ChatHandler* handler, const char* /*args*/)
    {
        Player* initiator = handler->GetSession()->GetPlayer();
        uint64 InitiatorAccount = sObjectMgr->GetPlayerAccountIdByGUID(initiator->GetGUID());
        
        PreparedStatement* stmt;
        stmt = LoginDatabase.GetPreparedStatement(LOGIN_DELETE_RECRUITER);
        stmt->setUInt64(0, InitiatorAccount);
        LoginDatabase.Execute(stmt);

        handler->PSendSysMessage(LANG_PLAYER_DELETE_RECRUITER);

        return true;
    }
};

void AddSC_custom_recruitafriend()
{
    new custom_recruitafriend();
}