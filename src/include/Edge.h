#ifndef __EDGE_H__
#define __EDGE_H__

class Edge
{

private:
     // Artributos
     int id;
     float weightEdge;
     Edge *nexEdge;
     int origin;
     int destiny;

public:
     Edge(int id);               // Construtor
     Edge(int id, float weight); // Aresta com peso
     ~Edge();                    // Destrutor

     int getId();
     float getWeightEdge();
     Edge *getNextEdge();

     int getOrigin();
     int getDestiny();

     void setNextEdge(Edge *nexEdge);
     void setWeightEdge(int WeightEdge);

     void setOrigin(int origin);
     void setDestiny(int destiny);
};

#endif // __EDGE_H__