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

#include "pythonlab/pygeometry.h"
#include "pythonlab/pythonengine_agros.h"

#include "sceneview_common.h"
#include "sceneview_geometry.h"
#include "sceneview_post2d.h"
#include "sceneview_post3d.h"
#include "scenenode.h"
#include "sceneedge.h"
#include "scenelabel.h"

void PyGeometry::activate()
{
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->actSceneModePreprocessor->trigger();
}

void PyGeometry::addNode(double x, double y)
{
    Agros2D::scene()->addNode(new SceneNode(Point(x, y)));
}

void PyGeometry::addEdge(double x1, double y1, double x2, double y2, double angle, map<char*, int> refinements, map<char*, char*> boundaries)
{
    // nodes
    SceneNode *nodeStart = Agros2D::scene()->addNode(new SceneNode(Point(x1, y1)));
    SceneNode *nodeEnd = Agros2D::scene()->addNode(new SceneNode(Point(x2, y2)));

    // angle
    if (angle > 90.0 || angle < 0.0)
        throw out_of_range(QObject::tr("Angle '%1' is out of range.").arg(angle).toStdString());

    SceneEdge *sceneEdge = new SceneEdge(nodeStart, nodeEnd, angle);

    // boundaries
    for (map<char*, char*>::iterator i = boundaries.begin(); i != boundaries.end(); ++i)
    {
        if (!Agros2D::problem()->hasField(QString((*i).first)))
        {
            delete sceneEdge;
            throw invalid_argument(QObject::tr("Invalid field id '%1'.").arg(QString((*i).first)).toStdString());
        }

        bool assigned = false;
        foreach (SceneBoundary *sceneBoundary, Agros2D::scene()->boundaries->filter(Agros2D::problem()->fieldInfo(QString((*i).first))).items())
        {
            if ((sceneBoundary->fieldId() == QString((*i).first)) && (sceneBoundary->name() == QString((*i).second)))
            {
                assigned = true;
                sceneEdge->addMarker(sceneBoundary);
                break;
            }
        }

        if (!assigned)
        {
            delete sceneEdge;
            throw invalid_argument(QObject::tr("Boundary condition '%1' doesn't exists.").arg(QString((*i).second)).toStdString());
        }
    }

    Agros2D::scene()->addEdge(sceneEdge);

    // refinements
    setMeshRefinementOnEdge(sceneEdge, refinements);
}

void PyGeometry::addEdgeByNodes(int nodeStartIndex, int nodeEndIndex, double angle, map<char *, int> refinements, map<char*, char*> boundaries)
{
    // nodes
    if (angle > 90.0 || angle < 0.0)
        throw out_of_range(QObject::tr("Angle '%1' is out of range.").arg(angle).toStdString());

    if (Agros2D::scene()->nodes->isEmpty())
        throw out_of_range(QObject::tr("Geometry does not contain nodes.").toStdString());

    if (nodeStartIndex > (Agros2D::scene()->nodes->length() - 1) || nodeStartIndex < 0)
        throw out_of_range(QObject::tr("Node with index '%1' does not exist.").arg(nodeStartIndex).toStdString());
    if (nodeEndIndex > (Agros2D::scene()->nodes->length() - 1) || nodeEndIndex < 0)
        throw out_of_range(QObject::tr("Node with index '%1' does not exist.").arg(nodeEndIndex).toStdString());

    SceneNode *nodeStart = Agros2D::scene()->nodes->at(nodeStartIndex);
    SceneNode *nodeEnd = Agros2D::scene()->nodes->at(nodeEndIndex);

    SceneEdge *sceneEdge = new SceneEdge(nodeStart, nodeEnd, angle);

    // boundaries
    for (map<char*, char*>::iterator i = boundaries.begin(); i != boundaries.end(); ++i)
    {
        if (!Agros2D::problem()->hasField(QString((*i).first)))
        {
            delete sceneEdge;
            throw invalid_argument(QObject::tr("Invalid field id '%1'.").arg(QString((*i).first)).toStdString());
        }

        bool assigned = false;
        foreach (SceneBoundary *sceneBoundary, Agros2D::scene()->boundaries->filter(Agros2D::problem()->fieldInfo(QString((*i).first))).items())
        {
            if ((sceneBoundary->fieldId() == QString((*i).first)) && (sceneBoundary->name() == QString((*i).second)))
            {
                assigned = true;
                sceneEdge->addMarker(sceneBoundary);
                break;
            }
        }

        if (!assigned)
        {
            delete sceneEdge;
            throw invalid_argument(QObject::tr("Boundary condition '%1' doesn't exists.").arg(QString((*i).second)).toStdString());
        }
    }

    Agros2D::scene()->addEdge(sceneEdge);

    // refinements
    setMeshRefinementOnEdge(sceneEdge, refinements);
}

