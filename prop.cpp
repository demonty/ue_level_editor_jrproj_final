#include "prop.h"

void Prop::GetBounds(AABB &box)
{
	myModel->boundingBox.xform(toWorld, box);
}

AABB Prop::GetAABB()
{
	return myModel->boundingBox;
}

void Tile::GetBounds(AABB &box)
{
	//the first tile's bounds is always in the same box, no matter the rotation
	myModel->boundingBox.xform(myMap.begin()->world, box);
}

TileModel* TileModel::Instance()
{
	static TileModel instance;
	return &instance;
}

FenceModel* FenceModel::Instance()
{
	static FenceModel instance;
	return &instance;
}

GateModel* GateModel::Instance()
{
	static GateModel instance;
	return &instance;
}

Rock01Model* Rock01Model::Instance()
{
	static Rock01Model instance;
	return &instance;
}

Rock02Model* Rock02Model::Instance()
{
	static Rock02Model instance;
	return &instance;
}

Rock03Model* Rock03Model::Instance()
{
	static Rock03Model instance;
	return &instance;
}

GraveStone01Model* GraveStone01Model::Instance()
{
	static GraveStone01Model instance;
	return &instance;
}

GraveStone02Model* GraveStone02Model::Instance()
{
	static GraveStone02Model instance;
	return &instance;
}

GroundUnitModel* GroundUnitModel::Instance()
{
	static GroundUnitModel instance;
	return &instance;
}

DestWallModel* DestWallModel::Instance()
{
	static DestWallModel instance;
	return &instance;
}

SPBaseModel* SPBaseModel::Instance()
{
	static SPBaseModel instance;
	return &instance;
}

SPBaseUpgradeModel* SPBaseUpgradeModel::Instance()
{
	static SPBaseUpgradeModel instance;
	return &instance;
}

SPGroundBuildingModel* SPGroundBuildingModel::Instance()
{
	static SPGroundBuildingModel instance;
	return &instance;
}

StraightPipeModel* StraightPipeModel::Instance()
{
	static StraightPipeModel instance;
	return &instance;
}

ElbowPipeModel* ElbowPipeModel::Instance()
{
	static ElbowPipeModel instance;
	return &instance;
}

CrossPipeModel* CrossPipeModel::Instance()
{
	static CrossPipeModel instance;
	return &instance;
}

ZombieGroundModel* ZombieGroundModel::Instance()
{
	static ZombieGroundModel instance;
	return &instance;
}

ZBaseModel* ZBaseModel::Instance()
{
	static ZBaseModel instance;
	return &instance;
}

CoalMineModel* CoalMineModel::Instance()
{
	static CoalMineModel instance;
	return &instance;
}

GraveyardModel* GraveyardModel::Instance()
{
	static GraveyardModel instance;
	return &instance;
}