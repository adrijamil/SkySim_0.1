#include "stdafx.h"
#include "Valve.h"
#include "ComponentBalance.h"
#include "HeatBalance.h"
#include "SimpleResistanceEquation.h"
#include "FlowBalance.h"

Valve::Valve()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	FlowBalance* BF0 = new FlowBalance;
	_bridgefunction->AddBridge(BF0);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	_bridgefunction->AddBridge(BF2);
	SimpleResistanceEquation* BF3 = new SimpleResistanceEquation;
	BF3->SetResistance(_k_resistance);
	BF3->SetPressureDrop(_pressuredrop);
	_bridgefunction->AddBridge(BF3);	
}


Valve::Valve(string name)
{
	_name = name;
	_bridgefunction->SetParent(this);
	FlowBalance* BF0 = new FlowBalance;
	_bridgefunction->AddBridge(BF0);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	_bridgefunction->AddBridge(BF2);
	SimpleResistanceEquation* BF3 = new SimpleResistanceEquation;
	BF3->SetResistance(_k_resistance);
	BF3->SetPressureDrop(_pressuredrop);
	_bridgefunction->AddBridge(BF3);
}

Valve::~Valve()
{
}

void Valve::_setupconnection(ConnectionType InOrOut)
{
	//MaterialBalance
	/*ComponentBalance
	HeatBalance
	SimpleResistanceEquation*/
	
	if (InOrOut == INLET)
	{
		//for MaterialBalance inlets
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[0]->MassFlow());
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[0]->MolarFlow());

		// for ComponentBalance inlets
		_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[0]->Composition());
		_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[0]->MolarFlow());

		//HeatBalance inlets
		_bridgefunction->GetStackObject(2)->AddVariable(_inletstreams[0]->MolarEnthalpy());
		_bridgefunction->GetStackObject(2)->AddVariable(_inletstreams[0]->MolarFlow());
		
		//SimpleResistanceEquation
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->Pressure());
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->MassFlow());
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->MassDensity());
	}
	else
	{
		//for MaterialBalance outlets
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[0]->MassFlow());
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[0]->MolarFlow());

		_bridgefunction->GetStackObject(1)->AddVariable(_outletstreams[0]->Composition());
		_bridgefunction->GetStackObject(1)->AddVariable(_outletstreams[0]->MolarFlow());

		_bridgefunction->GetStackObject(2)->AddVariable(_outletstreams[0]->MolarEnthalpy());
		_bridgefunction->GetStackObject(2)->AddVariable(_outletstreams[0]->MolarFlow());

		_bridgefunction->GetStackObject(3)->AddVariable(_outletstreams[0]->Pressure());
	}

	

}


void Valve::Output()
{
	cout << "\n";
	cout << _name << "\n";
	cout << "K resistance  [kPa-kg/h] " << K_Resistance()->GetValue() << "\n";
	cout << "Pressure Drop  [kPa] " << PressureDrop()->GetValue() << "\n";
}

void Valve::SpecifyVariable(RealVariableType vartype, double value)
{
	switch (vartype)
	{
	case DELTAPRESSURE:
		_pressuredrop->SetValue(value);
		break;
	case K_RESISTANCE:
		_k_resistance->SetValue(value);
		break;
	}
}

