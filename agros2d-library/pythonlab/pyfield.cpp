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

#include "pythonlab/pyfield.h"
#include "pythonlab/pythonengine_agros.h"

#include "hermes2d/plugin_interface.h"
#include "hermes2d/problem_config.h"
#include "hermes2d/solutionstore.h"

#include "scenemarker.h"
#include "sceneview_post2d.h"

PyField::PyField(char *fieldId)
{
    QMap<QString, QString> modules = Module::availableModules();

    if (modules.keys().contains(QString(fieldId)))
        if (Agros2D::problem()->hasField(QString(fieldId)))
        {
            m_fieldInfo = Agros2D::problem()->fieldInfo(fieldId);
        }
        else
        {
            try{
                m_fieldInfo = new FieldInfo(fieldId);
            }
            catch(AgrosPluginException& e)
            {
                throw invalid_argument(QObject::tr("Invalid field id. Plugin %1 cannot be loaded").arg(QString(fieldId)).toStdString());
            }

            Agros2D::problem()->addField(m_fieldInfo);
        }
    else
        throw invalid_argument(QObject::tr("Invalid field id. Valid keys: %1").arg(stringListToString(modules.keys())).toStdString());
}

void PyField::setAnalysisType(const char *analysisType)
{
    if (m_fieldInfo->analyses().contains(analysisTypeFromStringKey(QString(analysisType))))
    {
        m_fieldInfo->setAnalysisType(analysisTypeFromStringKey(QString(analysisType)));
    }
    else
    {
        QStringList list;
        foreach (AnalysisType analysis, m_fieldInfo->analyses().keys())
            list.append(analysisTypeToStringKey(analysis));

        throw invalid_argument(QObject::tr("Invalid argument. Valid keys: %1").arg(stringListToString(list)).toStdString());
    }
}

void PyField::setNumberOfRefinements(const int numberOfRefinements)
{
    if (numberOfRefinements >= 0 && numberOfRefinements <= 5)
        m_fieldInfo->setNumberOfRefinements(numberOfRefinements);
    else
        throw out_of_range(QObject::tr("Number of refinements is out of range (0 - 5).").toStdString());
}

void PyField::setPolynomialOrder(const int polynomialOrder)
{
    if (polynomialOrder > 0 && polynomialOrder <= 10)
        m_fieldInfo->setPolynomialOrder(polynomialOrder);
    else
        throw out_of_range(QObject::tr("Polynomial order is out of range (1 - 10).").toStdString());
}

void PyField::setLinearityType(const char *linearityType)
{
    if (linearityTypeStringKeys().contains(QString(linearityType)))
        m_fieldInfo->setLinearityType(linearityTypeFromStringKey(QString(linearityType)));
    else
        throw invalid_argument(QObject::tr("Invalid argument. Valid keys: %1").arg(stringListToString(linearityTypeStringKeys())).toStdString());
}

void PyField::setNonlinearTolerance(const double nonlinearTolerance)
{
    if (nonlinearTolerance > 0.0)
        m_fieldInfo->setNonlinearTolerance(nonlinearTolerance);
    else
        throw out_of_range(QObject::tr("Nonlinearity tolerance must be positive.").toStdString());
}

void PyField::setNonlinearSteps(const int nonlinearSteps)
{
    if (nonlinearSteps >= 1 && nonlinearSteps <= 100)
        m_fieldInfo->setNonlinearSteps(nonlinearSteps);
    else
        throw out_of_range(QObject::tr("Nonlinearity steps is out of range (1 - 100).").toStdString());
}

void PyField::setNewtonDampingCoeff(const double dampingCoeff)
{
    if (dampingCoeff > 0 && dampingCoeff <= 1)
        m_fieldInfo->setNewtonDampingCoeff(dampingCoeff);
    else
        throw out_of_range(QObject::tr("Newton damping coefficient is out of range (0 - 1).").toStdString());
}

void PyField::setNewtonAutomaticDamping(const bool automaticDamping)
{
    m_fieldInfo->setNewtonAutomaticDamping(automaticDamping);
}

