#include "stdafx.h"
#include "TwoPhaseSeparator.h"
#include "TwoPhaseSeparation.h"
#include "PressureBalance.h"
#include "FlowBalance.h"

TwoPhaseSeparator::TwoPhaseSeparator()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	TwoPhaseSeparation* BF0 = new TwoPhaseSeparation;
	_bridgefunction->AddBridge(BF0);
	//FlowBalance* BF1 = new FlowBalance;
	//_bridgefunction->AddBridge(BF1);
	PressureBalance* BF2 = new PressureBalance;
	_bridgefunction->AddBridge(BF2);
}

TwoPhaseSeparator::TwoPhaseSeparator(std::string name)
{
	_name = name;
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	TwoPhaseSeparation* BF0 = new TwoPhaseSeparation;
	_bridgefunction->AddBridge(BF0);
	//FlowBalance* BF1 = new FlowBalance;
	//->AddBridge(BF1);
	PressureBalance* BF2 = new PressureBalance;
	_bridgefunction->AddBridge(BF2);
}


TwoPhaseSeparator::~TwoPhaseSeparator()
{
}

//void TwoPhaseSeparator::SpecifyVariable(RealVariableType vartype, double value)
//{
//}
//
//void TwoPhaseSeparator::Output()
//{
//}
//
void TwoPhaseSeparator::_setupconnection(ConnectionType InOrOut)
{

		//when connecting outlets, set vfrac to 1, 0 accordingly
		
	//bridges - pressure balance

	if (InOrOut == INLET)
	{
		//for separation inlets
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[0]->Composition());
		_bridgefunction->GetStackObject(0)->AddVariable(_inletstreams[0]->MolarEnthalpy());

		// for flow balance inlets
		//_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[0]->MassFlow());
		//_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[0]->MolarFlow());

		//pressure balance inlets
		_bridgefunction->GetStackObject(1)->AddVariable(_inletstreams[0]->Pressure());


		
	}
	else if (InOrOut == VAPOUROUTLET)
	{
		//spec the vfrac
		_outletstreams[0]->VapourFraction()->IsCalculated(false);
		_outletstreams[0]->VapourFraction()->SetValue(1);

		//for separation outlets
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[0]->VapourFraction());
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[0]->Composition());
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[0]->MolarFlow());


		//pressure balance outlets
		_bridgefunction->GetStackObject(1)->AddVariable(_outletstreams[0]->Pressure());
	}
	else if (InOrOut == LIQUIDOUTLET)
	{
		//spec the vfrac
		_outletstreams[1]->VapourFraction()->IsCalculated(false);
		_outletstreams[1]->VapourFraction()->SetValue(0);

		//for separation outlets
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[1]->VapourFraction());
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[1]->Composition());
		_bridgefunction->GetStackObject(0)->AddVariable(_outletstreams[1]->MolarFlow());

		//pressure balance outlets
		_bridgefunction->GetStackObject(1)->AddVariable(_outletstreams[1]->Pressure());
	}
}
