#include "NavGraph.h"
#include <cassert>

bool IsValidNeighbor(int x, int y, int NumCellsX, int NumCellsY)
{
  return !((x < 0) || (x >= NumCellsX) || (y < 0) || (y >= NumCellsY));
}

NavGraph* NavGraph::m_pInstance = NULL;

NavGraph::NavGraph(int width, int height, float xwidthspacing, float yheightspacing, bool debug)
{
	ClearNavGraph();
	m_debugMode = debug;
	m_numNodesWide = width;
	m_numNodesTall = height;
	m_xWidthSpacing = xwidthspacing;
	m_yHeightSpacing = yheightspacing;
	float minx = -((width + 50) / 2) * xwidthspacing;
	float maxy = ((height - 50) / 2) * yheightspacing;
	m_upperLeft.x = minx;
	m_upperLeft.y = 0.0f;
	m_upperLeft.z = maxy;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			navGraphNode tmpnode;
			tmpnode.m_ID = GetNextID();
			tmpnode.m_gridX = j;
			tmpnode.m_gridY = i;
//			tmpnode.m_position.x = j * xwidthspacing;
			tmpnode.m_position.x = minx + (j * xwidthspacing);
			tmpnode.m_position.y = 0.0f;
//			tmpnode.m_position.z = i * yheightspacing;
			tmpnode.m_position.z = maxy - (i * yheightspacing);
			int result = AddNode(tmpnode);
		}
	}
	for (int k = 0; k < GetNumTotalNodes(); k++)
	{
		navGraphEdge tmpedge;
		std::list<navGraphEdge> tmpedgelist;
		D3DXVECTOR3 tovec;
		D3DXVECTOR3 frvec = m_nodeVector[k].m_position;
		if (IsValidNeighbor(m_nodeVector[k].m_gridX-1,m_nodeVector[k].m_gridY,width,height))
		{
			//Add edge to "west" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = k - 1;
			tovec = m_nodeVector[k -1].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.0;
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}
		if (IsValidNeighbor(m_nodeVector[k].m_gridX-1,m_nodeVector[k].m_gridY-1,width,height))
		{
			//Add edge to "northwest" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = (k - width) - 1;
			tovec = m_nodeVector[(k - width) - 1].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.4;
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}
		if (IsValidNeighbor(m_nodeVector[k].m_gridX,m_nodeVector[k].m_gridY-1,width,height))
		{
			//Add edge to "north" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = (k - width);
			tovec = m_nodeVector[k - width].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.0;
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}
		if (IsValidNeighbor(m_nodeVector[k].m_gridX+1,m_nodeVector[k].m_gridY-1,width,height))
		{
			//Add edge to "northeast" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = (k - width) + 1;
			tovec = m_nodeVector[(k - width) +1].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.4;
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}
		if (IsValidNeighbor(m_nodeVector[k].m_gridX+1,m_nodeVector[k].m_gridY,width,height))
		{
			//Add edge to "east" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = k + 1;
			tovec = m_nodeVector[k +1].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.0;
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}
		if (IsValidNeighbor(m_nodeVector[k].m_gridX+1,m_nodeVector[k].m_gridY+1,width,height))
		{
			//Add edge to "southeast" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = (k + width) + 1;
			tovec = m_nodeVector[(k + width) + 1].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.4;
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}

		if (IsValidNeighbor(m_nodeVector[k].m_gridX,m_nodeVector[k].m_gridY+1,width,height))
		{
			//Add edge to "south" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = k + width;
			tovec = m_nodeVector[k + width].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.0;
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}
		if (IsValidNeighbor(m_nodeVector[k].m_gridX-1,m_nodeVector[k].m_gridY+1,width,height))
		{
			//Add edge to "southwest" neighbor
			tmpedge.m_from = k;
			tmpedge.m_to = (k + width) - 1;
			tovec = m_nodeVector[(k + width) -1].m_position;
			tmpedge.m_cost = D3DXVec3LengthSq(&(tovec - frvec));
//			tmpedge.m_cost = 1.4; //Change
			AddEdge(tmpedge);
			//Draw edge lines for debug
			if (m_debugMode)
			{
				//CGraphicsCore::Instance()->AddLine(&frvec,&tovec,1,D3DCOLOR_XRGB(200,0,64));
			}
		}
		int test = 0;
	}
}

