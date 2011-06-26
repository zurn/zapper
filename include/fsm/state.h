#ifndef STATE_H
#define STATE_H

#ifndef NULL
	#define NULL 0
#endif

class state
{
	public:
		state();
		virtual ~state();
		virtual void enter()=0;
		virtual void exit()=0;
		virtual void update()=0;
		virtual void draw()=0;
		virtual void pause()=0;
		virtual void unpause()=0;
};

#endif /* STATE_H */

