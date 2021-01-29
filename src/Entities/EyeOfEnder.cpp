
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "EyeOfEnder.h"
#include "../ClientHandle.h"
#include "../Chunk.h"





cEyeOfEnder::cEyeOfEnder(
	Vector3d a_Pos
) :
	Super(etEyeOfEnder, a_Pos, 1.0, 1.0)
{
	SetMaxHealth(5);
}





void cEyeOfEnder::SpawnOn(cClientHandle & a_ClientHandle)
{
	GetWorld()->BroadcastSoundEffect("entity.ender_eye.launch", GetPosition(), 1.f, (0.75f + (static_cast<float>((GetUniqueID() * 23) % 32)) / 64));

	a_ClientHandle.SendSpawnEntity(*this);
	a_ClientHandle.SendEntityMetadata(*this);
}





void cEyeOfEnder::Tick(std::chrono::milliseconds a_Dt, cChunk & a_Chunk)
{
	if (m_Target.HasNonZeroLength())
	{
		m_DespawnTimer++;

		Vector3f a_Distance = m_Target - GetPosition();
		double Distance = a_Distance.Length();

		Vector3d SpeedDelta(a_Distance);
		SpeedDelta.Normalize();
		SpeedDelta *= 0.3;

		Vector3d CurrentSpeed = GetSpeed();
		CurrentSpeed += SpeedDelta;
		if (CurrentSpeed.Length() > 12)
		{
			CurrentSpeed.Normalize();
			CurrentSpeed *= 0.15;
		}

		SetSpeed(CurrentSpeed);
	
		m_Gravity = 0;

		if (IsInWater())
		{
			m_World->BroadcastParticleEffect("water_bubble",  GetPosition()+CurrentSpeed*0.25, Vector3f(0, 0, 0), 0, 1);
		}
		else
		{
			m_World->BroadcastParticleEffect("portal", GetPosition()+CurrentSpeed*0.25, Vector3f(GetRandomProvider().RandReal() * 0.6 - 0.3, 0, GetRandomProvider().RandReal() * 0.6 - 0.3), 0, 1);
		}

		HandlePhysics(a_Dt, a_Chunk);
		BroadcastMovementUpdate();

		if (m_DespawnTimer > 80)
		{
			/*GetWorld()->BroadcastChatInfo(Printf("Target X %f Z %f", m_Target.x, m_Target.z));
			GetWorld()->BroadcastChatInfo(Printf("Speed X %f Y %f Z %f", GetSpeed().x, GetSpeed().y, GetSpeed().z));*/
			if (GetRandomProvider().RandInt(0, 5) > 0)
			{
				m_World->SpawnItemPickup(GetPosition(), cItem(E_ITEM_EYE_OF_ENDER), Vector3f(0, 0, 0));
			}
			else
			{
				m_World->BroadcastSoundParticleEffect(EffectID::PARTICLE_EYE_OF_ENDER, GetPosition(), 0);
			}
	
			Destroy();
		}
	}
}





void cEyeOfEnder::MoveTowards(Vector3d a_Target)
{
	auto a_Pos = GetPosition();
	Vector3f a_Distance = a_Target - a_Pos;
	double Distance = a_Distance.Length();

	if (Distance > 12.0)
	{
		m_Target = Vector3d(a_Pos.x + a_Distance.x / Distance * 12.0, a_Pos.y + 8.0, a_Pos.z + a_Distance.z / Distance * 12.0);
	}
	else
	{
		m_Target = a_Target;
	}
}





