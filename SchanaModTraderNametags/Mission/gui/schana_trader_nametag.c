class SchanaTraderNametagMenu extends UIScriptedMenu
{
    private Widget m_SchanaTraderNametagRootWidget;
    private TextWidget m_SchanaTraderNametagTextWidget;
    private PlayerBase m_SchanaTraderNametagPlayer;

    void SchanaTraderNametagMenu(PlayerBase player)
    {
        m_SchanaTraderNametagRootWidget = GetGame().GetWorkspace().CreateWidgets("SchanaModTraderNametags/GUI/Layouts/nametag.layout");
        m_SchanaTraderNametagTextWidget = TextWidget.Cast(m_SchanaTraderNametagRootWidget);
        m_SchanaTraderNametagRootWidget.Show(false);
        m_SchanaTraderNametagPlayer = player;

        GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.SchanaUpdate, 1, true);
    }

    void ~SchanaTraderNametagMenu()
    {
        GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.SchanaUpdate);
        if (m_SchanaTraderNametagRootWidget != null)
        {
            m_SchanaTraderNametagRootWidget.Show(false);
            m_SchanaTraderNametagRootWidget.Unlink();
        }
    }

    void SchanaUpdate()
    {
        if (SchanaTraderNametagShouldShow())
        {
            SchanaTraderNametagUpdate();
        }
        else if (m_SchanaTraderNametagRootWidget != null)
        {
            m_SchanaTraderNametagRootWidget.Show(false);
            delete this;
        }
    }

    private bool SchanaTraderNametagShouldShow()
    {
        if (m_SchanaTraderNametagRootWidget == null)
        {
            return false;
        }
        if (!GetGame().GetPlayer())
        {
            return false;
        }
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if (!SchanaIsInSafezone(player, player))
        {
            return false;
        }
        if (!m_SchanaTraderNametagPlayer)
        {
            return false;
        }
        if (!m_SchanaTraderNametagPlayer.GetIdentity())
        {
            return false;
        }
        if (!SchanaIsInSafezone(player, m_SchanaTraderNametagPlayer))
        {
            return false;
        }
        return true;
    }

    private bool SchanaIsInSafezone(PlayerBase player, PlayerBase taggedPlayer)
    {
        vector position = taggedPlayer.GetPosition();

        for (int i=0; i<player.m_Trader_TraderPositions.Count(); ++i)
        {
            float distance = vector.Distance(position, player.m_Trader_TraderPositions.Get(i));

            if (distance <= player.m_Trader_TraderSafezones.Get(i))
            {
                return true;
            }
        }
        return false;
    }

    void SchanaTraderNametagUpdate()
    {
        float x, y, distance;
        vector position = m_SchanaTraderNametagPlayer.GetPosition();

        vector screenPosition = GetGame().GetScreenPos(position + "0 1.3 0");
        x = Math.Round(screenPosition[0]) - 40;
        y = Math.Round(screenPosition[1]);
        distance = Math.Round(screenPosition[2]);
        m_SchanaTraderNametagRootWidget.SetPos(x, y);
        string text = m_SchanaTraderNametagPlayer.GetIdentity().GetName() + " " + distance.ToString() + "m";
        m_SchanaTraderNametagTextWidget.SetText(text);
        m_SchanaTraderNametagRootWidget.Show(SchanaTraderNametagVisibleOnScreen());
    }

    private bool SchanaTraderNametagVisibleOnScreen()
    {
        vector position = m_SchanaTraderNametagPlayer.GetPosition();
        vector screenPositionRelative = GetGame().GetScreenPosRelative(position);

        if (screenPositionRelative[0] >= 1 || screenPositionRelative[0] == 0 || screenPositionRelative[1] >= 1 || screenPositionRelative[1] == 0)
        {
            return false;
        }
        else if (screenPositionRelative[2] < 0)
        {
            return false;
        }
        return true;
    }

    PlayerBase SchanaTraderNametagGetPlayer()
    {
        return m_SchanaTraderNametagPlayer;
    }
}
