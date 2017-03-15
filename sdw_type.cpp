#include "sdw_type.h"

n64 Align(n64 a_nData, n64 a_nAlignment)
{
	return (a_nData + a_nAlignment - 1) / a_nAlignment * a_nAlignment;
}