void PyField::setNewtonAutomaticDampingCoeff(const double dampingCoeff)
{
    if (dampingCoeff > 0 && dampingCoeff <= 1)
        m_fieldInfo->setNewtonAutomaticDampingCoeff(dampingCoeff);
    else
        throw out_of_range(QObject::tr("Newton automatic damping coefficient is out of range (0 - 1).").toStdString());
}

void PyField::setNewtonDampingNumberToIncrease(const int dampingNumberToIncrease)
{
    if (dampingNumberToIncrease >= 1 && dampingNumberToIncrease <= 5)
        m_fieldInfo->setNewtonAutomaticDamping(dampingNumberToIncrease);
    else
        throw out_of_range(QObject::tr("Number of steps needed to increase the damping coefficient is out of range (1 - 5).").toStdString());
}

void PyField::setPicardAndersonAcceleration(const bool acceleration)
{
    m_fieldInfo->setPicardAndersonAcceleration(acceleration);
}

void PyField::setPicardAndersonBeta(const double beta)
{
    if (beta > 0 && beta <= 1)
        m_fieldInfo->setPicardAndersonBeta(beta);
    else
        throw out_of_range(QObject::tr("Anderson coefficient is out of range (0 - 1).").toStdString());
}

void PyField::setPicardAndersonNumberOfLastVectors(const int number)
{
    if (number >= 1 && number <= 5)
        m_fieldInfo->setPicardAndersonNumberOfLastVectors(number);
    else
        throw out_of_range(QObject::tr("Number of last vector is out of range (1 - 5).").toStdString());
}

void PyField::setAdaptivityType(const char *adaptivityType)
{
    if (adaptivityTypeStringKeys().contains(QString(adaptivityType)))
        m_fieldInfo->setAdaptivityType(adaptivityTypeFromStringKey(QString(adaptivityType)));
    else
        throw invalid_argument(QObject::tr("Invalid argument. Valid keys: %1").arg(stringListToString(adaptivityTypeStringKeys())).toStdString());
}

void PyField::setAdaptivityTolerance(const double adaptivityTolerance)
{
    if (adaptivityTolerance > 0.0)
        m_fieldInfo->setAdaptivityTolerance(adaptivityTolerance);
    else
        throw out_of_range(QObject::tr("Adaptivity tolerance must be positive.").toStdString());
}

void PyField::setAdaptivitySteps(const int adaptivitySteps)
{
    if (adaptivitySteps >= 1 && adaptivitySteps <= 100)
        m_fieldInfo->setAdaptivitySteps(adaptivitySteps);
    else
        throw out_of_range(QObject::tr("Adaptivity steps is out of range (1 - 100).").toStdString());
}

void PyField::setAdaptivityBackSteps(const int adaptivityBackSteps)
{
    if (adaptivityBackSteps >= 0 && adaptivityBackSteps <= 100)
        m_fieldInfo->setAdaptivityBackSteps(adaptivityBackSteps);
    else
        throw out_of_range(QObject::tr("Adaptivity back steps is out of range (0 - 100).").toStdString());
}

void PyField::setAdaptivityRedoneEach(const int adaptivityRedoneEach)
{
    if (adaptivityRedoneEach >= 1 && adaptivityRedoneEach <= 100)
        m_fieldInfo->setAdaptivityRedoneEach(adaptivityRedoneEach);
    else
        throw out_of_range(QObject::tr("Adaptivity back steps is out of range (0 - 100).").toStdString());
}

void PyField::setInitialCondition(const double initialCondition)
{
    m_fieldInfo->setInitialCondition(initialCondition);
}

void PyField::setTimeSkip(const double timeSkip)
{
    if (timeSkip >= 0)
        m_fieldInfo->setTimeSkip(timeSkip);
    else
        throw out_of_range(QObject::tr("Time skip must be greater than or equal to zero.").toStdString());
}

