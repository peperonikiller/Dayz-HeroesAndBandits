class habAgressionZoneData{
	string id = "";
	float ag = 0;
	void habAgressionZoneData(string Key, float Val){
		id = Key;
		ag = Val;
	}
}

void habSaveAgressionData(	ref map<string, float> AggressorsData, float AggressorThreshold, string UID){
	ref array<ref habAgressionZoneData> AgressionData =  new ref array<ref habAgressionZoneData>;
	string fileName = habConstant.ZoneDB + "\\" + UID + ".json";
	if (AggressorsData){
		if (AggressorsData.Count() > 0){
			habPrint("Aggressors Count: " + AggressorsData.Count(), "Debug");
			for (int j = 0; j < AggressorsData.Count(); j++){
				if (AggressorsData.GetElement(j) > AggressorThreshold){
					habPrint("Saving Aggressor Count: " + AggressorsData.GetKey(j) + " with "  + AggressorsData.GetElement(j) + " Aggression", "Debug");
					AgressionData.Insert(new ref habAgressionZoneData(AggressorsData.GetKey(j),AggressorsData.GetElement(j)));
				}
			}
		}
	}
	JsonFileLoader< array<ref habAgressionZoneData> >.JsonSaveFile(fileName, AgressionData);
}

ref map<string, float> habLoadAgressionData(string UID){
	ref map<string, float> AggressorsData = new ref map<string, float>;
	ref array<ref habAgressionZoneData> AgressionData;
	string fileName = habConstant.ZoneDB + "\\" + UID + ".json";
	if (FileExist(fileName)){
		JsonFileLoader< array<ref habAgressionZoneData> >.JsonLoadFile(fileName, AgressionData);
		if (AgressionData){
			if (AgressionData.Count() > 0){
				for (int i = 0; i < AgressionData.Count(); i++){
					AggressorsData.Insert(AgressionData.Get(i).id, AgressionData.Get(i).ag);
				}
			}
		}
	}
	return AggressorsData;
}