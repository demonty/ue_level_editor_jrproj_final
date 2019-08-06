#ifndef ENTITY_RESOURCE_H
#define ENTITY_RESOURCE_H

#include "dxUtil.h"

//enum object that stores all the entity types
enum EntityType
{
	ETYPE_TEST,		//TEST TYPE
	ETYPE_SP_HERO,
	ETYPE_ZOMBIE_HERO,
	ETYPE_SPBRAIN,	// steam punk main brain
	ETYPE_SPTROOPER,//steam punk 1st grnd unit
	ETYPE_SPTANK,//steam punk 2nd ground unit - tank
	ETYPE_SPAIR,	//steam punk air to air unit
	ETYPE_SPAIR2,	//steam punk air to grnd unit
	ETYPE_ZBRAIN,	//zombie main brain
	ETYPE_ZOMBIE,	//zomnie 1st grnd unit
	ETYPE_ZOMBIE2,	//zombie 2nd ground unit
	ETYPE_ZAIR,		//zombie air to air unit
	ETYPE_ZAIR2,	//zombie air to grnd unit
	ETYPE_RESOURCE, //resource
	ETYPE_BUILDING, //building
	ETYPE_PROP,     //static obstacle
	ETYPE_INVALID = -1//invalid type
};

#include "serial/Serializable.h"

class Serialize;
class Deserialize;
class Prop;
// Class: EntityResource
// 
// Description:
// Encapsulates data needed by multiple cores so that they can all share one copy of the
// data without any of them having to contain it.
class EntityResource : public Serializable
{
public:
	// Constructor. Initializes properties of this entity resource.
	EntityResource(UINT id);

	// Contructor. Initializes properties from a prop. Just for editor.
	EntityResource(UINT id, Prop* prop);

	// Returns the ID of this entity resource.
	UINT GetID() const;

	// Saves the information of this entity resource
	void WriteTo(Serializer* destination);

	// Loads information to this entity resource
	void ReadFrom(Deserializer* source);
	void ReadFromOld(Deserializer* source);

	// This entity resource's EntityType
	int m_entityType;

	// This entity resource's position.
	D3DXVECTOR3 m_position;

	// This entity resource's rotation.
	D3DXVECTOR3 m_rotationVec;
	D3DXMATRIX  m_rotationMtx;

	// This entity resource's scale. Is this GraphicsCore specific?
	D3DXVECTOR3 m_scale;

	// This entity resource's velocity.
	D3DXVECTOR3 m_velocity;

	// The accumulated amount of force to be applied to this entity.
	D3DXVECTOR3 m_force;

	// The type of this entity's mesh. Static or Animated.
	bool m_staticMesh;
	
	// The ID of this entity's mesh.
	int m_meshID;

	// This entity resource's visiblity.
	bool m_visible;

	// obb for this entity resource...
	D3DXVECTOR3 m_points[4];

protected:
	// This entity resource's ID.
	UINT m_id;

	// returns true if static, false for animated, type by ref..
	bool GetMyETypeFromPType(PropType prop, int& type);
};

#endif
