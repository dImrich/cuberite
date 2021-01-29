
#pragma once

#include "Entity.h"





// tolua_begin
class cEyeOfEnder :
	public cEntity
{
	// tolua_end
	using Super = cEntity;

public:

	CLASS_PROTODEF(cEyeOfEnder)

	cEyeOfEnder(Vector3d a_Pos);

	// tolua_begin

	void MoveTowards(Vector3d a_Target);

	// tolua_end

private:
	Vector3d m_LastTickPos;

	Vector3d m_Target;

	int m_DespawnTimer = 0;

	// cEntity overrides:
	virtual void SpawnOn(cClientHandle & a_ClientHandle) override;
	virtual void Tick(std::chrono::milliseconds a_Dt, cChunk & a_Chunk) override;

};  // tolua_export




