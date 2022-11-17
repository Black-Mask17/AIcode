#include "Graph.h"

Graph::Graph() 
{

}

bool Graph::OnCreate(vector<Node*> nodes_) {
	// given a list of nodes
	// initialize a matrix of costs
	// with 0.0 weights
	int numNodes = nodes_.size();
	cost.resize(numNodes);

	for (int i = 0; i < numNodes; i++)
	{
		// add the nodes to internal List
		if ( i != nodes_[i]->getLabel()) 
		{
			return false;
		}
		node[i] = nodes_[i];

		//set up the connections
		cost[i].resize(numNodes);
		for (int j = 0; j < numNodes; j++)
		{
			//initialize connections
			cost[i][j] = 0.0f;
		}
	}
	return true;
}

Graph::~Graph() 
{}

int Graph::numNodes() {
	return node.size();
	// return cost.size();
}

void Graph::addWeightConnection(int fromNode, int toNode, float weight) {
	cost[fromNode][toNode] = weight;
}

vector<int> Graph::neighbours(int fromNode) {

	vector<int> result = {};
	for (int j = 0; j < numNodes(); j++)
	{
		if (cost[fromNode][j] > 0.0f)
		{
			result.push_back(j);
		}
	}
	return result;
}

struct NodeAndPriority {
	int node;
	float priority;

	NodeAndPriority(int node_, float priority_) {

		node = node_;
		priority = priority_;
	}
};

struct ComparePriority
{
	bool operator()(NodeAndPriority const& lhs, NodeAndPriority const& rhs)
	{
		// make it a min queue
		return lhs.priority > rhs.priority;
	}
};

vector<int> Graph::Dijkstra(int startNode, int goalNode) {

	// declare helper variables
	float new_cost;
	int current ;

	// declare current NodeAndPriority

	NodeAndPriority* currentNodeAndPriority;
	currentNodeAndPriority = new NodeAndPriority(startNode, 0.0f);
	// set up priority queue for frontier of nodes
	priority_queue< NodeAndPriority, deque<NodeAndPriority>, ComparePriority > frontier;
	frontier.push(*currentNodeAndPriority);

	// track solution path
	vector<int> came_from = {};
	came_from.resize(numNodes());
	// store cost so far to reach a node

	map<int, float> cost_so_far;
	cost_so_far[startNode] = 0.0;

	// TODO implement the algorithm
	
	
	// start looping through the frontier
	while(!frontier.empty())
	{
		//get the node from the top of the frontier, put it in "current"
		// pop it off
		//if its the goal, then break out of the loop
		const NodeAndPriority* s = &frontier.top();
		if (s == NULL)
			continue;

		current = s->node;

		if (current == goalNode) {
			break;
		}
		
		// for the neighbours of current node
		for( int next : neighbours(current)) {
			// calculate new_cost
			// if neighbour is not in cost_so_far OR new_cost is lower
			new_cost = cost_so_far[current] + cost[current][next];
			map<int, float>::iterator it = cost_so_far.find(next);
			if (it != cost_so_far.end() || new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				float priority = new_cost;

				NodeAndPriority* newNode = new NodeAndPriority(next, priority);
				frontier.push(*newNode);
				came_from[next] = current;
			}

		}

		frontier.pop();
	}


	return came_from;
}