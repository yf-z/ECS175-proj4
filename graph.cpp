#include "vertex.h"
#include "polygon.h"
#include "graph.h"

#include <cmath>

Graph::Graph() {
};

void Graph::initialization() {
    Vertex temp;
    Polygon poly;
    temp.x = -300;
    temp.y = -300;
    //vector <Vertex> v;
    //v.push_back(temp);
    
    poly.vertices.push_back(temp);
    polys.push_back(poly);
}

void Graph::printInfo(int i) {

        i--;    
        //cout << "ID: " << polys[i].id << endl;
        //cout << "Num of Vertices: " << polys[i].num_of_vertex << endl;

        for (int j = 0; j < polys[i].vertices.size(); j++) {
            cout << polys[i].vertices[j].x << ' ' << polys[i].vertices[j].y << ' ' << polys[i].vertices[j].z << endl;
        }

        // cout << "Num of connections: " << polys[i].num_of_edges << endl;
        // for (int k = 0; k < 6; k ++) {
        //     cout << polys[i].connections[k].x << ' ' << polys[i].connections[k].y << endl;
        // }

        // polys[i].printCentroid();
        cout << xMin << ' ' << xMax << ' ' << yMin <<  ' ' << yMax << endl;

}

void Graph::setXYZ() {
    for (int i = 0; i < polys.size(); i++) {
        for (int j = 0; j < polys[i].vertices.size(); j++) {
            int x;
            if (polys[i].vertices[j].x > 0)
                x = ceil(polys[i].vertices[j].x);
            else
                x = floor(polys[i].vertices[j].x);

            if (polys[i].vertices[j].x > xMax)
                xMax = x;
            if (polys[i].vertices[j].x < xMin)
                xMin = x;

            if (polys[i].vertices[j].y > 0)
                x = ceil(polys[i].vertices[j].y);
            else
                x = floor(polys[i].vertices[j].y);
            if (polys[i].vertices[j].y > yMax)
                yMax = x;
            if (polys[i].vertices[j].y < yMin)
                yMin = x;
    }
}

    cout << "xMin: " << xMin << endl;
    cout << "xMax: " << xMax << endl;
    cout << "yMin: " << yMin << endl;
    cout << "yMax: " << yMax << endl;
}

// void Graph::equal(Graph temp) {
//     polys.clear();

//     for (int i = 0; i < temp.polys.size(); i++) {
//         Polygon poly;
//         Vertex vertex;
//         Connection con;

//         poly.setId(temp.polys[i].id);
//         poly.num_of_vertex = temp.polys[i].num_of_vertex;
//         poly.num_of_edges = temp.polys[i].num_of_edges;

//         for (int j = 0; j < temp.polys[i].vertices.size(); j++) {
//             vertex.x = temp.polys[i].vertices[j].x;
//             vertex.y = temp.polys[i].vertices[j].y;
//             vertex.z = temp.polys[i].vertices[j].z;

//             poly.vertices.push_back(vertex);
//         }

//         for (int k = 0; k < temp.polys[i].connections.size(); k++) {
//             con.x = temp.polys[i].connections[k].x;
//             con.y = temp.polys[i].connections[k].y;

//             poly.connections.push_back(con);
//         }

//         polys.push_back(poly);

//     }

//     setXYZ();
// }

// void Graph::equalOne(Graph temp, int num) {
//     polys.clear();
    
//     int i = num-1;
//         Polygon poly;
//         Vertex vertex;
//         Connection con;

//         poly.setId(temp.polys[i].id);
//         poly.num_of_vertex = temp.polys[i].num_of_vertex;
//         poly.num_of_edges = temp.polys[i].num_of_edges;

//         for (int j = 0; j < temp.polys[i].vertices.size(); j++) {
//             vertex.x = temp.polys[i].vertices[j].x;
//             vertex.y = temp.polys[i].vertices[j].y;
//             vertex.z = temp.polys[i].vertices[j].z;

//             poly.vertices.push_back(vertex);
//         }

//         for (int k = 0; k < temp.polys[i].connections.size(); k++) {
//             con.x = temp.polys[i].connections[k].x;
//             con.y = temp.polys[i].connections[k].y;

//             poly.connections.push_back(con);
//         }

//         polys.push_back(poly);


//     setXYZ();
//}