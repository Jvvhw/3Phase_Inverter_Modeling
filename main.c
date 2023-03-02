#include "DllHeader.h"
#include "variable.h"
#include "math.h"

void SignalGenerator() {			   
	Theta = 0;
	V_sin_A = 0;
	V_sin_B = 0;
	V_sin_C = 0;
}

void InitController() {			   
	
}

void InitINV() {			   
	
}

DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
	aSizes->numInputs = 22;
	aSizes->numOutputs = 100;
}


//This function is automatically called at the beginning of the simulation
DLLEXPORT void plecsStart(struct SimulationState* aState)
{

}


//This function is automatically called every sample time
//output is written to DLL output port after the output delay
DLLEXPORT void plecsOutput(struct SimulationState* aState)
{

	//INPUT
	Vdc = aState->inputs[0]; 
	Fre = aState->inputs[1]; //Sin wave frequency
	ma = aState->inputs[2]; // Voltage modulation ratio
	INV_on = aState->inputs[3]; 
	// x = aState->inputs[n];

	Tsamp = aState->inputs[21];  //Fixed Tsamp


	if (init == 0) {
		SignalGenerator();
		INV_Vdc = 1/Vdc;
		init = 1;
	}

	// V_sin output
	if (INV_on) {
		Theta += 2 * PI * Fre * Tsamp; // Discrete angle output for Sin wave which has Fre
		if (Theta > 2 * PI) { // 2PI BOUND
			Theta = 0;
		}
		V_sin_A = (Vdc*ma*0.5)*sin(Theta); //amplitude modified by modulation ratio
		V_sin_B = (Vdc * ma * 0.5) * sin(Theta-2*PIOF3); //120 phase delay
		V_sin_C = (Vdc * ma * 0.5) * sin(Theta-4*PIOF3); //240 phase delay
		
		//0~1 Duty output
		A_Signal = (V_sin_A + 0.5 * Vdc) * INV_Vdc; 
		B_Signal = (V_sin_B + 0.5 * Vdc) * INV_Vdc;
		C_Signal = (V_sin_C + 0.5 * Vdc) * INV_Vdc;

	}
	else {
		A_Signal = 0.5;
		B_Signal = 0.5;
		C_Signal = 0.5;
	}


		
	//OUTPUT
	aState->outputs[0] = A_Signal;
	aState->outputs[1] = B_Signal;
	aState->outputs[2] = C_Signal;

	aState->outputs[3] = V_sin_A;
	aState->outputs[4] = V_sin_B;
	aState->outputs[5] = V_sin_C;
	// aState->outputs[n] = x ;
	











	
}





