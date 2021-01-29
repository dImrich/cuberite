
// StrongholdGen.h

// Declares the cStrongholdGen class representing the village generator





#pragma once

#include "GridStructGen.h"
#include "PrefabPiecePool.h"
#include "../ChunkDef.h"





// fwd:
class cStrongholdPiecePool;





class cStrongholdGen:
	public cGridStructGen
{
	using Super = cGridStructGen;

public:

	/** Creates a new instance of the generator with the specified parameters. */
	cStrongholdGen(
		int a_Seed,
		int a_GridSize,
		int a_MaxOffset,
		int a_MaxDepth,
		int a_MaxSize,
		int a_MinDensity, int a_MaxDensity,
		cBiomeGenPtr a_BiomeGen,
		cTerrainHeightGenPtr a_HeightGen,
		int a_SeaLevel
	);


	virtual void GenFinish(cChunkDesc & a_ChunkDesc) override;

	static cChunkCoordsList GeneratePositions(cNoise & a_Noise);

	static Vector3i GetNearestStronghold(cWorld & a_World, Vector3i a_Pos);

  protected:
	class cStronghold;  // fwd: StrongholdGen.cpp
	typedef std::vector<std::shared_ptr<cStrongholdPiecePool>> cStrongholdPiecePools;

	/** The noise used for generating random numbers */
	cNoise m_RandNoise;

	/** Maximum depth of the generator tree */
	int m_MaxDepth;

	/** Maximum size, in X / Z blocks, of the village (radius from the origin) */
	int m_MaxSize;

	/** Minimum density - percentage of allowed house connections. Range [0, 100] */
	int m_MinDensity;

	/** Maximum density - percentage of allowed house connections. Range [0, 100] */
	int m_MaxDensity;

	/** The underlying biome generator that defines whether the village is created or not */
	cBiomeGenPtr m_BiomeGen;

	/** The underlying height generator, used to position the prefabs crossing chunk borders */
	cTerrainHeightGenPtr m_HeightGen;

	/** All available prefab sets. Each village gets one of these chosen randomly. */
	cStrongholdPiecePools m_Pools;

	bool m_PositionsGenerated = false;


	// cGridStructGen overrides:
	virtual cStructurePtr CreateStructure(int a_GridX, int a_GridZ, int a_OriginX, int a_OriginZ) override;


	virtual void GeneratePositions();

	cChunkCoordsList m_StrongholdPositions;
	cStructurePtrs   m_StrongholdStructures;

} ;




