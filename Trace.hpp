#pragma once
#include "Living.hpp"
#include "Errors.hpp"
#include "funcs.hpp"

enum Trace_spec {
	Rabbit_spec,
	Fox_spec,
	undefined_spec
};


class Trace : public Living {
private:
	Trace_spec trace_spec = undefined_spec;
public:
	Trace() = default;
	Trace(int x, int y, Trace_spec trace_spec) : Living(x, y, Spec::trace, 2, 0), trace_spec(trace_spec) {}
	Trace_spec get_trace_spec() const { return trace_spec; }
	virtual void Behavior(Field& field) override;
	~Trace() {}
};

std::pair<int, int> Nearest_Trace(Field& field, int x, int y);