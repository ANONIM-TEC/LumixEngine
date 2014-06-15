General Rules
--------------------------------------------

* any block of code should not be longer than one page (about 40 lines), except namespaces and classes

---

#### Macros
  1. use pragma once
    * it's shorter

  2. \#if \#ifdef blocks only a few lines long
    * readability 
	
	wrong:
```
	#ifdef _XBOX_ONE
		int size_limit = 10;
		// multiple
		//
		// lines
		#ifdef NESTED_IFDEF
		//
		// with 
		//
		#else
		// code
		//
		// and
		// 
		// stuff
		#endif
	#elif defined WIN32
		int size_limit = 50;
		// other
		//
		// multiple
		//
		// lines
		//
		// with 
		//
		// code
		//
		// and
		// 
		// stuff
	#endif
```	

	right:

```
	int size_limit;
	#ifdef _XBOX_ONE
		size_limit = 10;
	#elif defined WIN32
		size_limit = 50;
	#endif
```

2. sort includes, use following rules (most important to least):
  * precompiled first, if necessary
  * in .cpp, corresponding header is first	
  * first #include "", then #include <>
  * alphabetically
    - It can be immediately seen, if some header is included twice

3. no other macros allowed
 - instead use inline functions, constant variables, ...

---

#### Comments
  1. less is more 
    - code should be readable enough
	
	wrong:

```
	// if there is not enought space allocated, allocate more
	if(c > m_size)
	{
		T* new_data = new [c * 2 + 1];
		delete[] m_data;
		m_data = new_data
		m_count = c;
		m_size = c * 2 + 1;
	}
```

	right:

```
	bool is_enough_space = count > m_size;
	if(!is_enough_space)
	{
		reserve(count * 2 + 1);
	}
```

  2. comment to answer "why?", not "how?" or "what?"
    - I can see what some code is doing or how is it doing it, but not why

	wrong:

```
	// bresenham line reasterization is used
```

	right:

```
	{ // dont remove this, it limits the scope of mutex lock
		Lock lock(m_mutex);
		m_world->update(time_delta);
		m_ai->update(time_delta);
		...
	}
```

---

#### General formatting
	most of the stuff listed here is just a personal preference, but it should be formatted consistently across the source code
  1. use tabs to indent
  2. spaces after comma
  3. no space before / after parenthesis	
  4. spaces around operators
  5. two empty lines between functions definitions
  6. constructors:
```	
	DamageEvent::DamageEvent(int damage, Entity sender)
		: Event(DamageEvent::s_type)
		, m_damage(damage)
		, m_sender(sender)
	{
		...
	}
```

  7.	curly braces on seperate lines

	wrong:
```
	if(condition) {
		foo();
	}

	if(condition) foo();

	if(condition)
		foo();

	if(condition) {
		foo();
	} else {
		foo2();
	}
```

	right:


```
	if(condition)
	{
		foo();
	}

	if(condition)
	{
		foo();
	}
	else
	{
		foo2();
	}	
```

---

#### Namespaces
  1. everything in Lux namespace
  2. there can be subnamespaces in Lux, e.g. Lux::Math

---

#### Files
  1. *.cpp, *.h
  2. lower case, use underscore
	render_scene.h
	array.h
	math/plane.h
  3. project should mirror the disc structure
     - file math/plane.h should be in a filter "math" in Visual Studio

---
#### Variables
  1. local variables, including function arguments
```
	void foo(int size, char* data)
	{
		int longer_name = 10;
		for(int i = 0; i < size; ++i)
		{
			data[i] = longer_name;
		}
	}
```

  2. global variables g_ prefix
	Log* g_error_log;

  3. static member variables s_ prefix
	if(event.getType() == DamageEvent::s_type)
  4. member variables m_ prefix
	bool m_is_visible;
	int m_count;
  5. constants upper case
	static const int MAX_COUNT = 256; 
	static const char* EVENT_NAME = "Damage";

---

#### Functions
  1. camel case - The first letter of an identifier is lowercase and the first letter of each subsequent concatenated 	word is capitalized
```
	int getSize();
	void reset();
	int getUID();
	const char* getIPAddress();
```

  2. do not use default function argument values

	wrong:
	
```
		void foo(int a, int b = 0)
		foo(4);
```

	right:
	
```
		void foo(int a, int b)
		foo(4, 0);
```	
	
	- if foo is refactored to have only b argument, the wrong case would compile
  3. do not use bool as function argument, except when it's the only argument
	wrong:

```
		void foo(const char* name, bool compressed);
		foo("human", true);
		foo2(true, true, false, true);
```

	right:

```
		void foo(const char* name, Compression compressed);
		foo("human", Compression::ENABLED);
		someObj->setCompression(true);
```

    - readability

---

#### Classes
  1. use forward declaration instead of include when possible
	- improves compile time
  2. order: public, protected, private
	- public interface is accessed most of the time, therefore it should be first
  3. order: types, methods, member variables
	- just to be consistent
  4. do not use structs, use classes with public members
	- forward declaration can mismatch
  5. consider using composition over inheritance
	- inheritance is quite often used wrong
  6. never use multiple inheritance, except if all base classes but one are abstract

---

#### Templates
  1. no template metaprogramming
	- can be hard to read
	- quite offten it abuses templates to do things, they are not supposed to do

  2. limit usage to the simplest cases, e.g. containers
	- most compilers produce unreadable, long error messages 
	- higher compile time

---

#### C++11
  1. C++11 features are allowed
	- as long as it's supported on all platforms

  2. override keyword is mandatory
	- can easily detect some easy to overlook issues

  3. do use 
	* enum class
		- does not pollute the global namespace
	* constexpr
		- can improve performance
	* static_assert
		- can detect some issues

  4. do not use
	* auto keyword
		- hides the type of a variable

---

#### Multiplatform
  1. 64bit friendly
  2. do not use long, long long, short, ...
	- they are platform dependent
  3. DWORD and such can be used only in pure platform specific files
	- there is no way to avoid this
  4. use int32_t, uint32_t
	- they are guaranteed to have exact size 
  5. size_t only in allocators and file systems
	- do you really need an array with more than MAX_INT items? If so, implement a special array with 64bit 
	indices
  6. use platform ifdefs only if they are very short, otherwise use different files for different platforms
	see 1.2.

---

#### Forbidden features
  1. RTTI, exceptions
	- performace

---

#### Others
  1. Asserts should not be triggered by data
  2. Data can not cause crash 
