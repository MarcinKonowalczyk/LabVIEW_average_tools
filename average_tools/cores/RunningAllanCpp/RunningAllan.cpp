//#include <stdio.h>
//#include <list>
#include <stdint.h> /* int32_t */
//#include <vector>
#include <math.h> /* pow, sqrt */
//#include <algorithm> /* max_element */

#ifdef RUNNINGALLANDLL_EXPORTS
#define RUNNINGALLANDLL_API __declspec(dllexport)
#else
#define RUNNINGALLANDLL_API __declspec(dllimport)
#endif

extern "C"
{
	RUNNINGALLANDLL_API
		void RunningAllanInit(
		int32_t *lengths, const int32_t lengthsN,		// (in)  Lengths of Allan dev to process
		int32_t *histN,									// (out) Length of the history stored in proc
		int32_t *procN,									// (out) Lengths of the proc segments
		int32_t *procLength								// (out) Length of the proc array
		)
	{
		/*
		Written by Marcin Konowalczyk
		*/

		// Figure out maximum length of the segment to process (and therefore the required histiry length)
		int maxLength = 1;
		for (int i = 0; i < lengthsN; i++){
			if (lengths[i] > maxLength) {
				maxLength = lengths[i];
			}
		}
		*histN = maxLength * 2;

		// Calculate the length of each segment in proc
		*procLength = 0;
		for (int i = 0; i < lengthsN; i++){
			int newLen = *histN / lengths[i] + 1;
			procN[i] = newLen;
			*procLength += newLen;
		}
	}

	RUNNINGALLANDLL_API
		void RunningAllanMain(
		const double input,							// Input value
		int32_t *lengths, const int32_t lengthsN,			// Lengths of Allan dev to process
		int32_t *procL,									// Lengths of the currently processing sequence
		int32_t *procI,									// Indices to the currently processing values (array if ints)
		double *proc, const int32_t *procN,				// Processed values containers (arrays)
		double *allanDevsWIP, double *allanDevs		// Output arrays
		)
	{
		/*
		Written by Marcin Konowalczyk
		*/
		
		// Initalise stuff
		int segmentOffset = 0; // Offset of the beginning of the current segment in `proc`
		int pointerToCurrValue = 0; // Pointer to the current value in `proc[]` beeing processed

		// Loop through all the lengths
		for (int i = 0; i<lengthsN; i+=1)
		{
			// Calculate usefull stuff
			int segmentLength = lengths[i]; // The length of the current segment to process
			pointerToCurrValue = segmentOffset + procI[i]; // Pointer to the current value in current segment

			// Reset the current element if procL
			if (procL[i] == 0) {
				proc[pointerToCurrValue] = 0;
			}

			// Add the input to the proc array
			proc[pointerToCurrValue] += input;
			procL[i] += 1;
			int N = procN[i]; // Length of the current segment in proc
			
			
			// Finalise the processing if the currentValue and progress the procI 
			if (procL[i] == segmentLength) {
				
				procL[i] = 0; // Reset numberOfProcElements
				proc[pointerToCurrValue] /= segmentLength; // Divide by len to get the mean

				// Figure out a pointer to the previous value
				int pointerToPreviousValue;
				if (procI[i] == 0){
					pointerToPreviousValue = segmentOffset + N - 1; // Point to last value
				}
				else {
					pointerToPreviousValue = pointerToCurrValue - 1; // Point to previous value
				}
				
				// New difference to come into the buffer
				double newDifference = proc[pointerToPreviousValue] - proc[pointerToCurrValue];
				newDifference *= newDifference; // Square

				// Push the pointer to point at the next value - now thet tail
				(procI[i] += 1) %= N; // Push the pointer to the next value
				pointerToCurrValue = segmentOffset + procI[i];

				// Figure out a pointer to the value after the tail
				int pointerToNextValue;
				if (procI[i] == N - 1){
					pointerToNextValue = segmentOffset; // Point to first value
				}
				else {
					pointerToNextValue = pointerToCurrValue + 1; // Point to next value
				}

				// Old difference to leave the buffer
				double oldDifference = proc[pointerToCurrValue] - proc[pointerToNextValue];
				oldDifference *= oldDifference;

				// Propagate differences
				(allanDevsWIP[i] -= oldDifference) += newDifference;
				double currentAllanDev = allanDevsWIP[i];

				// Recalculate the mean deviation of the segments
				int quotient = (N - 2); // Quotient to divide allanDev by ( -1 for the swap space and -1 for the diff() function)
				currentAllanDev /= quotient; // Divide by quotient to get the mean
				currentAllanDev = sqrt(currentAllanDev); // Take square root 
				
				// Put into the output array
				allanDevs[i] = currentAllanDev;
			}
			
			// Offset in the `proc` to add to the next segment
			segmentOffset += N;
		}
	}
}