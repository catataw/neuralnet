#define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))
#define PPCAT_NX(A, B) A ## B
#define PPCAT(A, B) PPCAT_NX(A, B)

#ifdef _BOX_NAMESPACE_NAME 
#undef _BOX_NAMESPACE_NAME
#endif

#ifdef Prop 
#undef Prop
#endif

#define _BOX_NAMESPACE_NAME PPCAT(_, _BOX_CLASS_NAME)
#define PROP _BOX_NAMESPACE_NAME::Prop

namespace _BOX_NAMESPACE_NAME {
	template<typename T>
	/**
	* Boxing class for creating properties
	*/
	class Prop {
	public:
		Prop() {}

		/**
		* Getter
		*/
		T const operator()() const {
			return CALL_MEMBER_FN(_getObj, _getter)();
		}

		/**
		* Setter
		*/
		void operator()(T const value) {
			CALL_MEMBER_FN(_setObj, _setter)(value);
		}

		/**
		* Sets the internal setter method
		*/
		void set(void(_BOX_CLASS_NAME::*setter)(T const), _BOX_CLASS_NAME *object) {
			this->_setter = setter;
			this->_setObj = object;
		}

		/**
		* Sets the internal getter method
		*/
		void get(T const (_BOX_CLASS_NAME::*getter)(), _BOX_CLASS_NAME *object) {
			this->_getter = getter;
			this->_getObj = object;
		}

	private:
		void(_BOX_CLASS_NAME::*_setter)(T const);
		T const (_BOX_CLASS_NAME::*_getter)();
		_BOX_CLASS_NAME *_getObj;
		_BOX_CLASS_NAME *_setObj;
	};
}