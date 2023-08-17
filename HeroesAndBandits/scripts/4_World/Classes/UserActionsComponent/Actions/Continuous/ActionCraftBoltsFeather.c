modded class ActionCraftBoltsFeather: ActionContinuousBase
{
	override void OnFinishProgressServer( ActionData action_data ) 
	{
		super.OnFinishProgressServer(action_data);
		PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
		string sourcePlayerID = sourcePlayer.GetIdentity().GetPlainId();
		GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "archery_boltCraft");
	}

	//added in case i add more to do with bolts
	override protected bool IsFeatherType(string itemInHandsType)
	{
		return itemInHandsType == "ChickenFeather";
	}
}
