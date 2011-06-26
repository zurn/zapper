#ifndef SINGLE_H
#define SINGLE_H

#ifndef NULL
	#define NULL 0
#endif

/*
singleton pattern template
this template can make any class into a singleton.

You can access a singleton by declaring
foo * x = single<foo>::Instance();

You can destroy a singleton with
delete x; or 
delete single<foo>::Instance();
*/

//-------------------------------------------------------------------

template <class T>
class single {

	public:
		static T * Instance();
		//returns a pointer to T class
		//if instance has not been created it will be.
		//otherwise returns instance
	private:
		static T * instance;
		//the actual single instance of the T class
};

//-------------------------------------------------------------------

template<class T>
T * single<T>::instance = NULL;

//-------------------------------------------------------------------

template<class T>
T * single<T>::Instance() {

	if (instance == NULL) 
		instance = new T;

	return instance;
}

//-------------------------------------------------------------------

/*
A helper macro to clean up the code using this class.

You can access a singleton by declaring
foo * x = SINGLETON(foo);

You can destroy a singleton with
delete SINGLETON(foo);
*/

#define SINGLETON(X) (single<typeof(X)>::Instance())

//-------------------------------------------------------------------

#endif

