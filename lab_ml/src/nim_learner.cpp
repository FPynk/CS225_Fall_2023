/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "nim_learner.h"

#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : r_(time(0)), g_(true, true) {
    /* Your code goes here! */
    // iterate over the possible number of tokens
    for (unsigned tokens = 0; tokens <= startingTokens; ++tokens) {
        // create vertices for P1 and P2's turn
        Vertex p1 = "p1-" + std::to_string(tokens);
        Vertex p2 = "p2-" + std::to_string(tokens);
        g_.insertVertex(p1);
        g_.insertVertex(p2);

        // if tokens 0, game ends
        if (tokens == 0) continue;

        // create edges for legal moves (1/2 tokens)
        // check for move of 1 token
        if (tokens >= 1) {
            g_.insertEdge(p1, "p2-" + std::to_string(tokens - 1));
            g_.insertEdge(p2, "p1-" + std::to_string(tokens - 1));
            g_.setEdgeWeight(p1, "p2-" + std::to_string(tokens - 1), 0);
            g_.setEdgeWeight(p2, "p1-" + std::to_string(tokens - 1), 0);
        }

        // check for move of 2 tokens
        if (tokens >= 2) {
            g_.insertEdge(p1, "p2-" + std::to_string(tokens - 2));
            g_.insertEdge(p2, "p1-" + std::to_string(tokens - 2));
            g_.setEdgeWeight(p1, "p2-" + std::to_string(tokens - 2), 0);
            g_.setEdgeWeight(p2, "p1-" + std::to_string(tokens - 2), 0);
        }
    }

    // set starting vertex
    startingVertex_ = "p1-" + std::to_string(startingTokens);
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
    std::vector<Edge> path;
    Vertex currentVertex = startingVertex_; // initial state

    while (true) {
        // get adjacent vertices
        std::vector<Vertex> adjacentVertices = g_.getAdjacent(currentVertex); 
        if (adjacentVertices.empty()) {
            break; // end the game if none left
        }

        // randomly select adjacent vertex (next state)
        int randomIndex = r_.nextInt() % adjacentVertices.size();
        Vertex nextVertex = adjacentVertices[randomIndex];

        // get the edge between the current and next vertex
        Edge e = g_.getEdge(currentVertex, nextVertex);
        if (e.source == Graph::InvalidVertex || e.dest == Graph::InvalidVertex) {
            throw std::runtime_error("Invalid edge encountered in playRandomGame");
        }
        path.push_back(e); // add edge to the path

        currentVertex = nextVertex; // update current vertex for next iteration
    }

  return path;
}
/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
    /* Your code goes here! */
    if (path.empty()) return; 

    // determine the winner
    bool player1Wins = path.back().dest.substr(1, 2) == "2-0";
    std::cout << "Game Winner: Player " << (player1Wins ? "1" : "2") << std::endl;

    for (const Edge & edge : path) {
        // determine if P1 or P2 move
        bool isPlayer1Move = edge.source.substr(1, 1) == "1";

        int currentWeight = g_.getEdgeWeight(edge.source, edge.dest);

        std::cout << "Edge from " << edge.source << " to " << edge.dest;
        std::cout << " (Player " << (isPlayer1Move ? "1" : "2") << " move). Current weight: " << currentWeight;

        // update the weight, +1 winner, -1 loser
        if (isPlayer1Move == player1Wins) {
            g_.setEdgeWeight(edge.source, edge.dest, currentWeight + 1);
            std::cout << ". Updated weight: " << currentWeight + 1 << std::endl;
        } else {
            g_.setEdgeWeight(edge.source, edge.dest, currentWeight - 1);
            std::cout << ". Updated weight: " << currentWeight - 1 << std::endl;
        }
    }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
