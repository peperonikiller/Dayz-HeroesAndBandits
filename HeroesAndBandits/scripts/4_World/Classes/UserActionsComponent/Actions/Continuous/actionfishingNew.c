modded class ActionFishingNew: ActionContinuousBase
{
	override void OnFinishProgressServer( ActionData action_data )
	{
		action_data.m_Callback.InternalCommand(DayZPlayerConstants.CMD_ACTIONINT_ACTION);
		FishingActionData.Cast(action_data).m_FishingResult = EvaluateFishingResult(action_data);
				
		
		
		
		if(FishingActionData.Cast(action_data).m_FishingResult > 0)  // > 0 only get points if you fishing something
		{
			PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
			string sourcePlayerID = sourcePlayer.GetIdentity().GetPlainId();
			GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "catch_fish");
		}
	}
	
};