void PyGeometry::setMeshRefinementOnEdge(SceneEdge *edge, map<char *, int> refinements)
{
    for (map<char*, int>::iterator i = refinements.begin(); i != refinements.end(); ++i)
    {
        if (!Agros2D::problem()->hasField(QString((*i).first)))
            throw invalid_argument(QObject::tr("Invalid field id '%1'.").arg(QString((*i).first)).toStdString());

        if (((*i).second < 0) || ((*i).second > 10))
            throw out_of_range(QObject::tr("Number of refinements '%1' is out of range (0 - 10).").arg((*i).second).toStdString());

        Agros2D::problem()->fieldInfo(QString((*i).first))->setEdgeRefinement(edge, (*i).second);
    }
}

void PyGeometry::addLabel(double x, double y, double area, map<char *, int> refinements, map<char *, int> orders, map<char *, char *> materials)
{
    if (area < 0.0)
        throw out_of_range(QObject::tr("Area must be positive.").toStdString());

    // TODO: (Franta) if (order < 0 || order > 10) throw out_of_range(QObject::tr("Polynomial order is out of range (0 - 10).").toStdString());

    SceneLabel *sceneLabel = new SceneLabel(Point(x, y), area);

    // materials
    for( map<char*, char*>::iterator i = materials.begin(); i != materials.end(); ++i)
    {
        if (!Agros2D::problem()->hasField(QString((*i).first)))
        {
            delete sceneLabel;
            throw invalid_argument(QObject::tr("Invalid field id '%1'.").arg(QString((*i).first)).toStdString());
        }

        if (QString((*i).second) != "none")
        {

            bool assigned = false;
            foreach (SceneMaterial *sceneMaterial, Agros2D::scene()->materials->filter(Agros2D::problem()->fieldInfo(QString((*i).first))).items())
            {
                if ((sceneMaterial->fieldId() == QString((*i).first)) && (sceneMaterial->name() == QString((*i).second)))
                {
                    assigned = true;
                    sceneLabel->addMarker(sceneMaterial);
                    break;
                }
            }

            if (!assigned)
            {
                delete sceneLabel;
                throw invalid_argument(QObject::tr("Material '%1' doesn't exists.").arg(QString((*i).second)).toStdString());
            }
        }
    }

    Agros2D::scene()->addLabel(sceneLabel);

    // refinements
    for (map<char*, int>::iterator i = refinements.begin(); i != refinements.end(); ++i)
    {
        if (!Agros2D::problem()->hasField(QString((*i).first)))
            throw invalid_argument(QObject::tr("Invalid field id '%1'.").arg(QString((*i).first)).toStdString());

        if (((*i).second < 0) || ((*i).second > 10))
            throw out_of_range(QObject::tr("Number of refinements '%1' is out of range (0 - 10).").arg((*i).second).toStdString());

        Agros2D::problem()->fieldInfo(QString((*i).first))->setLabelRefinement(sceneLabel, (*i).second);
    }

    // orders
    for (map<char*, int>::iterator i = orders.begin(); i != orders.end(); ++i)
    {
        if (!Agros2D::problem()->hasField(QString((*i).first)))
            throw invalid_argument(QObject::tr("Invalid field id '%1'.").arg(QString((*i).first)).toStdString());

        if (((*i).second < 1) || ((*i).second > 10))
            throw out_of_range(QObject::tr("Polynomial order '%1' is out of range (1 - 10).").arg((*i).second).toStdString());

        Agros2D::problem()->fieldInfo(QString((*i).first))->setLabelPolynomialOrder(sceneLabel, (*i).second);
    }
}

void PyGeometry::removeNode(int index)
{
    if (index < 0 || index >= Agros2D::scene()->nodes->length())
        throw out_of_range(QObject::tr("Index '%1' is out of range.").arg(index).toStdString());

    Agros2D::scene()->removeNode(Agros2D::scene()->nodes->at(index));
}

void PyGeometry::removeEdge(int index)
{
    if (index < 0 || index >= Agros2D::scene()->edges->length())
        throw out_of_range(QObject::tr("Index '%1' is out of range.").arg(index).toStdString());

    Agros2D::scene()->removeEdge(Agros2D::scene()->edges->at(index));
}

void PyGeometry::removeLabel(int index)
{
    if (index < 0 || index >= Agros2D::scene()->labels->length())
        throw out_of_range(QObject::tr("Index '%1' is out of range.").arg(index).toStdString());

    Agros2D::scene()->removeLabel(Agros2D::scene()->labels->at(index));
}

void PyGeometry::removeNodePoint(double x, double y)
{
    Agros2D::scene()->nodes->remove(Agros2D::scene()->getNode(Point(x, y)));
}

void PyGeometry::removeEdgePoint(double x1, double y1, double x2, double y2, double angle)
{
    Agros2D::scene()->edges->remove(Agros2D::scene()->getEdge(Point(x1, y1), Point(x2, y2), angle));
}

void PyGeometry::removeLabelPoint(double x, double y)
{
    Agros2D::scene()->labels->remove(Agros2D::scene()->getLabel(Point(x, y)));
}

