#ifndef DSP6713_INT_CODE_H
#define DSP6713_INT_CODE_H

extern u8 PulseBrake_flag;
extern u8 SpeedTime_flag;




extern void main_cycle(void);
extern void delay(int period);
extern void get_ABS_coordinate(void);
void interrupt4(void);

#endif  // end of definition

//===========================================================================
// No more.
//===========================================================================
