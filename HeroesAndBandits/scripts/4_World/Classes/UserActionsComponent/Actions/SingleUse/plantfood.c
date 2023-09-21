modded class ActionHarvestCrops extends ActionInteractBase
{
    override void OnExecuteServer( ActionData action_data )
    {
        if ( m_Plant )
        {
            if (m_Plant.GetType().Contains("Tomato") || m_Plant.GetType().Contains("Pepper") || m_Plant.GetType().Contains("Potato") || m_Plant.GetType().Contains("Pumpkin") || m_Plant.GetType().Contains("Zucchini"))
            {
                PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
                string sourcePlayerID = sourcePlayer.GetIdentity().GetPlainId();
                GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "plant_food_farm");
            }
        }
        
        super.OnExecuteServer(action_data);
    }
}