void PyField::addBoundary(const char *name, const char *type, map<char*, double> parameters, map<char *, char *> expressions)
{
    // check boundaries with same name
    foreach (SceneBoundary *boundary, Agros2D::scene()->boundaries->filter(m_fieldInfo->fieldId()).items())
    {
        if (boundary->name() == name)
            throw invalid_argument(QObject::tr("Boundary condition '%1' already exists.").arg(QString(name)).toStdString());
    }

    if (!m_fieldInfo->boundaryTypeContains(QString(type)))
        throw invalid_argument(QObject::tr("Wrong boundary type '%1'.").arg(type).toStdString());

    Module::BoundaryType boundaryType = m_fieldInfo->boundaryType(QString(type));

    // browse boundary parameters
    QHash<QString, Value> values;
    for (map<char*, double>::iterator i = parameters.begin(); i != parameters.end(); ++i)
    {
        bool assigned = false;
        foreach (Module::BoundaryTypeVariable variable, boundaryType.variables())
        {
            if (variable.id() == QString((*i).first))
            {
                assigned = true;
                if (expressions.count((*i).first) == 0)
                    values[variable.id()] = Value((*i).second);
                else
                    values[variable.id()] = Value(expressions[(*i).first]);
                break;
            }
        }

        if (!assigned)
            throw invalid_argument(QObject::tr("Wrong parameter '%1'.").arg(QString((*i).first)).toStdString());
    }

    Agros2D::scene()->addBoundary(new SceneBoundary(m_fieldInfo, name, type, values));
}

void PyField::modifyBoundary(const char *name, const char *type, map<char*, double> parameters, map<char *, char *> expressions)
{
    SceneBoundary *sceneBoundary = Agros2D::scene()->getBoundary(m_fieldInfo, QString(name));
    if (sceneBoundary == NULL)
        throw invalid_argument(QObject::tr("Boundary condition '%1' doesn't exists.").arg(name).toStdString());

    // browse boundary types
    foreach (Module::BoundaryType boundaryType, sceneBoundary->fieldInfo()->boundaryTypes())
    {
        if (QString(type) == boundaryType.id())
        {
            sceneBoundary->setType(QString(type));
            break;
        }
        else
            throw invalid_argument(QObject::tr("Wrong boundary type '%1'.").arg(type).toStdString());
    }

    // browse boundary parameters
    Module::BoundaryType boundaryType = m_fieldInfo->boundaryType(sceneBoundary->type());
    for (map<char*, double>::iterator i = parameters.begin(); i != parameters.end(); ++i)
    {
        bool assigned = false;
        foreach (Module::BoundaryTypeVariable variable, boundaryType.variables())
        {
            if (variable.id() == QString((*i).first))
            {
                assigned = true;
                if (expressions.count((*i).first) == 0)
                    sceneBoundary->setValue(QString((*i).first), Value((*i).second));
                else
                    sceneBoundary->setValue(QString((*i).first), Value(expressions[(*i).first]));
                break;
            }
        }

        if (!assigned)
            throw invalid_argument(QObject::tr("Wrong parameter '%1'.").arg(QString((*i).first)).toStdString());
    }
}

void PyField::removeBoundary(char *name)
{
    Agros2D::scene()->removeBoundary(Agros2D::scene()->getBoundary(m_fieldInfo, QString(name)));
}

void PyField::addMaterial(char *name, map<char*, double> parameters,
                          map<char*, char* > expressions,
                          map<char*, vector<double> > nonlin_x,
                          map<char*, vector<double> > nonlin_y)
{
    // check materials with same name
    foreach (SceneMaterial *material, Agros2D::scene()->materials->filter(m_fieldInfo->fieldId()).items())
    {
        if (material->name() == name)
            throw invalid_argument(QObject::tr("Material '%1' already exists.").arg(QString(name)).toStdString());
    }

    // browse material parameters
    QHash<QString, Value> values;
    for (std::map<char*, double>::iterator i = parameters.begin(); i != parameters.end(); ++i)
    {
        QList<Module::MaterialTypeVariable> materials = m_fieldInfo->materialTypeVariables();

        bool assigned = false;
        foreach (Module::MaterialTypeVariable variable, materials)
        {
            if (variable.id() == QString((*i).first))
            {
                int lenx = ((nonlin_x.find((*i).first) != nonlin_x.end()) ? nonlin_x[(*i).first].size() : 0);
                int leny = ((nonlin_y.find((*i).first) != nonlin_y.end()) ? nonlin_y[(*i).first].size() : 0);
                if (lenx != leny)
                    if (lenx > leny)
                        throw invalid_argument(QObject::tr("Size doesn't match (%1 > %2).").arg(lenx).arg(leny).toStdString());
                    else
                        throw invalid_argument(QObject::tr("Size doesn't match (%1 < %2).").arg(lenx).arg(leny).toStdString());

                assigned = true;
                if (expressions.count((*i).first) == 0)
                    values[variable.id()] = Value((*i).second,
                                                  (lenx > 0) ? nonlin_x[(*i).first] : vector<double>(),
                                                  (leny > 0) ? nonlin_y[(*i).first] : vector<double>());
                else
                    values[variable.id()] = Value(expressions[(*i).first],
                            (lenx > 0) ? nonlin_x[(*i).first] : vector<double>(),
                        (leny > 0) ? nonlin_y[(*i).first] : vector<double>());
                break;
            }
        }

        if (!assigned)
            throw invalid_argument(QObject::tr("Wrong parameter '%1'.").arg(QString((*i).first)).toStdString());
    }

    Agros2D::scene()->addMaterial(new SceneMaterial(m_fieldInfo, QString(name), values));
}

