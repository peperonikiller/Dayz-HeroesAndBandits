modded class ActionCraftBolts: ActionContinuousBase
{
	override void OnFinishProgressServer( ActionData action_data ) 
	{
		super.OnFinishProgressServer(action_data);
		PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
		string sourcePlayerID = sourcePlayer.GetIdentity().GetPlainId();
		GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "archery_boltCraft");
	}
};
