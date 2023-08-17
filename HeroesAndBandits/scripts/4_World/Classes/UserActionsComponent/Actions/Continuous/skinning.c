modded class ActionSkinning : ActionContinuousBase
{
    override void OnFinishProgressServer( ActionData action_data )
    {    
        super.OnFinishProgressServer(action_data);

        PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
        string sourcePlayerID = sourcePlayer.GetIdentity().GetPlainId();

        AnimalBase animal;
        if (Class.CastTo(animal, action_data.m_MainItem))
        {
            GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "SkinAnimal");
        }
        /*
        else
        {
            GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "SkinHuman");
        }
        */
    }
}