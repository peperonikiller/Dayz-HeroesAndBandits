//  Init for Dogtags, HeroesAndBandits
void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
	m_HeroesAndBandits.updatePlayerTotals();
}
class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

 	override Dogtag_Base EquipDogtag(PlayerBase player)
	{
    	if (!player.HasDogtag()) // check if the player has a tag already
    	{
	        // create a new tag is the player doesn't have one
        	int slotId = InventorySlots.GetSlotIdFromString("Dogtag");
			string tagtype = "Dogtag_Survivor";
			if(m_HeroesAndBandits.GetPlayerHeroOrBandit(player.GetIdentity().GetPlainId()) == "bandit")
        		{
            		tagtype = "Dogtag_Bandit";
        		} else if (m_HeroesAndBandits.GetPlayerHeroOrBandit(player.GetIdentity().GetPlainId()) == "hero") {
            		tagtype = "Dogtag_Hero";
        		}
        	return Dogtag_Base.Cast(player.GetInventory().CreateAttachmentEx(tagtype, slotId));
    	}
    return null;
	}

    override void UpdatePlayersStats()
    {
        super.UpdatePlayersStats();

        array<Man> players = {};
        GetGame().GetPlayers(players);

        for (int i = 0; i < players.Count(); i++)
        {
            PlayerBase player;
            if (!PlayerBase.CastTo(player, players.Get(i)))
                continue;

            // update player's dogtags base on time
            float playtime = player.StatGet("playtime");

            if (playtime > 6000 && playtime < 15000)
            {
                player.ReplaceDogtag("Dogtag_Granite");
            }
            else if (playtime > 15000)
            {
                player.ReplaceDogtag("Dogtag_Cobalt");
            }
        }
    }

