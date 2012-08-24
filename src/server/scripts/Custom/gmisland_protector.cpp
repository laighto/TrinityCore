#include "ScriptPCH.h"
#include "World.h"
#include "ObjectMgr.h"

const Position busted[1] =
{
    { -13201.88f, 276.512f, 21.86f, 4.304f },
};

class gmisland_protector : public CreatureScript
{
public:
    gmisland_protector() : CreatureScript("gmisland_protector") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new gmisland_protectorAI(pCreature);
    }

    struct gmisland_protectorAI : public ScriptedAI
    {
        gmisland_protectorAI(Creature* c) : ScriptedAI(c) {}

        void MoveInLineOfSight(Unit *who)
        {
            if (who->GetAreaId() == 876 /*&& who->GetPlayer()->GetSession()->GetSecurity() == SEC_PLAYER*/
                && who->IsHostileTo(me))
            {
                std::string str = "";
                str = "|cFFFFFC00[AhtunG!]|cFF00FFFF[|cFF60FF00" + std::string(who->GetName()) + "|cFF00FFFF] GMIsland Intruder DETECTED!";
                WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
                data << str;
                sWorld->SendGlobalGMMessage(&data);
                //who->TeleportTo(0, busted[0].GetPositionX(), busted[0].GetPositionY(), busted[0].GetPositionZ(), busted[0].GetOrientation());
                who->CastSpell(who, 9454, true);
                /*if (Aura * freeze = who->GetAura(9454))
                    freeze->SetDuration(600*IN_MILLISECONDS); // Заморозка */
            }
        }
    };
};

void AddSC_gmisland()
{
    new gmisland_protector();
}
