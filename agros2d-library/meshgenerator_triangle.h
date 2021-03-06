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

#ifndef MESHGENERATOR_TRIANGLE_H
#define MESHGENERATOR_TRIANGLE_H

#include "util.h"
#include "meshgenerator.h"

extern "C"
{
#include "../3rdparty/triangle/triangle.h"
}

class MeshGeneratorTriangleExternal : public MeshGenerator
{
    Q_OBJECT

private slots:
    void meshTriangleError(QProcess::ProcessError error);
    void meshTriangleCreated(int exitCode);
    bool writeToTriangle();
    bool readTriangleMeshFormat();

public:
    MeshGeneratorTriangleExternal();

    virtual bool mesh();
};

class MeshGeneratorTriangle : public MeshGenerator
{
    Q_OBJECT

private slots:
    bool writeToTriangle();
    bool readTriangleMeshFormat();

public:
    MeshGeneratorTriangle();

    virtual bool mesh();

private:
    struct triangulateio triOut;
};


#endif //MESHGENERATOR_TRIANGLE_H
