// This file is part of Agros2D.
//
// Agros2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Agros2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Agros2D.  If not, see <http://www.gnu.org/licenses/>.
//
// hp-FEM group (http://hpfem.org/)
// University of Nevada, Reno (UNR) and University of West Bohemia, Pilsen
// Email: agros2d@googlegroups.com, home page: http://hpfem.org/agros2d/

#ifndef PYTHONLABGEOMETRY_H
#define PYTHONLABGEOMETRY_H

#include "util.h"
#include "util/global.h"

#include "scene.h"
#include "scenenode.h"
#include "sceneedge.h"
#include "scenelabel.h"

class SceneViewPreprocessor;

class PyGeometry
{
    public:
        PyGeometry() {}
        ~PyGeometry() {}

        void activate();

        // add operations
        int addNode(double x, double y);
        int addEdge(double x1, double y1, double x2, double y2, double angle, map<std::string, int> refinements, map<std::string, std::string> boundaries);
        int addEdgeByNodes(int nodeStartIndex, int nodeEndIndex, double angle, map<std::string, int> refinements, map<std::string, std::string> boundaries);
        int addLabel(double x, double y, double area, map<std::string, int> refinements, map<std::string, int> orders, map<std::string, std::string> materials);

        inline int nodesCount() { return Agros2D::scene()->nodes->count(); }
        inline int edgesCount() { return Agros2D::scene()->edges->count(); }
        inline int labelsCount() { return Agros2D::scene()->labels->count(); }

        // modify operations
        void modifyEdge(int index, double angle, map<std::string, int> refinements, map<std::string, std::string> boundaries);
        void modifyLabel(int index, double area, map<std::string, int> refinements, map<std::string, int> orders, map<std::string, std::string> materials);

        // remove operations
        void removeNodes(vector<int> nodes);
        void removeEdges(vector<int> edges);
        void removeLabels(vector<int> labels);

        // select operations
        void selectNodes(vector<int> nodes);
        void selectEdges(vector<int> edges);
        void selectLabels(vector<int> labels);

        void selectNodeByPoint(double x, double y);
        void selectEdgeByPoint(double x, double y);
        void selectLabelByPoint(double x, double y);

        void selectNone();

        // transform operations
        void moveSelection(double dx, double dy, bool copy);
        void rotateSelection(double x, double y, double angle, bool copy);
        void scaleSelection(double x, double y, double scale, bool copy);
        void removeSelection();

private:
        void testAngle(double angle);
        void setBoundaries(SceneEdge *edge, map<std::string, std::string> boundaries);
        void setMaterials(SceneLabel *label, map<std::string, std::string> materials);
        void setRefinementsOnEdge(SceneEdge *edge, map<std::string, int> refinements);
        void setRefinements(SceneLabel *label, map<std::string, int> refinements);
        void setPolynomialOrders(SceneLabel *label, map<std::string, int> orders);
};

#endif // PYTHONLABGEOMETRY_H