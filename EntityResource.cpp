#include "EntityResource.h"
#include "prop.h"
#include "serial/Serializer.h"
#include "serial/Deserializer.h"
//--------------------------------------------------------------------------------------*
// Constructor. Initializes properties of this EntityResource.
//--------------------------------------------------------------------------------------*
EntityResource::EntityResource(UINT id)
	: m_id		(id),
	  m_entityType(ETYPE_INVALID),
	  m_position(0.0f, 0.0f, 0.0f),
	  m_rotationMtx(1.0f, 0.0f, 0.0f, 0.0f,
				 0.0f, 1.0f, 0.0f, 0.0f,
				 0.0f, 0.0f, 1.0f, 0.0f,
				 0.0f, 0.0f, 0.0f, 1.0f),
	  m_rotationVec(0.0f, 0.0f, 0.0f),
	  m_scale	(1.0f, 1.0f, 1.0f),
	  m_velocity(0.0f, 0.0f, 0.0),
	  m_force	(0.0f, 0.0f, 0.0f),
	  m_staticMesh(true),
	  m_meshID	(UINT_MAX),
	  m_visible	(true)
{
	;
}

//--------------------------------------------------------------------------------------*
// Constructor. Initializes properties of this EntityResource from a Prop type
//--------------------------------------------------------------------------------------*
EntityResource::EntityResource(UINT id, Prop* prop)
	: m_id(id)
{
	//position
	m_position = prop->position;

	//rotation
	D3DXMATRIX R;
	D3DXMatrixRotationYawPitchRoll(&R, prop->rotVec.x,
		prop->rotVec.y, prop->rotVec.z);
	m_rotationMtx = R;
	m_rotationVec = prop->rotVec;
	
	//scale
	m_scale = prop->scale;

	m_velocity = VEC3_ZERO;
	m_force    = VEC3_ZERO;

	m_meshID = prop->type;
	m_staticMesh = GetMyETypeFromPType(prop->type, m_entityType);

	m_visible = true;
}

//--------------------------------------------------------------------------------------*
// Returns the ID of this entity resource.
//--------------------------------------------------------------------------------------*
UINT EntityResource::GetID() const
{
	return m_id;
}

//--------------------------------------------------------------------------------------*
// Saves the members of this entity resource to a Serialzer object.
//--------------------------------------------------------------------------------------*
void EntityResource::WriteTo(Serializer *destination)
{
	std::string str = "";

	//destination->WriteParameter(str, m_id);
	destination->WriteParameter(str, m_entityType);
	destination->WriteParameter(str, m_position);
	destination->WriteParameter(str, m_rotationVec);
	destination->WriteParameter(str, m_rotationMtx);
	destination->WriteParameter(str, m_scale);
	destination->WriteParameter(str, m_velocity);
	destination->WriteParameter(str, m_force);
	destination->WriteParameter(str, m_staticMesh);
	destination->WriteParameter(str, m_meshID);
	destination->WriteParameter(str, m_visible);
}

//--------------------------------------------------------------------------------------*
// Loads the members of this entity resource from a Deserializer object.
//--------------------------------------------------------------------------------------*
void EntityResource::ReadFrom(Deserializer *source)
{
	std::string str = "";
	//int non_id = 0;
	//source->ReadParameter(str, non_id);
	source->ReadParameter(str, m_entityType);
	source->ReadParameter(str, m_position);
	source->ReadParameter(str, m_rotationVec);
	source->ReadParameter(str, m_rotationMtx);
	source->ReadParameter(str, m_scale);
	source->ReadParameter(str, m_velocity);
	source->ReadParameter(str, m_force);
	source->ReadParameter(str, m_staticMesh);
	source->ReadParameter(str, m_meshID);
	source->ReadParameter(str, m_visible);
	//for(int i = 0; i < 4; i++)
	//{
	//	source->ReadParameter(str, m_points[i]);
	//}
}

void EntityResource::ReadFromOld(Deserializer *source)
{
	std::string str = "";
	//int non_id = 0;
	//source->ReadParameter(str, non_id);
	source->ReadParameter(str, m_entityType);
	source->ReadParameter(str, m_position);
	source->ReadParameter(str, m_rotationVec);
	source->ReadParameter(str, m_rotationMtx);
	source->ReadParameter(str, m_scale);
	source->ReadParameter(str, m_velocity);
	source->ReadParameter(str, m_force);
	source->ReadParameter(str, m_staticMesh);
	source->ReadParameter(str, m_meshID);
	source->ReadParameter(str, m_visible);
}

bool EntityResource::GetMyETypeFromPType(PropType prop, int &type)
{
	switch(prop)
	{

	case PROP_FENCE:
	case PROP_GATE:
	case PROP_ROCK01:
	case PROP_ROCK02:
	case PROP_ROCK03:
	case PROP_TOMBSTONE01:
	case PROP_TOMBSTONE02:
	case PROP_DESTROYED_WALL_01:
	case PROP_PIPE_STRAIGHT:
	case PROP_PIPE_ELBOW:
	case PROP_PIPE_CROSS:
		type = ETYPE_PROP;
		return true;

	case UNIT_SP_GROUND:
		type = ETYPE_SPTROOPER;
		return false;

	case UNIT_Z_GROUND:
		type = ETYPE_ZOMBIE;
		return false;

	case BUILDING_SP_BASE:
	case BUILDING_Z_BASE:
		type = ETYPE_BUILDING;
		return true;

	case BUILDING_GRAVEYARD:
	case BUILDING_COAL_MINE:
		type = ETYPE_RESOURCE;
		return true;

	case INVALID_PROP:
	default:
		type = ETYPE_INVALID;
		return true;
	};
}