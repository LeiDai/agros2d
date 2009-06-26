#include "gui.h"

void fillComboBoxVariable(QComboBox *cmbFieldVariable, PhysicField physicField)
{
    // store variable
    PhysicFieldVariable physicFieldVariable = (PhysicFieldVariable) cmbFieldVariable->itemData(cmbFieldVariable->currentIndex()).toInt();

    // clear combo
    cmbFieldVariable->clear();

    switch (physicField)
    {
    case PHYSICFIELD_ELECTROSTATIC:
        {
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_ELECTROSTATIC_POTENTIAL), PHYSICFIELDVARIABLE_ELECTROSTATIC_POTENTIAL);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_ELECTROSTATIC_ELECTRICFIELD), PHYSICFIELDVARIABLE_ELECTROSTATIC_ELECTRICFIELD);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_ELECTROSTATIC_DISPLACEMENT), PHYSICFIELDVARIABLE_ELECTROSTATIC_DISPLACEMENT);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_ELECTROSTATIC_ENERGY_DENSITY), PHYSICFIELDVARIABLE_ELECTROSTATIC_ENERGY_DENSITY);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_ELECTROSTATIC_PERMITTIVITY), PHYSICFIELDVARIABLE_ELECTROSTATIC_PERMITTIVITY);
        }
        break;
    case PHYSICFIELD_MAGNETOSTATIC:
        {
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_MAGNETOSTATIC_VECTOR_POTENTIAL), PHYSICFIELDVARIABLE_MAGNETOSTATIC_VECTOR_POTENTIAL);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_MAGNETOSTATIC_FLUX_DENSITY), PHYSICFIELDVARIABLE_MAGNETOSTATIC_FLUX_DENSITY);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_MAGNETOSTATIC_MAGNETICFIELD), PHYSICFIELDVARIABLE_MAGNETOSTATIC_MAGNETICFIELD);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_MAGNETOSTATIC_ENERGY_DENSITY), PHYSICFIELDVARIABLE_MAGNETOSTATIC_ENERGY_DENSITY);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_MAGNETOSTATIC_PERMEABILITY), PHYSICFIELDVARIABLE_MAGNETOSTATIC_PERMEABILITY);
        }
        break;
    case PHYSICFIELD_HEAT_TRANSFER:
        {
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_HEAT_TEMPERATURE), PHYSICFIELDVARIABLE_HEAT_TEMPERATURE);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_HEAT_TEMPERATURE_GRADIENT), PHYSICFIELDVARIABLE_HEAT_TEMPERATURE_GRADIENT);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_HEAT_FLUX), PHYSICFIELDVARIABLE_HEAT_FLUX);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_HEAT_CONDUCTIVITY), PHYSICFIELDVARIABLE_HEAT_CONDUCTIVITY);
        }
        break;
    case PHYSICFIELD_CURRENT:
        {
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_CURRENT_POTENTIAL), PHYSICFIELDVARIABLE_CURRENT_POTENTIAL);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_CURRENT_ELECTRICFIELD), PHYSICFIELDVARIABLE_CURRENT_ELECTRICFIELD);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_CURRENT_CURRENT_DENSITY), PHYSICFIELDVARIABLE_CURRENT_CURRENT_DENSITY);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_CURRENT_LOSSES), PHYSICFIELDVARIABLE_CURRENT_LOSSES);
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_CURRENT_CONDUCTIVITY), PHYSICFIELDVARIABLE_CURRENT_CONDUCTIVITY);
        }
        break;
    case PHYSICFIELD_ELASTICITY:
        {
            cmbFieldVariable->addItem(physicFieldVariableString(PHYSICFIELDVARIABLE_ELASTICITY_VON_MISES_STRESS), PHYSICFIELDVARIABLE_ELASTICITY_VON_MISES_STRESS);
        }
        break;
    default:
        cerr << "Physical field '" + physicFieldStringKey(physicField).toStdString() + "' is not implemented. fillComboBoxVariable(QComboBox *cmbFieldVariable, PhysicField physicField)" << endl;
        throw;
        break;
    }

     cmbFieldVariable->setCurrentIndex(cmbFieldVariable->findData(physicFieldVariable));
     if (cmbFieldVariable->currentIndex() == -1)
         cmbFieldVariable->setCurrentIndex(0);
}

// ***********************************************************************************************************

SLineEdit::SLineEdit(QWidget *parent) : QLineEdit(parent)
{   
    SLineEdit::SLineEdit("", true, parent);
}

SLineEdit::SLineEdit(const QString &contents, bool hasValidator, QWidget *parent) : QLineEdit(contents, parent)
{
    if (hasValidator)
        this->setValidator(new QDoubleValidator(this));
}

double SLineEdit::value()
{
    QScriptEngine engine;

    QScriptValue scriptValue = engine.evaluate(text());
    if (scriptValue.isNumber())
        return scriptValue.toNumber();
}

double SLineEdit::value(const QString &script)
{
    QScriptEngine engine;

    // evaluate startup script
    if (!script.isEmpty())
        engine.evaluate(script);

    QScriptValue scriptValue = engine.evaluate(text());
    if (scriptValue.isNumber())
        return scriptValue.toNumber();
}

void SLineEdit::setValue(double value)
{
    setText(QString::number(value));
}

// ***********************************************************************************************************
