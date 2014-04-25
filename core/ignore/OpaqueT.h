/*
   Example files for explicit opaque templates
*/

#ifndef IGNORE_OPAQUET_H_
#define IGNORE_OPAQUET_H_

namespace NICE {
	template <class T> class OpaqueT {
		public:
			void CallMe(T arg);
	};
}

#endif