bool NavGraph::Initialize(int width, int height, float xwidthspacing, float yheightspacing, bool debug)
{
	if (m_pInstance != NULL)
	{
		m_pInstance = new NavGraph(width,height,xwidthspacing,yheightspacing,debug);
	}
	else 
	{
		delete m_pInstance;
		m_pInstance = new NavGraph(width,height,xwidthspacing,yheightspacing,debug);
	}
	return true;
}

NavGraph* NavGraph::Instance()
{
	return m_pInstance;
}

int NavGraph::GetNumTotalNodes()
{
	return m_nodeVector.size();
}

int NavGraph::GetNumActiveNodes()
{
	int counter = 0;
	std::vector<navGraphNode>::iterator it = m_nodeVector.begin();
	while (it != m_nodeVector.end())
	{
		if (it->m_ID == -1)
		{
			counter++;
		}
		++it;
	}
	return counter;
}

int NavGraph::GetNextID()
{
	return m_nextNodeID;
}

int NavGraph::GetNumEdges()
{
	int counter = 0;
	std::vector<EdgeList>::iterator it = m_edgesVector.begin();
	while (it != m_edgesVector.end())
	{
		counter += it->size();
	}
	++it;
	return counter;
}

bool NavGraph::EdgeExists(int from, int to)
{
	if (IsNodeActive(from) && IsNodeActive(to))
	{
		std::list<navGraphEdge>::iterator it = m_edgesVector[from].begin();
		while (it != m_edgesVector[from].end())
		{
			if (it->m_to == to)
			{
				return true;
			}
			++it;
		}
		return false;
	}
	else
	{
		return false;
	}
} 

