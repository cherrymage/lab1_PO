
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	Enable = 1;
	count = 0;
	Speed = 0;
	
	fb_motor.dt = 0.01;
	fb_motor.ke = 0.24;
	fb_motor.Tm = 0.1;
	fb_motor.u = 0;
	fb_motor.integrator.dt = 0.01;
	
	fb_motor2.dt = 0.01;
	fb_motor2.ke = 0.24;
	fb_motor2.Tm = 0.1;
	fb_motor2.u = 0;
	fb_motor2.integrator.dt = 0.01;
	
	fb_controller.dt = 0.01;
	fb_controller.integrator.dt = 0.01;
	fb_controller.k_i = 7.2*100;
	fb_controller.k_p = 0.24;
	fb_controller.max_abs_value = 24.0;
}

void _CYCLIC ProgramCyclic(void)
{
	if (Enable == 1)
	{
		count += 10;
		if (count >= 500 && count <= 1000) Speed = 40;
		else Speed = 5;
		if (count>1000) count = 0;
	}
	
	else Speed = 0;
	fb_controller.e = Speed - fb_motor.w;
	fb_motor2.u = Speed * fb_motor2.ke;
	fb_motor.u = fb_controller.u*fb_motor.ke;
	FB_Regulator(&fb_controller);
	FB_Motor(&fb_motor);
	FB_Motor(&fb_motor2);
		
}

void _EXIT ProgramExit(void)
{

}

