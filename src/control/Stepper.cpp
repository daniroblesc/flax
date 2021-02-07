#include "Stepper.h"
#include <iostream>


namespace control
{

Stepper::Stepper()
{
    outputs_.reserve(NUM_STEPS);
}

Stepper::~Stepper()
{}

void Stepper::update(bool clk)
{
    clockIn_.update(clk);
	reset_.update(outputs_[6].output());    

	step();

	// reset_ is instant so should do it immediately
	if (outputs_[6].output()) 
    {
		reset_.update(outputs_[6].output());
		step();
	}    
}

void Stepper::step()
{
    clockInNotGate_.update(clockIn_.output());
	resetNotGate_.update(reset_.output());

	inputOrGates_[0].update(reset_.output(), clockInNotGate_.output());
	inputOrGates_[1].update(reset_.output(), clockIn_.output());

	bits_[0].update(resetNotGate_.output(), inputOrGates_[0].output());
	bits_[1].update(bits_[0].output(), inputOrGates_[1].output());
	outputNotGates_[0].update(bits_[1].output());
	outputOrGate_.update(outputNotGates_[0].output(), reset_.output());

	bits_[2].update(bits_[1].output(), inputOrGates_[0].output());
	bits_[3].update(bits_[2].output(), inputOrGates_[1].output());
	outputNotGates_[1].update(bits_[3].output());
	outputAndGates_[0].update(outputNotGates_[1].output(), bits_[1].output());

	bits_[4].update(bits_[3].output(), inputOrGates_[0].output());
	bits_[5].update(bits_[4].output(), inputOrGates_[1].output());
	outputNotGates_[2].update(bits_[5].output());
	outputAndGates_[1].update(outputNotGates_[2].output(), bits_[3].output());

	bits_[6].update(bits_[5].output(), inputOrGates_[0].output());
	bits_[7].update(bits_[6].output(), inputOrGates_[1].output());
	outputNotGates_[3].update(bits_[7].output());
	outputAndGates_[2].update(outputNotGates_[3].output(), bits_[5].output());

	bits_[8].update(bits_[7].output(), inputOrGates_[0].output());
	bits_[9].update(bits_[8].output(), inputOrGates_[1].output());
	outputNotGates_[4].update(bits_[9].output());
	outputAndGates_[3].update(outputNotGates_[4].output(), bits_[7].output());

	bits_[10].update(bits_[9].output(), inputOrGates_[0].output());
	bits_[11].update(bits_[10].output(), inputOrGates_[1].output());
	outputNotGates_[5].update(bits_[11].output());
	outputAndGates_[4].update(outputNotGates_[5].output(), bits_[9].output());

	outputs_[0].update(outputOrGate_.output());
	outputs_[1].update(outputAndGates_[0].output());
	outputs_[2].update(outputAndGates_[1].output());
	outputs_[3].update(outputAndGates_[2].output());
	outputs_[4].update(outputAndGates_[3].output());
	outputs_[5].update(outputAndGates_[4].output());
	outputs_[6].update(bits_[11].output());    
}

bool Stepper::output(int index)
{
	return outputs_[index].output();
}

std::string Stepper::toString()
{
	std::string result;

	for (size_t i = 0; i < NUM_STEPS; ++i)
    {
		if (outputs_[i].output())
        {
			result.append("* ");
		} 
        else 
        {
			result.append("- ");
		}
	}

	return result;
}

}
