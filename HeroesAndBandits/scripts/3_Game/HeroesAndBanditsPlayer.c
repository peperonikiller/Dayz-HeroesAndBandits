class HeroesAndBanditsPlayer : RestCallback
{
	//Default Values
    string PlayerID = "";
	string GUID = "";
	ref array< ref habStat > Stats = new ref array< ref habStat >;
	ref array< ref habPlayerAffinity > Affinities = new ref array< ref habPlayerAffinity >;
	
	void HeroesAndBanditsPlayer(string pID = "", string guid = "") 
	{
        PlayerID = pID;
        GUID = guid;
		if (FileExist(habConstant.PlayerDB + "\\" + pID + ".json")) //If config file exsit load the file
        {
            HaBJSONHandler<HeroesAndBanditsPlayer>.FromFile(habConstant.PlayerDB+"\\" + pID + ".json", this);
        }
        else //If config file doesn't exsit create the file
        {
            if (GetGame().IsServer() || !GetGame().IsMultiplayer())
            {
                HaBJSONHandler<HeroesAndBanditsPlayer>.FromFile(habConstant.PlayerDB+"\\" + pID + ".json", this);
            }
        }
    }
    
	habLevel getLevel(){
		habLevel tempLevel = GetHeroesAndBanditsLevels().DefaultLevel;
		float points = 0;
		if (GetHeroesAndBanditsSettings().Mode == 0){
			float humanity = getHumanity();
			if ( humanity >= 0 ){
				tempLevel = GetHeroesAndBanditsLevels().getLevel("hero", humanity);	
			} else if ( humanity < 0 ) {
				tempLevel = GetHeroesAndBanditsLevels().getLevel("bandit", -humanity);	
			}
		} else if (GetHeroesAndBanditsSettings().Mode == 1){
			for (int i = 0; i < Affinities.Count(); i++)
			{
				if (GetHeroesAndBanditsLevels().getLevel(Affinities.Get(i).Name, Affinities.Get(i).Points) != GetHeroesAndBanditsLevels().DefaultLevel){
					if (Affinities.Get(i).Points > points){
						points = Affinities.Get(i).Points;
						tempLevel = GetHeroesAndBanditsLevels().getLevel(Affinities.Get(i).Name, Affinities.Get(i).Points);
					}
				}
			}
		}
		return tempLevel;
	}
	
	habLevel getSecondaryLevel(){
		habLevel tempLevel = GetHeroesAndBanditsLevels().DefaultLevel;
		float points = 0;
		if (GetHeroesAndBanditsSettings().Mode != 2){
			habPrint("Tried to use getSecondaryLevel in wrong mode", "Exception");
			return tempLevel;
		} else {
			for (int i = 0; i < Affinities.Count(); i++)
			{
				if (Affinities.Get(i).Name == "hero" || Affinities.Get(i).Name == "bandit"){
				} else{
					if ( GetHeroesAndBanditsLevels().getLevel(Affinities.Get(i).Name, Affinities.Get(i).Points) != GetHeroesAndBanditsLevels().DefaultLevel){
						if (Affinities.Get(i).Points > points){
							points = Affinities.Get(i).Points;
							tempLevel = GetHeroesAndBanditsLevels().getLevel(Affinities.Get(i).Name, Affinities.Get(i).Points);
						}
					}
				}
			}
		}
		return tempLevel;
	}
	
	int getLevelIndex(){
		int index = -1;
		float points = 0;
		if (GetHeroesAndBanditsSettings().Mode != 1){
			float humanity = getHumanity();
			if ( humanity > 0 ){
				index = GetHeroesAndBanditsLevels().getLevelIndex("hero", humanity);	
			} else if ( humanity < 0 ) {
				index = GetHeroesAndBanditsLevels().getLevelIndex("bandit", -humanity);	
			} 
		} else if (GetHeroesAndBanditsSettings().Mode == 1){
			for (int i = 0; i < Affinities.Count(); i++)
			{
				if (GetHeroesAndBanditsLevels().getLevel(Affinities.Get(i).Name, Affinities.Get(i).Points) != GetHeroesAndBanditsLevels().DefaultLevel){
					if (Affinities.Get(i).Points > points){
						points = Affinities.Get(i).Points;
						index = GetHeroesAndBanditsLevels().getLevelIndex(Affinities.Get(i).Name, Affinities.Get(i).Points);
					}
				}
			}
		}
		return index;
	}
	
	habAffinity getAffinity(){
		habAffinity tempAffinity = GetHeroesAndBanditsLevels().DefaultAffinity;
		habLevel tempLevel = getLevel();
		float points = 0;
		if (tempLevel != GetHeroesAndBanditsLevels().DefaultLevel){
			//habPrint(PlayerID + " is level: " + tempLevel.Name + " with affinity " + tempLevel.Affinity, "Debug");
			tempAffinity = GetHeroesAndBanditsLevels().getAffinity(tempLevel.Affinity);
		}
		return tempAffinity;
	}
	
	habAffinity getSecondaryAffinity(){
		habAffinity tempAffinity = GetHeroesAndBanditsLevels().DefaultAffinity;
		habLevel tempLevel = getSecondaryLevel();
		float points = 0;
		if (tempLevel != GetHeroesAndBanditsLevels().DefaultLevel){
			//habPrint(PlayerID + " is level: " + tempLevel.Name + " with affinity " + tempLevel.Affinity, "Debug");
			tempAffinity = GetHeroesAndBanditsLevels().getAffinity(tempLevel.Affinity);
		}
		return tempAffinity;
	}
	
	int getAffinityIndex(){
		int index = -1;
		habLevel tempLevel = getLevel();
		float points = 0;
		if (tempLevel != GetHeroesAndBanditsLevels().DefaultLevel){
			//habPrint(PlayerID + " is level: " + tempLevel.Name + " with affinity " + tempLevel.Affinity, "Debug");
			index = GetHeroesAndBanditsLevels().getAffinityIndex(tempLevel.Affinity);
		}
		return index;
	}
	
	
	
	float getAffinityPoints( string name){
		if (GetHeroesAndBanditsSettings().Mode != 1){
			if ( name == "hero" ||  name == "bandit") {
				float heroPoints = 0;
				float banditPoints = 0;
				for (int i = 0; i < Affinities.Count(); i++)
				{
					if (Affinities.Get(i).Name == "hero") {
						heroPoints = Affinities.Get(i).getPoints();
					} else if (Affinities.Get(i).Name == "bandit") {
						banditPoints = Affinities.Get(i).getPoints();
					}
				}
				if (name == "hero"){
					return heroPoints - banditPoints;
				} else {
					return banditPoints - heroPoints;
				}
			}
		}
		for (int j = 0; j < Affinities.Count(); j++)
		{
			if (Affinities.Get(j).Name == name) {
				return Affinities.Get(j).getPoints();
			}
		}
		return 0;
	}
	
	bool checkItem(string itemType, string location){
		if (GetHeroesAndBanditsSettings().Mode == 0){// shouldn't get called in my mod alone but just encase someone else wants to use the check item in their own mods :)
			return getAffinity().checkItem(getAffinityPoints(getAffinity().Name ), itemType, location );
		}
		bool canAttach = true;
		for (int j = 0; j < Affinities.Count(); j++)
		{
			if ( !GetHeroesAndBanditsLevels().getAffinity(Affinities.Get(j).Name).checkItem(Affinities.Get(j).Points, itemType, location)){
				return false;
			}
		}
		
		return true;
	}
	
	void addAffinityPoints( string name, float points ){
		bool found = false;
		for (int i = 0; i < Affinities.Count(); i++)
		{
			if (Affinities.Get(i).Name == name) {
				Affinities.Get(i).updatePoints(points);
				if (Affinities.Get(i).Points < 0 && GetHeroesAndBanditsSettings().AffintyCantGoBelowZero){
					Affinities.Get(i).setPoints(0);
				}
				found = true;
			}
		}
			
		if (!found && GetHeroesAndBanditsLevels().doesAffinityExsit(name)){
			habPrint("Creating affinity " + name + " for player " + PlayerID + " with " + points, "Verbose");
			Affinities.Insert(new ref habPlayerAffinity(name, points));
		} else if (!found) {
			habPrint("Tried to add "+ points + " for player " + PlayerID + " to " + name + " but affinity does not exist", "Exception");
		}
	}
	
	string getAffinityName(){
		return getAffinity().Name;
	}
		
	
	string getHeroOrBandit(){
		
		habLevel tempLevel = GetHeroesAndBanditsLevels().DefaultLevel;
		float points = 0;
		if (GetHeroesAndBanditsSettings().Mode == 0){
			float humanity = getHumanity();
			if ( humanity > 0 ){
				tempLevel = GetHeroesAndBanditsLevels().getLevel("hero", humanity);	
			} else if ( humanity < 0 ) {
				tempLevel = GetHeroesAndBanditsLevels().getLevel("bandit", -humanity);	
			} 
		} else if (GetHeroesAndBanditsSettings().Mode == 1){
			if (getAffinityPoints( "hero" ) > getAffinityPoints( "bandit" )){
				tempLevel = GetHeroesAndBanditsLevels().getLevel("hero", getAffinityPoints( "hero" ));
			} else {
				tempLevel = GetHeroesAndBanditsLevels().getLevel("bandit", getAffinityPoints( "bandit" ));
			}
		}
		return tempLevel.Affinity;
	}
		
	
	void saveData(){
		if (GetGame().IsServer())
		{
			HaBJSONHandler<HeroesAndBanditsPlayer>.ToFile(habConstant.PlayerDB + "\\" + PlayerID + ".json", this);
	    }
	}
	
	float getHumanity(){
		return getAffinityPoints("hero");
	}

	float getStat(string statName){
		//Print("[HeroesAndBandits][DebugClient] Looking for Stat: " + statName );
		float statTotal = 0;
		string prefix;
		int nameLength;
		if ( statName == "Kill" ){
			for ( int h =0; h < Stats.Count(); h++ )
			{
				if (Stats.Get(h).Name == "heroVshero" || Stats.Get(h).Name == "heroVsbambi" || Stats.Get(h).Name == "heroVsbandit" || Stats.Get(h).Name == "banditVshero" || Stats.Get(h).Name == "banditVsbambi" || Stats.Get(h).Name == "bambiVsbandit" || Stats.Get(h).Name == "bambiVshero" || Stats.Get(h).Name == "bambiVsbambi" || Stats.Get(h).Name == "bambiVshero"){
					statTotal = statTotal + Stats.Get(h).Stat;
				}
			}
			return statTotal;
		} else if ( statName == "Hunt" ) {
			for ( int j =0; j < Stats.Count(); j++ )
			{
				if ( Stats.Get(j).Name.Contains("Hunt") ){
					statTotal = statTotal + Stats.Get(j).Stat;
				}
			}
			return statTotal;
		} else if ( statName == "Medic" ){
			for ( int k =0; k < Stats.Count(); k++ )
			{
				if ( Stats.Get(k).Name.Contains("Medic") ){
					statTotal = statTotal + Stats.Get(k).Stat;
				}
			}
			return statTotal;
		} else if ( statName == "Fisher" ){
			for ( int p =0; p < Stats.Count(); p++ )
			{
				if ( Stats.Get(p).Name.Contains("fish") ){
					statTotal = statTotal + Stats.Get(p).Stat;
				}
			}
			return statTotal;
		} else if ( statName == "Archery" ){
			for ( int y =0; y < Stats.Count(); y++ )
			{
				if ( Stats.Get(y).Name.Contains("archery") ){
					statTotal = statTotal + Stats.Get(y).Stat;
				}
			}
			return statTotal;
		} else if ( statName == "Gunsmith" ){
			for ( int x =0; x < Stats.Count(); x++ )
			{
				if ( Stats.Get(x).Name.Contains("gun") ){
					statTotal = statTotal + Stats.Get(x).Stat;
				}
			}
			return statTotal;
		} else if ( statName == "Farming" ){
			for ( int z =0; z < Stats.Count(); z++ )
			{
				if ( Stats.Get(z).Name.Contains("farm") ){
					statTotal = statTotal + Stats.Get(z).Stat;
				}
			}
			return statTotal;

		} else if ( statName == "Raid" ) {
			for ( int l =0; l < Stats.Count(); l++ )
			{
				if ( Stats.Get(l).Name.Contains("Raid") || Stats.Get(l).Name.Contains("Hack") ){
					statTotal = statTotal + Stats.Get(l).Stat;
				}
			}
			return statTotal;
		} else if ( statName == "Mission" ) {
			for ( int m =0; m < Stats.Count(); m++ )
			{
				prefix = Stats.Get(m).Name.Substring(0, 3);;
				
				//Print("[HeroesAndBandits][DebugClient] Looking for Stat: " + statName + " comparing to " + Stats.Get(j).Name + " Prefix is " + prefix );
				if ( prefix == "SMM" ){
					statTotal = statTotal + Stats.Get(m).Stat;
				}
			}
			return statTotal;
		}  else if ( statName == "Sucide" ) {
			for ( int n =0; n < Stats.Count(); n++ )
			{
				if ( Stats.Get(n).Name.Contains("Sucide") ){
					statTotal = statTotal + Stats.Get(n).Stat;
				}
			}
			return statTotal;
		}   else if ( statName == "ZombieKill" ) {
			for ( int o =0; o < Stats.Count(); o++ )
			{
				if ( Stats.Get(o).Name.Contains("ZombieKill") ){
					statTotal = statTotal + Stats.Get(o).Stat;
				}
			}
			return statTotal;
		} 
		
		for ( int i =0; i < Stats.Count(); i++ )
		{
			if (Stats.Get(i).Name == statName){
				return Stats.Get(i).Stat;
			}
		}
		habPrint("Stat: " + statName + " for player " + PlayerID + " not found", "Verbose");
		return 0;
	}
	
	// Will return true if player leveled up from the action
	bool NewAction(string actionName){
		int statID = -1;
		habPrint("Player: " + PlayerID + " performed Action: " + actionName, "Verbose");
		for ( int i =0; i < Stats.Count(); i++ )
		{
			if (Stats.Get(i).Name == actionName){
				statID = i;
			}
		}
		if (statID == -1){//Stat Not found so adding it
			Stats.Insert(new ref habStat(actionName, 1));
			habPrint("Stat: " + actionName + " for player " + PlayerID + " Created", "Debug");
		}else
		{
			Stats.Get(statID).updateStat();
			habPrint("Stat: " + actionName + " for player " + PlayerID + " Updated to " + Stats.Get(statID).Stat, "Debug");
		}
		string oldLevel = getLevel().Name;
		habAction tempAction = GetHeroesAndBanditsActions().getAction(actionName);
		habPrint( "Found action: " + tempAction.Name, "Debug");
		if ( tempAction.Affinity != "none" ){
			habPrint( "Player: " + PlayerID + " adding " + tempAction.Points + " points to  " + tempAction.Affinity + " currenlty: " + getAffinityPoints(tempAction.Affinity), "Debug");
			addAffinityPoints(tempAction.Affinity, tempAction.Points);
			habPrint( "Player: " + PlayerID + " adding " + tempAction.Points + " points to  " + tempAction.Affinity + " now: " + getAffinityPoints(tempAction.Affinity), "Debug");
		}
		if (( tempAction.SecondaryAffinity != "none" )){
			habPrint( "Player: " + PlayerID + " adding " + tempAction.Points + " points to  " + tempAction.SecondaryAffinity + " currenlty: " + getAffinityPoints(tempAction.SecondaryAffinity), "Debug");
			addAffinityPoints(tempAction.SecondaryAffinity, tempAction.Points);
			habPrint( "Player: " + PlayerID + " adding " + tempAction.Points + " points to  " + tempAction.SecondaryAffinity + " now: " + getAffinityPoints(tempAction.SecondaryAffinity), "Debug");
			
		}
		if (oldLevel == getLevel().Name){ //Check if Level Changed
			return false;
		} else
		{
			habPrint( "Player: " + PlayerID + " Leveled Changed from " + oldLevel + " to " + getLevel().Name, "Verbose");
			return true;
		}
		
	}
	
	void recalculateTotals()
	{
		if (Affinities){
			for (int i = 0; i < Affinities.Count(); i++)
			{
				Affinities.Get(i).setPoints(0);
			}
		}
		float subTotal = 0;
		for ( int j =0; j < Stats.Count(); j++ ) {
			habAction tempAction = GetHeroesAndBanditsActions().getAction(Stats.Get(j).Name);
			
			if (tempAction.Name != "Null"){
				subTotal = Stats.Get(j).Stat * tempAction.Points;
				if ( tempAction.Affinity != "none" ){
					addAffinityPoints(tempAction.Affinity, subTotal);
				}
				if (( tempAction.SecondaryAffinity != "none" )){
					addAffinityPoints(tempAction.SecondaryAffinity, subTotal);
				}
			} else {
				habPrint( "Player: " + PlayerID + " has stat that does not exsit " + tempAction.Name, "Verbose");
			}
		}
	}
	
	
	void OnDeath(){
		if (GetHeroesAndBanditsSettings().ResetAffinitiesOnDeath){
			for (int i = 0; i < Affinities.Count(); i++){
				Affinities.Get(i).setPoints(0);
			}
		}
		if (GetHeroesAndBanditsSettings().ResetStatsOnDeath){
			for ( int j =0; j < Stats.Count(); j++ ){
				Stats.Get(j).Stat = 0;
			}
		}
		
	}
	
};
