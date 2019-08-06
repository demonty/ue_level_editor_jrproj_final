#ifndef NAVGRAPH_H
#define NAVGRAPH_H

#include <vector>
#include <list>
#include "serial/Serializable.h"
#include "serial/Serializer.h"
#include "serial/Deserializer.h"



struct navGraphNode : public Serializable {
	int m_ID;
	D3DXVECTOR3 m_position;
	int m_gridX;
	int m_gridY;

	void WriteTo(Serializer* destination)
	{
		std::string str = "";
		destination->WriteParameter(str, m_ID);
		destination->WriteParameter(str, m_position);
		destination->WriteParameter(str, m_gridX);
		destination->WriteParameter(str, m_gridY);
	}
	void ReadFrom(Deserializer* source)
	{
		std::string str = "";
		source->ReadParameter(str, m_ID);
		source->ReadParameter(str, m_position);
		source->ReadParameter(str, m_gridX);
		source->ReadParameter(str, m_gridY);
	}
};

struct navGraphEdge : public Serializable {
	int m_from;
	int m_to;
	float m_cost;

	void WriteTo(Serializer* destination)
	{
		std::string str = "";
		destination->WriteParameter(str, m_from);
		destination->WriteParameter(str, m_to);
		destination->WriteParameter(str, m_cost);
	}
	void ReadFrom(Deserializer* source)
	{
		std::string str = "";
		source->ReadParameter(str, m_from);
		source->ReadParameter(str, m_to);
		source->ReadParameter(str, m_cost);
	}
};

class NavGraph : public Serializable {
public:

	~NavGraph() { delete m_pInstance;}

	static bool Initialize(int width, int height, float xwidthspacing, float yheightspacing, bool debug);


	//Returns true if the Edge exists
	bool EdgeExists(int from, int to);

	//Returns true if the node is active (traversable)
	bool IsNodeActive(int nodeid);

	//Returns a reference to a node with the given index
	navGraphNode& GetNode(int index);

	//Returns a reference to an edge with the given index
	navGraphEdge& GetEdge(int from, int to);

	//Returns the next available Node ID
	int GetNextID();

	//Adds a node to the graph
	int AddNode(navGraphNode newnode);

	//Removes a node from the graph (marks it inactive)
	void RemoveNode(int nodeID);

	//Add an edge to the graph
	void AddEdge(navGraphEdge newedge);

	//Remove the given edge from the graph
	void RemoveEdge(int from, int to);

	//Returns the number of active (traversable) nodes in the graph
	int GetNumActiveNodes();

	//Returns the total number of nodes in the graph, including inactive ones
	int GetNumTotalNodes();

	//Returns the total number of edges in the graph
	int GetNumEdges();

	//Returns true if there are zero nodes in the graph
	bool IsEmpty();	

	//Clear the entire navgraph (node vector)
	void ClearNavGraph();

	//Returns the World Coordinates for the given Node ID
	D3DXVECTOR3 GetNodeWorldCoords(int nodeID); 

	//Instance function to access NavGraph as a singleton
	static NavGraph* Instance();

	//Returns the Node ID nearest the position vector
	int GetClosestNodeToPosition(D3DXVECTOR3 pos);
	int GetClosestNodeToPosition(D3DXVECTOR3 pos, bool includeinactives);

	void WriteTo(Serializer* destination);
	void ReadFrom(Deserializer* source);	

private:

	NavGraph(int width, int height, float xwidthspacing, float yheightspacing, bool debug);

	static NavGraph* m_pInstance;
public:
	std::vector<navGraphNode> m_nodeVector;

	typedef std::list<navGraphEdge> EdgeList;
	std::vector<EdgeList> m_edgesVector;

	int m_nextNodeID;
	int m_numNodesWide;
	int m_numNodesTall;
	float m_xWidthSpacing;
	float m_yHeightSpacing;
	D3DXVECTOR3 m_upperLeft;

	bool m_debugMode;
};



#endif