/*
modded class CleanWeapon extends RecipeBase
{	
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		string sourcePlayerID = player.GetIdentity().GetPlainId();
		GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "gun_clean");
	}
};
*/