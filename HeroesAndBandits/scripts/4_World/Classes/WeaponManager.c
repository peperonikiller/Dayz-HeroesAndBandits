modded class WeaponManager
{
	override void Fire(Weapon_Base wpn)
	{
		PlayerBase sourcePlayer = PlayerBase.Cast( m_player );
		int mi = wpn.GetCurrentMuzzle();
		if ( GetGame().IsServer() ) {
			if(!wpn.IsChamberFiredOut(mi) && !wpn.IsJammed() && !wpn.IsChamberEmpty(mi) && sourcePlayer && sourcePlayer.GetIdentity()){
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetHeroesAndBandits().NewAggressorAction, 1, false, sourcePlayer, "ShotFired", wpn);
			}
		}
		super.Fire(wpn);
	}
}