#pragma once
class UnitConvertor
{
	static UnitConvertor *s_instance;
	int m_value;
	
	UnitConvertor(int v = 0)
	{
		m_value = v;
	}
public:
	
	int get_value()
	{
		return m_value;
	}
	void set_value(int v)
	{
		m_value = v;
	}
	static UnitConvertor *instance()
	{
		if (!s_instance)
			s_instance = new UnitConvertor;
		return s_instance;
	}
};