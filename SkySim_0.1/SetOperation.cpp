#include "SetOperation.h"

#include "SetFunction.h"

SetOperation::SetOperation()
{
	_bridgefunction = new BridgeFunction;
	_bridgefunction->SetParent(this);
	SetFunction* BF0 = new SetFunction;
	_bridgefunction->AddBridge(BF0);
}

SetOperation::SetOperation(string name)
{
}


SetOperation::~SetOperation()
{
}

void SetOperation::TempConnectQ(RealVariable * theX, RealVariable * theY)
{
	StackObject* SO;
	SetFunction* SF;
	SO = _bridgefunction->GetStackObject(0);
	SF = dynamic_cast<SetFunction*>(SO);

	SF->SetX(theX);
	SF->SetY(theY);

}

void SetOperation::SpecifyVariable(RealVariableType vartype, double value)
{

	StackObject* SO;
	SetFunction* SF;
	SO = _bridgefunction->GetStackObject(0);
	SF = dynamic_cast<SetFunction*>(SO);


	switch (vartype)
	{
	case SET_OFFSET:
		_offset->SetValue(value);
		break;
	case SET_MULTIPLIER:
		_multiplier->SetValue(value);
		break;
	}
}
