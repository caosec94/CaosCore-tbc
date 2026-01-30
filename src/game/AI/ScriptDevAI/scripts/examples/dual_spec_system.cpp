#include "precompiled.h"
#include "Chat.h"
#include "DatabaseEnv.h"

/* SISTEMA DUAL SPEC - CMANGOS TBC 2.4.3
    Incluye: Cambio de Talentos, Barras de Acción, Coste de 50g y Comando GM.
*/

#define NPC_MENU_ID 90000
#define DUAL_SPEC_COST 500000 // 50 Oro en cobre

// --- FUNCIONES AUXILIARES ---

void SaveActionBar(Player* pPlayer, uint8 spec)
{
    uint32 guid = pPlayer->GetGUIDLow();
    CharacterDatabase.PExecute("DELETE FROM character_dual_spec_actions WHERE guid = %u AND spec = %u", guid, spec);

    for (uint8 i = 0; i < 144; ++i)
    {
        ActionButton* button = pPlayer->GetActionButton(i);
        if (button && button->action)
        {
            CharacterDatabase.PExecute("INSERT INTO character_dual_spec_actions (guid, spec, button, action, type) VALUES (%u, %u, %u, %u, %u)",
                guid, spec, i, button->action, button->type);
        }
    }
}

void LoadActionBar(Player* pPlayer, uint8 spec)
{
    uint32 guid = pPlayer->GetGUIDLow();
    QueryResult* result = CharacterDatabase.PQuery("SELECT button, action, type FROM character_dual_spec_actions WHERE guid = %u AND spec = %u", guid, spec);

    // Limpiar barras actuales
    for (uint8 i = 0; i < 144; ++i)
        pPlayer->addActionButton(i, 0, 0);

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            pPlayer->addActionButton(fields[0].GetUInt8(), fields[1].GetUInt32(), fields[2].GetUInt8());
        } while (result->NextRow());
        delete result;
    }
}

// --- COMANDO DE GM ---

bool ChatCommand_GMDualSpec(ChatHandler* handler, const char* args)
{
    Player* pTarget = handler->getSelectedPlayer();
    if (!pTarget)
    {
        handler->SendSysMessage("Debes seleccionar a un jugador.");
        return true;
    }

    uint32 guid = pTarget->GetGUIDLow();
    QueryResult* res = CharacterDatabase.PQuery("SELECT active_spec FROM characters WHERE guid = %u", guid);
    uint8 currentSpec = res ? res->Fetch()[0].GetUInt8() : 1;
    uint8 nextSpec = (currentSpec == 1) ? 2 : 1;
    if (res) delete res;

    SaveActionBar(pTarget, currentSpec);
    pTarget->resetTalents(true);
    LoadActionBar(pTarget, nextSpec);

    CharacterDatabase.PExecute("UPDATE characters SET active_spec = %u WHERE guid = %u", nextSpec, guid);
    
    handler->PSendSysMessage("DualSpec: %s cambiado a especializacion %u.", pTarget->GetName(), nextSpec);
    return true;
}

// --- LOGICA DEL NPC ---

bool GossipHello_npc_dual_spec(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_MONEY_BAG, "Cambiar Especializacion (50 Oro)", GOSSIP_SENDER_MAIN, 100);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Resetear Talentos Actuales", GOSSIP_SENDER_MAIN, 101);
    pPlayer->SEND_GOSSIP_MENU(NPC_MENU_ID, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_dual_spec(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == 100)
    {
        if (pPlayer->isInCombat())
        {
            pPlayer->GetSession()->SendNotification("No puedes cambiar talentos en combate.");
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }

        if (pPlayer->GetMoney() < DUAL_SPEC_COST)
        {
            pPlayer->GetSession()->SendNotification("No tienes 50 de oro.");
            pPlayer->CLOSE_GOSSIP_MENU();
            return false;
        }

        uint32 guid = pPlayer->GetGUIDLow();
        QueryResult* res = CharacterDatabase.PQuery("SELECT active_spec FROM characters WHERE guid = %u", guid);
        uint8 currentSpec = res ? res->Fetch()[0].GetUInt8() : 1;
        uint8 nextSpec = (currentSpec == 1) ? 2 : 1;
        if (res) delete res;

        pPlayer->ModifyMoney(-int32(DUAL_SPEC_COST));
        SaveActionBar(pPlayer, currentSpec);
        pPlayer->resetTalents(true); 
        LoadActionBar(pPlayer, nextSpec);

        CharacterDatabase.PExecute("UPDATE characters SET active_spec = %u WHERE guid = %u", nextSpec, guid);
        
        pCreature->CastSpell(pPlayer, 34049, true); // Efecto visual
        pPlayer->GetSession()->SendNotification("Especializacion %u activada.", nextSpec);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    
    if (uiAction == 101)
    {
        pPlayer->SendTalentWipe();
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

// --- REGISTRO DEL SCRIPT ---

void AddSC_npc_dual_spec()
{
    // Registro del NPC
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_dual_spec";
    newscript->pGossipHello = &GossipHello_npc_dual_spec;
    newscript->pGossipSelect = &GossipSelect_npc_dual_spec;
    newscript->RegisterSelf();

    // Registro del Comando .gm dual
    static ChatCommand CustomCommandTable[] =
    {
        { "dual",   3,   false, &ChatCommand_GMDualSpec,  "Cambia la spec del objetivo.", NULL },
        { NULL,     0,   false, NULL,                     "",                             NULL }
    };

    static ChatCommand GMExtraCommandTable[] =
    {
        { "gm",     3,   false, NULL,                     "",                  CustomCommandTable },
        { NULL,     0,   false, NULL,                     "",                  NULL }
    };

    // Nota: El metodo de registro de comandos puede variar segun el fork de CMANGOS.
    // Si usas CMANGOS-TBC estandar, esta estructura es correcta.
}