void PyGeometry::selectNodes(vector<int> nodes)
{
    Agros2D::scene()->selectNone();

    if (!nodes.empty())
    {
        for (vector<int>::iterator it = nodes.begin(); it != nodes.end(); ++it)
        {
            if ((*it >= 0) && (*it < Agros2D::scene()->nodes->length()))
                Agros2D::scene()->nodes->at(*it)->setSelected(true);
            else
                throw out_of_range(QObject::tr("Node index must be between 0 and '%1'.").arg(Agros2D::scene()->nodes->length()-1).toStdString());
        }
    }
    else
    {
        Agros2D::scene()->selectAll(SceneGeometryMode_OperateOnNodes);
    }

    Agros2D::scene()->invalidate();
}

void PyGeometry::selectEdges(vector<int> edges)
{
    Agros2D::scene()->selectNone();

    if (!edges.empty())
    {
        for (vector<int>::iterator it = edges.begin(); it != edges.end(); ++it)
        {
            if ((*it >= 0) && (*it < Agros2D::scene()->edges->length()))
                Agros2D::scene()->edges->at(*it)->setSelected(true);
            else
                throw out_of_range(QObject::tr("Edge index must be between 0 and '%1'.").arg(Agros2D::scene()->edges->length()-1).toStdString());
        }
    }
    else
    {
        Agros2D::scene()->selectAll(SceneGeometryMode_OperateOnEdges);
    }

    Agros2D::scene()->invalidate();
}

void PyGeometry::selectLabels(vector<int> labels)
{
    Agros2D::scene()->selectNone();

    if (!labels.empty())
    {
        for (vector<int>::iterator it = labels.begin(); it != labels.end(); ++it)
        {
            if ((*it >= 0) && (*it < Agros2D::scene()->labels->length()))
                Agros2D::scene()->labels->at(*it)->setSelected(true);
            else
                throw out_of_range(QObject::tr("Label index must be between 0 and '%1'.").arg(Agros2D::scene()->labels->length()-1).toStdString());
        }
    }
    else
    {
        Agros2D::scene()->selectAll(SceneGeometryMode_OperateOnLabels);
    }

    Agros2D::scene()->invalidate();
}

void PyGeometry::selectNodePoint(double x, double y)
{
    SceneNode *node = SceneNode::findClosestNode(Point(x, y));
    if (node)
    {
        node->setSelected(true);
        // sceneView()->doInvalidated();
    }
}

void PyGeometry::selectEdgePoint(double x, double y)
{
    SceneEdge *edge = SceneEdge::findClosestEdge(Point(x, y));
    if (edge)
    {
        edge->setSelected(true);
        // sceneView()->doInvalidated();
    }
}

void PyGeometry::selectLabelPoint(double x, double y)
{
    SceneLabel *label = SceneLabel::findClosestLabel(Point(x, y));
    if (label)
    {
        label->setSelected(true);
        // sceneView()->doInvalidated();
    }
}

void PyGeometry::selectNone()
{
    Agros2D::scene()->selectNone();
    Agros2D::scene()->invalidate();
}

void PyGeometry::moveSelection(double dx, double dy, bool copy)
{
    Agros2D::scene()->transformTranslate(Point(dx, dy), copy);
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->refresh();
}

void PyGeometry::rotateSelection(double x, double y, double angle, bool copy)
{
    Agros2D::scene()->transformRotate(Point(x, y), angle, copy);
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->refresh();
}

void PyGeometry::scaleSelection(double x, double y, double scale, bool copy)
{
    Agros2D::scene()->transformScale(Point(x, y), scale, copy);
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->refresh();
}

void PyGeometry::removeSelection()
{
    Agros2D::scene()->deleteSelected();
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->refresh();
}

void PyGeometry::mesh()
{
    // trigger preprocessor
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->actSceneModePreprocessor->trigger();

    Agros2D::problem()->mesh();
    if (Agros2D::problem()->isMeshed())
    {
        // trigger mesh
        if (!silentMode())
            currentPythonEngineAgros()->sceneViewMesh()->actSceneModeMesh->trigger();
    }
}

const char *PyGeometry::meshFileName()
{
    if (Agros2D::problem()->isMeshed())
        return const_cast<char*>(QString(tempProblemFileName() + ".mesh").toStdString().c_str());
    else
        throw invalid_argument(QObject::tr("Problem is not meshed.").toStdString());
}

void PyGeometry::zoomBestFit()
{
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->doZoomBestFit();
}

void PyGeometry::zoomIn()
{
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->doZoomIn();
}

void PyGeometry::zoomOut()
{
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->doZoomOut();
}

void PyGeometry::zoomRegion(double x1, double y1, double x2, double y2)
{
    if (!silentMode())
        currentPythonEngineAgros()->sceneViewPreprocessor()->doZoomRegion(Point(x1, y1), Point(x2, y2));
}
