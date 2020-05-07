#include "ucgenleme.h"

Ucgenleme::Ucgenleme()
{

}



vector<Point> Ucgenleme::Ucgenle(QList<Nokta> veriler)
{


    vector<vector<Point>> ucgenlenecekVeri;

    vector<Point> outputTriangles;
    vector<Point> data;


    for(int i=0;i<veriler.size();i++)
    {
        data.push_back(Point(veriler[i].x,veriler[i].y));
    }

    ucgenlenecekVeri.push_back(data);

    vector<Point> boundingPolygon;


    clip2tri clip2tri;


    clip2tri.triangulate(ucgenlenecekVeri, outputTriangles, boundingPolygon);


    return outputTriangles;
}