void PyField::modifyMaterial(char *name, map<char*, double> parameters,
                          map<char*, char* > expressions,
                          map<char*, vector<double> > nonlin_x,
                          map<char*, vector<double> > nonlin_y)
{
    SceneMaterial *sceneMaterial = Agros2D::scene()->getMaterial(m_fieldInfo, QString(name));

    if (sceneMaterial == NULL)
        throw invalid_argument(QObject::tr("Material '%1' doesn't exists.").arg(name).toStdString());

    for( map<char*, double>::iterator i=parameters.begin(); i!=parameters.end(); ++i)
    {
        QList<Module::MaterialTypeVariable> materialVariables = m_fieldInfo->materialTypeVariables();

        bool assigned = false;
        foreach (Module::MaterialTypeVariable variable, materialVariables)
        {
            if (variable.id() == QString((*i).first))
            {
                int lenx = ((nonlin_x.find((*i).first) != nonlin_x.end()) ? nonlin_x[(*i).first].size() : 0);
                int leny = ((nonlin_y.find((*i).first) != nonlin_y.end()) ? nonlin_y[(*i).first].size() : 0);
                if (lenx != leny)
                    if (lenx > leny)
                        throw invalid_argument(QObject::tr("Size doesn't match (%1 > %2).").arg(lenx).arg(leny).toStdString());
                    else
                        throw invalid_argument(QObject::tr("Size doesn't match (%1 < %2).").arg(lenx).arg(leny).toStdString());

                assigned = true;
                if (expressions.count((*i).first) == 0)
                    sceneMaterial->setValue(QString((*i).first), Value((*i).second,
                                                                       (lenx > 0) ? nonlin_x[(*i).first] : vector<double>(),
                                                                       (leny > 0) ? nonlin_y[(*i).first] : vector<double>()));
                else
                    sceneMaterial->setValue(QString((*i).first), Value(expressions[(*i).first],
                                            (lenx > 0) ? nonlin_x[(*i).first] : vector<double>(),
                                            (leny > 0) ? nonlin_y[(*i).first] : vector<double>()));
                break;
            }
        }

        if (!assigned)
            throw invalid_argument(QObject::tr("Wrong parameter '%1'.").arg(QString((*i).first)).toStdString());
    }
}

void PyField::removeMaterial(char *name)
{
    Agros2D::scene()->removeMaterial(Agros2D::scene()->getMaterial(m_fieldInfo, QString(name)));
}

