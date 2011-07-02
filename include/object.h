
#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "matho.h"

class object
{
	public:
		object();
		virtual ~object();


		Vector pos;
		bool dead;
		bool collidable;

	private:

};
#endif /* __OBJECT_H__ */
