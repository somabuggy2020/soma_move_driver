#pragma once

namespace RotaryInfo
{
	struct Data_t
	{
		long pulse[2];
		double v;
		double d[2];
		double T;

		Data_t() : pulse(), v(0.0), d(), T(0.0) {}
	};

	struct Recv_t
	{
		long pulse;
		double velo;

		Recv_t():pulse(0), velo(0.0){}
	};
}

