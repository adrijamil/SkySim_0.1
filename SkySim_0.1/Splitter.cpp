
#include "stdafx.h"
#include "Splitter.h"
#include "ComponentBalance.h"
#include "HeatBalance.h"
#include "PressureBalance.h"
#include "FlowBalance.h"

Splitter::Splitter()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	FlowBalance* BF0 = new FlowBalance;
	_bridgefunction->AddBridge(BF0);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	_bridgefunction->AddBridge(BF2);
	PressureBalance* BF3 = new PressureBalance;
	_bridgefunction->AddBridge(BF3);
}


Splitter::Splitter(string name)
{
	_name = name;

	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	FlowBalance* BF0 = new FlowBalance;
	_bridgefunction->AddBridge(BF0);
	ComponentBalance* BF1 = new ComponentBalance;
	_bridgefunction->AddBridge(BF1);
	HeatBalance* BF2 = new HeatBalance;
	_bridgefunction->AddBridge(BF2);
	PressureBalance* BF3 = new PressureBalance;
	_bridgefunction->AddBridge(BF3);
}



void Splitter::_setupconnection(ConnectionType InOrOut)
{
	//MaterialBalance
	/*ComponentBalance
	HeatBalance
	SimpleResistanceEquation*/
	int i = -1;
	if (InOrOut == INLET)
	{
		i = _ninlets - 1;
		//for MaterialBalance inlets
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[i]->MassFlow());
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[i]->MolarFlow());

		// for ComponentBalance inlets
		_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[i]->Composition());
		_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[i]->MolarFlow());

		//HeatBalance inlets
		_bridgefunction->GetStackObject(2)->AddVariable(_inletstreams[i]->MolarEnthalpy());
		_bridgefunction->GetStackObject(2)->AddVariable(_inletstreams[0]->MolarFlow());

		//Pressure balance
		_bridgefunction->GetStackObject(3)->AddVariable(_inletstreams[i]->Pressure());
	}
	else
	{
		//_addoutlet();
		i = _noutlets - 1;
		//for MaterialBalance outlets
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[i]->MassFlow());
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[i]->MolarFlow());

		_bridgefunction->GetStackObject(1)->AddVariable(_outletstreams[i]->Composition());
		_bridgefunction->GetStackObject(1)->AddVariable(_outletstreams[i]->MolarFlow());

		_bridgefunction->GetStackObject(2)->AddVariable(_outletstreams[i]->MolarEnthalpy());
		_bridgefunction->GetStackObject(2)->AddVariable(_outletstreams[i]->MolarFlow());

		_bridgefunction->GetStackObject(3)->AddVariable(_outletstreams[i]->Pressure());
	}



}

//void Splitter::_addoutlet()
//{
//	int i = _noutlets - 1;
//	if (_noutlets > 1)
//	{
//		_bridgefunction->GetStackObject(0)->s
//	}
//	_bridgefunction->GetStackObject(0)->AddVariable(_splitfractions[i]);
//}


Splitter::~Splitter()
{
}