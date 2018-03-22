#include "stdafx.h"
#include "component.h"



component::~component()
{

}


void component::Simulation(void)
{
	if (m_up)
	{
		m_output = m_output + 1;

		for (int i = 0; i < 10; i++)
		{
			m_output_d[i] = m_output_d[i] + 1;
		}
	}

	else if (m_down)
	{
		m_output = m_output - 1;

		for (int i = 0; i < 10; i++)
		{
			m_output_d[i] = m_output_d[i] - 1;
		}
	}
}