void PyField::localValues(const double x, const double y, int timeStep, int adaptivityStep,
                          const char *solutionType, map<std::string, double> &results)
{
    map<std::string, double> values;

    if (Agros2D::problem()->isSolved())
    {
        // set mode
        if (!silentMode())
        {
            currentPythonEngineAgros()->sceneViewPost2D()->actSceneModePost2D->trigger();
            currentPythonEngineAgros()->sceneViewPost2D()->actPostprocessorModeNothing->trigger();
        }

        Point point(x, y);

        if (!solutionTypeStringKeys().contains(QString(solutionType)))
            throw invalid_argument(QObject::tr("Invalid argument. Valid keys: %1").arg(stringListToString(solutionTypeStringKeys())).toStdString());

        SolutionMode solutionMode = solutionTypeFromStringKey(QString(solutionType));

        // FIXME: (Franta) solutionMode have to be tested, but not here
        // FIXME: (Franta) finer solution is nor supported yet
        if (solutionMode != SolutionMode_Normal && m_fieldInfo->adaptivityType() == AdaptivityType_None)
            throw logic_error(QObject::tr("Reference solution doesn't exist.").toStdString());

        if (timeStep == -1)
            timeStep = Agros2D::solutionStore()->lastTimeStep(m_fieldInfo, solutionMode);
        else if (timeStep < 0 || timeStep > Agros2D::problem()->numTimeLevels() - 1)
            throw out_of_range(QObject::tr("Time step is out of range (0 - %1).").arg(Agros2D::problem()->numTimeLevels()-1).toStdString());

        if (adaptivityStep == -1)
            adaptivityStep = Agros2D::solutionStore()->lastAdaptiveStep(m_fieldInfo, solutionMode, timeStep);
        else if (adaptivityStep < 0 || adaptivityStep > m_fieldInfo->adaptivitySteps()-1)
                throw out_of_range(QObject::tr("Adaptivity step is out of range. (0 to %2).").arg(m_fieldInfo->adaptivitySteps()-1).toStdString());

        LocalValue *value = m_fieldInfo->plugin()->localValue(m_fieldInfo, timeStep, adaptivityStep, solutionMode, point);
        QMapIterator<QString, PointValue> it(value->values());
        while (it.hasNext())
        {
            it.next();

            Module::LocalVariable variable = m_fieldInfo->localVariable(it.key());

            if (variable.isScalar())
            {
                values[variable.shortname().toStdString()] = it.value().scalar;
            }
            else
            {
                values[variable.shortname().toStdString()] = it.value().vector.magnitude();
                values[variable.shortname().toStdString() + Agros2D::problem()->config()->labelX().toLower().toStdString()] = it.value().vector.x;
                values[variable.shortname().toStdString() + Agros2D::problem()->config()->labelY().toLower().toStdString()] = it.value().vector.y;
            }
        }
        delete value;
    }
    else
    {
        throw logic_error(QObject::tr("Problem is not solved.").toStdString());
    }

    results = values;
}

void PyField::surfaceIntegrals(vector<int> edges, int timeStep, int adaptivityStep,
                               const char *solutionType, map<std::string, double> &results)
{
    map<std::string, double> values;

    if (Agros2D::problem()->isSolved())
    {
        // set mode
        if (!silentMode())
        {
            currentPythonEngineAgros()->sceneViewPost2D()->actSceneModePost2D->trigger();
            currentPythonEngineAgros()->sceneViewPost2D()->actPostprocessorModeSurfaceIntegral->trigger();
        }
        Agros2D::scene()->selectNone();

        if (!edges.empty())
        {
            for (vector<int>::iterator it = edges.begin(); it != edges.end(); ++it)
            {
                if ((*it >= 0) && (*it < Agros2D::scene()->edges->length()))
                {
                    Agros2D::scene()->edges->at(*it)->setSelected(true);
                }
                else
                {
                    throw out_of_range(QObject::tr("Edge index must be between 0 and '%1'.").arg(Agros2D::scene()->edges->length()-1).toStdString());
                    results = values;
                    return;
                }
            }

            if (!silentMode())
                currentPythonEngineAgros()->sceneViewPost2D()->updateGL();
        }
        else
        {
            Agros2D::scene()->selectAll(SceneGeometryMode_OperateOnEdges);
        }

        if (!solutionTypeStringKeys().contains(QString(solutionType)))
            throw invalid_argument(QObject::tr("Invalid argument. Valid keys: %1").arg(stringListToString(solutionTypeStringKeys())).toStdString());

        SolutionMode solutionMode = solutionTypeFromStringKey(QString(solutionType));

        // FIXME: (Franta) solutionMode have to be tested, but not here
        // FIXME: (Franta) finer solution is nor supported yet
        if (solutionMode != SolutionMode_Normal && m_fieldInfo->adaptivityType() == AdaptivityType_None)
            throw logic_error(QObject::tr("Reference solution doesn't exist.").toStdString());

        if (timeStep == -1)
            timeStep = Agros2D::solutionStore()->lastTimeStep(m_fieldInfo, solutionMode);
        else if (timeStep < 0 || timeStep > Agros2D::problem()->numTimeLevels() - 1)
            throw out_of_range(QObject::tr("Time step is out of range (0 - %1).").arg(Agros2D::problem()->numTimeLevels()-1).toStdString());

        if (adaptivityStep == -1)
            adaptivityStep = Agros2D::solutionStore()->lastAdaptiveStep(m_fieldInfo, solutionMode, timeStep);
        else if (adaptivityStep < 0 || adaptivityStep > m_fieldInfo->adaptivitySteps()-1)
                throw out_of_range(QObject::tr("Adaptivity step is out of range. (0 to %2).").arg(m_fieldInfo->adaptivitySteps()-1).toStdString());

        IntegralValue *integral = m_fieldInfo->plugin()->surfaceIntegral(m_fieldInfo, timeStep, adaptivityStep, solutionMode);
        QMapIterator<QString, double> it(integral->values());
        while (it.hasNext())
        {
            it.next();

            Module::Integral integral = m_fieldInfo->surfaceIntegral(it.key());

            values[integral.shortname().toStdString()] = it.value();
        }
        delete integral;
    }
    else
    {
        throw logic_error(QObject::tr("Problem is not solved.").toStdString());
    }

    results = values;
}

