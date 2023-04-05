#pragma once
class Arm
{
private:
	double range{};
public:
	Arm();
	bool if_reachable(double, double, double) const;
	double get_range() const;
	void set_range(double);
};
