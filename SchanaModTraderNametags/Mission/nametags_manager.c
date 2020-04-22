class SchanaTraderNametagsManager
{
    private ref map<string, ref SchanaTraderNametagMenu> m_SchanaNametags;

    void SchanaTraderNametagsManager()
    {
        m_SchanaNametags = new map<string, ref SchanaTraderNametagMenu>();
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.Update, 1000, true);
    }

    void ~SchanaTraderNametagsManager()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.Update);
    }

    private void Update()
    {
        PlayerBase activePlayer = GetGame().GetPlayer();
        if (activePlayer && activePlayer.GetIdentity())
        {
            if (SchanaTraderNametagMenu.SchanaIsInSafezone(activePlayer, activePlayer))
            {
                string activePlayerId = activePlayer.GetIdentity().GetId();
                string id;
                foreach (Man man : ClientData.m_PlayerBaseList)
                {
                    PlayerBase player = PlayerBase.Cast(man);
                    if (player && player.GetIdentity())
                    {
                        id = player.GetIdentity().GetId();
                        if (!m_SchanaNametags.Get(id) && id != activePlayerId)
                        {
                            m_SchanaNametags[id] = new SchanaTraderNametagMenu(player);
                        }
                    }
                }
            }
        }
    }
}

static ref SchanaTraderNametagsManager g_schanaTraderNametagsManager;
static ref SchanaTraderNametagsManager GetSchanaTraderNametagsManager()
{
    if (!g_Game.IsServer() && !g_schanaTraderNametagsManager)
    {
        g_schanaTraderNametagsManager = new SchanaTraderNametagsManager;
    }
    return g_schanaTraderNametagsManager;
}