bool NavGraph::IsNodeActive(int nodeid)
{
	if (nodeid >= m_nextNodeID)
	{
		return false;
	}
	else if (m_nodeVector[nodeid].m_ID == -1)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool NavGraph::IsEmpty()
{
	return m_nodeVector.empty();
}

int NavGraph::AddNode(navGraphNode newnode)
{
	if (newnode.m_ID < (int)m_nodeVector.size())
	{
		//Error Attempting to add a node with ID that already exists
		return m_nextNodeID;
	}
	else
	{
		assert(newnode.m_ID == m_nextNodeID && "INVALID NODE INDEX");
		EdgeList newEmptyEdgeList;
		newEmptyEdgeList.clear();
		m_nodeVector.push_back(newnode);
		m_edgesVector.push_back(newEmptyEdgeList);
	}
	return m_nextNodeID++;
}

void NavGraph::AddEdge(navGraphEdge newedge)
{
	assert((newedge.m_from < m_nextNodeID) && (newedge.m_to < m_nextNodeID) &&
		"INVALID EDGE");
	if ((IsNodeActive(newedge.m_from) && IsNodeActive(newedge.m_to)))
	{
		if (!(EdgeExists(newedge.m_from, newedge.m_to)))
		{
			m_edgesVector[newedge.m_from].push_back(newedge);
			if (!(EdgeExists(newedge.m_to,newedge.m_from)))
			{
				//Add the reverse edge
				navGraphEdge reverse;
				reverse.m_from = newedge.m_to;
				reverse.m_to = newedge.m_from;
				reverse.m_cost = newedge.m_cost;
				m_edgesVector[newedge.m_to].push_back(reverse);
			}
		}
	}
}

navGraphNode& NavGraph::GetNode(int index)
{
	return m_nodeVector[index];
}

navGraphEdge& NavGraph::GetEdge(int from, int to)
{
	std::list<navGraphEdge>::iterator it = m_edgesVector[from].begin();
	while (it != m_edgesVector[from].end())
	{
		if (it->m_to == to)
		{
			return (*it);
		}
		++it;
	}
	assert (0 && "EDGE DOES NOT EXIST");
	return (*it);
}

void NavGraph::RemoveNode(int nodeID)
{
	assert(nodeID < (int)m_nodeVector.size() && "INVALID NODE INDEX");
	m_nodeVector[nodeID].m_ID = -1;
	
	std::list<navGraphEdge>::iterator it = m_edgesVector[nodeID].begin();
	while (it != m_edgesVector[nodeID].end())
	{
		std::list<navGraphEdge>::iterator it2 = m_edgesVector[it->m_to].begin();
		while (it2 != m_edgesVector[it->m_to].end())
		{
			if (it2->m_to == nodeID)
			{
				it2 = m_edgesVector[it->m_to].erase(it2);
				break;
			}
			++it2;
		}
		++it;
	}
	m_edgesVector[nodeID].clear();
}

void NavGraph::RemoveEdge(int from, int to)
{
	assert((from < (int)m_nodeVector.size()) && (to < (int)m_nodeVector.size()) &&
		"INVALID NODE INDEX");

	std::list<navGraphEdge>::iterator it = m_edgesVector[to].begin();
	while (it != m_edgesVector[to].end())
	{
		if (it->m_to == from)
		{
			it = m_edgesVector[to].erase(it);
			break;
		}
		++it;
	}
	it = m_edgesVector[from].begin();
	while (it != m_edgesVector[from].end())
	{
		if (it->m_to == to)
		{
			it = m_edgesVector[from].erase(it);
			break;
		}
		++it;
	}
}

D3DXVECTOR3 NavGraph::GetNodeWorldCoords(int nodeID)
{
	return m_nodeVector[nodeID].m_position;
}

void NavGraph::ClearNavGraph()
{
	m_nextNodeID = 0;
	m_nodeVector.clear();
	m_edgesVector.clear();
}

int NavGraph::GetClosestNodeToPosition(D3DXVECTOR3 pos)
{
	int bestNode = -1;
	double bestDistance = DBL_MAX;
	D3DXVECTOR3 calcdist;

	double calcdistdbl;
	int nWidth = m_numNodesWide;
	int startingnode = (int((m_upperLeft.z - pos.z)/ m_yHeightSpacing) * nWidth) +
						int((pos.x - m_upperLeft.x)/ m_xWidthSpacing);

	if (IsNodeActive(startingnode))
	{
		bestNode = startingnode;
		calcdist = pos - m_nodeVector[startingnode].m_position;
		bestDistance = D3DXVec3LengthSq(&(calcdist));
	}
	if (IsNodeActive(startingnode + 1))
	{
		calcdist = pos - m_nodeVector[startingnode+1].m_position;
		calcdistdbl = D3DXVec3LengthSq(&(calcdist));
		if (calcdistdbl < bestDistance)
		{
			bestNode = startingnode + 1;
			bestDistance = calcdistdbl;
		}
	}
	if (IsNodeActive(startingnode + nWidth))
	{
		calcdist = pos - m_nodeVector[startingnode + nWidth].m_position;
		calcdistdbl = D3DXVec3LengthSq(&(calcdist));
		if (calcdistdbl < bestDistance)
		{
			bestNode = startingnode + nWidth;
			bestDistance = calcdistdbl;
		}
	}
	if (IsNodeActive(startingnode + nWidth + 1))
	{
		calcdist = pos - m_nodeVector[startingnode + nWidth + 1].m_position;
		calcdistdbl = D3DXVec3LengthSq(&(calcdist));
		if (calcdistdbl < bestDistance)
		{
			bestNode = startingnode + nWidth + 1;
			bestDistance = calcdistdbl;
		}
	}
	return bestNode;
}

int NavGraph::GetClosestNodeToPosition(D3DXVECTOR3 pos, bool includeinactives)
{
	if (!includeinactives)
	{
		return GetClosestNodeToPosition(pos);
	}
	int bestNode = -1;
	double bestDistance = DBL_MAX;
	D3DXVECTOR3 calcdist;
	double calcdistdbl;
	int nWidth = m_numNodesWide;
	int startingnode = (int((m_upperLeft.z - pos.z)/ m_yHeightSpacing) * nWidth) +
						int((pos.x - m_upperLeft.x)/ m_xWidthSpacing);
	if (startingnode >= m_nextNodeID)
	{
		return -1;
	}
	bestNode = startingnode;
	calcdist = pos - m_nodeVector[startingnode].m_position;
	bestDistance = D3DXVec3LengthSq(&(calcdist));
	if ((startingnode+1) < m_nextNodeID)
	{
		calcdist = pos - m_nodeVector[startingnode+1].m_position;
		calcdistdbl = D3DXVec3LengthSq(&(calcdist));
		if (calcdistdbl < bestDistance)
		{
			bestNode = startingnode + 1;
			bestDistance = calcdistdbl;
		}
	}
	if ((startingnode + nWidth) < m_nextNodeID)
	{
		calcdist = pos - m_nodeVector[startingnode + nWidth].m_position;
		calcdistdbl = D3DXVec3LengthSq(&(calcdist));
		if (calcdistdbl < bestDistance)
		{
			bestNode = startingnode + nWidth;
			bestDistance = calcdistdbl;
		}
	}
	if ((startingnode + nWidth + 1) < m_nextNodeID)
	{
		calcdist = pos - m_nodeVector[startingnode + nWidth + 1].m_position;
		calcdistdbl = D3DXVec3LengthSq(&(calcdist));
		if (calcdistdbl < bestDistance)
		{
			bestNode = startingnode + nWidth + 1;
			bestDistance = calcdistdbl;
		}
	}
	return bestNode;
}

void NavGraph::WriteTo(Serializer* destination)
{
	std::string str = "";

	//graph's own
	destination->WriteParameter(str, m_nextNodeID);
	destination->WriteParameter(str, m_numNodesWide);
	destination->WriteParameter(str, m_numNodesTall);
	destination->WriteParameter(str, m_xWidthSpacing);
	destination->WriteParameter(str, m_yHeightSpacing);
	destination->WriteParameter(str, m_upperLeft);

	//nodes
	destination->WriteNumberOfElements(m_nodeVector.size());
	for(std::vector<navGraphNode>::iterator it = m_nodeVector.begin();
		it != m_nodeVector.end(); ++it)
	{
		it->WriteTo(destination);
	}

	//edges
	destination->WriteNumberOfElements(m_edgesVector.size());
	for(std::vector<EdgeList>::iterator it = m_edgesVector.begin();
		it != m_edgesVector.end(); ++it)
	{
		destination->WriteNumberOfElements(it->size());
		for(std::list<navGraphEdge>::iterator jt = it->begin();
			jt != it->end(); ++jt)
		{
			jt->WriteTo(destination);
		}
	}
}

void NavGraph::ReadFrom(Deserializer* source)
{//do you have some sort of "clear graph" function??

	std::string str = "";
	
	//graph's own
	source->ReadParameter(str, m_nextNodeID);
	source->ReadParameter(str, m_numNodesWide);
	source->ReadParameter(str, m_numNodesTall);
	source->ReadParameter(str, m_xWidthSpacing);
	source->ReadParameter(str, m_yHeightSpacing);
	source->ReadParameter(str, m_upperLeft);

	//nodes
	int numNodes = source->ReadNumberOfElements();
	m_nodeVector.clear();
	m_nodeVector.resize(numNodes);
	for(int i = 0; i < numNodes; i++)
	{
		m_nodeVector[i].ReadFrom(source);
	}

	//edges
	int numEdgeLists = source->ReadNumberOfElements();
	m_edgesVector.clear();
	m_edgesVector.resize(numEdgeLists);
	for(int i = 0; i < numEdgeLists; i++)
	{

		int numEdges = source->ReadNumberOfElements();
		m_edgesVector[i].clear();
		for(int j = 0; j < numEdges; j++)
		{
			navGraphEdge edge;
			edge.ReadFrom(source);
			m_edgesVector[i].push_back(edge);
		}

	}
}