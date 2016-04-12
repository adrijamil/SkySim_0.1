#include "stdafx.h"
#include "Compressor.h"
#include "ComponentBalance.h"
#include "HeatBalance.h"
#include "IsentropicCompression.h"
#include "FlowBalance.h"

Compressor::Compressor()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	FlowBalance* BF0 = new FlowBalance;
	_bridgefunction->AddBridge(BF0);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);

	HeatBalance* BF2 = new HeatBalance;
	BF2->SetHeatInput(_energyinput);
	_bridgefunction->AddBridge(BF2);
	IsentropicCompression* BF3 = new IsentropicCompression;
	BF3->SetDeltaPressure(_deltapressure); //map unit op member variable to bridge function member variable
	BF3->SetEnergyInput(_energyinput);
	BF3->SetIsentropicEfficiency(_isentropicefficiency);
	_bridgefunction->AddBridge(BF3);
}

Compressor::Compressor(string name)
{
	_name = name;
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	FlowBalance* BF0 = new FlowBalance;
	_bridgefunction->AddBridge(BF0);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	BF2->SetHeatInput(_energyinput);
	_bridgefunction->AddBridge(BF2);
	IsentropicCompression* BF3 = new IsentropicCompression;
	BF3->SetDeltaPressure(_deltapressure); //this adds variable to bridge function
	BF3->SetEnergyInput(_energyinput);
	BF3->SetIsentropicEfficiency(_isentropicefficiency);
	_bridgefunction->AddBridge(BF3);
}


void Compressor::_setupconnection(ConnectionType InOrOut)
{
	//FlowBalance
	/*ComponentBalance
	HeatBalance
	IsentropicCompression*/

	if (InOrOut == INLET)
	{
		//for FlowBalance inlets
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[0]->MassFlow());
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[0]->MolarFlow());

		// for ComponentBalance inlets
		_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[0]->Composition());
		_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[0]->MolarFlow());

		//HeatBalance inlets
		_bridgefunction->GetStackObject(2)->AddVariable(_inletstreams[0]->MolarEnthalpy());
		_bridgefunction->GetStackObject(2)->AddVariable(_inletstreams[0]->MolarFlow());

		//IsentropicCompression
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->Pressure());
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->MassFlow());
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->MolarEnthalpy());
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->MolarEntropy());
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[0]->Temperature());
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
		_bridgefunction->GetStackObject(3)->AddVariable(_outletstreams[0]->MolarEnthalpy());
		_bridgefunction->GetStackObject(3)->AddVariable(_outletstreams[0]->MolarEntropy());
		_bridgefunction->GetStackObject(3)->AddVariable(_outletstreams[0]->Temperature());
	}



}




Compressor::~Compressor()
{
}

void Compressor::SpecifyVariable(RealVariableType vartype, double value)
{

		switch (vartype)
		{
		case DELTAPRESSURE:
			_deltapressure->SetValue(value);
			break;
		case ENERGYINPUT:
			_energyinput->SetValue(value);
			break;
		case ISENTROPICEFFICIENCY:
			_isentropicefficiency->SetValue(value);
			break;
		}
		
}


void Compressor::Output()
{
	cout << "\n";
	cout << _name << "\n";
	cout << "Delta Pressure  [kPa] " << _deltapressure->GetValue() << "\n";
	cout << "Energy Input[W] " << _energyinput->GetValue() << "\n";
	cout << "Isentropic Efficiency [frac]" << _isentropicefficiency->GetValue() << "\n";
}