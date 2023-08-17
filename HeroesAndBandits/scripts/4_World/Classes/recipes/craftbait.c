modded class CraftBait extends RecipeBase	
{	
	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		Debug.Log("Recipe Do method called","recipes");
		string sourcePlayerID = player.GetIdentity().GetPlainId();
		GetHeroesAndBandits().NewPlayerAction(sourcePlayerID, "craft_fish_bait");
	}
};