void PyField::volumeIntegrals(vector<int> labels, int timeStep, int adaptivityStep,
                              const char *solutionType, map<std::string, double> &results)
{
    map<std::string, double> values;

    if (Agros2D::problem()->isSolved())
    {
        // set mode
        if (!silentMode())
        {
            currentPythonEngineAgros()->sceneViewPost2D()->actSceneModePost2D->trigger();
            currentPythonEngineAgros()->sceneViewPost2D()->actPostprocessorModeVolumeIntegral->trigger();
        }
        Agros2D::scene()->selectNone();

        if (!labels.empty())
        {
            for (vector<int>::iterator it = labels.begin(); it != labels.end(); ++it)
            {
                if ((*it >= 0) && (*it < Agros2D::scene()->labels->length()))
                {
                    if (Agros2D::scene()->labels->at(*it)->marker(m_fieldInfo) != Agros2D::scene()->materials->getNone(m_fieldInfo))
                    {
                        Agros2D::scene()->labels->at(*it)->setSelected(true);
                    }
                    else
                    {
                        throw out_of_range(QObject::tr("Label with index '%1' is 'none'.").arg(*it).toStdString());
                    }
                }
                else
                {
                    throw out_of_range(QObject::tr("Label index must be between 0 and '%1'.").arg(Agros2D::scene()->labels->length()-1).toStdString());
                    results = values;
                    return;
                }
            }

            if (!silentMode())
                currentPythonEngineAgros()->sceneViewPost2D()->updateGL();
        }
        else
        {
            Agros2D::scene()->selectAll(SceneGeometryMode_OperateOnLabels);
        }

        if (!solutionTypeStringKeys().contains(QString(solutionType)))
            throw invalid_argument(QObject::tr("Invalid argument. Valid keys: %1").arg(stringListToString(solutionTypeStringKeys())).toStdString());

        SolutionMode solutionMode = solutionTypeFromStringKey(QString(solutionType));

        // FIXME: (Franta) solutionMode have to be tested, but not here
        // FIXME: (Franta) finer solution is nor supported yet
        if (solutionMode != SolutionMode_Normal && m_fieldInfo->adaptivityType() == AdaptivityType_None)
            throw logic_error(QObject::tr("Reference solution doesn't exist.").toStdString());

        if (timeStep == -1)
            timeStep = Agros2D::solutionStore()->lastTimeStep(m_fieldInfo, solutionMode);
        else if (timeStep < 0 || timeStep > Agros2D::problem()->numTimeLevels() - 1)
            throw out_of_range(QObject::tr("Time step is out of range (0 - %1).").arg(Agros2D::problem()->numTimeLevels()-1).toStdString());

        if (adaptivityStep == -1)
            adaptivityStep = Agros2D::solutionStore()->lastAdaptiveStep(m_fieldInfo, solutionMode, timeStep);
        else if (adaptivityStep < 0 || adaptivityStep > m_fieldInfo->adaptivitySteps()-1)
                throw out_of_range(QObject::tr("Adaptivity step is out of range. (0 to %1).").arg(m_fieldInfo->adaptivitySteps()-1).toStdString());

        IntegralValue *integral = m_fieldInfo->plugin()->volumeIntegral(m_fieldInfo, timeStep, adaptivityStep, solutionMode);
        QMapIterator<QString, double> it(integral->values());
        while (it.hasNext())
        {
            it.next();

            Module::Integral integral = m_fieldInfo->volumeIntegral(it.key());

            values[integral.shortname().toStdString()] = it.value();

        }
        delete integral;
    }
    else
    {
        throw logic_error(QObject::tr("Problem is not solved.").toStdString());
    }

    results = values;
}