//MODDED LOADOUTS - BEGIN-----------------------------------
	EntityAI randomMaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin","PowderedMilk","Rice","BakedBeansCan_Opened","PeachesCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Apple","Tomato","GreenBellPepper","Zucchini","SlicedPumpkin","Potato","SambucusBerry","CaninaBerry","Plum","Pear","AgaricusMushroom","AmanitaMushroom","MacrolepiotaMushroom","LactariusMushroom","PsilocybeMushroom","AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","SodaCan_Kvass","WaterBottle"};
		ref TStringArray hatArray = {"BaseballCap_Blue","","","","BaseballCap_Beige","","","","BaseballCap_Black","","","","BaseballCap_Olive","","","","BaseballCap_Pink","","","","BaseballCap_Red","","","","BaseballCap_Camo","","","","BaseballCap_CMMG_Black","","","","BaseballCap_CMMG_Pink","","","","BeanieHat_Beige","","","","BeanieHat_Black","","","","BeanieHat_Blue","","","","BeanieHat_Brown","","","","BeanieHat_Green","","","","BeanieHat_Grey","","","","BeanieHat_Pink","","","","BeanieHat_Red","","","","Ushanka_Black","","","","Ushanka_Blue","","","","Ushanka_Green","","","","RadarCap_Black","","","","RadarCap_Blue","","","","RadarCap_Brown","","","","RadarCap_Green","","","","RadarCap_Red","","","","FlatCap_Black","","","","FlatCap_Blue","","","","FlatCap_Red","","","","FlatCap_Brown","","","","FlatCap_Grey","","","","FlatCap_BrownCheck","","","","FlatCap_GreyCheck","","","","FlatCap_BlackCheck","","","","ZmijovkaCap_Black","","","","ZmijovkaCap_Blue","","","","ZmijovkaCap_Brown","","","","ZmijovkaCap_Green","","","","ZmijovkaCap_Red","","","","CowboyHat_Brown","","","","CowboyHat_black","","","","CowboyHat_darkBrown","","","","CowboyHat_green","","","","SkateHelmet_Black","","","","SkateHelmet_Blue","","","","SkateHelmet_Gray","","","","SkateHelmet_Green","","","","SkateHelmet_Red","","","","WeldingMask","","","","LeatherHat_Natural","","","","LeatherHat_Beige","","","","LeatherHat_Brown","","","","LeatherHat_Black","","","","GreatHelm","","",""};
		ref TStringArray topArray = {"Sweater_Gray","Sweater_Blue","Sweater_Green","Sweater_Red","Shirt_BlueCheck","Shirt_BlueCheckBright","Shirt_GreenCheck","Shirt_RedCheck","Shirt_WhiteCheck","Shirt_PlaneBlack","TacticalShirt_Grey","TacticalShirt_Black","M65Jacket_Black","TShirt_Beige","TShirt_Black","TShirt_Blue","TShirt_Green","TShirt_OrangeWhiteStripes","TShirt_Red","TShirt_RedBlackStripes","TShirt_White","TShirt_Grey","Hoodie_Blue","Hoodie_Black","Hoodie_Brown","Hoodie_Green","Hoodie_Grey","Hoodie_Red","HikingJacket_Black","HikingJacket_Blue","HikingJacket_Red","HikingJacket_Green","Raincoat_Orange","Raincoat_Green","Raincoat_Yellow","Raincoat_Pink","Raincoat_Red","Raincoat_Blue","Raincoat_Black","TrackSuitJacket_Black","TrackSuitJacket_Blue","TrackSuitJacket_Green","TrackSuitJacket_LightBlue","TrackSuitJacket_Red","QuiltedJacket_Black","QuiltedJacket_Green","QuiltedJacket_Blue","QuiltedJacket_Red","QuiltedJacket_Grey","QuiltedJacket_Orange","QuiltedJacket_Yellow","QuiltedJacket_Violet","BomberJacket_Black","BomberJacket_Brown","BomberJacket_Blue","BomberJacket_Grey","BomberJacket_Maroon","BomberJacket_Olive","BomberJacket_SkyBlue","LeatherJacket_Natural","LeatherJacket_Beige","LeatherJacket_Brown","LeatherJacket_Black","Blouse_Blue","Blouse_Green","Blouse_Violet","Blouse_White"};
		ref TStringArray pantsArray = {"Jeans_Black","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","Jeans_BlueDark","CargoPants_Beige","CargoPants_Black","CargoPants_Blue","CargoPants_Green","CargoPants_Grey","CanvasPants_Beige","CanvasPants_Blue","CanvasPants_Grey","CanvasPants_Red","CanvasPants_Violet","CanvasPantsMidi_Beige","CanvasPantsMidi_Blue","CanvasPantsMidi_Grey","CanvasPantsMidi_Red","CanvasPantsMidi_Violet","TrackSuitPants_Black","TrackSuitPants_Blue","TrackSuitPants_Green","TrackSuitPants_Red","TrackSuitPants_LightBlue","LeatherPants_Natural","LeatherPants_Beige","LeatherPants_Brown","LeatherPants_Black","SlacksPants_Beige","SlacksPants_Black","SlacksPants_Blue","SlacksPants_Brown","SlacksPants_DarkGrey","SlacksPants_Khaki","SlacksPants_LightGrey","SlacksPants_White","Breeches_Pink","Breeches_Red","Breeches_White","Breeches_Green","Breeches_Browncheck","Breeches_Blue","Breeches_Blackcheck","Breeches_Black","Breeches_Beige","Breeches_Beetcheck","ShortJeans_Black","ShortJeans_Blue","ShortJeans_Brown","ShortJeans_Darkblue","ShortJeans_Green","ShortJeans_Red"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","","SportGlasses_Black","","","","SportGlasses_Green","","","","SportGlasses_Orange","","","","AviatorGlasses","","","","ThickFramesGlasses","","","","ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"AthleticShoes_Blue","AthleticShoes_Black","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey","DressShoes_Beige","DressShoes_Black","DressShoes_Brown","DressShoes_Sunburst","DressShoes_White","HikingBoots_Brown","HikingBoots_Black","HikingBootsLow_Black","HikingBootsLow_Blue","HikingBootsLow_Beige","HikingBootsLow_Grey","Wellies_Black","Wellies_Brown","Wellies_Green","Wellies_Grey","WorkingBoots_Grey","WorkingBoots_Brown","WorkingBoots_Green","WorkingBoots_Yellow","WorkingBoots_Beige","JoggingShoes_Black","JoggingShoes_Blue","JoggingShoes_Red","JoggingShoes_Violet","JoggingShoes_White","Sneakers_Black","Sneakers_Gray","Sneakers_Green","Sneakers_Red","Sneakers_White"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","","","BandanaMask_BlackPattern","","","","","","BandanaMask_PolkaPattern","","","","","","BandanaMask_GreenPattern","","","","","","BandanaMask_CamoPattern","","","","","","NioshFaceMask","","","","","","HockeyMask","","","","","","BalaclavaMask_Black","","","","","","BalaclavaMask_Blackskull","","","","","","BalaclavaMask_Beige","","","","","","BalaclavaMask_Blue","","","","","","BalaclavaMask_Green","","","","","","BalaclavaMask_Pink","","","","","","BalaclavaMask_White","","","","","","GP5GasMask","","","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("RoadFlare");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	EntityAI randomFemaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin", "PowderedMilk", "Rice", "BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "SlicedPumpkin", "Potato", "SambucusBerry", "CaninaBerry", "Plum", "Pear", "AgaricusMushroom", "AmanitaMushroom", "MacrolepiotaMushroom", "LactariusMushroom", "PsilocybeMushroom", "AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"BaseballCap_Blue","","","", "BaseballCap_Beige","","","", "BaseballCap_Black","","","", "BaseballCap_Olive","","","", "BaseballCap_Pink","","","", "BaseballCap_Red","","","", "BaseballCap_Camo","","","", "BaseballCap_CMMG_Black","","","", "BaseballCap_CMMG_Pink","","","", "BeanieHat_Beige","","","", "BeanieHat_Black","","","", "BeanieHat_Blue","","","", "BeanieHat_Brown","","","", "BeanieHat_Green","","","", "BeanieHat_Grey","","","", "BeanieHat_Pink","","","", "BeanieHat_Red","","","", "Ushanka_Black","","","", "Ushanka_Blue","","","", "Ushanka_Green","","","", "RadarCap_Black","","","", "RadarCap_Blue","","","", "RadarCap_Brown","","","", "RadarCap_Green","","","", "RadarCap_Red","","","", "FlatCap_Black","","","", "FlatCap_Blue","","","", "FlatCap_Red","","","", "FlatCap_Brown","","","", "FlatCap_Grey","","","", "FlatCap_BrownCheck","","","", "FlatCap_GreyCheck","","","", "FlatCap_BlackCheck","","","", "ZmijovkaCap_Black","","","", "ZmijovkaCap_Blue","","","", "ZmijovkaCap_Brown","","","", "ZmijovkaCap_Green","","","", "ZmijovkaCap_Red","","","", "CowboyHat_Brown","","","", "CowboyHat_black","","","", "CowboyHat_darkBrown","","","", "CowboyHat_green","","","", "SkateHelmet_Black","","","", "SkateHelmet_Blue","","","", "SkateHelmet_Gray","","","", "SkateHelmet_Green","","","", "SkateHelmet_Red","","","", "WeldingMask","","","", "LeatherHat_Natural","","","", "LeatherHat_Beige","","","", "LeatherHat_Brown","","","", "LeatherHat_Black","","","", "GreatHelm","","",""}; 		
		ref TStringArray topArray = {"Sweater_Gray", "Sweater_Blue", "Sweater_Green", "Sweater_Red", "Shirt_BlueCheck", "Shirt_BlueCheckBright", "Shirt_GreenCheck", "Shirt_RedCheck", "Shirt_WhiteCheck", "Shirt_PlaneBlack", "TacticalShirt_Grey", "TacticalShirt_Black", "M65Jacket_Black", "TShirt_Beige", "TShirt_Black", "TShirt_Blue", "TShirt_Green", "TShirt_OrangeWhiteStripes", "TShirt_Red", "TShirt_RedBlackStripes", "TShirt_White", "TShirt_Grey", "Hoodie_Blue", "Hoodie_Black", "Hoodie_Brown", "Hoodie_Green", "Hoodie_Grey", "Hoodie_Red", "HikingJacket_Black", "HikingJacket_Blue", "HikingJacket_Red", "HikingJacket_Green", "Raincoat_Orange", "Raincoat_Green", "Raincoat_Yellow", "Raincoat_Pink", "Raincoat_Red", "Raincoat_Blue", "Raincoat_Black", "TrackSuitJacket_Black", "TrackSuitJacket_Blue", "TrackSuitJacket_Green", "TrackSuitJacket_LightBlue", "TrackSuitJacket_Red", "QuiltedJacket_Black", "QuiltedJacket_Green", "QuiltedJacket_Blue", "QuiltedJacket_Red", "QuiltedJacket_Grey", "QuiltedJacket_Orange", "QuiltedJacket_Yellow", "QuiltedJacket_Violet", "BomberJacket_Black", "BomberJacket_Brown", "BomberJacket_Blue", "BomberJacket_Grey", "BomberJacket_Maroon", "BomberJacket_Olive", "BomberJacket_SkyBlue", "LeatherJacket_Natural", "LeatherJacket_Beige", "LeatherJacket_Brown", "LeatherJacket_Black", "Blouse_Blue", "Blouse_Green", "Blouse_Violet", "Blouse_White"};
		ref TStringArray pantsArray = {"ShortJeans_Black", "ShortJeans_Blue", "ShortJeans_Brown", "ShortJeans_Darkblue", "ShortJeans_Green", "ShortJeans_Red", "Skirt_Blue", "Skirt_Red", "Skirt_White", "Skirt_Yellow"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","", "SportGlasses_Black","","","", "SportGlasses_Green","","","", "SportGlasses_Orange","","","", "AviatorGlasses","","","", "ThickFramesGlasses","","","", "ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"AthleticShoes_Blue", "AthleticShoes_Black", "AthleticShoes_Brown", "AthleticShoes_Green", "AthleticShoes_Grey", "DressShoes_Beige", "DressShoes_Black", "DressShoes_Brown", "DressShoes_Sunburst", "DressShoes_White", "HikingBoots_Brown", "HikingBoots_Black", "HikingBootsLow_Black", "HikingBootsLow_Blue", "HikingBootsLow_Beige", "HikingBootsLow_Grey", "Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Green", "WorkingBoots_Yellow", "WorkingBoots_Beige", "JungleBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Beige", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey", "JoggingShoes_Black", "JoggingShoes_Blue", "JoggingShoes_Red", "JoggingShoes_Violet", "JoggingShoes_White", "Sneakers_Black", "Sneakers_Gray", "Sneakers_Green", "Sneakers_Red", "Sneakers_White"};
		ref TStringArray glovesArray = {"WorkingGloves_Black","","","", "WorkingGloves_Beige","","","", "WorkingGloves_Brown","","","", "WorkingGloves_Yellow","","","", "TacticalGloves_Beige","","","", "TacticalGloves_Black","","","", "TacticalGloves_Green","","","", "OMNOGloves_Brown","","","", "OMNOGloves_Gray","","","", "SurgicalGloves_White","","","", "SurgicalGloves_LightBlue","","","", "SurgicalGloves_Blue","","","", "SurgicalGloves_Green","","",""};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","","", "BandanaMask_BlackPattern","","","","","", "BandanaMask_PolkaPattern","","","","","", "BandanaMask_GreenPattern","","","","","", "BandanaMask_CamoPattern","","","","","", "NioshFaceMask","","","","","", "HockeyMask","","","","","", "BalaclavaMask_Black","","","","","", "BalaclavaMask_Blackskull","","","","","", "BalaclavaMask_Beige","","","","","", "BalaclavaMask_Blue","","","","","", "BalaclavaMask_Green","","","","","", "BalaclavaMask_Pink","","","","","", "BalaclavaMask_White","","","","","", "GP5GasMask","","","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("RoadFlare");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	EntityAI randomFemale2Class(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin", "PowderedMilk", "Rice", "BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "SlicedPumpkin", "Potato", "SambucusBerry", "CaninaBerry", "Plum", "Pear", "AgaricusMushroom", "AmanitaMushroom", "MacrolepiotaMushroom", "LactariusMushroom", "PsilocybeMushroom", "AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"BaseballCap_Blue","","","","", "BaseballCap_Beige","","","","", "BaseballCap_Black","","","","", "BaseballCap_Olive","","","","", "BaseballCap_Pink","","","","", "BaseballCap_Red","","","","", "BaseballCap_Camo","","","","", "BaseballCap_CMMG_Black","","","","", "BaseballCap_CMMG_Pink","","","","", "BeanieHat_Beige","","","","", "BeanieHat_Black","","","","", "BeanieHat_Blue","","","","", "BeanieHat_Brown","","","","", "BeanieHat_Green","","","","", "BeanieHat_Grey","","","","", "BeanieHat_Pink","","","","", "BeanieHat_Red","","","","", "Ushanka_Black","","","","", "Ushanka_Blue","","","","", "Ushanka_Green","","","","", "RadarCap_Black","","","","", "RadarCap_Blue","","","","", "RadarCap_Brown","","","","", "RadarCap_Green","","","","", "RadarCap_Red","","","","", "FlatCap_Black","","","","", "FlatCap_Blue","","","","", "FlatCap_Red","","","","", "FlatCap_Brown","","","","", "FlatCap_Grey","","","","", "FlatCap_BrownCheck","","","","", "FlatCap_GreyCheck","","","","", "FlatCap_BlackCheck","","","","", "ZmijovkaCap_Black","","","","", "ZmijovkaCap_Blue","","","","", "ZmijovkaCap_Brown","","","","", "ZmijovkaCap_Green","","","","", "ZmijovkaCap_Red","","","","", "CowboyHat_Brown","","","","", "CowboyHat_black","","","","", "CowboyHat_darkBrown","","","","", "CowboyHat_green","","","","", "SkateHelmet_Black","","","","", "SkateHelmet_Blue","","","","", "SkateHelmet_Gray","","","","", "SkateHelmet_Green","","","","", "SkateHelmet_Red","","","","", "WeldingMask","","","","", "LeatherHat_Natural","","","","", "LeatherHat_Beige","","","","", "LeatherHat_Brown","","","","", "LeatherHat_Black","","","","", "GreatHelm","","","",""};
		ref TStringArray topArray = {"MiniDress_Pink", "MiniDress_PinkChecker", "MiniDress_RedChecker", "MiniDress_WhiteChecker", "MiniDress_GreenChecker", "MiniDress_BrownChecker", "MiniDress_BlueChecker", "MiniDress_BlueWithDots"};
		ref TStringArray pantsArray = {"", ""};
		ref TStringArray vestArray  = {"ChestHolster","", "","", "","", "","", "",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","", "SportGlasses_Black","","","", "SportGlasses_Green","","","", "SportGlasses_Orange","","","", "AviatorGlasses","","","", "ThickFramesGlasses","","","", "ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"AthleticShoes_Blue", "AthleticShoes_Black", "AthleticShoes_Brown", "AthleticShoes_Green", "AthleticShoes_Grey", "DressShoes_Beige", "DressShoes_Black", "DressShoes_Brown", "DressShoes_Sunburst", "DressShoes_White", "HikingBoots_Brown", "HikingBoots_Black", "HikingBootsLow_Black", "HikingBootsLow_Blue", "HikingBootsLow_Beige", "HikingBootsLow_Grey", "Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Green", "WorkingBoots_Yellow", "WorkingBoots_Beige", "JungleBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Beige", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey", "JoggingShoes_Black", "JoggingShoes_Blue", "JoggingShoes_Red", "JoggingShoes_Violet", "JoggingShoes_White", "Sneakers_Black", "Sneakers_Gray", "Sneakers_Green", "Sneakers_Red", "Sneakers_White"};
		ref TStringArray glovesArray = {"WorkingGloves_Black","","","", "WorkingGloves_Beige","","","", "WorkingGloves_Brown","","","", "WorkingGloves_Yellow","","","", "TacticalGloves_Beige","","","", "TacticalGloves_Black","","","", "TacticalGloves_Green","","","", "OMNOGloves_Brown","","","", "OMNOGloves_Gray","","","", "SurgicalGloves_White","","","", "SurgicalGloves_LightBlue","","","", "SurgicalGloves_Blue","","","", "SurgicalGloves_Green","","",""};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","", "BandanaMask_BlackPattern","","","","", "BandanaMask_PolkaPattern","","","","", "BandanaMask_GreenPattern","","","","", "BandanaMask_CamoPattern","","","","", "NioshFaceMask","","","","", "HockeyMask","","","","","", "BalaclavaMask_Black","","","","", "BalaclavaMask_Blackskull","","","","", "BalaclavaMask_Beige","","","","", "BalaclavaMask_Blue","","","","", "BalaclavaMask_Green","","","","", "BalaclavaMask_Pink","","","","", "BalaclavaMask_White","","","","", "GP5GasMask","","","",""};
		ref TStringArray backpackArray = {"BagTaloon_Blue", "BagTaloon_Green", "BagTaloon_Orange", "BagTaloon_Violet", "BagCourierImprovised", "BagCourierImprovisedFur", "BagImprovised", "BagImprovisedFur", "BagHunting", "BagMountain_Blue", "BagMountain_Green", "BagMountain_Orange", "BagMountain_Red", "ChildBag_Blue", "ChildBag_Green", "ChildBag_Red", "ChildBag_Blue", "ChildBag_Green", "ChildBag_Red", "ChildBag_Blue", "ChildBag_Green", "ChildBag_Red", "ChildBag_Blue", "ChildBag_Green", "ChildBag_Red", "LeatherSack_Natural", "LeatherSack_Black", "LeatherSack_Beige", "LeatherSack_Brown", "AssaultBag_Ttsko", "AssaultBag_Black", "AssaultBag_Green", "CoyoteBag_Brown", "CoyoteBag_Green"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("RoadFlare");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	EntityAI scientistClass(PlayerBase player)
	{
		player.GetInventory().CreateInInventory("Skirt_White");
		player.GetInventory().CreateInInventory("LabCoat");
		player.GetInventory().CreateInInventory("ThinFramesGlasses");
		player.GetInventory().CreateInInventory("DressShoes_White");
		player.GetInventory().CreateInInventory("WaterBottle");
		player.GetInventory().CreateInInventory("Apple");
		player.GetInventory().CreateInInventory("BloodTestKit");
		player.GetInventory().CreateInInventory("Screwdriver");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	EntityAI doctorClass(PlayerBase player)
	{
		player.GetInventory().CreateInInventory("SlacksPants_Black");
		player.GetInventory().CreateInInventory("LabCoat");
		player.GetInventory().CreateInInventory("ThinFramesGlasses");
		player.GetInventory().CreateInInventory("DressShoes_Brown");
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("WaterBottle");
		player.GetInventory().CreateInInventory("Apple");
		player.GetInventory().CreateInInventory("Thermometer");
		player.GetInventory().CreateInInventory("PainkillerTablets");
		player.GetInventory().CreateInInventory("Morphine");
		ItemBase light = player.GetInventory().CreateInInventory("Headtorch_Grey");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI nurseClass(PlayerBase player)
	{
		ref TStringArray hatArray = {"MedicalScrubsHat_Blue","","","","","","MedicalScrubsHat_Green","","","","","","MedicalScrubsHat_White","","","","",""};
		ref TStringArray dressArray = {"NurseDress_White","NurseDress_Blue"};
		ref TStringArray backpackArray  = {"ChildBag_Blue","SmershBag"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","ThickFramesGlasses","ThinFramesGlasses","","","","","",""};
		ref TStringArray shoesArray = {"JoggingShoes_White","Ballerinas_White","DressShoes_White","Ballerinas_White","Ballerinas_Blue","Ballerinas_Red","Ballerinas_White"};
		ref TStringArray glovesArray = {"SurgicalGloves_White","SurgicalGloves_LightBlue","SurgicalGloves_Blue","SurgicalGloves_Green"};
		ref TStringArray maskArray = {"SurgicalMask","","SurgicalMask"};
		ref TStringArray medsArray = {"PainkillerTablets","Morphine","BloodTestKit","DisinfectantAlcohol"};
		ref TStringArray meds2Array = {"TetracyclineAntibiotics","Epinephrine","Thermometer","VitaminBottle"};
		ref TStringArray meds3Array = {"BloodBagIV","BloodBagFull","BloodBagEmpty","SalineBag","SalineBagIV","StartKitIV"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(dressArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(medsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(meds2Array.GetRandomElement());
		player.GetInventory().CreateInInventory(meds3Array.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("WaterBottle");
		player.GetInventory().CreateInInventory("Apple");
		ItemBase light = player.GetInventory().CreateInInventory("Headtorch_Grey");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI nurseMaleClass(PlayerBase player)
	{
		ref TStringArray hatArray = {"MedicalScrubsHat_Blue","MedicalScrubsHat_Green","MedicalScrubsHat_White"};
		ref TStringArray topArray = {"MedicalScrubsShirt_Blue","MedicalScrubsShirt_Green","MedicalScrubsShirt_White"};
		ref TStringArray pantsArray = {"MedicalScrubsPants_Blue","MedicalScrubsPants_Green","MedicalScrubsPants_White"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","ThickFramesGlasses","ThinFramesGlasses","","","","","",""};
		ref TStringArray shoesArray = {"JoggingShoes_White","DressShoes_White"};
		ref TStringArray glovesArray = {"SurgicalGloves_White","SurgicalGloves_LightBlue","SurgicalGloves_Blue","SurgicalGloves_Green"};
		ref TStringArray medsArray = {"PainkillerTablets","Morphine","BloodTestKit","DisinfectantAlcohol"};
		ref TStringArray meds2Array = {"TetracyclineAntibiotics","Epinephrine","Thermometer","VitaminBottle"};
		ref TStringArray meds3Array = {"BloodBagIV","BloodBagFull","BloodBagEmpty","SalineBag","SalineBagIV","StartKitIV"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(medsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(meds2Array.GetRandomElement());
		player.GetInventory().CreateInInventory(meds3Array.GetRandomElement());
		player.GetInventory().CreateInInventory("SurgicalMask");
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("WaterBottle");
		player.GetInventory().CreateInInventory("Apple");
		player.GetInventory().CreateInInventory("RoadFlare");
		return rags;
	}

	EntityAI policemanClass(PlayerBase player)
	{
		ref TStringArray hatArray = {"DirtBikeHelmet_Police","PoliceCap","PoliceCap","PoliceCap"};
		ref TStringArray topArray = {"PoliceJacket","PoliceJacketOrel"};
		ref TStringArray pantsArray = {"PolicePants","PolicePantsOrel"};
		ref TStringArray vestArray  = {"PoliceVest","PoliceVest"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","AviatorGlasses","SportGlasses_Black","SportGlasses_Green","SportGlasses_Orange","AviatorGlasses","AviatorGlasses","AviatorGlasses",""};
		ref TStringArray shoesArray = {"DressShoes_Black","WorkingBoots_Grey"};
		ref TStringArray glovesArray = {"OMNOGloves_Brown","OMNOGloves_Gray","OMNOGloves_Brown","OMNOGloves_Gray","SurgicalGloves_Blue"};
		ref TStringArray extraArray = {"Megaphone","DisinfectantAlcohol","Lockpick"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(extraArray.GetRandomElement());
		player.GetInventory().CreateInInventory("Handcuffs");
		player.GetInventory().CreateInInventory("HandcuffKeys");
		player.GetInventory().CreateInInventory("PersonalRadio");
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("SodaCan_Pipsi");
		player.GetInventory().CreateInInventory("Potato");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI policewomanClass(PlayerBase player)
	{
		ref TStringArray hatArray = {"DirtBikeHelmet_Police","PoliceCap","PoliceCap","PoliceCap"};
		ref TStringArray topArray = {"PoliceJacket","PoliceJacketOrel"};
		ref TStringArray pantsArray = {"PolicePants","PolicePantsOrel","Skirt_Blue","Skirt_Blue","Skirt_Blue","Skirt_Blue"};
		ref TStringArray vestArray  = {"PoliceVest","PoliceVest"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","AviatorGlasses","SportGlasses_Black","SportGlasses_Green","SportGlasses_Orange","AviatorGlasses","AviatorGlasses","AviatorGlasses","LeatherBelt_Beige",""};
		ref TStringArray shoesArray = {"MilitaryBoots_Black","TTSKOBoots","CombatBoots_Black","HikingBootsLow_Black","HikingBoots_Black","JungleBoots_Black","WorkingBoots_Grey"};
		ref TStringArray glovesArray = {"OMNOGloves_Brown","OMNOGloves_Gray","SurgicalGloves_Blue"};
		ref TStringArray extraArray = {"Megaphone","DisinfectantAlcohol","Lockpick"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(extraArray.GetRandomElement());
		player.GetInventory().CreateInInventory("Handcuffs");
		player.GetInventory().CreateInInventory("HandcuffKeys");
		player.GetInventory().CreateInInventory("PersonalRadio");
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("SodaCan_Spite");
		player.GetInventory().CreateInInventory("Plum");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI soldierClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"TacticalBaconCan_Opened", "TacticalBaconCan_Opened"};
		ref TStringArray drinkArray = {"Canteen", "Canteen"};
		ref TStringArray hatArray = {"BallisticHelmet_Green", "BallisticHelmet_Black", "BallisticHelmet_UN", "ZSh3PilotHelmet", "ZSh3PilotHelmet_Green", "ZSh3PilotHelmet_Black", "MilitaryBeret_Red", "MilitaryBeret_UN", "MilitaryBeret_NZ", "MilitaryBeret_ChDKZ", "MilitaryBeret_CDF", "OfficerHat", "PilotkaCap", "TankerHelmet", "GorkaHelmet", "GorkaHelmet_Green", "GorkaHelmet_Black", "GorkaHelmetComplete", "GorkaHelmetComplete_Green", "GorkaHelmetComplete_Black", "Ssh68Helmet"};
		ref TStringArray topArray = {"TacticalShirt_Olive", "TacticalShirt_Tan", "M65Jacket_Khaki", "M65Jacket_Tan", "M65Jacket_Olive", "TTsKOJacket_Camo", "GorkaEJacket_Summer", "GorkaEJacket_Flat", "GorkaEJacket_Autumn", "GorkaEJacket_PautRev", "USMCJacket_Desert", "USMCJacket_Woodland"};
		ref TStringArray pantsArray = {"TTSKOPants", "GorkaPants_Summer", "GorkaPants_Autumn", "GorkaPants_Flat", "GorkaPants_PautRev", "USMCPants_Desert", "USMCPants_Woodland", "BDUPants"};
		ref TStringArray vestArray  = {"SmershVest","", "BallisticVest","", "UKAssVest_Black","", "UKAssVest_Camo","", "UKAssVest_Khaki","", "UKAssVest_Olive","", "HighCapacityVest_Black","", "HighCapacityVest_Olive",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","",""};
		ref TStringArray shoesArray = {"JungleBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Beige", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		ref TStringArray glovesArray = {"TacticalGloves_Beige","", "TacticalGloves_Black","", "TacticalGloves_Green","", "OMNOGloves_Brown","", "OMNOGloves_Gray",""};
		ref TStringArray maskArray = {"BandanaMask_CamoPattern","","","","", "BalaclavaMask_Green","","","","", "GP5GasMask","","","",""};
		ref TStringArray backpackArray = {"AssaultBag_Ttsko","", "AssaultBag_Black","", "AssaultBag_Green","", "CoyoteBag_Brown","", "CoyoteBag_Green",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI firefighterClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin", "PowderedMilk", "Rice", "BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "SlicedPumpkin", "Potato", "Plum", "Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"FirefightersHelmet_Red", "FirefightersHelmet_White", "FirefightersHelmet_Yellow"};
		ref TStringArray topArray = {"TShirt_White", "FirefighterJacket_Beige", "FirefighterJacket_Black", "FirefighterJacket_Beige", "FirefighterJacket_Black", "FirefighterJacket_Beige", "FirefighterJacket_Black"};
		ref TStringArray pantsArray = {"FirefightersPants_Beige", "FirefightersPants_Black"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","",""};
		ref TStringArray shoesArray = {"Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Green", "WorkingBoots_Yellow", "WorkingBoots_Beige"};
		ref TStringArray glovesArray = {"WorkingGloves_Black", "WorkingGloves_Beige", "WorkingGloves_Brown", "WorkingGloves_Yellow"};
		ref TStringArray maskArray = {"GP5GasMask","","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI prisonerClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin", "PowderedMilk", "Rice", "BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "SlicedPumpkin", "Potato", "SambucusBerry", "CaninaBerry", "Plum", "Pear", "AgaricusMushroom", "AmanitaMushroom", "MacrolepiotaMushroom", "LactariusMushroom", "PsilocybeMushroom", "AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"PrisonerCap","PrisonerCap"};
		ref TStringArray topArray = {"PrisonUniformJacket","PrisonUniformJacket"};
		ref TStringArray pantsArray = {"PrisonUniformPants","PrisonUniformPants"};
		ref TStringArray shoesArray = {"AthleticShoes_Blue", "AthleticShoes_Black", "AthleticShoes_Brown", "AthleticShoes_Green", "AthleticShoes_Grey", "JoggingShoes_Black", "JoggingShoes_Blue", "JoggingShoes_Red", "JoggingShoes_Violet", "JoggingShoes_White"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","", "BandanaMask_BlackPattern","","","","", "BandanaMask_PolkaPattern","","","","", "BandanaMask_GreenPattern","","","","", "BandanaMask_CamoPattern","","","","", "HockeyMask","","","HockeyMask","","","","", "BalaclavaMask_Black","","","","", "BalaclavaMask_Blackskull","","","","","","","","", "BalaclavaMask_Blue","","","","","","","","","","","",""};
		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("RoadFlare");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	EntityAI hunterMaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"PigSteakMeat", "DeerSteakMeat", "Rice", "BakedBeansCan_Opened", "SheepSteakMeat", "WolfSteakMeat", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "CowSteakMeat", "Potato", "SambucusBerry", "CaninaBerry", "Plum", "Pear", "BoarSteakMeat", "GoatSteakMeat", "AgaricusMushroom", "AmanitaMushroom", "MacrolepiotaMushroom", "LactariusMushroom", "PsilocybeMushroom", "AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "Canteen", "WaterBottle"};
		ref TStringArray hatArray = {"Ushanka_Black","", "Ushanka_Blue","", "Ushanka_Green","", "RadarCap_Black","", "RadarCap_Blue","", "RadarCap_Brown","", "RadarCap_Green","", "RadarCap_Red","", "ZmijovkaCap_Black","", "ZmijovkaCap_Blue","", "ZmijovkaCap_Brown","", "ZmijovkaCap_Green","", "ZmijovkaCap_Red","", "BoonieHat_Black","", "BoonieHat_Blue","", "BoonieHat_DPM","", "BoonieHat_Dubok","", "BoonieHat_Flecktran","", "BoonieHat_NavyBlue","", "BoonieHat_Olive","", "BoonieHat_Orange","", "BoonieHat_Red","", "BoonieHat_Tan","", "LeatherHat_Natural","", "LeatherHat_Beige","", "LeatherHat_Brown","", "LeatherHat_Black",""};
		ref TStringArray topArray = {"HuntingJacket_Autumn", "HuntingJacket_Brown", "HuntingJacket_Spring", "HuntingJacket_Summer", "HuntingJacket_Winter", "HuntingJacket_Autumn", "HuntingJacket_Brown", "HuntingJacket_Spring", "HuntingJacket_Summer", "HuntingJacket_Winter"};
		ref TStringArray pantsArray = {"HunterPants_Autumn", "HunterPants_Brown", "HunterPants_Spring", "HunterPants_Summer", "HunterPants_Winter"};
		ref TStringArray vestArray  = {"LeatherStorageVest_Natural","","", "LeatherStorageVest_Beige","","", "LeatherStorageVest_Brown","","", "LeatherStorageVest_Black","",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","", "SportGlasses_Black","","","", "SportGlasses_Green","","","", "SportGlasses_Orange","","","", "AviatorGlasses","","","", "ThickFramesGlasses","","","", "ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"HikingBoots_Brown", "HikingBoots_Black", "HikingBootsLow_Black", "HikingBootsLow_Beige", "HikingBootsLow_Grey", "Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Green", "WorkingBoots_Beige"};
		ref TStringArray glovesArray = {"WorkingGloves_Black","","", "WorkingGloves_Beige","","", "WorkingGloves_Brown","",""};
		ref TStringArray backpackArray = {"BagHunting","","","", "BagHunting","","","", "BagHunting","","","", "BagHunting","","","", "BagHunting","","","", "LeatherSack_Natural","","","", "LeatherSack_Black","","","", "LeatherSack_Beige","","","", "LeatherSack_Brown","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI hunterFemaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"PigSteakMeat", "DeerSteakMeat", "Rice", "BakedBeansCan_Opened", "SheepSteakMeat", "WolfSteakMeat", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "CowSteakMeat", "Potato", "SambucusBerry", "CaninaBerry", "Plum", "Pear", "BoarSteakMeat", "GoatSteakMeat", "AgaricusMushroom", "AmanitaMushroom", "MacrolepiotaMushroom", "LactariusMushroom", "PsilocybeMushroom", "AuriculariaMushroom"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "Canteen", "WaterBottle"};
		ref TStringArray hatArray = {"Ushanka_Black","","", "Ushanka_Blue","","", "Ushanka_Green","","", "RadarCap_Black","","", "RadarCap_Blue","","", "RadarCap_Brown","","", "RadarCap_Green","","", "RadarCap_Red","","", "ZmijovkaCap_Black","","", "ZmijovkaCap_Blue","","", "ZmijovkaCap_Brown","","", "ZmijovkaCap_Green","","", "ZmijovkaCap_Red","","", "BoonieHat_Black","","", "BoonieHat_Blue","","", "BoonieHat_DPM","","", "BoonieHat_Dubok","","", "BoonieHat_Flecktran","","", "BoonieHat_NavyBlue","","", "BoonieHat_Olive","","", "BoonieHat_Orange","","", "BoonieHat_Red","","", "BoonieHat_Tan","","", "LeatherHat_Natural","","", "LeatherHat_Beige","","", "LeatherHat_Brown","","", "LeatherHat_Black","",""};
		ref TStringArray topArray = {"Raincoat_Orange", "Raincoat_Green", "Raincoat_Yellow", "Raincoat_Pink", "Raincoat_Red", "Raincoat_Blue", "Raincoat_Black", "HuntingJacket_Autumn", "HuntingJacket_Brown", "HuntingJacket_Spring", "HuntingJacket_Summer", "HuntingJacket_Winter", "HuntingJacket_Autumn", "HuntingJacket_Brown", "HuntingJacket_Spring", "HuntingJacket_Summer", "HuntingJacket_Winter"};
		ref TStringArray pantsArray = {"ShortJeans_Black", "ShortJeans_Blue", "ShortJeans_Brown", "ShortJeans_Darkblue", "ShortJeans_Green", "ShortJeans_Red", "Skirt_Blue", "Skirt_Red", "Skirt_White", "Skirt_Yellow"};
		ref TStringArray vestArray  = {"LeatherStorageVest_Natural","","", "LeatherStorageVest_Beige","","", "LeatherStorageVest_Brown","","", "LeatherStorageVest_Black","",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","", "SportGlasses_Black","","","", "SportGlasses_Green","","","", "SportGlasses_Orange","","","", "AviatorGlasses","","","", "ThickFramesGlasses","","","", "ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"HikingBoots_Brown", "HikingBoots_Black", "HikingBootsLow_Black", "HikingBootsLow_Beige", "HikingBootsLow_Grey", "Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Green", "WorkingBoots_Beige"};
		ref TStringArray glovesArray = {"WorkingGloves_Black","","", "WorkingGloves_Beige","","", "WorkingGloves_Brown","",""};
		ref TStringArray backpackArray = {"BagHunting","","","", "BagHunting","","","", "BagHunting","","","", "BagHunting","","","", "BagHunting","","","", "LeatherSack_Natural","","","", "LeatherSack_Black","","","", "LeatherSack_Beige","","","", "LeatherSack_Brown","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI constructionMaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Plum", "Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"ConstructionHelmet_Blue", "ConstructionHelmet_Lime", "ConstructionHelmet_Orange", "ConstructionHelmet_Red", "ConstructionHelmet_White", "ConstructionHelmet_Yellow"};
		ref TStringArray topArray = {"Shirt_BlueCheck", "Shirt_BlueCheckBright", "Shirt_GreenCheck", "Shirt_RedCheck", "Shirt_WhiteCheck", "Shirt_PlaneBlack"};
		ref TStringArray pantsArray = {"Jeans_Black", "Jeans_Blue", "Jeans_Brown", "Jeans_Green", "Jeans_Grey", "Jeans_BlueDark", "CargoPants_Beige", "CargoPants_Black", "CargoPants_Blue", "CargoPants_Grey"};
		ref TStringArray vestArray  = {"ReflexVest",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","","", "ThickFramesGlasses","","", "ThinFramesGlasses","",""};
		ref TStringArray shoesArray = {"Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey", "WorkingBoots_Yellow", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Green", "WorkingBoots_Yellow", "WorkingBoots_Beige", "WorkingBoots_Yellow"};
		ref TStringArray maskArray = {"NioshFaceMask","","",""};
		ref TStringArray glovesArray = {"WorkingGloves_Black","", "WorkingGloves_Beige","", "WorkingGloves_Brown","", "WorkingGloves_Yellow",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI constructionFemaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Plum", "Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"ConstructionHelmet_Blue", "ConstructionHelmet_Lime", "ConstructionHelmet_Orange", "ConstructionHelmet_Red", "ConstructionHelmet_White", "ConstructionHelmet_Yellow"};
		ref TStringArray topArray = {"Shirt_BlueCheck", "Shirt_BlueCheckBright", "Shirt_GreenCheck", "Shirt_RedCheck", "Shirt_WhiteCheck", "Shirt_PlaneBlack", "TShirt_Blue", "TShirt_Red", "TShirt_White"};
		ref TStringArray pantsArray = {"ShortJeans_Black", "ShortJeans_Blue", "ShortJeans_Brown", "ShortJeans_Darkblue", "ShortJeans_Green", "ShortJeans_Red", "Skirt_Blue", "Skirt_Red", "Skirt_White", "Skirt_Yellow"};
		ref TStringArray vestArray  = {"ReflexVest",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","","", "ThickFramesGlasses","","", "ThinFramesGlasses","",""};
		ref TStringArray shoesArray = {"Wellies_Black", "Wellies_Brown", "Wellies_Green", "Wellies_Grey", "WorkingBoots_Yellow", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Green", "WorkingBoots_Yellow", "WorkingBoots_Beige", "WorkingBoots_Yellow"};
		ref TStringArray maskArray = {"NioshFaceMask","",""};
		ref TStringArray glovesArray = {"WorkingGloves_Black","", "WorkingGloves_Beige","", "WorkingGloves_Brown","", "WorkingGloves_Yellow",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI officeMaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Plum", "Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "WaterBottle"};
		ref TStringArray hatArray = {"FlatCap_Black","","","","", "FlatCap_Blue","","","","", "FlatCap_Red","","","","", "FlatCap_Brown","","","","", "FlatCap_Grey","","","","", "FlatCap_BrownCheck","","","","", "FlatCap_GreyCheck","","","","", "FlatCap_BlackCheck","","","",""};
		ref TStringArray topArray = {"WoolCoat_Black", "WoolCoat_Red", "WoolCoat_Blue", "WoolCoat_Green", "WoolCoat_Beige", "WoolCoat_RedCheck", "WoolCoat_BlackCheck", "WoolCoat_BlueCheck", "WoolCoat_GreyCheck", "WoolCoat_BrownCheck", "Blouse_Blue", "Blouse_Green", "Blouse_Violet", "Blouse_White"};
		ref TStringArray pantsArray = {"SlacksPants_Beige", "SlacksPants_Black", "SlacksPants_Blue", "SlacksPants_Brown", "SlacksPants_DarkGrey", "SlacksPants_Khaki", "SlacksPants_LightGrey", "SlacksPants_White"};
		ref TStringArray glassesArray = {"ThickFramesGlasses","","","","ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"DressShoes_Beige", "DressShoes_Black", "DressShoes_Brown", "DressShoes_Black", "DressShoes_Brown", "DressShoes_Sunburst", "DressShoes_White"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("Pen_Black");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI officeFemaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Plum", "Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "WaterBottle"};
		ref TStringArray hatArray = {"FlatCap_Black","","","","", "FlatCap_Blue","","","","", "FlatCap_Red","","","","", "FlatCap_Brown","","","","", "FlatCap_Grey","","","","", "FlatCap_BrownCheck","","","","", "FlatCap_GreyCheck","","","","", "FlatCap_BlackCheck","","","",""};
		ref TStringArray topArray = {"WoolCoat_Black", "WoolCoat_Red", "WoolCoat_Blue", "WoolCoat_Green", "WoolCoat_Beige", "WoolCoat_RedCheck", "WoolCoat_BlackCheck", "WoolCoat_BlueCheck", "WoolCoat_GreyCheck", "WoolCoat_BrownCheck", "Blouse_Blue", "Blouse_Green", "Blouse_Violet", "Blouse_White"};
		ref TStringArray pantsArray = {"Skirt_Blue", "Skirt_Red", "Skirt_White", "Skirt_Yellow"};
		ref TStringArray glassesArray = {"ThickFramesGlasses","","","","ThinFramesGlasses","","",""};
		ref TStringArray shoesArray = {"DressShoes_Beige", "DressShoes_Black", "DressShoes_Brown", "DressShoes_Black", "DressShoes_Brown", "DressShoes_Sunburst", "DressShoes_White"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("Pen_Blue");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}

	EntityAI bikerMaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin", "PowderedMilk", "Rice", "BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "SlicedPumpkin", "Potato", "Plum", "Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"MotoHelmet_Black", "MotoHelmet_Grey", "MotoHelmet_Green", "MotoHelmet_Lime", "MotoHelmet_Blue", "MotoHelmet_Red", "MotoHelmet_White", "DarkMotoHelmet_Black", "DarkMotoHelmet_Grey", "DarkMotoHelmet_Green", "DarkMotoHelmet_Lime", "DarkMotoHelmet_Blue", "DarkMotoHelmet_Red", "DarkMotoHelmet_White", "DirtBikeHelmet_Green", "DirtBikeHelmet_Chernarus", "DirtBikeHelmet_Khaki", "DirtBikeHelmet_Red", "DirtBikeHelmet_Black", "DirtBikeHelmet_Blue"};
		ref TStringArray topArray = {"RidersJacket_Black","RidersJacket_Black"};
		ref TStringArray pantsArray = {"Jeans_Black", "Jeans_Blue", "Jeans_Brown", "Jeans_Green", "Jeans_Grey", "Jeans_BlueDark", "CargoPants_Beige", "CargoPants_Black", "CargoPants_Blue", "CargoPants_Green", "CargoPants_Grey", "TTSKOPants", "HunterPants_Autumn", "HunterPants_Brown", "HunterPants_Spring", "HunterPants_Summer", "HunterPants_Winter", "GorkaPants_Summer", "GorkaPants_Autumn", "GorkaPants_Flat", "GorkaPants_PautRev", "USMCPants_Desert", "USMCPants_Woodland", "BDUPants"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","", "SportGlasses_Black","", "SportGlasses_Green","", "SportGlasses_Orange","", "AviatorGlasses",""};
		ref TStringArray shoesArray = {"HikingBoots_Brown", "HikingBoots_Black", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		ref TStringArray glovesArray = {"WorkingGloves_Black", "WorkingGloves_Brown", "TacticalGloves_Black", "TacticalGloves_Green", "OMNOGloves_Brown", "OMNOGloves_Gray"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","", "BandanaMask_BlackPattern","", "BandanaMask_PolkaPattern","", "BandanaMask_GreenPattern","", "BandanaMask_CamoPattern","", "HockeyMask","", "BalaclavaMask_Black","", "BalaclavaMask_Blackskull","", "BalaclavaMask_Green",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("BrassKnuckles_Shiny");
		player.GetInventory().CreateInInventory("RoadFlare");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	EntityAI bikerFemaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin", "PowderedMilk", "Rice", "BakedBeansCan_Opened", "PeachesCan_Opened", "SpaghettiCan_Opened", "SardinesCan_Opened", "TunaCan_Opened", "Apple", "Tomato", "GreenBellPepper", "Zucchini", "SlicedPumpkin", "Potato", "Plum", "Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola", "SodaCan_Pipsi", "SodaCan_Spite", "SodaCan_Kvass", "WaterBottle"};
		ref TStringArray hatArray = {"MotoHelmet_Black", "MotoHelmet_Grey", "MotoHelmet_Green", "MotoHelmet_Lime", "MotoHelmet_Blue", "MotoHelmet_Red", "MotoHelmet_White", "DarkMotoHelmet_Black", "DarkMotoHelmet_Grey", "DarkMotoHelmet_Green", "DarkMotoHelmet_Lime", "DarkMotoHelmet_Blue", "DarkMotoHelmet_Red", "DarkMotoHelmet_White", "DirtBikeHelmet_Green", "DirtBikeHelmet_Chernarus", "DirtBikeHelmet_Khaki", "DirtBikeHelmet_Red", "DirtBikeHelmet_Black", "DirtBikeHelmet_Blue"};
		ref TStringArray topArray = {"RidersJacket_Black","RidersJacket_Black"};
		ref TStringArray pantsArray = {"ShortJeans_Black", "ShortJeans_Blue", "ShortJeans_Brown", "ShortJeans_Darkblue", "ShortJeans_Green", "ShortJeans_Red", "Skirt_Blue", "Skirt_Red", "Skirt_White", "Skirt_Yellow"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","", "SportGlasses_Black","", "SportGlasses_Green","", "SportGlasses_Orange","", "AviatorGlasses",""};
		ref TStringArray shoesArray = {"HikingBoots_Brown", "HikingBoots_Black", "WorkingBoots_Grey", "WorkingBoots_Brown", "WorkingBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		ref TStringArray glovesArray = {"WorkingGloves_Black", "WorkingGloves_Brown", "TacticalGloves_Black", "TacticalGloves_Green", "OMNOGloves_Brown", "OMNOGloves_Gray"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","", "BandanaMask_BlackPattern","", "BandanaMask_PolkaPattern","", "BandanaMask_GreenPattern","", "BandanaMask_CamoPattern","", "HockeyMask","", "BalaclavaMask_Black","", "BalaclavaMask_Blackskull","", "BalaclavaMask_Green",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("BrassKnuckles_Shiny");
		player.GetInventory().CreateInInventory("RoadFlare");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	EntityAI nbcClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin","PowderedMilk","Rice","BakedBeansCan_Opened","PeachesCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Apple","Tomato","GreenBellPepper","Zucchini","SlicedPumpkin","Potato","Plum","Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","WaterBottle"};
		ref TStringArray hatArray = {"NBCHoodGray","NBCHoodGray"};
		ref TStringArray topArray = {"NBCJacketGray","NBCJacketGray"};
		ref TStringArray pantsArray = {"NBCPantsGray","NBCPantsGray"};
		ref TStringArray shoesArray = {"NBCBootsGray","NBCBootsGray"};
		ref TStringArray glovesArray = {"NBCGlovesGray","NBCGlovesGray"};
		ref TStringArray maskArray = {"GP5GasMask","GP5GasMask"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}
	
	EntityAI mechanicClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BakedBeansCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Potato"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","WaterBottle"};
		ref TStringArray hatArray = {"BaseballCap_Blue","","","","BaseballCap_Beige","","","","BaseballCap_Black","","","","BaseballCap_Olive","","","","BaseballCap_Pink","","","","BaseballCap_Red","","","","BaseballCap_Camo","","","","BaseballCap_CMMG_Black","","","","BaseballCap_CMMG_Pink","","","","BeanieHat_Beige","","","","BeanieHat_Black","","","","BeanieHat_Blue","","","","BeanieHat_Brown","","","","BeanieHat_Green","","","","BeanieHat_Grey","","","","BeanieHat_Pink","","","","BeanieHat_Red","","","","Ushanka_Black","","","","Ushanka_Blue","","","","Ushanka_Green","","","","RadarCap_Black","","","","RadarCap_Blue","","","","RadarCap_Brown","","","","RadarCap_Green","","","","RadarCap_Red","","","","FlatCap_Black","","","","FlatCap_Blue","","","","FlatCap_Red","","","","FlatCap_Brown","","","","FlatCap_Grey","","","","FlatCap_BrownCheck","","","","FlatCap_GreyCheck","","","","FlatCap_BlackCheck"};
		ref TStringArray topArray = {"JumpsuitJacket_Blue","JumpsuitJacket_Gray","JumpsuitJacket_Green","JumpsuitJacket_Red"};
		ref TStringArray pantsArray = {"JumpsuitPants_Blue","JumpsuitPants_Green","JumpsuitPants_Grey","JumpsuitPants_Red"};
		ref TStringArray shoesArray = {"AthleticShoes_Blue","AthleticShoes_Black","AthleticShoes_Brown","AthleticShoes_Green","AthleticShoes_Grey","WorkingBoots_Grey","WorkingBoots_Brown","WorkingBoots_Green","WorkingBoots_Yellow","WorkingBoots_Beige","JoggingShoes_Black","JoggingShoes_Blue","JoggingShoes_Red","JoggingShoes_Violet","JoggingShoes_White","Sneakers_Black","Sneakers_Gray","Sneakers_Green","Sneakers_Red","Sneakers_White"};
		ref TStringArray glovesArray = {"WorkingGloves_Black","", "WorkingGloves_Beige","", "WorkingGloves_Brown","", "WorkingGloves_Yellow","", "SurgicalGloves_Blue","", "SurgicalGloves_Green",""};
		ref TStringArray maskArray = {"NioshFaceMask","","","","",""};
		ref TStringArray mechanicArray = {"TireRepairKit","EngineOil","CarBattery","BatteryCharger","Wrench","Screwdriver"};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory(mechanicArray.GetRandomElement());
		player.GetInventory().CreateInInventory("SparkPlug");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(6);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}
	
	EntityAI mercenaryMaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin","PowderedMilk","Rice","BakedBeansCan_Opened","PeachesCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Apple","Tomato","GreenBellPepper","Zucchini","SlicedPumpkin","Potato","Plum","Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","SodaCan_Kvass","WaterBottle"};
		ref TStringArray hatArray = {"BallisticHelmet_Green", "BallisticHelmet_Black", "BallisticHelmet_UN", "ZSh3PilotHelmet", "ZSh3PilotHelmet_Green", "ZSh3PilotHelmet_Black", "MilitaryBeret_Red", "MilitaryBeret_UN", "MilitaryBeret_NZ", "MilitaryBeret_ChDKZ", "MilitaryBeret_CDF", "OfficerHat", "PilotkaCap", "TankerHelmet", "GorkaHelmet", "GorkaHelmet_Green", "GorkaHelmet_Black", "GorkaHelmetComplete", "GorkaHelmetComplete_Green", "GorkaHelmetComplete_Black", "Ssh68Helmet","","","","","","","","",""};
		ref TStringArray topArray = {"TacticalShirt_Olive", "TacticalShirt_Tan", "M65Jacket_Khaki", "M65Jacket_Tan", "M65Jacket_Olive", "TTsKOJacket_Camo", "GorkaEJacket_Summer", "GorkaEJacket_Flat", "GorkaEJacket_Autumn", "GorkaEJacket_PautRev", "USMCJacket_Desert", "USMCJacket_Woodland", "RidersJacket_Black"};
		ref TStringArray pantsArray = {"TTSKOPants", "GorkaPants_Summer", "GorkaPants_Autumn", "GorkaPants_Flat", "GorkaPants_PautRev", "USMCPants_Desert", "USMCPants_Woodland", "BDUPants", "Jeans_Black","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","Jeans_BlueDark","CargoPants_Beige","CargoPants_Black","CargoPants_Blue","CargoPants_Green","CargoPants_Grey"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","",""};
		ref TStringArray shoesArray = {"JungleBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Beige", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		ref TStringArray glovesArray = {"TacticalGloves_Beige","", "TacticalGloves_Black","", "TacticalGloves_Green","", "OMNOGloves_Brown","", "OMNOGloves_Gray",""};
		ref TStringArray maskArray = {"BandanaMask_CamoPattern","","BalaclavaMask_Green","","BandanaMask_RedPattern","","BandanaMask_BlackPattern","","","BandanaMask_PolkaPattern","","BandanaMask_GreenPattern","","BalaclavaMask_Black","","BalaclavaMask_Blackskull","","BalaclavaMask_Beige","","BalaclavaMask_Blue","","BalaclavaMask_Pink","","BalaclavaMask_White"};
		ref TStringArray backpackArray = {"AssaultBag_Ttsko","", "AssaultBag_Black","", "AssaultBag_Green","", "CoyoteBag_Brown","", "CoyoteBag_Green","","","","","","","","","","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("DuctTape");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}
	
	EntityAI mercenaryFemaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"BoxCerealCrunchin","PowderedMilk","Rice","BakedBeansCan_Opened","PeachesCan_Opened","SpaghettiCan_Opened","SardinesCan_Opened","TunaCan_Opened","Apple","Tomato","GreenBellPepper","Zucchini","SlicedPumpkin","Potato","Plum","Pear"};
		ref TStringArray drinkArray = {"SodaCan_Cola","SodaCan_Pipsi","SodaCan_Spite","SodaCan_Kvass","WaterBottle"};
		ref TStringArray hatArray = {"BallisticHelmet_Green", "BallisticHelmet_Black", "BallisticHelmet_UN", "ZSh3PilotHelmet", "ZSh3PilotHelmet_Green", "ZSh3PilotHelmet_Black", "MilitaryBeret_Red", "MilitaryBeret_UN", "MilitaryBeret_NZ", "MilitaryBeret_ChDKZ", "MilitaryBeret_CDF", "OfficerHat", "PilotkaCap", "TankerHelmet", "GorkaHelmet", "GorkaHelmet_Green", "GorkaHelmet_Black", "GorkaHelmetComplete", "GorkaHelmetComplete_Green", "GorkaHelmetComplete_Black", "Ssh68Helmet","","","","","","","","",""};
		ref TStringArray topArray = {"TacticalShirt_Olive", "TacticalShirt_Tan", "M65Jacket_Khaki", "M65Jacket_Tan", "M65Jacket_Olive", "TTsKOJacket_Camo", "GorkaEJacket_Summer", "GorkaEJacket_Flat", "GorkaEJacket_Autumn", "GorkaEJacket_PautRev", "USMCJacket_Desert", "USMCJacket_Woodland", "RidersJacket_Black"};
		ref TStringArray pantsArray = {"TTSKOPants", "GorkaPants_Summer", "GorkaPants_Autumn", "GorkaPants_Flat", "GorkaPants_PautRev", "USMCPants_Desert", "USMCPants_Woodland", "BDUPants", "Jeans_Black","Jeans_Blue","Jeans_Brown","Jeans_Green","Jeans_Grey","Jeans_BlueDark","CargoPants_Beige","CargoPants_Black","CargoPants_Blue","CargoPants_Green","CargoPants_Grey"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","",""};
		ref TStringArray shoesArray = {"JungleBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Beige", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		ref TStringArray glovesArray = {"TacticalGloves_Beige","", "TacticalGloves_Black","", "TacticalGloves_Green","", "OMNOGloves_Brown","", "OMNOGloves_Gray",""};
		ref TStringArray maskArray = {"BandanaMask_CamoPattern","","BalaclavaMask_Green","","BandanaMask_RedPattern","","BandanaMask_BlackPattern","","","BandanaMask_PolkaPattern","","BandanaMask_GreenPattern","","BalaclavaMask_Black","","BalaclavaMask_Blackskull","","BalaclavaMask_Beige","","BalaclavaMask_Blue","","BalaclavaMask_Pink","","BalaclavaMask_White"};
		ref TStringArray backpackArray = {"AssaultBag_Ttsko","", "AssaultBag_Black","", "AssaultBag_Green","", "CoyoteBag_Brown","", "CoyoteBag_Green","","","","","","","","","","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("DuctTape");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}
	
	EntityAI sniperMaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"TacticalBaconCan_Opened", "TacticalBaconCan_Opened"};
		ref TStringArray drinkArray = {"Canteen", "Canteen"};
		ref TStringArray hatArray = {"GhillieHood_Tan", "GhillieHood_Woodland", "GhillieHood_Mossy", ""};
		ref TStringArray topArray = {"TacticalShirt_Olive", "TacticalShirt_Tan", "M65Jacket_Khaki", "M65Jacket_Tan", "M65Jacket_Olive", "TTsKOJacket_Camo", "GorkaEJacket_Summer", "GorkaEJacket_Flat", "GorkaEJacket_Autumn", "GorkaEJacket_PautRev", "USMCJacket_Desert", "USMCJacket_Woodland"};
		ref TStringArray pantsArray = {"TTSKOPants", "GorkaPants_Summer", "GorkaPants_Autumn", "GorkaPants_Flat", "GorkaPants_PautRev", "USMCPants_Desert", "USMCPants_Woodland", "BDUPants"};
		ref TStringArray vestArray  = {"SmershVest","", "BallisticVest","", "UKAssVest_Black","", "UKAssVest_Camo","", "UKAssVest_Khaki","", "UKAssVest_Olive","", "HighCapacityVest_Black","", "HighCapacityVest_Olive",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","",""};
		ref TStringArray shoesArray = {"JungleBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Beige", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		ref TStringArray glovesArray = {"TacticalGloves_Beige","", "TacticalGloves_Black","", "TacticalGloves_Green","", "OMNOGloves_Brown","", "OMNOGloves_Gray",""};
		ref TStringArray maskArray = {"BandanaMask_CamoPattern","","","","", "BalaclavaMask_Green","","","","", "GP5GasMask","","","",""};
		ref TStringArray backpackArray = {"GhillieTop_Woodland","", "GhillieSuit_Woodland","", "GhillieBushrag_Tan","", "GhillieTop_Tan","", "GhillieSuit_Tan","", "GhillieTop_Mossy","", "GhillieSuit_Mossy",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("Compass");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}
	
	EntityAI sniperFemaleClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"TacticalBaconCan_Opened", "TacticalBaconCan_Opened"};
		ref TStringArray drinkArray = {"Canteen", "Canteen"};
		ref TStringArray hatArray = {"BallisticHelmet_Green", "BallisticHelmet_Black", "BallisticHelmet_UN", "ZSh3PilotHelmet", "ZSh3PilotHelmet_Green", "ZSh3PilotHelmet_Black", "MilitaryBeret_Red", "MilitaryBeret_UN", "MilitaryBeret_NZ", "MilitaryBeret_ChDKZ", "MilitaryBeret_CDF", "OfficerHat", "PilotkaCap", "TankerHelmet", "GorkaHelmet", "GorkaHelmet_Green", "GorkaHelmet_Black", "GorkaHelmetComplete", "GorkaHelmetComplete_Green", "GorkaHelmetComplete_Black", "GhillieHood_Tan", "GhillieHood_Woodland", "GhillieHood_Mossy", "Ssh68Helmet"};
		ref TStringArray topArray = {"TacticalShirt_Olive", "TacticalShirt_Tan", "M65Jacket_Khaki", "M65Jacket_Tan", "M65Jacket_Olive", "TTsKOJacket_Camo", "GorkaEJacket_Summer", "GorkaEJacket_Flat", "GorkaEJacket_Autumn", "GorkaEJacket_PautRev", "USMCJacket_Desert", "USMCJacket_Woodland", "MiniDress_GreenChecker"};
		ref TStringArray pantsArray = {"TTSKOPants", "GorkaPants_Summer", "GorkaPants_Autumn", "GorkaPants_Flat", "GorkaPants_PautRev", "USMCPants_Desert", "USMCPants_Woodland", "BDUPants", "ShortJeans_Black", "ShortJeans_Blue", "ShortJeans_Brown", "ShortJeans_Darkblue", "ShortJeans_Green", "ShortJeans_Red", "Skirt_Blue", "Skirt_Red", "Skirt_White", "Skirt_Yellow"};
		ref TStringArray vestArray  = {"SmershVest","", "BallisticVest","", "UKAssVest_Black","", "UKAssVest_Camo","", "UKAssVest_Khaki","", "UKAssVest_Olive","", "HighCapacityVest_Black","", "HighCapacityVest_Olive",""};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","", "SportGlasses_Black","","", "SportGlasses_Green","","", "SportGlasses_Orange","","", "AviatorGlasses","",""};
		ref TStringArray shoesArray = {"JungleBoots_Beige", "JungleBoots_Black", "JungleBoots_Brown", "JungleBoots_Green", "JungleBoots_Olive", "MilitaryBoots_Beige", "MilitaryBoots_Black", "MilitaryBoots_Bluerock", "MilitaryBoots_Brown", "MilitaryBoots_Redpunk", "CombatBoots_Beige", "CombatBoots_Black", "CombatBoots_Brown", "CombatBoots_Green", "CombatBoots_Grey"};
		ref TStringArray glovesArray = {"TacticalGloves_Beige","", "TacticalGloves_Black","", "TacticalGloves_Green","", "OMNOGloves_Brown","", "OMNOGloves_Gray",""};
		ref TStringArray maskArray = {"BandanaMask_CamoPattern","","","","", "BalaclavaMask_Green","","","","", "GP5GasMask","","","",""};
		ref TStringArray backpackArray = {"GhillieTop_Woodland","", "GhillieSuit_Woodland","", "GhillieBushrag_Tan","", "GhillieTop_Tan","", "GhillieSuit_Tan","", "GhillieTop_Mossy","", "GhillieSuit_Mossy","", "AssaultBag_Ttsko","", "AssaultBag_Black","", "AssaultBag_Green","", "CoyoteBag_Brown","", "CoyoteBag_Green",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glovesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(backpackArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		ItemBase rags = player.GetInventory().CreateInInventory("BandageDressing");
		player.GetInventory().CreateInInventory("Compass");
		ItemBase light = player.GetInventory().CreateInInventory("Flashlight");
		light.GetInventory().CreateAttachment("Battery9V");
		return rags;
	}
	
	EntityAI cowboyClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"CowSteakMeat","PowderedMilk","Rice","BakedBeansCan_Opened","Potato"};
		ref TStringArray drinkArray = {"SodaCan_Kvass","SodaCan_Kvass"};
		ref TStringArray hatArray = {"CowboyHat_Brown","CowboyHat_black","CowboyHat_darkBrown","CowboyHat_green"};
		ref TStringArray topArray = {"Shirt_BlueCheck","Shirt_BlueCheckBright","Shirt_GreenCheck","Shirt_RedCheck","Shirt_WhiteCheck","Shirt_PlaneBlack"};
		ref TStringArray pantsArray = {"Jeans_Blue","Jeans_BlueDark"};
		ref TStringArray vestArray  = {"LeatherStorageVest_Natural","", "LeatherStorageVest_Beige","", "LeatherStorageVest_Brown","", "LeatherStorageVest_Black","","ChestHolster","ChestHolster","ChestHolster","ChestHolster"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","","SportGlasses_Black","","","","SportGlasses_Green","","","","SportGlasses_Orange","","","","AviatorGlasses","","","",""};
		ref TStringArray shoesArray = {"Wellies_Black","Wellies_Brown","Wellies_Green","Wellies_Grey","WorkingBoots_Grey","WorkingBoots_Brown","WorkingBoots_Green","WorkingBoots_Beige"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","","","BandanaMask_BlackPattern","","","","","","BandanaMask_PolkaPattern","","","","","","BandanaMask_GreenPattern","","","","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("RoadFlare");
		player.GetInventory().CreateInInventory("Rope");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}
	
	EntityAI cowgirlClass(PlayerBase player)
	{
		ref TStringArray foodArray = {"CowSteakMeat","PowderedMilk","Rice","BakedBeansCan_Opened","Tomato","GreenBellPepper","SlicedPumpkin","Potato"};
		ref TStringArray drinkArray = {"SodaCan_Kvass","SodaCan_Kvass"};
		ref TStringArray hatArray = {"CowboyHat_Brown","CowboyHat_black","CowboyHat_darkBrown","CowboyHat_green"};
		ref TStringArray topArray = {"Shirt_BlueCheck","Shirt_BlueCheckBright","Shirt_GreenCheck","Shirt_RedCheck","Shirt_WhiteCheck","Shirt_PlaneBlack"};
		ref TStringArray pantsArray = {"ShortJeans_Black", "ShortJeans_Blue", "ShortJeans_Brown", "ShortJeans_Darkblue", "ShortJeans_Green", "ShortJeans_Red", "Skirt_Blue", "Skirt_Red", "Skirt_White", "Skirt_Yellow"};
		ref TStringArray vestArray  = {"LeatherStorageVest_Natural","","","", "LeatherStorageVest_Beige","","","", "LeatherStorageVest_Brown","","","", "LeatherStorageVest_Black","","","","ChestHolster","ChestHolster","ChestHolster","ChestHolster"};
		ref TStringArray glassesArray = {"SportGlasses_Blue","","","","SportGlasses_Black","","","","SportGlasses_Green","","","","SportGlasses_Orange","","","","AviatorGlasses","","","",""};
		ref TStringArray shoesArray = {"Wellies_Black","Wellies_Brown","Wellies_Green","Wellies_Grey","WorkingBoots_Grey","WorkingBoots_Brown","WorkingBoots_Green","WorkingBoots_Beige"};
		ref TStringArray maskArray = {"BandanaMask_RedPattern","","","","","","BandanaMask_BlackPattern","","","","","","BandanaMask_PolkaPattern","","","","","","BandanaMask_GreenPattern","","","","","",""};

		player.GetInventory().CreateInInventory(hatArray.GetRandomElement());
		player.GetInventory().CreateInInventory(topArray.GetRandomElement());
		player.GetInventory().CreateInInventory(pantsArray.GetRandomElement());
		player.GetInventory().CreateInInventory(vestArray.GetRandomElement());
		player.GetInventory().CreateInInventory(glassesArray.GetRandomElement());
		player.GetInventory().CreateInInventory(shoesArray.GetRandomElement());
		//player.GetInventory().CreateInInventory(maskArray.GetRandomElement());
		player.GetInventory().CreateInInventory(foodArray.GetRandomElement());
		player.GetInventory().CreateInInventory(drinkArray.GetRandomElement());
		player.GetInventory().CreateInInventory("RoadFlare");
		player.GetInventory().CreateInInventory("Rope");
		ItemBase rags = player.GetInventory().CreateInInventory("Rag");
		rags.SetQuantity(4);
		return rags;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		//  * * * * * * * * * * * * HEROES AND BANDITS CHANGES START * * * * * * * * * * * * * *
		//	Give hero or bandit specific load-outs 
		player.RemoveAllItems();
		//setup bandit masks, add more from a mod
		TStringArray bandanaMask = {"BandanaMask_BlackPattern","BandanaMask_CamoPattern","BandanaMask_GreenPattern", "BandanaMask_PolkaPattern"};
		if(m_HeroesAndBandits.GetPlayerHeroOrBandit(player.GetIdentity().GetPlainId()) == "bandit")
		{
			//Bandit Loadouts
			if(player.IsMale()) {
				EntityAI banditmale;
				switch (Math.RandomInt(0, 4)) {
					case 0: banditmale = bikerMaleClass(player); break; //bandit
					case 1: banditmale = mercenaryMaleClass(player); break;//bandit
					case 2: banditmale = sniperMaleClass(player); break; //bandit
					case 3: banditmale = prisonerClass(player); break;
				}
			}
			else
			{
				EntityAI banditfemale;
				switch (Math.RandomInt(0, 2)) {
					case 0: banditfemale = bikerFemaleClass(player); break; //bandit
					case 1: banditfemale = mercenaryFemaleClass(player); break; //bandit
				}
			}
			//make sure to remove bandana's from other loadouts
			player.GetInventory().CreateInInventory(bandanaMask.GetRandomElement());
		} else if (m_HeroesAndBandits.GetPlayerHeroOrBandit(player.GetIdentity().GetPlainId()) == "hero") {
			//Hero Loadouts
			if(player.IsMale()) {
				EntityAI heromale;
				switch (Math.RandomInt(0, 4)) {
					case 0: heromale = policemanClass(player); break;//hero
					case 1: heromale = soldierClass(player); break;//hero
					case 2: heromale = firefighterClass(player); break;//hero
					case 3: heromale = cowboyClass(player); break; //hero
				}
			}
			else
			{
				EntityAI herofemale;
				switch (Math.RandomInt(0, 2)) {
					case 0: herofemale = policewomanClass(player); break; //hero
					case 1: herofemale = soldierClass(player); break; //hero
				}
			}
		} else {
			//Bambi Loadouts
			if(player.IsMale()) {
				EntityAI bambimale;
				switch (Math.RandomInt(0, 3)) {
					case 0: bambimale = randomMaleClass(player); break; //bambi
					case 1: bambimale = officeMaleClass(player); break;
					case 2: bambimale = constructionMaleClass(player); break;
				}
			} else {
				EntityAI bambifemale;
				switch (Math.RandomInt(0, 3)) {
					case 0: bambifemale = scientistClass(player); break;
					case 1: bambifemale = mechanicClass(player); break;
					case 2: bambifemale = prisonerClass(player); break;
				}
			}
		}
		//Humanity based extra's
		float playerHumanity = m_HeroesAndBandits.GetPlayerHumanity(player.GetIdentity().GetPlainId());
		if(playerHumanity < -501) // Player is level 1 bandit or higher
		{
			player.GetInventory().CreateInInventory("Armband_Pirates"); // Assign player armband to assign Bandit faction in Expansion
		}
		if (playerHumanity > 501) //Player is level 1 Hero or higher
		{
			player.GetInventory().CreateInInventory("Armband_CDF"); // Assign player armband to assign 'PlayerSurvivor' faction in Expansion
		}
		if (playerHumanity>-500 && playerHumanity<500) //Player is bambi aww haha.
		{
			player.GetInventory().CreateInInventory("Armband_White"); // Assign player armband to assign 'Civilian' faction in Expansion
		}
		
		//Medic Items
		if ( m_HeroesAndBandits.GetPlayerStat( player.GetIdentity().GetPlainId(), "Medic" ) > 100) //Player has made over 100 Medic Actions so giving them a first aid kit
		{
			EntityAI firstAidKit = player.GetInventory().CreateInInventory("FirstAidKit");
				firstAidKit.GetInventory().CreateInInventory("TetracyclineAntibiotics");
				firstAidKit.GetInventory().CreateInInventory("BandageDressing");
				firstAidKit.GetInventory().CreateInInventory("BandageDressing");
				firstAidKit.GetInventory().CreateInInventory("CharcoalTablets");
				firstAidKit.GetInventory().CreateInInventory("BloodTestKit");
		}
		//Fisherman Items
		if ( m_HeroesAndBandits.GetPlayerStat( player.GetIdentity().GetPlainId(), "Fish" ) > 25) //Player has caught over 25 fish
		{
				EntityAI fishhat = player.GetInventory().CreateInInventory("FC_Fish_Hat_Base");
					fishhat.GetInventory().CreateInInventory("FC_Fish_Bait_Green");
		}
		if ( m_HeroesAndBandits.GetPlayerStat( player.GetIdentity().GetPlainId(), "Fish" ) > 100) //Player has caught over 100 fish
		{
				EntityAI fishbag = player.GetInventory().CreateInInventory("FC_Fish_Bag");
					fishbag.GetInventory().CreateInInventory("FC_Fish_Lure_Case");
					fishbag.GetInventory().CreateInInventory("FC_Fish_Lure_Can");
					fishbag.GetInventory().CreateInInventory("FC_Fish_Cooler_50");
					fishbag.GetInventory().CreateInInventory("FishingRod");
				player.GetInventory().CreateInInventory("FC_Fish_Hat_Base");
				player.GetInventory().CreateInInventory("FC_Fish_Lure_1_1");
		}
		//universal items to all loadouts
		player.GetInventory().CreateInInventory("ChernarusMap");
		EntityAI vape = player.GetInventory().CreateInInventory("AX_Vape");
			vape.GetInventory().CreateInInventory("Battery9V");
		player.GetInventory().CreateInInventory("metro_lighter");
		
		
	}
	//MODDED LOADOUTS - END-------------------------------------
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}
