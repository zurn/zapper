
#ifndef __TIP_H__
#define __TIP_H__

#include "gfx.h"
#include "matho.h"
#include "object.h"
#include "counter.h"
#include "emitter.h"

class tip: public object
{
	public:
		tip(Vector pos);
		virtual ~tip();

		void update();
		void draw();

		image * pic;
		emitter * poof;

		bool skip;
		counter delay;
	private:

};
#endif /* __TIP_H__ */