void PyField::initialMeshParameters(map<std::string, int> &parameters)
{
    if (!Agros2D::problem()->isMeshed())
        throw logic_error(QObject::tr("Problem is not meshed.").toStdString());

    parameters["nodes"] = m_fieldInfo->initialMesh()->get_num_vertex_nodes();
    parameters["elements"] = m_fieldInfo->initialMesh()->get_num_active_elements();

    if (Agros2D::problem()->isSolved())
    {
        int timeStep = Agros2D::solutionStore()->lastTimeStep(m_fieldInfo, SolutionMode_Normal);
        MultiArray<double> msa = Agros2D::solutionStore()->multiArray(FieldSolutionID(m_fieldInfo, timeStep, 0, SolutionMode_Normal));

        parameters["dofs"] = Hermes::Hermes2D::Space<double>::get_num_dofs(msa.spaces());
    }
}

void PyField::solutionMeshParameters(map<std::string, int> &parameters)
{
    if (!Agros2D::problem()->isSolved())
        throw logic_error(QObject::tr("Problem is not solved.").toStdString());

    if (m_fieldInfo->adaptivityType() != AdaptivityType_None)
    {
        int timeStep = Agros2D::solutionStore()->lastTimeStep(m_fieldInfo, SolutionMode_Normal);
        int adaptiveStep = Agros2D::solutionStore()->lastAdaptiveStep(m_fieldInfo, SolutionMode_Normal);
        MultiArray<double> msa = Agros2D::solutionStore()->multiArray(FieldSolutionID(m_fieldInfo, timeStep, adaptiveStep, SolutionMode_Normal));

        parameters["nodes"] = msa.solutions().at(0)->get_mesh()->get_num_vertex_nodes();
        parameters["elements"] = msa.solutions().at(0)->get_mesh()->get_num_active_elements();
        parameters["dofs"] = Hermes::Hermes2D::Space<double>::get_num_dofs(msa.spaces());
    }
    else
        initialMeshParameters(parameters);
}

void PyField::adaptivityInfo(vector<double> &error, vector<int> &dofs)
{
    if (!Agros2D::problem()->isSolved())
        throw logic_error(QObject::tr("Problem is not solved.").toStdString());

    if (m_fieldInfo->adaptivityType() != AdaptivityType_None)
    {
        int timeStep = Agros2D::solutionStore()->timeLevels(m_fieldInfo).count() - 1;
        int adaptiveSteps = Agros2D::solutionStore()->lastAdaptiveStep(m_fieldInfo, SolutionMode_Normal) + 1;

        for (int i = 0; i < adaptiveSteps; i++)
        {
            SolutionStore::SolutionRunTimeDetails runTime = Agros2D::solutionStore()->multiSolutionRunTimeDetail(FieldSolutionID(m_fieldInfo, timeStep, i, SolutionMode_Normal)); // TODO: (Franta) wrapper
            error.push_back(runTime.adaptivity_error);
            dofs.push_back(runTime.DOFs);
        }
    }
    else
        throw logic_error(QObject::tr("Solution is not adaptive.").toStdString());
}