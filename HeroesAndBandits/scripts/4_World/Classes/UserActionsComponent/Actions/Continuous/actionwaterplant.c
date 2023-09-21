modded class ActionWaterPlantCB : ActionContinuousBaseCB
{
	//add farmer check here later for less water usage per watering
	private const float QUANTITY_USED_PER_SEC = 150;
	
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousWaterPlant(QUANTITY_USED_PER_SEC);
	}
};

modded class ActionWaterPlant: ActionContinuousBase
{
	
	override void OnFinishProgressServer( ActionData action_data )
	{
		PlayerBase sourcePlayer = PlayerBase.Cast(action_data.m_Player);
		string sourcePlayerID = sourcePlayer.GetIdentity().GetPlainId();
		GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "water_plant_farm");
	}
};