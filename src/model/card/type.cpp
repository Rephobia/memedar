#include "memedar/model/card/type.hpp"
#include "memedar/model/card/visitor.hpp"


using namespace md::model::card;

void noob_t::accept(visitor& v)
{
	v.visit(*this);
}


void ready_t::accept(visitor& v)
{
	v.visit(*this);
}


void delayed_t::accept(visitor& v)
{
	v.visit(*this);
}
